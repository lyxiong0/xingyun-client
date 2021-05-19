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
        QString pf=ui->lineEdit_3->text();
        if(datapath.length()==0||wm.length()==0){
            QMessageBox::critical(this,"datapath error","请填入数据地址或水印长度");
        }else{
            std::string str2="";
            str2=str2+pf.toUtf8().data()+":&&cd "+datapath.toUtf8().data()+"&&D:\\Python36\\python wm_ext.py "+wm.toUtf8().data();
            qDebug() << QString(str2.c_str());
            //获取命令行输出
            FILE *fp;
            char tmp[1024] = {0};
            std::string result;
            if ((fp = popen(str2.c_str(), "r")) != nullptr) {
                while (fgets(tmp, 1024, fp) != nullptr)
                    result += tmp;
                pclose(fp);
            }
            QString success = QString::fromStdString("成功提取水印：" + result);
            //判断
            if(result.size() == 0){
                QMessageBox::critical(this,"length error","请输入正确的水印长度");
            }else{
                QMessageBox::information(this,"提示", success);
            }
        }
    });
}

qushuiyin::~qushuiyin()
{
    delete ui;
}
