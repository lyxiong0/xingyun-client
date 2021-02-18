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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
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
    QString user = ui->editUser->text();
    QString password = ui->editPassword->text();
    QString database = ui->editDatabase->text();

    MainWindow::createConnection(user, password, database);
}

void MainWindow::on_btnShow_clicked()
{
    QString table = ui->editTable->text();
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
    QString table = ui->editTable->text();
    QString comment = QString("show full columns from %1").arg(table);
    QSqlQueryModel *queryModel = new QSqlQueryModel;

    queryModel->setQuery(comment);
    ui->tableView->setModel(queryModel);
//    QSqlTableModel *tableModel = new QSqlTableModel;
//    tableModel->setQuery(comment);
//    ui->tableView->setModel(tableModel);
}

void MainWindow::on_btnOutExcel_clicked()
{
    QFileDialog dlg;
    QString filename;
    dlg.setAcceptMode(QFileDialog::AcceptSave);
    dlg.setDirectory(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));
    dlg.setNameFilter("*.xlsb");
    filename = QDateTime::currentDateTime().toString("yyyyMMdd hh-mm-ss") + ".xlsb";
    dlg.selectFile(filename);
    if (dlg.exec() != QDialog::Accepted)
        return;
    QString filePath = dlg.selectedFiles()[0];
    qDebug() << filePath;

    if (MainWindow::saveFromTable(filePath, ui->tableView, ""))
        QMessageBox::information(this, QString("Information"), QString("保存成功"));
    else
        QMessageBox::critical(this, QString("Error"), QString("保存失败"));
}

bool MainWindow::saveFromTable(QString filePath, QTableView *tableView, QString comment) {
    QAbstractItemModel *model = tableView->model();
    const int column = model->columnCount();
    const int row = model->rowCount();

    //header
    QStringList headers;
    for (int i = 0; i < column; ++i) {
        //跳过隐藏列
        if (tableView->isColumnHidden(i))
            continue;
        //返回具有指定方向的标题中给定 role（角色）和 section（节）的数据。
        //对于水平标题，节号对应于列号。 同样，对于垂直标题，节号对应于行号
        headers << model->headerData(i, Qt::Horizontal).toString();
    }

    //data
    QStringList list;
    QList<QStringList> data;
    for (int i = 0; i < row; ++i) {
        if (model->index(i, 0).data().isNull())
            continue;
        list.clear();
        for (int j = 0; j < column; ++j) {
            //跳过隐藏列
            if (tableView->isColumnHidden(j))
                continue;
            list << model->index(i, j).data().toString();
        }
        data << list;
    }

    return MainWindow::save(filePath, headers, data, comment);
}

bool MainWindow::save(QString filePath, QStringList headers, QList<QStringList> data,QString comment) {
    QString sheetName = "Sheet1";

    // 创建一个数据库实例， 设置连接字符串
    QSqlDatabase dbexcel = QSqlDatabase::addDatabase("QODBC","excelexport");
    if(!dbexcel.isValid())
    {
        qDebug()<<"数据库驱动异常";
        return false;   //! type error
    }

    QString dsn = QString("DRIVER={Microsoft Excel Driver (*.xls, *.xlsx, *.xlsm, *.xlsb)};DSN='';FIRSTROWHASNAMES=1;READONLY=FALSE;CREATE_DB=\"%1\";DBQ=%2").
                  arg(filePath).arg(filePath);
    qDebug()<<dsn;
    dbexcel.setDatabaseName(dsn);

    // open connection
    if(!dbexcel.open())
    {
        qDebug()<<"无法打开数据库";
        return false;  //! db error
    }

    QSqlQuery query(dbexcel);
    QString sql;

    // drop the table if it's already exists
    sql = QString("DROP TABLE [%1]").arg(sheetName);
    query.exec( sql);
    //create the table (sheet in Excel file)
    sql = QString("CREATE TABLE [%1] (").arg(sheetName);
    foreach (QString name, headers) {
        sql +=QString("[%1] varchar(200)").arg(name);
        if(name!=headers.last())
            sql +=",";
    }
    sql += ")";
    query.prepare(sql);
    if( !query.exec()) {
        dbexcel.close();
        return false;
    }
    foreach (QStringList slist, data) {
        insert(query,sheetName,slist);
    }
    if(!comment.isEmpty())
    {
        QStringList slist;
        slist<<comment;
        for(int i=0,n=headers.size()-1;i<n;i++)
        {
            slist<<"";
        }
        insert(query,sheetName,slist);
    }

    dbexcel.close();
    return true;
}

bool MainWindow::insert(QSqlQuery &query, QString sheetName, QStringList slist)
{
    QString sSql = QString("INSERT INTO [%1] VALUES(").arg(sheetName);
    for(int i=0,n=slist.size();i<n;i++)
    {
        sSql+=QString(":%1").arg(i);
        if(i!=n-1)
            sSql+=",";
        else
            sSql+=")";
    }
    query.prepare(sSql);
    for(int i=0,n=slist.size();i<n;i++)
    {
        query.bindValue(QString(":%1").arg(i),slist.at(i));
    }
    if( !query.exec()) {

        return false;
    }
    return true;
}

bool MainWindow::createConnection(QString user, QString password, QString database,
                                  QString hostName, int port) {
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
