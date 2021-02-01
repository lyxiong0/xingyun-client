#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

    createConnection(user, password, database);
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
}
