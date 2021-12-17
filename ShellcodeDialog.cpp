#include <QDebug>
#include "ShellcodeDialog.h"
#include "ui_ShellcodeDialog.h"

ShellcodeDialog::ShellcodeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShellcodeDialog)
{
    ui->setupUi(this);

    /* Parser engine */
    disasm = new Parser();
}

ShellcodeDialog::~ShellcodeDialog()
{
    delete ui;
    delete disasm;
}

void ShellcodeDialog::on_pushButton_clicked()
{
    QString inputShellcode = ui->shellcodeEdit->toPlainText();

    QRegExp hexMatcher("^[0-9A-Fa-f]+$", Qt::CaseInsensitive);
    if (hexMatcher.exactMatch(inputShellcode.remove(' ')))
    {
        ui->asmEdit->clear();

        QByteArray bytes = QByteArray::fromHex(inputShellcode.toUtf8());
        QString disassembled = "";

        for (int i = 0, count = 0; i < bytes.size(); i += count) {
            count = disasm->Disassemble((unsigned char *)bytes.data() + i, bytes.size() - i, i, disassembled);
            ui->asmEdit->append(QString("%1: %2").arg(i, 8, 16, QChar('0')).arg(disassembled).toUpper());
        }

    }else
        ui->asmEdit->setText("Invalid input! Only hexadecimal values that encode x86 instructions are allowed.");

}
