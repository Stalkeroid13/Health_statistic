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
    connect(ui->pushButton_2, &QPushButton::clicked, this, &foodform::onSaveButtonClicked);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &foodform::onSaveButtonClickedAdd);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &foodform::onNextButtonClicked);
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
    food_list_object.Add(full);
    ui->label_4->setText(foodName);
    //updateTable();
}

void foodform::onSaveButtonClicked()
{
    //QString foodName = ui->lineEdit->text();
    //ui->label_4->setText(foodName);
    updateTable();
}

void foodform::updateTable()
{
    auto *model = new QStandardItemModel(this); // вказуємо this — модель буде автоматично видалена разом з вікном
    model->setColumnCount(2);
    model->setHorizontalHeaderLabels({"Назва", "Рядок з файлу"});
    ui->tableView->setStyleSheet("QTableView { color: black; }");
    //ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    //ui->tableView->setStyleSheet("QTableView { gridline-color: #00FF00; }");
    ui->tableView->setShowGrid(true);


    int row = 0;

    for (const auto& [name, fullString] : food_list_object.catalogue_) {
        model->setItem(row, 0, new QStandardItem(QString::fromStdString(name)));
        model->setItem(row, 1, new QStandardItem(QString::fromStdString(fullString)));
        ++row;
    }

    // Прив’язуємо модель до TableView
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    ui->tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);

    ui->tableView->setColumnWidth(0, 100);
    ui->tableView->setColumnWidth(1, 200);
    //ui->tableView->resizeColumnsToContents();
}

/*QString foodform::getFoodName()const
{
    return ui->lineEdit->text();
}*/
