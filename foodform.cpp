#include "foodform.h"
#include "ui_foodform.h"
#include "foodchangeinfo.h"
#include <QStandardItem>
#include <QStandardItemModel>

foodform::foodform(int sex, int height, int weight, int age, QWidget *parent)
    : QDialog(parent), m_sex(sex), m_height(height), m_weight(weight), m_age(age)
    , ui(new Ui::foodform)
{
    ui->setupUi(this);
    food_list_object.nutrition_diary_.diary_.LoadDataFromFile("DiaryFood.txt");
    food_list_object.nutrition_diary_.list_.DownloadData();
    connect(ui->pushButton_2, &QPushButton::clicked, this, &foodform::updateList);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &foodform::addNoteToList);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &foodform::toChangeForm);
    connect(ui->pushButton_7, &QPushButton::clicked, this, &foodform::updateDiary);
    connect(ui->pushButton_6, &QPushButton::clicked, this, &foodform::addNoteToDiary);
    connect(ui->pushButton, &QPushButton::clicked, this, &foodform::generateTotalScore);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &foodform::closeWindow);
    updateDiary();
    updateList();
    ui->label_4->setText(" ");
}

foodform::~foodform()
{
    food_list_object.nutrition_diary_.diary_.WriteDataToFile("DiaryFood.txt");
    food_list_object.nutrition_diary_.list_.UploadData();
    delete ui;
}


void foodform::toChangeForm()
{
    foodChangeInfoWindow = new FoodChangeInfo(&food_list_object, this);
    foodChangeInfoWindow->show();
}

void foodform::closeWindow()
{
    this->close();
}

float foodform::generateTotalScore()
{
    //зчитуємо усю необхідну інформацію
    QString startTime = ui->lineEdit_7->text();
    QString endTime = ui->lineEdit_8->text();
    int strategy = ui->spinBox->value();

    // викликаємо функцію визначення оцінки
    float score=food_list_object.GetStatistics(m_sex, m_weight, m_height, m_age, startTime.toStdString(), endTime.toStdString(), strategy);
    ui->label_5->setText(QString::number(score,'f', 2));

    return score;
}

void foodform::addNoteToList()
{
    //зчитуємо усю необхідну інформацію
    QString foodName = ui->lineEdit->text();
    QString foodCalorie = ui->lineEdit_2->text();
    QString foodProteins = ui->lineEdit_3->text();
    QString foodFats = ui->lineEdit_4->text();
    QString foodCarbohydrates = ui->lineEdit_5->text();
    QString foodWeight = ui->lineEdit_6->text();

    QString  fullQ = foodName + " " + foodCalorie + " " + foodProteins + " " + foodFats + " " + foodCarbohydrates + " " + foodWeight;
    food_list_object.nutrition_diary_.list_.Add(fullQ.toStdString());

    //очищуємо поля вводу
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
}

void foodform::addNoteToDiary()
{
    //зчитуємо усю необхідну інформацію
    QString timeQ = ui->lineEdit_10->text();
    QString foodName = ui->lineEdit_9->text();
    QString foodWeight = ui->lineEdit_14->text();

    QString  fullQ = foodName + " " + foodWeight;

    if (food_list_object.nutrition_diary_.list_.Read(foodName.toStdString())=="Not found")
    {
        ui->label_4->setText("Cant be added because not found in product list");
    }
    else
    {
        food_list_object.nutrition_diary_.AddNoteAboutFood(timeQ.toStdString(), fullQ.toStdString());
    }

    //очищуємо поля вводу
    ui->lineEdit_10->clear();
    ui->lineEdit_9->clear();
    ui->lineEdit_14->clear();
}

//оновлюємо список продуктів
void foodform::updateList()
{
    auto *model = new QStandardItemModel(this);
    model->setColumnCount(1);
    model->setHorizontalHeaderLabels({"Інформація"});
    ui->tableView->setStyleSheet("QTableView { color: black; }");
    ui->tableView->setShowGrid(true);

    //заповнюємо таблицю
    int row = 0;
    for (const auto& [name, fullString] : food_list_object.nutrition_diary_.list_.catalogue_) {
        //model->setItem(row, 0, new QStandardItem(QString::fromStdString(name)));
        model->setItem(row, 0, new QStandardItem(QString::fromStdString(fullString)));
        ++row;
    }

    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(0, 368);
}

//оновлюємо щоденник харчування
void foodform::updateDiary()
{
    auto *model = new QStandardItemModel(this);
    model->setColumnCount(2);
    model->setHorizontalHeaderLabels({"Час", "Запис"});
    ui->tableView_2->setShowGrid(true);

    //заповнюємо таблицю
    int row = 0;
    for (const auto& [time, fullString] : food_list_object.nutrition_diary_.diary_.general_map_) {
        model->setItem(row, 0, new QStandardItem(QString::fromStdString(time)));
        model->setItem(row, 1, new QStandardItem(QString::fromStdString(fullString)));
        ++row;
    }

    ui->tableView_2->setModel(model);
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);

    ui->tableView_2->setColumnWidth(0, 92);
    ui->tableView_2->setColumnWidth(1, 276);
}
