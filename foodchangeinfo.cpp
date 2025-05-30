#include "foodchangeinfo.h"
#include "ui_foodchangeinfo.h"
#include <QMessageBox>

FoodChangeInfo::FoodChangeInfo(FoodStatistics* stats, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FoodChangeInfo)
    , mainFoodObject(stats)
{
    ui->setupUi(this);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &FoodChangeInfo::deleteDiary);
    connect(ui->pushButton, &QPushButton::clicked, this, &FoodChangeInfo::deleteList);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &FoodChangeInfo::changeDiary);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &FoodChangeInfo::changeList);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &FoodChangeInfo::deleteSpecificDiary);
}

//змінюємо запис у щоденнику харчування
void FoodChangeInfo::changeDiary()
{
    //зчитуємо усю необхідну інформацію
    QString timeQ = ui->lineEdit_12->text();
    QString nameOldQ = ui->lineEdit_26->text();
    QString weightOldQ = ui->lineEdit_29->text();
    QString nameNewQ = ui->lineEdit_27->text();
    QString weightNewQ = ui->lineEdit_28->text();
    if(timeQ.isEmpty() || nameOldQ.isEmpty() || weightOldQ.isEmpty() ||
        nameNewQ.isEmpty() || weightNewQ.isEmpty())
    {
        QMessageBox::warning(this, "Помилка", "Усі поля дії мають бути заповненими");
        return;
    }

    nameOldQ.replace(" ", "_");
    nameNewQ.replace(" ", "_");

    //формуємо повні рядки, що відповідають новому та старому запису відповідно
    string newValue = nameNewQ.toStdString() + " " + weightNewQ.toStdString();
    string oldValue = nameOldQ.toStdString() + " " + weightOldQ.toStdString();

    //викликаємо функцію заміни
    mainFoodObject->nutrition_diary_.ChangeNoteAboutFood(timeQ.toStdString(), oldValue, newValue);

    //очищуємо поля вводу
    ui->lineEdit_12->clear();
    ui->lineEdit_26->clear();
    ui->lineEdit_27->clear();
    ui->lineEdit_28->clear();
    return;
}

//змінюємо запис у списку продуктів
void FoodChangeInfo::changeList()
{
    //зчитуємо усю необхідну інформацію
    QString foodName = ui->lineEdit_4->text();
    QString foodCalorie = ui->lineEdit_5->text();
    QString foodProteins = ui->lineEdit_6->text();
    QString foodFats = ui->lineEdit_3->text();
    QString foodCarbohydrates = ui->lineEdit_7->text();
    QString foodWeight = ui->lineEdit_8->text();

    if(foodCalorie.isEmpty() || foodName.isEmpty() || foodWeight.isEmpty() ||
        foodProteins.isEmpty() || foodFats.isEmpty() || foodCarbohydrates.isEmpty())
    {
        QMessageBox::warning(this, "Помилка", "Усі поля дії мають бути заповненими");
        return;
    }

    foodName.replace(" ", "_");
    //формуємо об'єкт для заміни
    QString  fullQ = foodName + " " + foodCalorie + " " + foodProteins + " " + foodFats + " " + foodCarbohydrates + " " + foodWeight;

    //викликаємо функцію заміни
    mainFoodObject->nutrition_diary_.list_.Change(foodName.toStdString(), fullQ.toStdString());

    //очищуємо поля вводу
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
    ui->lineEdit_8->clear();
    return;
}

//видаляємо запис з щоденника по даті
void FoodChangeInfo::deleteDiary()
{
    //зчитуємо усю необхідну інформацію
    QString timeQ = ui->lineEdit_11->text();
    if(timeQ.isEmpty())
    {
        QMessageBox::warning(this, "Помилка", "Усі поля дії мають бути заповненими");
        return;
    }

    //викликаємо функцію видалення
    mainFoodObject->nutrition_diary_.DeleteNotesAboutFood(timeQ.toStdString());

    //очищуємо поля вводу
    ui->lineEdit_11->clear();
    return;
}

//видаляємо конкретний запис з щоденника (по даті та вмісту)
void FoodChangeInfo::deleteSpecificDiary()
{
    //зчитуємо усю необхідну інформацію
    QString timeQ = ui->lineEdit_13->text();
    QString nameQ = ui->lineEdit_14->text();
    QString weightQ = ui->lineEdit_30->text();

    if(timeQ.isEmpty() || nameQ.isEmpty() || weightQ.isEmpty())
    {
        QMessageBox::warning(this, "Помилка", "Усі поля дії мають бути заповненими");
        return;
    }

    nameQ.replace(" ", "_");
    //формуємо повний об'єкт для видалення
    string value = nameQ.toStdString() + " " + weightQ.toStdString();

    //викликаємо функцію видалення
    mainFoodObject->nutrition_diary_.DeleteOneNoteAboutFood(timeQ.toStdString(), value);

    //очищуємо поля вводу
    ui->lineEdit_13->clear();
    ui->lineEdit_14->clear();
    ui->lineEdit_30->clear();
    return;
}

//видаляємо запис зі списку продуктів по назві продукті
void FoodChangeInfo::deleteList()
{
    //зчитуємо усю необхідну інформацію
    QString nameQ = ui->lineEdit_2->text();
    if(nameQ.isEmpty())
    {
        QMessageBox::warning(this, "Помилка", "Усі поля дії мають бути заповненими");
        return;
    }

    nameQ.replace(" ", "_");

    //викликаємо функцію видалення
    mainFoodObject->nutrition_diary_.list_.Remove(nameQ.toStdString());

    //очищуємо поля вводу
    ui->lineEdit_2->clear();
    return;
}

FoodChangeInfo::~FoodChangeInfo()
{
    delete ui;
}
