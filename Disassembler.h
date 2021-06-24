#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Disassembler.h"
#include "PortableExecutable.h"

class Disassembler : public QMainWindow
{
    Q_OBJECT

public:
    Disassembler(QWidget *parent = Q_NULLPTR);

private slots:
    void on_actionOpen_triggered();

private:
    Ui::DisassemblerClass ui;

private:
    bool readPEFile(const QString& peExecutableFileName);

private:
    PortableExecutable PE;
};
