#include "mainwindow.h"
#include <QApplication>
#include <QFile>

class CLoadQSS
{
    public:
    static void setStyle(const QString &style)
    {
        QFile qss(style);
        qss.open(QFile::ReadOnly);
        qApp->setStyleSheet(qss.readAll());
        qss.close();
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CLoadQSS::setStyle(":/themes/Aqua.qss");
    MainWindow w;
    w.show();
    return a.exec();
}
