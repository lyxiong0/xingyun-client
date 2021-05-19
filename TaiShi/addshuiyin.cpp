#include "addshuiyin.h"
#include "ui_addshuiyin.h"
#include <string>
#include <cstdlib>
#include <QDebug>
#include <QMessageBox>
#include <Windows.h>

addshuiyin::addshuiyin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addshuiyin)
{
    ui->setupUi(this);

    //点击添加水印,触发加水印代码
    connect(ui->pushButton,&QPushButton::clicked,[=](){
        QString datapath=ui->lineEdit->text();
        QString wm=ui->lineEdit_2->text();
        QString pf=ui->lineEdit_3->text();
        if(datapath.length()==0||wm.length()==0){
            QMessageBox::critical(this,"datapath error","请填入数据地址或水印");
        }else{
            std::string str2="cmd.exe /c";
            str2=str2+pf.toUtf8().data()+":&&cd "+datapath.toUtf8().data()+"&&D:\\Python36\\python wm_emb.py "+wm.toUtf8().data();
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
            //判断结果
            if(result == "OK"){
                QMessageBox::critical(this,"datapath error","请使用绝对路径路径,并且不包含中文路径名");
            }else{
                QMessageBox::information(this,"提示","成功加入水印");
            }
        }
    });
}

addshuiyin::~addshuiyin()
{
    delete ui;
}

