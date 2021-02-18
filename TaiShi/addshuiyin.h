#ifndef ADDSHUIYIN_H
#define ADDSHUIYIN_H
#include <QDialog>
#include <string>

namespace Ui {
class addshuiyin;
}

class addshuiyin : public QDialog
{
    Q_OBJECT

public:
    explicit addshuiyin(QWidget *parent = nullptr);
    ~addshuiyin();


private:
    Ui::addshuiyin *ui;
};

#endif // ADDSHUIYIN_H
