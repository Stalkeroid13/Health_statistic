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

    connect(ui->checkBox_range, &QCheckBox::toggled, this, [this](bool checked) {
        ui->dateEdit_to->setEnabled(checked);
        loadExercises();
    });

    connect(ui->dateEdit_from, &QDateEdit::dateChanged, this, [this](const QDate &) {
        loadExercises();
    });

    connect(ui->dateEdit_to, &QDateEdit::dateChanged, this, [this](const QDate &) {
        loadExercises();
    });

    connect(ui->addButton, &QPushButton::clicked, this, [=]() {
        int row = ui->table->rowCount();
        ui->table->insertRow(row);
        ui->table->setItem(row, 0, new QTableWidgetItem(ui->dateEdit_from->date().toString("dd.MM.yyyy")));
    });

    connect(ui->saveButton, &QPushButton::clicked, this, &WorkoutWindow::saveExercises);

    loadExercises();
}

WorkoutWindow::~WorkoutWindow() {
    delete ui;
}

auto sanitize = [](const QString& text) {
    return text.trimmed().replace(" ", "_").toStdString();
};

auto desanitize = [](const string& text) {
    string result = text;
    replace(result.begin(), result.end(), '_', ' ');
    return result;
};

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
        string dateStr = current.toString("dd.MM.yyyy").toStdString();
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
            ui->table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(desanitize(name))));
            ui->table->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(desanitize(muscle))));
            ui->table->setItem(row, 3, new QTableWidgetItem(QString::number(reps)));
            ui->table->setItem(row, 4, new QTableWidgetItem(QString::number(sets)));
        }

        current = current.addDays(-1);
    }
}

void WorkoutWindow::saveExercises()
{
    vector<string> alreadyClearedDates;

    for (int row = 0; row < ui->table->rowCount(); ++row) {
        auto* dateItem = ui->table->item(row, 0);
        auto* nameItem = ui->table->item(row, 1);
        auto* muscleItem = ui->table->item(row, 2);
        auto* repsItem = ui->table->item(row, 3);
        auto* setsItem = ui->table->item(row, 4);

        if (!dateItem || !nameItem || !muscleItem || !repsItem || !setsItem) continue;
        if (dateItem->text().isEmpty() || nameItem->text().isEmpty() ||
            muscleItem->text().isEmpty() || repsItem->text().isEmpty() ||
            setsItem->text().isEmpty()) continue;

        string date = dateItem->text().toStdString();

        if (std::find(alreadyClearedDates.begin(), alreadyClearedDates.end(), date) == alreadyClearedDates.end())
        {
            bios.RemoveEntry(date);
            alreadyClearedDates.push_back(date);
        }

        stringstream entry;
        entry << sanitize(nameItem->text()) << " "
              << sanitize(muscleItem->text()) << " "
              << repsItem->text().toInt() << " "
              << setsItem->text().toInt();


        bios.AddEntry(date, entry.str());
    }
}

void WorkoutWindow::closeEvent(QCloseEvent *event)
{
    ui->table->setCurrentCell(-1, -1);
    saveExercises();
    bios.WriteDataToFile(fileName);
    QMainWindow::closeEvent(event);
}
