#include "Disassembler.h"
#include <Windows.h>
#include <qmessagebox.h>
#include <qfiledialog.h>

Disassembler::Disassembler(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}


void Disassembler::on_actionOpen_triggered() 
{
    QString filePath = QFileDialog::getOpenFileName(this,
        tr("Open binary file"), QDir::homePath(), tr("EXE Files (*.exe)"));

    PE.fileInfo = filePath;

    if (PE.fileInfo.exists() && PE.fileInfo.isExecutable()) {

        if (PE.Open(filePath)) {

            QString fString;

            /* Get PE details */

            ui.fileNameEdit->setText(PE.fileInfo.fileName());
            ui.fileSizeEdit->setText(QString::number(PE.fileInfo.size()) + " bytes");
            ui.fileTypeEdit->setText(PE.fileInfo.isExecutable() ? "Portable Executable" : "Non-executable");

            /* Evaluate all sections */

            ui.tableWidgetPESections->setRowCount(PE.fileHeader.NumberOfSections);
            for (int i = 0; i < PE.fileHeader.NumberOfSections; i++) {

                ui.tableWidgetPESections->setItem(i, 0, new QTableWidgetItem(fString.sprintf("%s", PE.sectionHeaders[i].Name)));
                ui.tableWidgetPESections->setItem(i, 1, new QTableWidgetItem(fString.sprintf("0x%x", PE.sectionHeaders[i].VirtualAddress)));
                ui.tableWidgetPESections->setItem(i, 2, new QTableWidgetItem(fString.sprintf("0x%x", PE.sectionHeaders[i].VirtualSize)));
                ui.tableWidgetPESections->setItem(i, 3, new QTableWidgetItem(fString.sprintf("0x%x", PE.sectionHeaders[i].PointerToRawData)));

            }

            /* Get PE entrypoint section */

            ui.epSectionEdit->setText(fString.sprintf("%s", PE.sectionHeaders[PE.GetEntrySectionIndex()].Name));

        }

    }
}