/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.14
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *openButton;
    QPushButton *pushButton;
    QPushButton *tButton;
    QPushButton *cButton;
    QPushButton *runButton;
    QHBoxLayout *horizontalLayout;
    QTextEdit *srcEdit;
    QTextBrowser *asmBrowser;
    QVBoxLayout *verticalLayout;
    QTextBrowser *stdOut;
    QLineEdit *stdIn;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(787, 537);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_3 = new QVBoxLayout(centralwidget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        openButton = new QPushButton(centralwidget);
        openButton->setObjectName(QString::fromUtf8("openButton"));

        horizontalLayout_2->addWidget(openButton);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_2->addWidget(pushButton);

        tButton = new QPushButton(centralwidget);
        tButton->setObjectName(QString::fromUtf8("tButton"));

        horizontalLayout_2->addWidget(tButton);

        cButton = new QPushButton(centralwidget);
        cButton->setObjectName(QString::fromUtf8("cButton"));

        horizontalLayout_2->addWidget(cButton);

        runButton = new QPushButton(centralwidget);
        runButton->setObjectName(QString::fromUtf8("runButton"));

        horizontalLayout_2->addWidget(runButton);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        srcEdit = new QTextEdit(centralwidget);
        srcEdit->setObjectName(QString::fromUtf8("srcEdit"));
        QFont font;
        font.setFamily(QString::fromUtf8("Monospace"));
        font.setPointSize(18);
        srcEdit->setFont(font);
        srcEdit->setAutoFillBackground(false);
        srcEdit->setTabChangesFocus(false);
        srcEdit->setTabStopDistance(57.666666999999997);

        horizontalLayout->addWidget(srcEdit);

        asmBrowser = new QTextBrowser(centralwidget);
        asmBrowser->setObjectName(QString::fromUtf8("asmBrowser"));

        horizontalLayout->addWidget(asmBrowser);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        stdOut = new QTextBrowser(centralwidget);
        stdOut->setObjectName(QString::fromUtf8("stdOut"));
        stdOut->setEnabled(true);

        verticalLayout->addWidget(stdOut);

        stdIn = new QLineEdit(centralwidget);
        stdIn->setObjectName(QString::fromUtf8("stdIn"));

        verticalLayout->addWidget(stdIn);


        verticalLayout_2->addLayout(verticalLayout);

        verticalLayout_2->setStretch(1, 5);
        verticalLayout_2->setStretch(2, 1);

        verticalLayout_3->addLayout(verticalLayout_2);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        openButton->setText(QCoreApplication::translate("MainWindow", "open", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        tButton->setText(QCoreApplication::translate("MainWindow", "Terminate", nullptr));
        cButton->setText(QCoreApplication::translate("MainWindow", "Compile", nullptr));
        runButton->setText(QCoreApplication::translate("MainWindow", "Run", nullptr));
        srcEdit->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Monospace'; font-size:18pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        srcEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "#include <iostream>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
