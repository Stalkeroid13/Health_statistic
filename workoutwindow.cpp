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

    connect(ui->checkBox_range, &QCheckBox::toggled, this, [this](bool checked) {
        ui->dateEdit_to->setEnabled(checked);
    });

    connect(ui->dateEdit_from, &QDateEdit::dateChanged, this, [this](const QDate &newDate) {
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
        ui->table->setItem(row, 0, new QTableWidgetItem(ui->dateEdit_from->date().toString("yyyy-MM-dd")));
    });

    loadExercises();
}

WorkoutWindow::~WorkoutWindow() {
    delete ui;
}

void WorkoutWindow::loadExercises()
{
    bios.LoadDataFromFile(fileName);
    ui->table->setRowCount(0);

    QDate startDate = ui->dateEdit_from->date();
    QDate endDate = startDate;

    if (ui->checkBox_range->isChecked())
        endDate = ui->dateEdit_to->date();

    QDate current = startDate;

    while (current >= endDate)
    {
        string dateStr = current.toString("yyyy-MM-dd").toStdString();
        auto entries = bios.GetValues(dateStr);

        for (const auto& entry : entries)
        {
            istringstream ss(entry);
            string name, muscle;
            int reps, sets;
            ss >> name >> muscle >> reps >> sets;

            int row = ui->table->rowCount();
            ui->table->insertRow(row);
            ui->table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(dateStr)));
            ui->table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(name)));
            ui->table->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(muscle)));
            ui->table->setItem(row, 3, new QTableWidgetItem(QString::number(reps)));
            ui->table->setItem(row, 4, new QTableWidgetItem(QString::number(sets)));
        }

        current = current.addDays(-1);
    }
}

void WorkoutWindow::saveExercises()
{
    bios.LoadDataFromFile(fileName);

    vector<string> alreadyClearedDates;

    for (int row = 0; row < ui->table->rowCount(); ++row) {
        QTableWidgetItem* dateItem   = ui->table->item(row, 0);
        QTableWidgetItem* nameItem   = ui->table->item(row, 1);
        QTableWidgetItem* muscleItem = ui->table->item(row, 2);
        QTableWidgetItem* repsItem   = ui->table->item(row, 3);
        QTableWidgetItem* setsItem   = ui->table->item(row, 4);

        if (!dateItem || !nameItem || !muscleItem || !repsItem || !setsItem) continue;
        if (dateItem->text().isEmpty() || nameItem->text().isEmpty() ||
            muscleItem->text().isEmpty() || repsItem->text().isEmpty() ||
            setsItem->text().isEmpty()) continue;

        string date   = dateItem->text().toStdString();

        // Якщо дату ще не очищали — видаляємо старі записи
        if (std::find(alreadyClearedDates.begin(), alreadyClearedDates.end(), date) == alreadyClearedDates.end()) {
            bios.RemoveEntry(date);
            alreadyClearedDates.push_back(date);
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



