#include "messegefromdevs.h"
#include "ui_messegefromdevs.h"

MessegeFromDevs::MessegeFromDevs(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MessegeFromDevs)
{
    ui->setupUi(this);
}

MessegeFromDevs::~MessegeFromDevs()
{
    delete ui;
}
