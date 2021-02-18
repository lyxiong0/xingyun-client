#include "qushuiyin.h"
#include "ui_qushuiyin.h"
#include <string>
#include <QDebug>
#include <QMessageBox>
#include   "windows.h "

qushuiyin::qushuiyin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::qushuiyin)
{
    ui->setupUi(this);
    connect(ui->pushButton,&QPushButton::clicked,[=](){
        QString datapath=ui->lineEdit->text();
        QString wm=ui->lineEdit_2->text();
        if(datapath.length()==0||wm.length()==0){
            QMessageBox::critical(this,"datapath error","请填入数据地址或水印长度");
        }else{
            std::string str2="cmd /c d:&&cd ";
            str2=str2+datapath.toUtf8().data()+"&&python wm_ext.py "+wm.toUtf8().data();
            qDebug() << QString(str2.c_str());
            int status=WinExec(str2.c_str(), SW_HIDE);
//          int status=std::system("d:&&cd D:\\ideaspace\\xingyun-backend\\eladmin-system\\watermark&&python wm_emb.py jinlei");
            qDebug()<<status;
            if(status<31){
                QMessageBox::critical(this,"length error","请输入正确的水印长度");
            }else{
                QMessageBox::information(this,"提示","成功取出水印");
            }


        }
    });
}

qushuiyin::~qushuiyin()
{
    delete ui;
}