// workoutwindow.cpp
#include "workoutwindow.h"
#include "ui_workoutwindow.h"

#include <QCloseEvent>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <sstream>
#include <QDebug>

WorkoutWindow::WorkoutWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WorkoutWindow)
{
    ui->setupUi(this);

    connect(ui->saveButton, &QPushButton::clicked, this, &WorkoutWindow::saveExercises);

    connect(ui->dateEdit, &QDateEdit::dateChanged, this, [this](const QDate &newDate) {
        saveExercises();
        loadExercises();
    });

    ui->table->setColumnCount(5);
    ui->table->setHorizontalHeaderLabels({"Дата", "Вправа", "М'язи", "Повторення", "Підходи"});
    ui->table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->table->setEditTriggers(QAbstractItemView::AllEditTriggers);

    connect(ui->addButton, &QPushButton::clicked, this, [=]() {
        int row = ui->table->rowCount();
        ui->table->insertRow(row);
        ui->table->setItem(row, 0, new QTableWidgetItem(ui->dateEdit->date().toString("yyyy-MM-dd")));
    });

    loadExercises();
}

WorkoutWindow::~WorkoutWindow() {
    delete ui;
}

void WorkoutWindow::loadExercises()
{
    ui->table->setRowCount(0);
    string date = ui->dateEdit->date().toString("yyyy-MM-dd").toStdString();

    bios.LoadDataFromFile(fileName);
    auto entries = bios.GetValues(date);

    for (const auto& entry : entries) {
        istringstream ss(entry);
        string name, muscle;
        int reps, sets;
        ss >> name >> muscle >> reps >> sets;

        int row = ui->table->rowCount();
        ui->table->insertRow(row);
        ui->table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(date)));
        ui->table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(name)));
        ui->table->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(muscle)));
        ui->table->setItem(row, 3, new QTableWidgetItem(QString::number(reps)));
        ui->table->setItem(row, 4, new QTableWidgetItem(QString::number(sets)));
    }

    qDebug() << "Loaded entries for date:" << QString::fromStdString(date)
             << ", count:" << entries.size();
}

void WorkoutWindow::saveExercises()
{
    bios.LoadDataFromFile(fileName);

    string date = ui->dateEdit->date().toString("yyyy-MM-dd").toStdString();
    bios.RemoveEntry(date);

    for (int row = 0; row < ui->table->rowCount(); ++row) {
        QTableWidgetItem* nameItem   = ui->table->item(row, 1);
        QTableWidgetItem* muscleItem = ui->table->item(row, 2);
        QTableWidgetItem* repsItem   = ui->table->item(row, 3);
        QTableWidgetItem* setsItem   = ui->table->item(row, 4);

        if (!nameItem || !muscleItem || !repsItem || !setsItem ||
            nameItem->text().isEmpty() ||
            muscleItem->text().isEmpty() ||
            repsItem->text().isEmpty() ||
            setsItem->text().isEmpty()) {
            qDebug() << "Пропускаємо незаповнений рядок:" << row;
            continue;
        }

        string name   = nameItem->text().toStdString();
        string muscle = muscleItem->text().toStdString();
        int reps      = repsItem->text().toInt();
        int sets      = setsItem->text().toInt();

        stringstream entry;
        entry << name << " " << muscle << " " << reps << " " << sets;
        bios.AddEntry(date, entry.str());
    }

    bios.WriteDataToFile(fileName);
}


void WorkoutWindow::closeEvent(QCloseEvent *event)
{
    ui->table->setCurrentCell(-1, -1);
    saveExercises();
    QMainWindow::closeEvent(event);
}



