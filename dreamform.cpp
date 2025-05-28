#include "dreamform.h"
#include "ui_dreamform.h"
#include <QTime>


dreamform::dreamform(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::dreamform)
    ,user("TestUser", 8701, "Sleep.txt")
{
    ui->setupUi(this);

    ui->lineEdit_date->setPlaceholderText("Введіть дату (dd/mm/yyyy)");
    ui->lineEdit_bedtime->setPlaceholderText("Введіть час засинання (hh:mm)");
    ui->lineEdit_wakeuptime->setPlaceholderText("Введіть час пробудження (hh:mm)");
}

dreamform::~dreamform()
{
    delete ui;
}


int convertTimeToMinutes(const QString& timeStr)
{
    QTime time = QTime::fromString(timeStr, "hh:mm");
    if (!time.isValid()) return -1; // або обробка помилки
    return time.hour() * 60 + time.minute();
}



void dreamform::on_AddDream_clicked()
{
    QString dateStr = ui->lineEdit_date->text();
    QString bedtimeStr = ui->lineEdit_bedtime->text();
    QString wakeStr = ui->lineEdit_wakeuptime->text();

    string date = dateStr.toStdString();
    int bedtime_minutes = convertTimeToMinutes(bedtimeStr);
    int wakeup_minutes = convertTimeToMinutes(wakeStr);


    user.addDream(date, bedtime_minutes, wakeup_minutes);

    QString entry = QString("Користувач: TestUser\nДата: %1\nЗасинання: %2 хв\nПробудження: %3 хв\n")
                        .arg(dateStr)
                        .arg(bedtime_minutes)
                        .arg(wakeup_minutes);

    ui->textEdit->append(entry);
}


void dreamform::on_UpdateButton_clicked()
{
    ui->textEdit->clear();

    user.loadDreams("Sleep.txt");

    vector<Dream> dreams = user.getDreamsForLastDays(10000);

    for (const auto& dream : dreams)
    {
        QString entry = dream.toQString();
        ui->textEdit->append(entry);
    }

}


void dreamform::on_BackButton_clicked()
{
    this->close();
}

