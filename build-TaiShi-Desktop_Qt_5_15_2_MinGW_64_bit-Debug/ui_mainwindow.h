/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionadd;
    QAction *actionqu;
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QWidget *widget;
    QGridLayout *gridLayout_4;
    QWidget *widget_2;
    QGridLayout *gridLayout;
    QLabel *label_5;
    QLineEdit *editHostName;
    QLabel *label_2;
    QLineEdit *editPassword;
    QLabel *label_6;
    QLineEdit *editPort;
    QLabel *label_4;
    QLineEdit *editDatabase;
    QLabel *label;
    QLineEdit *editUser;
    QLabel *label_3;
    QLineEdit *editTable;
    QPushButton *btnConnect;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnShow;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnAnalyze;
    QPushButton *btnOutExcel;
    QTableView *tableView;
    QMenuBar *menuBar;
    QMenu *menu;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        actionadd = new QAction(MainWindow);
        actionadd->setObjectName(QString::fromUtf8("actionadd"));
        actionqu = new QAction(MainWindow);
        actionqu->setObjectName(QString::fromUtf8("actionqu"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        gridLayout_4 = new QGridLayout(widget);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        gridLayout = new QGridLayout(widget_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_5 = new QLabel(widget_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 0, 0, 1, 1);

        editHostName = new QLineEdit(widget_2);
        editHostName->setObjectName(QString::fromUtf8("editHostName"));
        editHostName->setEchoMode(QLineEdit::Normal);

        gridLayout->addWidget(editHostName, 0, 1, 1, 1);

        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 2, 1, 1);

        editPassword = new QLineEdit(widget_2);
        editPassword->setObjectName(QString::fromUtf8("editPassword"));
        editPassword->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(editPassword, 0, 3, 1, 1);

        label_6 = new QLabel(widget_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 1, 0, 1, 1);

        editPort = new QLineEdit(widget_2);
        editPort->setObjectName(QString::fromUtf8("editPort"));
        editPort->setEchoMode(QLineEdit::Normal);

        gridLayout->addWidget(editPort, 1, 1, 1, 1);

        label_4 = new QLabel(widget_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 1, 2, 1, 1);

        editDatabase = new QLineEdit(widget_2);
        editDatabase->setObjectName(QString::fromUtf8("editDatabase"));

        gridLayout->addWidget(editDatabase, 1, 3, 1, 1);

        label = new QLabel(widget_2);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 2, 0, 1, 1);

        editUser = new QLineEdit(widget_2);
        editUser->setObjectName(QString::fromUtf8("editUser"));

        gridLayout->addWidget(editUser, 2, 1, 1, 1);

        label_3 = new QLabel(widget_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 2, 1, 1);

        editTable = new QLineEdit(widget_2);
        editTable->setObjectName(QString::fromUtf8("editTable"));
        editTable->setEchoMode(QLineEdit::Normal);

        gridLayout->addWidget(editTable, 2, 3, 1, 1);


        gridLayout_4->addWidget(widget_2, 0, 1, 4, 1);

        btnConnect = new QPushButton(widget);
        btnConnect->setObjectName(QString::fromUtf8("btnConnect"));

        gridLayout_4->addWidget(btnConnect, 0, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer, 1, 2, 1, 1);

        btnShow = new QPushButton(widget);
        btnShow->setObjectName(QString::fromUtf8("btnShow"));

        gridLayout_4->addWidget(btnShow, 1, 3, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_3, 1, 4, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_2, 2, 0, 1, 1);

        btnAnalyze = new QPushButton(widget);
        btnAnalyze->setObjectName(QString::fromUtf8("btnAnalyze"));

        gridLayout_4->addWidget(btnAnalyze, 2, 3, 1, 1);

        btnOutExcel = new QPushButton(widget);
        btnOutExcel->setObjectName(QString::fromUtf8("btnOutExcel"));

        gridLayout_4->addWidget(btnOutExcel, 3, 3, 1, 1);

        tableView = new QTableView(widget);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        gridLayout_4->addWidget(tableView, 4, 0, 1, 5);


        gridLayout_2->addWidget(widget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 21));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(actionadd);
        menu->addSeparator();
        menu->addAction(actionqu);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\346\200\201\345\212\277\345\271\263\345\217\260\346\241\214\351\235\242\345\256\242\346\210\267\347\253\257", nullptr));
        actionadd->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\346\260\264\345\215\260", nullptr));
        actionadd->setIconText(QCoreApplication::translate("MainWindow", "\346\260\264\345\215\260", nullptr));
        actionqu->setText(QCoreApplication::translate("MainWindow", "\345\217\226\345\207\272\346\260\264\345\215\260", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\344\270\273\346\234\272\345\220\215\357\274\232", nullptr));
        editHostName->setText(QString());
        label_2->setText(QCoreApplication::translate("MainWindow", "\345\257\206  \347\240\201\357\274\232", nullptr));
        editPassword->setText(QString());
        label_6->setText(QCoreApplication::translate("MainWindow", "\347\253\257  \345\217\243\357\274\232", nullptr));
        editPort->setText(QString());
        label_4->setText(QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256\345\272\223\357\274\232", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\350\241\250  \345\220\215\357\274\232", nullptr));
        editTable->setText(QString());
        btnConnect->setText(QCoreApplication::translate("MainWindow", "\350\277\236\346\216\245", nullptr));
        btnShow->setText(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\351\200\211\344\270\255\350\241\250", nullptr));
        btnAnalyze->setText(QCoreApplication::translate("MainWindow", "\347\224\237\346\210\220\347\273\237\350\256\241\344\277\241\346\201\257", nullptr));
        btnOutExcel->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\207\272\345\210\260Excel", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\345\267\245\345\205\267", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
