// workoutwindow.cpp
#include "workoutwindow.h"
#include "ui_workoutwindow.h"

#include <QCloseEvent>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <sstream>

WorkoutWindow::WorkoutWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WorkoutWindow)
{
    ui->setupUi(this);

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

void WorkoutWindow::loadExercises() {
    ui->table->setRowCount(0);
    string date = ui->dateEdit->date().toString("yyyy-MM-dd").toStdString();
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
}

void WorkoutWindow::saveExercises() {
    string date = ui->dateEdit->date().toString("yyyy-MM-dd").toStdString();
    bios.RemoveEntry(date);

    for (int row = 0; row < ui->table->rowCount(); ++row) {
        string name = ui->table->item(row, 1)->text().toStdString();
        string muscle = ui->table->item(row, 2)->text().toStdString();
        int reps = ui->table->item(row, 3)->text().toInt();
        int sets = ui->table->item(row, 4)->text().toInt();

        stringstream entry;
        entry << name << " " << muscle << " " << reps << " " << sets;
        bios.AddEntry(date, entry.str());
    }

    bios.WriteDataToFile("Exercise.txt");
}

void WorkoutWindow::closeEvent(QCloseEvent *event) {
    saveExercises();
    QMainWindow::closeEvent(event);
}
