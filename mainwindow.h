#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dreamform.h"
#include "foodform.h"
#include "messegefromdevs.h"
#include "workoutwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void GoToFoodForm();
    void GoToMessage();

    void on_pushButton_6_clicked();
    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    foodform *foodForm;
    MessegeFromDevs *message;
    dreamform *dreamForm;
    WorkoutWindow *workoutWindow;
};
#endif // MAINWINDOW_H
