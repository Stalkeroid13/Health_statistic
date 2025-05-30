#include "workoutwindow.h"
#include "ui_workoutwindow.h"
#include "performance_evaluator.h"
#include "exercisefactory.h"

#include <QCloseEvent>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <sstream>

WorkoutWindow::WorkoutWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WorkoutWindow)
{
    ui->setupUi(this);

    ui->table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->table->setEditTriggers(QAbstractItemView::AllEditTriggers);
    connect(ui->evaluateButton, &QPushButton::clicked, this, &WorkoutWindow::evaluatePerformance);

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

WorkoutWindow::~WorkoutWindow()
{
    delete ui;
    physicalTest = PhysicalTest
    {
        70,    // вага
        175,   // зріст
        25,    // відтискання
        35,    // присідання
        90,    // планка (сек)
        5,     // тест Купера (км)
        2,     // гнучкість (1–3)
        180    // стрибок в довжину (см)
    };
    idealRepo.LoadFromFile("ideal_exercises.txt");
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

Workout WorkoutWindow::createWorkoutFromTable()
{
    QDate date = ui->dateEdit_from->date();
    Workout workout(date.toString("dd.MM.yyyy").toStdString());

    for (int row = 0; row < ui->table->rowCount(); ++row)
    {
        QString name_ukr = ui->table->item(row, 1)->text().trimmed();  // тепер — УКРАЇНСЬКА назва
        int reps = ui->table->item(row, 3)->text().toInt();
        int sets = ui->table->item(row, 4)->text().toInt();

        std::string key = idealRepo.GetKeyByUkrName(name_ukr.toStdString());
        if (key.empty()) continue;

        const ExerciseMeta* meta = idealRepo.Get(key);
        if (!meta) continue;

        Exercise ex(key, meta->name_ukr, meta->category, reps, sets);
        workout.AddExercise(ex);
    }

    return workout;
}

void WorkoutWindow::evaluatePerformance()
{
    Workout w = createWorkoutFromTable();
    PerformanceEvaluator evaluator(physicalTest);

    double totalScore = 0;
    int count = 0;

    for (const auto& ex : w.GetExercises()) {
        const ExerciseMeta* meta = idealRepo.Get(ex.GetKeyName());
        if (!meta) continue;

        double score = evaluator.EvaluateScore(ex, *meta);
        totalScore += score;
        ++count;
    }

    double average = (count == 0) ? 0.0 : totalScore / count;

    QString resultText = QString("Оцінка: %1 / 100").arg(QString::number(average, 'f', 1));
    ui->label_score->setText(resultText);
}
