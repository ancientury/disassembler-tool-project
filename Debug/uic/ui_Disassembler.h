/********************************************************************************
** Form generated from reading UI file 'Disassembler.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISASSEMBLER_H
#define UI_DISASSEMBLER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DisassemblerClass
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionExit;
    QAction *actionAbout;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab_4;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_3;
    QGridLayout *gridLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *epSectionEdit;
    QLineEdit *epAddressEdit;
    QLineEdit *fileNameEdit;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_4;
    QLineEdit *firstBytesEdit;
    QLineEdit *fileTypeEdit;
    QSpacerItem *horizontalSpacer;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_4;
    QLineEdit *fileSizeEdit;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer;
    QTableWidget *tableWidgetPESections;
    QSpacerItem *verticalSpacer_2;
    QWidget *tab;
    QVBoxLayout *verticalLayout_2;
    QWidget *tab_2;
    QWidget *tab_3;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuView;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *DisassemblerClass)
    {
        if (DisassemblerClass->objectName().isEmpty())
            DisassemblerClass->setObjectName(QString::fromUtf8("DisassemblerClass"));
        DisassemblerClass->resize(807, 564);
        actionOpen = new QAction(DisassemblerClass);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/Open.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon);
        actionSave = new QAction(DisassemblerClass);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/Save.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon1);
        actionExit = new QAction(DisassemblerClass);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionAbout = new QAction(DisassemblerClass);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/Information.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout->setIcon(icon2);
        centralWidget = new QWidget(DisassemblerClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        verticalLayout_3 = new QVBoxLayout(tab_4);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_3);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(tab_4);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 2, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 2, 1, 1);

        epSectionEdit = new QLineEdit(tab_4);
        epSectionEdit->setObjectName(QString::fromUtf8("epSectionEdit"));
        QPalette palette;
        QBrush brush(QColor(240, 240, 240, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        epSectionEdit->setPalette(palette);
        epSectionEdit->setReadOnly(true);

        gridLayout->addWidget(epSectionEdit, 0, 9, 1, 1);

        epAddressEdit = new QLineEdit(tab_4);
        epAddressEdit->setObjectName(QString::fromUtf8("epAddressEdit"));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::Base, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush);
        epAddressEdit->setPalette(palette1);
        epAddressEdit->setReadOnly(true);

        gridLayout->addWidget(epAddressEdit, 1, 9, 1, 1);

        fileNameEdit = new QLineEdit(tab_4);
        fileNameEdit->setObjectName(QString::fromUtf8("fileNameEdit"));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::Base, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush);
        fileNameEdit->setPalette(palette2);
        fileNameEdit->setReadOnly(true);

        gridLayout->addWidget(fileNameEdit, 0, 3, 1, 1);

        label_2 = new QLabel(tab_4);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 2, 7, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 8, 1, 1);

        label_3 = new QLabel(tab_4);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 1, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 0, 0, 1, 1);

        firstBytesEdit = new QLineEdit(tab_4);
        firstBytesEdit->setObjectName(QString::fromUtf8("firstBytesEdit"));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::Base, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::Base, brush);
        firstBytesEdit->setPalette(palette3);
        firstBytesEdit->setReadOnly(true);

        gridLayout->addWidget(firstBytesEdit, 2, 9, 1, 1);

        fileTypeEdit = new QLineEdit(tab_4);
        fileTypeEdit->setObjectName(QString::fromUtf8("fileTypeEdit"));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::Base, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::Base, brush);
        fileTypeEdit->setPalette(palette4);
        fileTypeEdit->setReadOnly(true);

        gridLayout->addWidget(fileTypeEdit, 2, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 4, 1, 1);

        label_5 = new QLabel(tab_4);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 1, 7, 1, 1);

        label_6 = new QLabel(tab_4);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 0, 7, 1, 1);

        label_4 = new QLabel(tab_4);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 0, 1, 1, 1);

        fileSizeEdit = new QLineEdit(tab_4);
        fileSizeEdit->setObjectName(QString::fromUtf8("fileSizeEdit"));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::Base, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::Base, brush);
        fileSizeEdit->setPalette(palette5);
        fileSizeEdit->setReadOnly(true);

        gridLayout->addWidget(fileSizeEdit, 1, 3, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 0, 10, 1, 1);


        verticalLayout_3->addLayout(gridLayout);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer);

        tableWidgetPESections = new QTableWidget(tab_4);
        if (tableWidgetPESections->columnCount() < 4)
            tableWidgetPESections->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetPESections->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetPESections->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetPESections->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetPESections->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidgetPESections->setObjectName(QString::fromUtf8("tableWidgetPESections"));
        tableWidgetPESections->setAutoScroll(false);
        tableWidgetPESections->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidgetPESections->setAlternatingRowColors(true);
        tableWidgetPESections->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetPESections->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidgetPESections->setTextElideMode(Qt::ElideRight);
        tableWidgetPESections->setShowGrid(false);
        tableWidgetPESections->setGridStyle(Qt::SolidLine);
        tableWidgetPESections->setSortingEnabled(false);
        tableWidgetPESections->setRowCount(0);
        tableWidgetPESections->setColumnCount(4);
        tableWidgetPESections->horizontalHeader()->setVisible(true);
        tableWidgetPESections->horizontalHeader()->setCascadingSectionResizes(false);
        tableWidgetPESections->horizontalHeader()->setMinimumSectionSize(180);
        tableWidgetPESections->horizontalHeader()->setDefaultSectionSize(180);
        tableWidgetPESections->horizontalHeader()->setHighlightSections(false);
        tableWidgetPESections->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableWidgetPESections->horizontalHeader()->setStretchLastSection(false);

        verticalLayout_3->addWidget(tableWidgetPESections);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_2);

        tabWidget->addTab(tab_4, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_2 = new QVBoxLayout(tab);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        tabWidget->addTab(tab_3, QString());

        verticalLayout->addWidget(tabWidget);

        DisassemblerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(DisassemblerClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 807, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        DisassemblerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(DisassemblerClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        DisassemblerClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(DisassemblerClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        DisassemblerClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuHelp->addAction(actionAbout);
        mainToolBar->addAction(actionOpen);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionSave);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionAbout);
        mainToolBar->addSeparator();

        retranslateUi(DisassemblerClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(DisassemblerClass);
    } // setupUi

    void retranslateUi(QMainWindow *DisassemblerClass)
    {
        DisassemblerClass->setWindowTitle(QCoreApplication::translate("DisassemblerClass", "Disassembler++", nullptr));
        actionOpen->setText(QCoreApplication::translate("DisassemblerClass", "Open", nullptr));
        actionSave->setText(QCoreApplication::translate("DisassemblerClass", "Save", nullptr));
        actionExit->setText(QCoreApplication::translate("DisassemblerClass", "Exit", nullptr));
        actionAbout->setText(QCoreApplication::translate("DisassemblerClass", "About", nullptr));
        label->setText(QCoreApplication::translate("DisassemblerClass", "File Type:", nullptr));
        label_2->setText(QCoreApplication::translate("DisassemblerClass", "First Bytes:", nullptr));
        label_3->setText(QCoreApplication::translate("DisassemblerClass", "File Size:", nullptr));
        label_5->setText(QCoreApplication::translate("DisassemblerClass", "Entrypoint Address:", nullptr));
        label_6->setText(QCoreApplication::translate("DisassemblerClass", "Entrypoint Section:", nullptr));
        label_4->setText(QCoreApplication::translate("DisassemblerClass", "File Name:", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetPESections->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("DisassemblerClass", "Section", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetPESections->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("DisassemblerClass", "VirtualAddress", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetPESections->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("DisassemblerClass", "VirtualSize", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetPESections->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("DisassemblerClass", "PointerToRawData", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("DisassemblerClass", "PE Details", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("DisassemblerClass", "Hex Dump", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("DisassemblerClass", "Disassembly", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("DisassemblerClass", "Strings", nullptr));
        menuFile->setTitle(QCoreApplication::translate("DisassemblerClass", "File", nullptr));
        menuView->setTitle(QCoreApplication::translate("DisassemblerClass", "View", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("DisassemblerClass", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DisassemblerClass: public Ui_DisassemblerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISASSEMBLER_H
