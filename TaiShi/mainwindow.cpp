#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QProcess>

#include <QFileDialog>
#include <QStandardPaths>
#include <QDateTime>
#include <QAbstractItemModel>
#include <QList>
#include <addshuiyin.h>
#include <qushuiyin.h>
#include <QDebug>
//Table2Excel
#include <QTableWidget>
#include <QDesktopServices>
#include <QAxObject>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //点击添加水印按钮,,弹出模态对话框
    connect(ui->actionadd,&QAction::triggered,[=](){
        //创建模态对话框
        addshuiyin dlg(this);
        dlg.resize(500,500);
        dlg.exec();
    });

    //点击取水印按钮,,弹出模态对话框
    connect(ui->actionqu,&QAction::triggered,[=](){
        //创建模态对话框
        qushuiyin dlg1(this);
        dlg1.resize(500,500);
        dlg1.exec();
    });



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnConnect_clicked()
{
    //点击“连接”按钮，从输入框获取信息
    QString user = ui->editUser->text(); //用户名
    QString password = ui->editPassword->text(); //密码
    QString database = ui->editDatabase->text(); //数据库名
    QString hostName = ui->editHostName->text(); //主机名
    int port = ui->editPort->text().toInt(); //端口

    //连接数据库
    MainWindow::createConnection(user, password, database, hostName, port);
}

void MainWindow::on_btnShow_clicked()
{
    //“显示选中表”按钮
    QString table = ui->editTable->text(); //表名
    //判断用户是否有输入表名
    if (table.length()) {
        model = new QSqlTableModel(this);
        model->setTable(table);
        model->select();
        // 设置编辑策略为OnManualSubmit
        // OnManualSubmit：所有的更改都将缓存到模型中，直到submitAll()或revertAll()被调用。
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        ui->tableView->setModel(model);
    }else{
        QMessageBox::warning(this, QString("Warning"),
                             QString("表名不能为空"), QMessageBox::Cancel);
    }
}


void MainWindow::on_btnAnalyze_clicked()
{
    //“生成统计信息”按钮
    QString table = ui->editTable->text(); //表名
    //QString comment = QString("show full columns from %1").arg(table);
    //执行SQL语句
    QString comment = QString("select "
        "COLUMN_NAME as columnName, DATA_TYPE as columnType, CHARACTER_OCTET_LENGTH as columnLength,"
        "COLUMN_COMMENT as remarks, COLUMN_DEFAULT as defaultValue, IS_NULLABLE as nullable from "
        "(select * from INFORMATION_SCHEMA.COLUMNS where table_name='%1') dt;").arg(table);
    qDebug() << comment;
    QSqlQueryModel *queryModel = new QSqlQueryModel;

    queryModel->setQuery(comment);
    ui->tableView->setModel(queryModel);
}

void MainWindow::Table2ExcelByHtml(QTableView *table, QString title, QString fileName)
{
    //QString fileName = QFileDialog::getSaveFileName(table, "保存", QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation), "Excel 文件(*.xls *.xlsx)");
    if (fileName == "") {
        QMessageBox::critical(0, QString("Error"),
                              "文件名不能为空", QMessageBox::Cancel);
        return ;
    }

    qDebug() << fileName << Qt::endl;
    QAxObject *excel = new QAxObject;
    //连接Excel控件
    if (excel->setControl("Excel.Application")) {
        excel->dynamicCall("SetVisible (bool Visible)","false");//不显示窗体
        excel->setProperty("DisplayAlerts", false);//不显示任何警告信息。如果为true那么在关闭是会出现类似“文件已修改，是否保存”的提示
        QAxObject *workbooks = excel->querySubObject("WorkBooks");//获取工作簿集合
        workbooks->dynamicCall("Add");//新建一个工作簿
        QAxObject *workbook = excel->querySubObject("ActiveWorkBook");//获取当前工作簿
        QAxObject *worksheet = workbook->querySubObject("Worksheets(int)", 1);

        int i,j;
        QAbstractItemModel *model = table->model();
        const int colcount = model->columnCount();
        const int rowcount = model->rowCount();

        QAxObject *cell,*col;
        //             //标题行
        //             cell=worksheet->querySubObject("Cells(int,int)", 1, 1);
        //             cell->dynamicCall("SetValue(const QString&)", title);
        //             cell->querySubObject("Font")->setProperty("Size", 18);
        //             //调整行高
        //             worksheet->querySubObject("Range(const QString&)", "1:1")->setProperty("RowHeight", 30);
        //合并标题行
        QString cellTitle;
        cellTitle.append("A1:");
        cellTitle.append(QChar(colcount - 1 + 'A'));
        cellTitle.append(QString::number(1));
        QAxObject *range = worksheet->querySubObject("Range(const QString&)", cellTitle);
        //             range->setProperty("WrapText", true);
        //             range->setProperty("MergeCells", true);
        //             range->setProperty("HorizontalAlignment", -4108);//xlCenter
        //             range->setProperty("VerticalAlignment", -4108);//xlCenter
        //列标题
        for(i = 0; i < colcount;i++) {
            QString columnName;
            columnName.append(QChar(i  + 'A'));
            columnName.append(":");
            columnName.append(QChar(i + 'A'));
            col = worksheet->querySubObject("Columns(const QString&)", columnName);
            col->setProperty("ColumnWidth", table->columnWidth(i)/6);
            cell=worksheet->querySubObject("Cells(int,int)", 2, i+1);
            //QTableView 获取表格头部文字信息
            columnName= model->headerData(i,Qt::Horizontal,Qt::DisplayRole).toString();
            cell->dynamicCall("SetValue(const QString&)", columnName);
            //                 cell->querySubObject("Font")->setProperty("Bold", true);
            //                 cell->querySubObject("Interior")->setProperty("Color",QColor(191, 191, 191));
            //                 cell->setProperty("HorizontalAlignment", -4108);//xlCenter
            //                 cell->setProperty("VerticalAlignment", -4108);//xlCenter
        }

        //数据区
        //QTableView 获取表格数据部分
        //行数
        for(i=0;i<rowcount;i++)
            for (j=0;j<colcount;j++) { //列数
                QModelIndex index = model->index(i, j);
                QString strdata=model->data(index).toString();
                worksheet->querySubObject("Cells(int,int)", i+3, j+1)->dynamicCall("SetValue(const QString&)", strdata);
            }


        //             //画框线
        //             QString lrange;
        //             lrange.append("A2:");
        //             lrange.append(colcount - 1 + 'A');
        //             lrange.append(QString::number(rowcount + 2));
        //             range = worksheet->querySubObject("Range(const QString&)", lrange);
        //             range->querySubObject("Borders")->setProperty("LineStyle", QString::number(1));
        //             range->querySubObject("Borders")->setProperty("Color", QColor(0, 0, 0));
        //调整数据区行高
        QString rowsName;
        rowsName.append("2:");
        rowsName.append(QString::number(rowcount + 2));
        range = worksheet->querySubObject("Range(const QString&)", rowsName);
        //             range->setProperty("RowHeight", 20);
        workbook->dynamicCall("SaveAs(const QString&)",QDir::toNativeSeparators(fileName));//保存至fileName
        workbook->dynamicCall("Close()");//关闭工作簿
        excel->dynamicCall("Quit()");//关闭excel
        delete excel;
        excel=NULL;
        if (QMessageBox::question(NULL,"完成","文件已经导出，是否现在打开？",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
            QDesktopServices::openUrl(QUrl("file:///" + QDir::toNativeSeparators(fileName)));
    }
    else
        QMessageBox::warning(NULL,"错误","未能创建 Excel 对象，请安装 Microsoft Excel。",QMessageBox::Apply);
}

void MainWindow::on_btnOutExcel_clicked()
{
    //导出到Excel按钮
    QFileDialog dlg;
    QString filename;
    dlg.setAcceptMode(QFileDialog::AcceptSave);
    dlg.setDirectory(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));
    dlg.setNameFilter("*.xlsb");
    // filename = QDateTime::currentDateTime().toString("yyyyMMdd hh-mm-ss") + ".xlsb";
    QString table = ui->editTable->text();
    QString database = ui->editDatabase->text();
    //文件名格式：数据库名-表名.xlsx
    filename = database + "-" + table + ".xlsx";
    dlg.selectFile(filename);
    if (dlg.exec() != QDialog::Accepted)
        return;
    QString filePath = dlg.selectedFiles()[0];
    qDebug() << filePath;
    Table2ExcelByHtml(ui->tableView, "test", filePath);
}

bool MainWindow::createConnection(QString user, QString password, QString database,
                                  QString hostName, int port) {
    //创建数据库连接，hostName默认localhost，port默认3306
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(hostName);
    db.setPort(port);
    if (!database.length()) {
        QMessageBox::critical(0, QString("Error"),
                              "数据库名不能为空!", QMessageBox::Cancel);
        return false;
    }
    db.setDatabaseName(database);
    db.setUserName(user);
    db.setPassword(password);
    if (!db.open()) {
        QMessageBox::critical(0, QString("Error"),
                              "连接失败！", QMessageBox::Cancel);
        return false;
    }
    QMessageBox::information(0, QString("Information"),
                             "已成功连接所选数据库！", QMessageBox::Ok);
    return true;
}
