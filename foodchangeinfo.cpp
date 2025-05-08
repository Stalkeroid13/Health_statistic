#include "foodchangeinfo.h"
#include "ui_foodchangeinfo.h"

FoodChangeInfo::FoodChangeInfo(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FoodChangeInfo)
{
    ui->setupUi(this);
}

FoodChangeInfo::~FoodChangeInfo()
{
    delete ui;
}
