/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAbout;
    QAction *actionFind;
    QAction *actionSet_Directory;
    QAction *actionFormat;
    QAction *actionText;
    QAction *actionBinary;
    QAction *actionCopy;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QPushButton *checkButton;
    QPushButton *saveButton;
    QPushButton *pushButton;
    QTextBrowser *textBrowser;
    QTableWidget *tableWidget;
    QMenuBar *menuBar;
    QMenu *menuHelp;
    QMenu *menuTools;
    QMenu *menuFormat;
    QMenu *menuEdit;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(627, 403);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionFind = new QAction(MainWindow);
        actionFind->setObjectName(QStringLiteral("actionFind"));
        actionSet_Directory = new QAction(MainWindow);
        actionSet_Directory->setObjectName(QStringLiteral("actionSet_Directory"));
        actionFormat = new QAction(MainWindow);
        actionFormat->setObjectName(QStringLiteral("actionFormat"));
        actionFormat->setCheckable(true);
        actionText = new QAction(MainWindow);
        actionText->setObjectName(QStringLiteral("actionText"));
        actionText->setCheckable(true);
        actionBinary = new QAction(MainWindow);
        actionBinary->setObjectName(QStringLiteral("actionBinary"));
        actionBinary->setCheckable(true);
        actionCopy = new QAction(MainWindow);
        actionCopy->setObjectName(QStringLiteral("actionCopy"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        checkButton = new QPushButton(centralWidget);
        checkButton->setObjectName(QStringLiteral("checkButton"));

        gridLayout->addWidget(checkButton, 3, 1, 1, 1);

        saveButton = new QPushButton(centralWidget);
        saveButton->setObjectName(QStringLiteral("saveButton"));

        gridLayout->addWidget(saveButton, 2, 1, 1, 1);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(pushButton, 2, 0, 2, 1);

        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        sizePolicy.setHeightForWidth(textBrowser->sizePolicy().hasHeightForWidth());
        textBrowser->setSizePolicy(sizePolicy);
        textBrowser->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        textBrowser->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContentsOnFirstShow);

        gridLayout->addWidget(textBrowser, 1, 0, 1, 1);

        tableWidget = new QTableWidget(centralWidget);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        tableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
        tableWidget->setTextElideMode(Qt::ElideNone);
        tableWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        tableWidget->setWordWrap(true);

        gridLayout->addWidget(tableWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 627, 25));
        menuBar->setNativeMenuBar(false);
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QStringLiteral("menuTools"));
        menuFormat = new QMenu(menuBar);
        menuFormat->setObjectName(QStringLiteral("menuFormat"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuFormat->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuHelp->addAction(actionAbout);
        menuTools->addAction(actionSet_Directory);
        menuTools->addAction(actionFind);
        menuFormat->addAction(actionText);
        menuFormat->addAction(actionBinary);
        menuEdit->addAction(actionCopy);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "PenguSniff", 0));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0));
        actionFind->setText(QApplication::translate("MainWindow", "Find...", 0));
        actionSet_Directory->setText(QApplication::translate("MainWindow", "Set Directory", 0));
        actionFormat->setText(QApplication::translate("MainWindow", "Format", 0));
        actionText->setText(QApplication::translate("MainWindow", "Text", 0));
        actionBinary->setText(QApplication::translate("MainWindow", "Binary", 0));
        actionCopy->setText(QApplication::translate("MainWindow", "Copy", 0));
        checkButton->setText(QApplication::translate("MainWindow", "Check", 0));
        saveButton->setText(QApplication::translate("MainWindow", "Save", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Scan", 0));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0));
        menuTools->setTitle(QApplication::translate("MainWindow", "Tools", 0));
        menuFormat->setTitle(QApplication::translate("MainWindow", "Format", 0));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
