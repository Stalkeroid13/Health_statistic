#pragma once
#include <QMainWindow>
#include "bios.h"
#include "ideal_exercise_repository.h"
#include "exercise_model.h"
#include "physical_test.h"

QT_BEGIN_NAMESPACE
namespace Ui { class WorkoutWindow; }
QT_END_NAMESPACE

class WorkoutWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit WorkoutWindow(QWidget *parent = nullptr);
    ~WorkoutWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    // === Основні поля ===
    string fileName = "Exercise.txt";
    Ui::WorkoutWindow *ui;
    BIOS bios;
    IdealExerciseRepository idealRepo;
    PhysicalTest physicalTest;

    // === Основна логіка ===
    void loadExercises();
    void saveExercises();
    Workout createWorkoutFromTable();
    void evaluatePerformance();

    // === Додаткові можливості ===
    void showHelpDialog();
};
