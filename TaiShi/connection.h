#ifndef CONNECTION_H
#define CONNECTION_H
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

static bool createConnection(QString user, QString password, QString database)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setPort(3306);
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
    QSqlQuery query(db);
    QMessageBox::information(0, QString("Information"),
    "已成功连接所选数据库！", QMessageBox::Ok);
    return true;
}

#endif // CONNECTION_H
