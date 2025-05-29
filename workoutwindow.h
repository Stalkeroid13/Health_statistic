#ifndef WORKOUTWINDOW_H
#define WORKOUTWINDOW_H

#include <QMainWindow>
#include "bios.h"

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
    void loadExercises();
    void saveExercises();

    string fileName = "Exercise.txt";
    Ui::WorkoutWindow *ui;
    BIOS bios;
};

#endif // WORKOUTWINDOW_H
