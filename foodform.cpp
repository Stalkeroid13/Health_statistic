#include "foodform.h"
#include "ui_foodform.h"
#include "foodchangeinfo.h"
#include <QStandardItem>
#include <QStandardItemModel>

foodform::foodform(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::foodform)
{
    ui->setupUi(this);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &foodform::updateList);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &foodform::onSaveButtonClickedAdd);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &foodform::onNextButtonClicked);
    connect(ui->pushButton_7, &QPushButton::clicked, this, &foodform::updateDiary);
    connect(ui->pushButton_6, &QPushButton::clicked, this, &foodform::addNoteInDiary);
    /*QPalette palette = ui->label->palette();
    palette.setColor(QPalette::WindowText, Qt::black);
    ui->label->setPalette(palette);*/
    // qApp->setStyleSheet("QLabel { color: black; }");
}

foodform::~foodform()
{
    delete ui;
}

void foodform::onNextButtonClicked()
{
    foodChangeInfoWindow = new FoodChangeInfo(this);
    foodChangeInfoWindow->show();
}

void foodform::onSaveButtonClickedAdd()
{
    QString foodName = ui->lineEdit->text();
    QString foodCalorie = ui->lineEdit_2->text();
    QString foodProteins = ui->lineEdit_3->text();
    QString foodFats = ui->lineEdit_4->text();
    QString foodCarbohydrates = ui->lineEdit_5->text();
    QString foodWeight = ui->lineEdit_6->text();
    QString  fullQ = foodName + " " + foodCalorie + " " + foodProteins + " " + foodFats + " " + foodCarbohydrates + " " + foodWeight;
    string full = fullQ.toStdString();
    food_list_object.nutrition_diary_.list_.Add(full);
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
    //ui->label_4->setText(foodName);
    //updateTable();
}

void foodform::addNoteInDiary()
{
    QString timeQ = ui->lineEdit_10->text();
    QString foodName = ui->lineEdit_9->text();
    QString foodWeight = ui->lineEdit_14->text();
    QString  fullQ = foodName + " " + foodWeight;
    string full = fullQ.toStdString();
    string time = timeQ.toStdString();
    food_list_object.nutrition_diary_.AddNoteAboutFood(time, full);
    ui->lineEdit_10->clear();
    ui->lineEdit_9->clear();
    ui->lineEdit_14->clear();
}

void foodform::updateList()
{
    updateTable();
}

void foodform::updateTable()
{
    auto *model = new QStandardItemModel(this);
    model->setColumnCount(2);
    model->setHorizontalHeaderLabels({"Назва", "Інформація"});
    ui->tableView->setStyleSheet("QTableView { color: black; }");
    //ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    //ui->tableView->setStyleSheet("QTableView { gridline-color: #00FF00; }");
    ui->tableView->setShowGrid(true);


    int row = 0;

    for (const auto& [name, fullString] : food_list_object.nutrition_diary_.list_.catalogue_) {
        model->setItem(row, 0, new QStandardItem(QString::fromStdString(name)));
        model->setItem(row, 1, new QStandardItem(QString::fromStdString(fullString)));
        ++row;
    }

    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    ui->tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);

    ui->tableView->setColumnWidth(0, 92);
    ui->tableView->setColumnWidth(1, 276);
    //ui->tableView->resizeColumnsToContents();
}

void foodform::updateDiary()
{
    updateDiaryTable();
}

void foodform::updateDiaryTable()
{
    auto *model = new QStandardItemModel(this);
    model->setColumnCount(2);
    model->setHorizontalHeaderLabels({"Час", "Запис"});
    ui->tableView_2->setStyleSheet("QTableView { color: black; }");
    //ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    //ui->tableView->setStyleSheet("QTableView { gridline-color: #00FF00; }");
    ui->tableView_2->setShowGrid(true);


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
    //ui->tableView->resizeColumnsToContents();
}
