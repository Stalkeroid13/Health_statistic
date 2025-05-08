#ifndef FOODCHANGEINFO_H
#define FOODCHANGEINFO_H

#include <QDialog>

namespace Ui {
class FoodChangeInfo;
}

class FoodChangeInfo : public QDialog
{
    Q_OBJECT

public:
    explicit FoodChangeInfo(QWidget *parent = nullptr);
    ~FoodChangeInfo();

private:
    Ui::FoodChangeInfo *ui;
};

#endif // FOODCHANGEINFO_H
