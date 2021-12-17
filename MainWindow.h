#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QHexView/include/QHexView.h"
#include "ShellcodeDialog.h"
#include "PatchDialog.h"
#include "PortableExecutable.h"
#include "Parser.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_disasmBtn_clicked();

    void on_actionUnload_file_triggered();

    void on_codeCaveBtn_clicked();

    void on_actionHexToAsm_triggered();

    void on_tableWidgetDisasm_itemSelectionChanged();

    void on_patchBtn_clicked();

private:
    QHexView *pwgt = nullptr;
    Parser *disasm = nullptr;
    PortableExecutable *pe = nullptr;

private:
    Ui::MainWindow *ui;
    ShellcodeDialog *sc_ui = nullptr;
    PatchDialog *p_ui = nullptr;
};
#endif // MAINWINDOW_H
