#include "Disassembler.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Disassembler w;
    w.show();
    return a.exec();
}
