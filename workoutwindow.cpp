#include "workoutwindow.h"
#include "ui_workoutwindow.h"
#include "physical_test.h"
#include "physicaltestwindow.h"
#include "string_utils.h"

#include <QCloseEvent>
#include <QMessageBox>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QFile>
#include <sstream>
#include <algorithm>

// --- Завантаження фізичного профілю з файлу ---

PhysicalTest LoadPhysicalTestFromFile(const QString& filename)
{
    QFile file(filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream in(&file);
    int pu, sd, plank, flex, coop, jump;
    in >> pu >> sd >> plank >> flex >> coop >> jump;

    file.close();
    return PhysicalTest{pu, sd, plank, flex, coop, jump};
}

// --- Конструктор головного вікна ---

WorkoutWindow::WorkoutWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WorkoutWindow)
{
    // Ініціалізація інтерфейсу
    ui->setupUi(this);

    // Початкові значення дат
    ui->dateEdit_from->setDate(QDate::currentDate());
    ui->dateEdit_to->setDate(QDate::currentDate().addDays(-1));

    // Параметри таблиці
    ui->table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->table->setEditTriggers(QAbstractItemView::AllEditTriggers);

    // Завантаження початкових даних
    physicalTest = LoadPhysicalTestFromFile("profile.txt");
    idealRepo.LoadFromFile("ideal_exercises.txt");

    // Кнопка "Додати запис" — новий рядок із сьогоднішньою датою
    connect(ui->addButton, &QPushButton::clicked, this, [=]() {
        int row = ui->table->rowCount();
        ui->table->insertRow(row);
        ui->table->setItem(row, 0, new QTableWidgetItem(ui->dateEdit_from->date().toString("dd.MM.yyyy")));
    });

    // Кнопка "Зберегти" — запис у файл
    connect(ui->saveButton, &QPushButton::clicked, this, &WorkoutWindow::saveExercises);

    // Кнопка "Дати оцінку" — виклик функції оцінювання
    connect(ui->evaluateButton, &QPushButton::clicked, this, &WorkoutWindow::evaluatePerformance);

    // Чекбокс діапазону — увімкнення другого поля дати + оновлення таблиці
    connect(ui->checkBox_range, &QCheckBox::toggled, this, [this](bool) {
        ui->dateEdit_to->setEnabled(ui->checkBox_range->isChecked());
        loadExercises();
    });

    // Реакція на зміну дат — перезавантаження даних
    connect(ui->dateEdit_from, &QDateEdit::dateChanged, this, [this](const QDate &) { loadExercises(); });
    connect(ui->dateEdit_to, &QDateEdit::dateChanged, this, [this](const QDate &) { loadExercises(); });

    // Кнопка "Памʼятка" — відкриває перелік вправ
    connect(ui->helpButton, &QPushButton::clicked, this, &WorkoutWindow::showHelpDialog);

    // Кнопка "Фізичні дані" — форма з фізичними тестами
    connect(ui->openProfileButton, &QPushButton::clicked, this, [=]() {
        auto* form = new PhysicalTestWindow(this);
        form->loadFromFile();
        form->show();
    });

    // Завантаження тренувань у таблицю
    loadExercises();
}

WorkoutWindow::~WorkoutWindow()
{
    delete ui;
}

// Завантаження вправ із хеш-таблиці BIOS
void WorkoutWindow::loadExercises()
{
    bios.LoadDataFromFile(fileName);
    ui->table->setRowCount(0);

    QDate start = ui->dateEdit_from->date();
    QDate end = ui->checkBox_range->isChecked() ? ui->dateEdit_to->date() : start;

    QDate current = start;
    while (current >= end)
    {
        // Отримати вправи за поточну дату
        string date = current.toString("dd.MM.yyyy").toStdString();
        for (const auto& entry : bios.GetValues(date))
        {
            // Розбір запису з тексту
            istringstream ss(entry);
            string name_key, muscle;
            int reps, sets;
            ss >> name_key >> muscle >> reps >> sets;

            // Отримати українську назву (якщо знайдено)
            const ExerciseMeta* meta = idealRepo.Get(name_key);
            QString name_ukr = meta
                                   ? DesanitizeToQString(meta->name_ukr)
                                   : DesanitizeToQString(name_key);

            // Додати новий рядок у таблицю
            int row = ui->table->rowCount();
            ui->table->insertRow(row);
            ui->table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(date)));
            ui->table->setItem(row, 1, new QTableWidgetItem(name_ukr));
            ui->table->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(DesanitizeName(muscle))));
            ui->table->setItem(row, 3, new QTableWidgetItem(QString::number(reps)));
            ui->table->setItem(row, 4, new QTableWidgetItem(QString::number(sets)));
        }

        current = current.addDays(-1);
    }
}

// Збереження всіх вправ у файл через BIOS
void WorkoutWindow::saveExercises()
{
    vector<string> cleared;

    for (int row = 0; row < ui->table->rowCount(); ++row)
    {
        // Отримати дані з таблиці
        auto* dateItem = ui->table->item(row, 0);
        auto* nameItem = ui->table->item(row, 1);
        auto* muscleItem = ui->table->item(row, 2);
        auto* repsItem = ui->table->item(row, 3);
        auto* setsItem = ui->table->item(row, 4);

        // Пропустити, якщо щось не заповнено
        if (!dateItem || !nameItem || !muscleItem || !repsItem || !setsItem)
            continue;
        if (nameItem->text().trimmed().isEmpty())
            continue;

        // Нормалізація і перевірка назви вправи
        QString name_ukr = nameItem->text().trimmed();
        string key = idealRepo.GetKeyByUkrName(NormalizeUkrainianName(name_ukr.toStdString()));

        if (key.empty())
        {
            QMessageBox::warning(this, "Помилка", "Невідома вправа: " + name_ukr);
            continue;
        }

        // Якщо ця дата ще не очищена - видалити попередні записи
        string date = dateItem->text().toStdString();
        if (std::find(cleared.begin(), cleared.end(), date) == cleared.end())
        {
            bios.RemoveEntry(date);
            cleared.push_back(date);
        }

        // Зібрати новий запис
        stringstream ss;
        ss << key << " "
           << NormalizeUkrainianName(muscleItem->text().toStdString()) << " "
           << repsItem->text().toInt() << " "
           << setsItem->text().toInt();

        // Додати запис до BIOS
        bios.AddEntry(date, ss.str());
    }
}

// Створення об'єкта Workout з таблиці
Workout WorkoutWindow::createWorkoutFromTable()
{
    QDate date = ui->dateEdit_from->date();
    Workout workout(date.toString("dd.MM.yyyy").toStdString());

    for (int row = 0; row < ui->table->rowCount(); ++row)
    {
        // Отримати необхідні клітинки
        auto* nameItem = ui->table->item(row, 1);
        auto* repsItem = ui->table->item(row, 3);
        auto* setsItem = ui->table->item(row, 4);

        if (!nameItem || !repsItem || !setsItem)
            continue;

        // Нормалізована назва вправи
        QString name_ukr = nameItem->text().trimmed();
        string key = idealRepo.GetKeyByUkrName(name_ukr.toStdString());

        if (key.empty())
        {
            QMessageBox::warning(this, "Помилка", "Невідома вправа: " + name_ukr);
            continue;
        }

        // Отримати мета-дані
        const ExerciseMeta* meta = idealRepo.Get(key);
        if (!meta)
            continue;

        // Створити об'єкт вправи
        Exercise ex(key, meta->name_ukr, meta->category,
                    repsItem->text().toInt(), setsItem->text().toInt());

        workout.AddExercise(ex);
    }

    return workout;
}

// Оцінювання усіх вправ у таблиці
void WorkoutWindow::evaluatePerformance()
{
    Workout w = createWorkoutFromTable();
    double total = 0;
    int count = 0;

    // Накопичення оцінок за всі вправи
    for (const auto& ex : w.GetExercises())
    {
        const ExerciseMeta* meta = idealRepo.Get(ex.GetKeyName());
        if (!meta)
            continue;

        total += EvaluateScore(ex, *meta, physicalTest);
        ++count;
    }

    // Розрахунок середнього значення
    double avg = count ? total / count : 0;
    ui->label_score->setText(QString("Оцінка: %1 / 100").arg(QString::number(avg, 'f', 1)));
}

// Подія закриття вікна
void WorkoutWindow::closeEvent(QCloseEvent *event)
{
    ui->table->setCurrentCell(-1, -1);
    saveExercises();
    bios.WriteDataToFile(fileName);
    QMainWindow::closeEvent(event);
}

// Отримання одиниці виміру за категорією вправи
QString GetUnitLabel(ExerciseCategory cat)
{
    using C = ExerciseCategory;
    switch (cat)
    {
    case C::CardioIntense:
    case C::CardioLight:
    case C::Speed:
    case C::Flexibility:
    case C::Balance:
    case C::CoreIsometric:
        return "сек";
    case C::CooperTest:
        return "км";
    default:
        return "разів";
    }
}

// Вікно пам'ятки з переліком вправ
void WorkoutWindow::showHelpDialog()
{
    QString message = "Список доступних вправ:\n\n";

    for (const auto& [key, meta] : idealRepo.GetAll())
    {
        QString name = DesanitizeToQString(meta.name_ukr);
        QString unit = GetUnitLabel(meta.category);
        message += QString("- %1 (%2)\n").arg(name, unit);
    }

    QMessageBox::information(this, "Памʼятка вправ", message);
}
