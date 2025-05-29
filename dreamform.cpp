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


QString minutesToHHMM(int totalMinutes)
{
    int hours = totalMinutes / 60;
    int minutes = totalMinutes % 60;
    return QString("%1:%2")
        .arg(hours, 2, 10, QLatin1Char('0'))
        .arg(minutes, 2, 10, QLatin1Char('0'));
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

    QString daysText = ui->lineEdit_days->text();
    int days = 10000;

    if (!daysText.isEmpty())
    {
        bool ok;
        int entered = daysText.toInt(&ok);
        if (ok && entered > 0)
        {
            days = entered;
        }
    }

    vector<Dream> dreams = user.getAllDreamsForLastDays(days);

    for (const Dream& dream : dreams)
    {
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);

        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(dream.getDate())));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(minutesToHHMM(dream.getBedtime())));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(minutesToHHMM(dream.getWakeUptime())));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(minutesToHHMM(dream.getDuration())));
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

    QString daysText = ui->lineEdit_days->text();
    int defaultDays = 30;  // Значення за замовчуванням
    int days = defaultDays;

    if (!daysText.isEmpty())
    {
        bool ok;
        int entered = daysText.toInt(&ok);
        if (ok && entered > 0)
        {
            days = entered;
        }
        else
        {
            ui->label_score->setText("Невірне значення днів");
            return;
        }
    }

    int score = user.getAssesment(days);
    ui->label_score->setText("Оцінка: " + QString::number(score));
}

