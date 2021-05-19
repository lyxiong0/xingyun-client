#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QTableView>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QSqlTableModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static bool createConnection(QString user, QString password, QString database,
                                 QString hostName="localhost", int port=3306);
    static void Table2ExcelByHtml(QTableView *table,QString title, QString fileName);

private slots:
    void on_btnConnect_clicked();

    void on_btnShow_clicked();


    void on_btnAnalyze_clicked();


    void on_btnOutExcel_clicked();

private:
    Ui::MainWindow *ui;
    QSqlTableModel *model;

};
#endif // MAINWINDOW_H
