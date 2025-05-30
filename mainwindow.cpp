#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::GoToMessage);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::GoToFood);
    connect(ui->pushButton_6, &QPushButton::clicked, this, &MainWindow::GoToDream);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &MainWindow::GoToSport);
    connect(ui->radioButton, &QRadioButton::toggled, this, [this](bool checked){
        if (checked)
            sex = 1;
    });

    connect(ui->radioButton_2, &QRadioButton::toggled, this, [this](bool checked){
        if (checked)
            sex = 2;
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::GoToFood()
{
    bool check1, check2, check3;
    QString heightText = ui->lineEdit->text().trimmed();
    QString weightText = ui->lineEdit_2->text().trimmed();
    QString ageText = ui->lineEdit_3->text().trimmed();
    if(heightText.isEmpty() || weightText.isEmpty() || ageText.isEmpty())
    {
        QMessageBox::warning(this, "Помилка", "Усі поля мають бути заповненими");
        return;
    }

    height = heightText.toInt(&check1);
    weight = weightText.toInt(&check2);
    age = ageText.toInt(&check3);
    if(!check1 || !check2 || !check3)
    {
        QMessageBox::warning(this, "Помилка", "Введіть коректне число");
        return;
    }

    foodForm = new foodform(sex, height, weight, age, this);
    foodForm->show();
}

//перехід до вікна "Від розробників"
void MainWindow::GoToMessage()
{
    message = new MessegeFromDevs(this);
    message->show();
}


void MainWindow::GoToDream()
{
    dreamForm = new dreamform(this);
    dreamForm->show();
}

void MainWindow::GoToSport()
{
    workoutWindow = new WorkoutWindow(this);
    workoutWindow->setAttribute(Qt::WA_DeleteOnClose);
    workoutWindow->show();
}
