/********************************************************************************
** Form generated from reading UI file 'QtGUI.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTGUI_H
#define UI_QTGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtGUIClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtGUIClass)
    {
        if (QtGUIClass->objectName().isEmpty())
            QtGUIClass->setObjectName(QString::fromUtf8("QtGUIClass"));
        QtGUIClass->resize(600, 400);
        centralWidget = new QWidget(QtGUIClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(60, 140, 75, 24));
        QtGUIClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QtGUIClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 22));
        QtGUIClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtGUIClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QtGUIClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QtGUIClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QtGUIClass->setStatusBar(statusBar);

        retranslateUi(QtGUIClass);

        QMetaObject::connectSlotsByName(QtGUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtGUIClass)
    {
        QtGUIClass->setWindowTitle(QCoreApplication::translate("QtGUIClass", "QtGUI", nullptr));
        pushButton->setText(QCoreApplication::translate("QtGUIClass", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtGUIClass: public Ui_QtGUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTGUI_H
