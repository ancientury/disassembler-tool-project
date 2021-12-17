#include <QSettings>
#include <QMessageBox>
#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* Show column headers for table widgets -> Designer bug */
    ui->tableWidgetPESections->horizontalHeader()->setVisible(true);
    ui->tableWidgetDisasm->horizontalHeader()->setVisible(true);

    /* QHexView widget */
    pwgt = new QHexView;
    ui->hexVLayout->addWidget(pwgt);

    /* Parser engine */
    disasm = new Parser();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete pwgt;
    delete disasm;

    if(pe != nullptr)
        delete pe;
}

void MainWindow::on_actionOpen_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this,
        tr("Open binary file"), QDir::homePath(), tr("EXE files (*.exe)"));

    if(!filePath.isEmpty() && !filePath.isNull()){

        delete pe;

        /* Portable executable loader */
        pe = new PortableExecutable(filePath);

        if (pe->fileInfo.exists() && pe->fileInfo.isExecutable()) {

            if(pe->Open()){

                /* Enable file unloading action */
                ui->actionUnload_file->setEnabled(true);

                /* Enable tabs when file is loaded */
                ui->hexTab->setEnabled(true);
                ui->disasmTab->setEnabled(true);

                /* Get PE details */
                ui->fileNameEdit->setText(pe->fileInfo.fileName());
                ui->fileSizeEdit->setText(QString::number(pe->fileInfo.size()) + " bytes");

                /* Disassembly default settings */
                ui->disasmSizeEdit->setText(QString("0x%1").arg(pe->fileBuffer.size() - pe->GetEntryPointOffset(), 8, 16, QChar('0')));
                ui->offsetEdit->setText(QString("0x%1").arg(pe->GetEntryPointOffset(), 8, 16, QChar('0')));

                /* Evaluate all sections */
                ui->tableWidgetPESections->setRowCount(pe->fileHeader.NumberOfSections);
                for (int i = 0; i < pe->fileHeader.NumberOfSections; i++) {
                    ui->tableWidgetPESections->setItem(i, 0, new QTableWidgetItem(QString((char *)pe->sectionHeaders[i].Name)));
                    ui->tableWidgetPESections->setItem(i, 1, new QTableWidgetItem("0x" + QString::number(pe->sectionHeaders[i].VirtualAddress, 16).toUpper()));
                    ui->tableWidgetPESections->setItem(i, 2, new QTableWidgetItem("0x" +QString::number(pe->sectionHeaders[i].VirtualSize, 16).toUpper()));
                    ui->tableWidgetPESections->setItem(i, 3, new QTableWidgetItem("0x" +QString::number(pe->sectionHeaders[i].PointerToRawData, 16).toUpper()));
                }

                /* Address of Entrypoint */
                ui->epEdit->setText(QString("0x%1").arg(pe->optionalHeader.AddressOfEntryPoint, 8, 16, QChar('0')));

                /* Entrypoint offset */
                ui->epOffsetEdit->setText(QString("0x%1").arg(pe->GetEntryPointOffset(), 8, 16, QChar('0')));

                /* Get entrypoint section */
                int EPSectionIndex = pe->GetEntrySectionIndex();
                ui->epSectionEdit->setText(QString((char*)pe->sectionHeaders[EPSectionIndex].Name));

                /* Get entry point first 5 bytes */
                unsigned char * EPFirstBytes = pe->GetEPFirstBytes();
                ui->firstBytesEdit->setText("0x" + QString(QByteArray((char*)EPFirstBytes, 5).toHex().constData()).toUpper());

                /* Load PE file buffer to hex viewer */
                pwgt -> clear();
                pwgt -> setData(new QHexView::DataStorageArray(pe->fileBuffer));


            }else
                QMessageBox::warning(this, "Access denied", "File is currently in use or inaccessible.", QMessageBox::Ok);

        }
    }
}

void MainWindow::on_disasmBtn_clicked()
{
    ui->disasmBtn->setEnabled(false);
    if(pe->file){

        ui->tableWidgetDisasm->clear();

        /* Prepare table columns for disassembly */
        ui->tableWidgetDisasm->setColumnCount(3);
        ui->tableWidgetDisasm->setHorizontalHeaderItem(0, new QTableWidgetItem("Offset"));
        ui->tableWidgetDisasm->setHorizontalHeaderItem(1, new QTableWidgetItem("Opcodes"));
        ui->tableWidgetDisasm->setHorizontalHeaderItem(2, new QTableWidgetItem("Disassembly"));

        /* Reset progress bar value */
        ui->progressBar->setValue(0);

        /* Load Disassembly */
        QString disassembled = "";
        QString instruction = "";

        unsigned char * fileOffset = (unsigned char *)pe->fileBuffer.data() + ui->offsetEdit->text().toULong(nullptr, 16);

        for (int i = 0, count = 0, row = 0; i < pe->fileBuffer.size(); i += count, row++) {
            count = disasm->Disassemble(fileOffset + i, pe->fileBuffer.size() - i, i, disassembled);

            instruction.clear();
            for (int e = 0; e < count; e++){
                instruction.append(QString("%1 ").arg(fileOffset[i + e], 2, 16, QChar('0')).toUpper());
            }
            ui->tableWidgetDisasm->insertRow (ui->tableWidgetDisasm->rowCount());

            ui->tableWidgetDisasm->setItem   (row,
                                     0,
                                     new QTableWidgetItem(QString("%1").arg(i, 8, 16, QChar('0')) + ": "));
            ui->tableWidgetDisasm->setItem   (row,
                                     1,
                                     new QTableWidgetItem(instruction));
            ui->tableWidgetDisasm->setItem   (row,
                                     2,
                                     new QTableWidgetItem(disassembled.toUpper()));

            double progressValue = qRound((double(i) / pe->fileBuffer.size()) * 100);
            ui->progressBar->setValue(progressValue);

        }
    }

    ui->disasmBtn->setEnabled(true);
}

void MainWindow::on_actionUnload_file_triggered()
{
    if(pe->file->isOpen()){

        pe->~PortableExecutable();
        pe = nullptr;

        ui->actionUnload_file->setEnabled(false);
        ui->hexTab->setEnabled(false);
        ui->disasmTab->setEnabled(false);
    }
}

void MainWindow::on_codeCaveBtn_clicked()
{
    ui->codeCaveBtn->setEnabled(false);

    if(pe->file){
        /* Reset progress bar value */
        ui->progressBar->setValue(0);

        /* Prepare table columns for code cave details */
        ui->tableWidgetDisasm->setColumnCount(3);
        ui->tableWidgetDisasm->setHorizontalHeaderItem(0, new QTableWidgetItem("Section"));
        ui->tableWidgetDisasm->setHorizontalHeaderItem(1, new QTableWidgetItem("Size in bytes"));
        ui->tableWidgetDisasm->setHorizontalHeaderItem(2, new QTableWidgetItem("Code cave offset"));

        QList<QStringList> Codecaves = pe->FindCodeCaves(ui->codeCaveSizeEdit->text().toInt());

        ui->tableWidgetDisasm->setRowCount(Codecaves.size());

        for (int i = 0; i < Codecaves.size(); i++){
                ui->tableWidgetDisasm->setItem   (i,
                                         0,
                                         new QTableWidgetItem(Codecaves[i][0]));

                ui->tableWidgetDisasm->setItem   (i,
                                         1,
                                         new QTableWidgetItem(Codecaves[i][1]));


                ui->tableWidgetDisasm->setItem   (i,
                                         2,
                                         new QTableWidgetItem(Codecaves[i][2]));

        }

        ui->codeCaveBtn->setEnabled(true);
    }
}

void MainWindow::on_actionHexToAsm_triggered()
{
    if(sc_ui == nullptr)
        sc_ui = new ShellcodeDialog(this);

    sc_ui->show();
}

void MainWindow::on_tableWidgetDisasm_itemSelectionChanged()
{
    if(ui->tableWidgetDisasm->selectedItems().count() > 0)
        ui->patchBtn->setEnabled(true);
     else
        ui->patchBtn->setEnabled(false);

}

void MainWindow::on_patchBtn_clicked()
{
    QString filePath = pe->fileInfo.fileName();

    if(p_ui == nullptr)
        p_ui = new PatchDialog(this);

    unsigned long fileOffset = ui->offsetEdit->text().toULong(nullptr, 16) + ui->tableWidgetDisasm->item(ui->tableWidgetDisasm->currentRow(), 0)->text().toULong(nullptr, 16);

    p_ui->setByteValues(QString("%1").arg(fileOffset, 8, 16, QChar('0')), ui->tableWidgetDisasm->item(ui->tableWidgetDisasm->currentRow(), 1)->text());
    p_ui->exec();

    if(p_ui->result() == QDialog::Accepted){

        QString inputHexValues = p_ui->getByteValues();

        QRegExp hexMatcher("^[0-9A-Fa-f]+$", Qt::CaseInsensitive);
        if (hexMatcher.exactMatch(inputHexValues.remove(' ')))
        {
            pe->file->seek(fileOffset); // Seek to selected offset

            if(pe->file->write(QByteArray::fromHex(inputHexValues.toUtf8()).data(), QByteArray::fromHex(inputHexValues.toUtf8()).size() > 0)){

                pe->fileBuffer.clear();
                pe->fileBuffer = pe->file->readAll();

                on_disasmBtn_clicked();

                QMessageBox::information(this, "Bytes written", "File has been patched and saved!", QMessageBox::Ok);

            }
        }
    }
}
