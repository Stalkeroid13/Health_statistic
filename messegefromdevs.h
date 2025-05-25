#ifndef MESSEGEFROMDEVS_H
#define MESSEGEFROMDEVS_H

#include <QDialog>

namespace Ui {
class MessegeFromDevs;
}

class MessegeFromDevs : public QDialog
{
    Q_OBJECT

public:
    explicit MessegeFromDevs(QWidget *parent = nullptr);
    ~MessegeFromDevs();

private:
    Ui::MessegeFromDevs *ui;
};

#endif // MESSEGEFROMDEVS_H
