#ifndef QUSHUIYIN_H
#define QUSHUIYIN_H

#include <QDialog>

namespace Ui {
class qushuiyin;
}

class qushuiyin : public QDialog
{
    Q_OBJECT

public:
    explicit qushuiyin(QWidget *parent = nullptr);
    ~qushuiyin();

private:
    Ui::qushuiyin *ui;
};

#endif // QUSHUIYIN_H
