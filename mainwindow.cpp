#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::GoToMessage);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::GoToFood);
    connect(ui->pushButton_6, &QPushButton::clicked, this, &MainWindow::GoToDream);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &MainWindow::GoToSport);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::GoToFood()
{
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
