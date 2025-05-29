#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::GoToMessage);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::GoToFoodForm);
    connect(ui->pushButton_6, &QPushButton::clicked, this, &MainWindow::GoToDream);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//перехід до категорії харчування
void MainWindow::GoToFoodForm()
{
    foodForm = new foodform(this);
    //foodForm->setAttribute(Qt::WA_DeleteOnClose);
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

void MainWindow::on_pushButton_5_clicked()
{
    workoutWindow = new WorkoutWindow(this);
    workoutWindow->setAttribute(Qt::WA_DeleteOnClose);
    workoutWindow->show();
}
