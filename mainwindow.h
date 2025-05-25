#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "foodform.h"
#include "messegefromdevs.h"

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

private:
    Ui::MainWindow *ui;
    foodform *foodForm;
    MessegeFromDevs *message;
};
#endif // MAINWINDOW_H
