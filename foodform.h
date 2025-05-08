#ifndef FOODFORM_H
#define FOODFORM_H

#include <QDialog>
#include "foodlist.h"
#include "foodchangeinfo.h"

namespace Ui {
class foodform;
}

class foodform : public QDialog
{
    Q_OBJECT

public:
    explicit foodform(QWidget *parent = nullptr);
    //QString getFoodName()const;
    ~foodform();

private slots:
    void onSaveButtonClicked();
    void onSaveButtonClickedAdd();
    void onNextButtonClicked();

private:
    Ui::foodform *ui;
    FoodChangeInfo *foodChangeInfoWindow;
    FoodList food_list_object;
    void updateTable();
};

#endif // FOODFORM_H
