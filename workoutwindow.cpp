#include "workoutwindow.h"
#include "ui_workoutwindow.h"
#include "performance_evaluator.h"
#include "exercisefactory.h"

#include <QCloseEvent>
#include <QMessageBox>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <sstream>
#include <algorithm>

WorkoutWindow::WorkoutWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WorkoutWindow)
{
    ui->setupUi(this);

    ui->table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->table->setEditTriggers(QAbstractItemView::AllEditTriggers);

    physicalTest = PhysicalTest{70, 175, 25, 35, 90, 5, 2, 180};
    idealRepo.LoadFromFile("ideal_exercises.txt");

    connect(ui->addButton, &QPushButton::clicked, this, [=]() {
        int row = ui->table->rowCount();
        ui->table->insertRow(row);
        ui->table->setItem(row, 0, new QTableWidgetItem(ui->dateEdit_from->date().toString("dd.MM.yyyy")));
    });

    connect(ui->saveButton, &QPushButton::clicked, this, &WorkoutWindow::saveExercises);
    connect(ui->evaluateButton, &QPushButton::clicked, this, &WorkoutWindow::evaluatePerformance);

    connect(ui->checkBox_range, &QCheckBox::toggled, this, [this](bool) {
        ui->dateEdit_to->setEnabled(ui->checkBox_range->isChecked());
        loadExercises();
    });

    connect(ui->dateEdit_from, &QDateEdit::dateChanged, this, [this](const QDate &) { loadExercises(); });
    connect(ui->dateEdit_to, &QDateEdit::dateChanged, this, [this](const QDate &) { loadExercises(); });

    loadExercises();
}

WorkoutWindow::~WorkoutWindow()
{
    delete ui;
}

auto sanitize = [](const QString& text) {
    return text.trimmed().replace(" ", "_").toStdString();
};

auto desanitize = [](const std::string& text) {
    std::string result = text;
    std::replace(result.begin(), result.end(), '_', ' ');
    return result;
};

void WorkoutWindow::loadExercises()
{
    bios.LoadDataFromFile(fileName);
    ui->table->setRowCount(0);

    QDate start = ui->dateEdit_from->date();
    QDate end = ui->checkBox_range->isChecked() ? ui->dateEdit_to->date() : start;

    QDate current = start;
    while (current >= end)
    {
        std::string date = current.toString("dd.MM.yyyy").toStdString();
        for (const auto& entry : bios.GetValues(date))
        {
            std::istringstream ss(entry);
            std::string name_key, muscle;
            int reps, sets;
            ss >> name_key >> muscle >> reps >> sets;

            const ExerciseMeta* meta = idealRepo.Get(name_key);
            QString name_ukr = meta ? QString::fromStdString(meta->name_ukr)
                                    : QString::fromStdString(name_key);

            int row = ui->table->rowCount();
            ui->table->insertRow(row);
            ui->table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(date)));
            ui->table->setItem(row, 1, new QTableWidgetItem(name_ukr));
            ui->table->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(desanitize(muscle))));
            ui->table->setItem(row, 3, new QTableWidgetItem(QString::number(reps)));
            ui->table->setItem(row, 4, new QTableWidgetItem(QString::number(sets)));
        }
        current = current.addDays(-1);
    }
}

void WorkoutWindow::saveExercises()
{
    std::vector<std::string> cleared;

    for (int row = 0; row < ui->table->rowCount(); ++row)
    {
        auto* dateItem = ui->table->item(row, 0);
        auto* nameItem = ui->table->item(row, 1);
        auto* muscleItem = ui->table->item(row, 2);
        auto* repsItem = ui->table->item(row, 3);
        auto* setsItem = ui->table->item(row, 4);

        if (!dateItem || !nameItem || !muscleItem || !repsItem || !setsItem) continue;
        if (nameItem->text().trimmed().isEmpty()) continue;

        QString name_ukr = nameItem->text().trimmed();
        std::string key = idealRepo.GetKeyByUkrName(name_ukr.toStdString());
        if (key.empty()) {
            QMessageBox::warning(this, "Помилка", "Невідома вправа: " + name_ukr);
            continue;
        }

        std::string date = dateItem->text().toStdString();
        if (std::find(cleared.begin(), cleared.end(), date) == cleared.end()) {
            bios.RemoveEntry(date);
            cleared.push_back(date);
        }

        std::stringstream ss;
        ss << key << " "
           << sanitize(muscleItem->text()) << " "
           << repsItem->text().toInt() << " "
           << setsItem->text().toInt();

        bios.AddEntry(date, ss.str());
    }
}

Workout WorkoutWindow::createWorkoutFromTable()
{
    QDate date = ui->dateEdit_from->date();
    Workout workout(date.toString("dd.MM.yyyy").toStdString());

    for (int row = 0; row < ui->table->rowCount(); ++row)
    {
        auto* nameItem = ui->table->item(row, 1);
        auto* repsItem = ui->table->item(row, 3);
        auto* setsItem = ui->table->item(row, 4);
        if (!nameItem || !repsItem || !setsItem) continue;

        QString name_ukr = nameItem->text().trimmed();
        std::string key = idealRepo.GetKeyByUkrName(name_ukr.toStdString());
        if (key.empty()) {
            QMessageBox::warning(this, "Помилка", "Невідома вправа: " + name_ukr);
            continue;
        }

        const ExerciseMeta* meta = idealRepo.Get(key);
        if (!meta) continue;

        Exercise ex(key, meta->name_ukr, meta->category, repsItem->text().toInt(), setsItem->text().toInt());
        workout.AddExercise(ex);
    }

    return workout;
}

void WorkoutWindow::evaluatePerformance()
{
    Workout w = createWorkoutFromTable();
    PerformanceEvaluator evaluator(physicalTest);

    double total = 0;
    int count = 0;

    for (const auto& ex : w.GetExercises())
    {
        const ExerciseMeta* meta = idealRepo.Get(ex.GetKeyName());
        if (!meta) continue;

        total += evaluator.EvaluateScore(ex, *meta);
        ++count;
    }

    double avg = count ? total / count : 0;
    ui->label_score->setText(QString("Оцінка: %1 / 100").arg(QString::number(avg, 'f', 1)));
}

void WorkoutWindow::closeEvent(QCloseEvent *event)
{
    ui->table->setCurrentCell(-1, -1);
    saveExercises();
    bios.WriteDataToFile(fileName);
    QMainWindow::closeEvent(event);
}
