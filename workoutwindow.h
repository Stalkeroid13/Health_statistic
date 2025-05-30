#ifndef WORKOUTWINDOW_H
#define WORKOUTWINDOW_H

#include <QMainWindow>
#include "bios.h"
#include "ideal_exercise_repository.h"
#include "workout.h"
#include "physical_test.h"

QT_BEGIN_NAMESPACE
namespace Ui { class WorkoutWindow; }
QT_END_NAMESPACE

class WorkoutWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit WorkoutWindow(QWidget *parent = nullptr);
    ~WorkoutWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    void loadExercises();
    void saveExercises();

    string fileName = "Exercise.txt";
    Ui::WorkoutWindow *ui;
    BIOS bios;

    Workout createWorkoutFromTable();
    void evaluatePerformance();

    IdealExerciseRepository idealRepo;
    PhysicalTest physicalTest;
};

#endif // WORKOUTWINDOW_H
