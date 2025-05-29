#include "dreamform.h"
#include "ui_dreamform.h"
#include <QTime>


dreamform::dreamform(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::dreamform)
    ,user("TestUser", 8701, "Sleep.txt")
{
    ui->setupUi(this);

    QPixmap pixmap(":/images/sobachka.png");
    ui->label_sobachka->setPixmap(pixmap);

    if (pixmap.isNull()) {
        qDebug() << "Не вдалося завантажити зображення";
    } else {
        qDebug() << "Зображення завантажено успішно";
    }



    ui->tableWidget->setColumnCount(5);
    QStringList headers = {"Дата", "Час засинання", "Час пробудження", "Тривалість", "Тип сну"};
    ui->tableWidget->setHorizontalHeaderLabels(headers);

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


}


void dreamform::on_UpdateButton_clicked()
{
    ui->tableWidget->setRowCount(0);

    if (!isDataLoaded)
    {
        user.loadDreams("Sleep.txt");
        isDataLoaded = true;
    }

    vector<Dream> dreams = user.getAllDreamsForLastDays(10000);

    for (const Dream& dream : dreams)
    {
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);

        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(dream.getDate())));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(dream.getBedtime()) + " хв"));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(dream.getWakeUptime()) + " хв"));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(dream.getDuration()) + " хв"));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(dream.getSleepType() ? "Нічний" : "Денний"));
    }

}


void dreamform::on_BackButton_clicked()
{
    this->close();
}


void dreamform::on_GenereteButton_clicked()
{
    if (!isDataLoaded)
    {
        user.loadDreams("Sleep.txt");
        isDataLoaded = true;
    }

    int score = user.getAssesment(30); // наприклад, за останні 30 днів

    ui->label_score->setText("Оцінка: " + QString::number(score));
}

