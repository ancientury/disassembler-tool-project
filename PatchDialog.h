#ifndef PATCHDIALOG_H
#define PATCHDIALOG_H

#include <QDialog>

namespace Ui {
class PatchDialog;
}

class PatchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PatchDialog(QWidget *parent = nullptr);
    ~PatchDialog();

    QString getByteValues() const;
    void setByteValues(QString offsetStr, QString bytesStr);

private:
    Ui::PatchDialog *ui;
};

#endif // PATCHDIALOG_H
