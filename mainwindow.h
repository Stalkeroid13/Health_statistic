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
    void GoToFood();
    void GoToMessage();
    void GoToDream();
    void GoToSport();

private:
    Ui::MainWindow *ui;
    foodform *foodForm;
    MessegeFromDevs *message;
    dreamform *dreamForm;
    WorkoutWindow *workoutWindow;
    int sex=2, height =190, age =145, weight = 52;
};
#endif // MAINWINDOW_H
