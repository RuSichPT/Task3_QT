/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QPushButton *m_buttonStart;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *m_lineEditUN;
    QPushButton *m_buttonStop;
    QLineEdit *m_lineEditP;
    QTableView *m_tableView;
    QPushButton *m_buttonTest1;
    QPushButton *m_buttonTest2;
    QPushButton *m_buttonDeleteTable;
    QPushButton *m_buttonCreateTable;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(600, 400);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_buttonStart = new QPushButton(centralwidget);
        m_buttonStart->setObjectName(QString::fromUtf8("m_buttonStart"));

        gridLayout->addWidget(m_buttonStart, 1, 4, 1, 1);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 2, 1, 1);

        m_lineEditUN = new QLineEdit(centralwidget);
        m_lineEditUN->setObjectName(QString::fromUtf8("m_lineEditUN"));

        gridLayout->addWidget(m_lineEditUN, 1, 1, 1, 1);

        m_buttonStop = new QPushButton(centralwidget);
        m_buttonStop->setObjectName(QString::fromUtf8("m_buttonStop"));

        gridLayout->addWidget(m_buttonStop, 1, 5, 1, 1);

        m_lineEditP = new QLineEdit(centralwidget);
        m_lineEditP->setObjectName(QString::fromUtf8("m_lineEditP"));

        gridLayout->addWidget(m_lineEditP, 1, 3, 1, 1);

        m_tableView = new QTableView(centralwidget);
        m_tableView->setObjectName(QString::fromUtf8("m_tableView"));

        gridLayout->addWidget(m_tableView, 0, 0, 1, 7);

        m_buttonTest1 = new QPushButton(centralwidget);
        m_buttonTest1->setObjectName(QString::fromUtf8("m_buttonTest1"));

        gridLayout->addWidget(m_buttonTest1, 2, 4, 1, 1);

        m_buttonTest2 = new QPushButton(centralwidget);
        m_buttonTest2->setObjectName(QString::fromUtf8("m_buttonTest2"));

        gridLayout->addWidget(m_buttonTest2, 2, 5, 1, 1);

        m_buttonDeleteTable = new QPushButton(centralwidget);
        m_buttonDeleteTable->setObjectName(QString::fromUtf8("m_buttonDeleteTable"));

        gridLayout->addWidget(m_buttonDeleteTable, 2, 6, 1, 1);

        m_buttonCreateTable = new QPushButton(centralwidget);
        m_buttonCreateTable->setObjectName(QString::fromUtf8("m_buttonCreateTable"));

        gridLayout->addWidget(m_buttonCreateTable, 1, 6, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 600, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Task3", nullptr));
        m_buttonStart->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\260\321\200\321\202", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "UserName:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Password:", nullptr));
        m_buttonStop->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\276\320\277", nullptr));
        m_buttonTest1->setText(QCoreApplication::translate("MainWindow", "\320\242\320\265\321\201\321\2021", nullptr));
        m_buttonTest2->setText(QCoreApplication::translate("MainWindow", "\320\242\320\265\321\201\321\2022", nullptr));
        m_buttonDeleteTable->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \321\202\320\260\320\261\320\273\320\270\321\206\321\203", nullptr));
        m_buttonCreateTable->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \321\202\320\260\320\261\320\273\320\270\321\206\321\203", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
