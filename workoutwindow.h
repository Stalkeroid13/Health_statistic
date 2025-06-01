#pragma once

#include <QMainWindow>
#include "bios.h"
#include "ideal_exercise_repository.h"
#include "exercise_model.h"
#include "physical_test.h"

QT_BEGIN_NAMESPACE
namespace Ui { class WorkoutWindow; }
QT_END_NAMESPACE

// Головне вікно тренувального додатку
class WorkoutWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit WorkoutWindow(QWidget *parent = nullptr);
    ~WorkoutWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    // Ім'я файлу з тренуваннями
    string fileName = "Exercise.txt";

    // Вказівник на інтерфейс
    Ui::WorkoutWindow *ui;

    // Джерела даних
    BIOS bios;
    IdealExerciseRepository idealRepo;
    PhysicalTest physicalTest;

    // Завантаження і збереження вправ
    void loadExercises();
    void saveExercises();

    // Створення об'єкта тренування
    Workout createWorkoutFromTable();

    // Оцінювання продуктивності
    void evaluatePerformance();

    // Вікно пам'ятки вправ
    void showHelpDialog();
};
