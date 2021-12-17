#ifndef SHELLCODEDIALOG_H
#define SHELLCODEDIALOG_H

#include <QDialog>
#include "Parser.h"

namespace Ui {
class ShellcodeDialog;
}

class ShellcodeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShellcodeDialog(QWidget *parent = nullptr);
    ~ShellcodeDialog();

private slots:
    void on_pushButton_clicked();

private:
    Parser *disasm = nullptr;

private:
    Ui::ShellcodeDialog *ui;
};

#endif // SHELLCODEDIALOG_H
