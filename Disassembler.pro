QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Main.cpp \
    MainWindow.cpp \
    Parser.cpp \
    PatchDialog.cpp \
    PortableExecutable.cpp \
    QHexView/src/QHexView.cpp \
    ShellcodeDialog.cpp

HEADERS += \
    MainWindow.h \
    Parser.h \
    ParserTypes.h \
    PatchDialog.h \
    PortableExecutable.h \
    QHexView/include/QHexView.h \
    ShellcodeDialog.h

FORMS += \
    MainWindow.ui \
    PatchDialog.ui \
    ShellcodeDialog.ui

TRANSLATIONS += \
    Disassembler_en_GB.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Disassembler.qrc
