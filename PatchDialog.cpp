#include "PatchDialog.h"
#include "ui_PatchDialog.h"

PatchDialog::PatchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PatchDialog)
{
    ui->setupUi(this);
}

PatchDialog::~PatchDialog()
{
    delete ui;
}

QString PatchDialog::getByteValues() const
{
    return ui->valuesTextEdit->toPlainText();
}

void PatchDialog::setByteValues(QString offsetStr, QString bytesStr)
{
    ui->offsetValueLabel->setText(offsetStr);
    ui->originalValuesLabel->setText(bytesStr);
    ui->valuesTextEdit->setPlainText(bytesStr);
}
