/********************************************************************************
** Form generated from reading UI file 'addshuiyin.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDSHUIYIN_H
#define UI_ADDSHUIYIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_addshuiyin
{
public:
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout;
    QWidget *widget_3;
    QFormLayout *formLayout;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QSpacerItem *verticalSpacer_2;
    QPushButton *pushButton;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *addshuiyin)
    {
        if (addshuiyin->objectName().isEmpty())
            addshuiyin->setObjectName(QString::fromUtf8("addshuiyin"));
        addshuiyin->resize(600, 300);
        addshuiyin->setMinimumSize(QSize(600, 300));
        addshuiyin->setMaximumSize(QSize(600, 300));
        verticalLayout_2 = new QVBoxLayout(addshuiyin);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        widget_4 = new QWidget(addshuiyin);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        verticalLayout = new QVBoxLayout(widget_4);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget_3 = new QWidget(widget_4);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        formLayout = new QFormLayout(widget_3);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label_3 = new QLabel(widget_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_3);

        lineEdit_3 = new QLineEdit(widget_3);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit_3->sizePolicy().hasHeightForWidth());
        lineEdit_3->setSizePolicy(sizePolicy);

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit_3);


        verticalLayout->addWidget(widget_3);

        widget = new QWidget(widget_4);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        sizePolicy.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(lineEdit);


        verticalLayout->addWidget(widget);

        widget_2 = new QWidget(widget_4);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        lineEdit_2 = new QLineEdit(widget_2);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        sizePolicy.setHeightForWidth(lineEdit_2->sizePolicy().hasHeightForWidth());
        lineEdit_2->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(lineEdit_2);


        verticalLayout->addWidget(widget_2);


        verticalLayout_2->addWidget(widget_4);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        pushButton = new QPushButton(addshuiyin);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout_2->addWidget(pushButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        retranslateUi(addshuiyin);

        QMetaObject::connectSlotsByName(addshuiyin);
    } // setupUi

    void retranslateUi(QWidget *addshuiyin)
    {
        addshuiyin->setWindowTitle(QCoreApplication::translate("addshuiyin", "Form", nullptr));
        label_3->setText(QCoreApplication::translate("addshuiyin", "\346\225\260\346\215\256\346\211\200\345\234\250\347\233\230\347\254\246\357\274\232", nullptr));
        label->setText(QCoreApplication::translate("addshuiyin", "\346\225\260 \346\215\256 \345\234\260 \345\235\200\357\274\232 ", nullptr));
        label_2->setText(QCoreApplication::translate("addshuiyin", "\346\260\264 \345\215\260 \345\206\205 \345\256\271\357\274\232 ", nullptr));
        pushButton->setText(QCoreApplication::translate("addshuiyin", "\346\267\273\345\212\240\346\260\264\345\215\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class addshuiyin: public Ui_addshuiyin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDSHUIYIN_H
