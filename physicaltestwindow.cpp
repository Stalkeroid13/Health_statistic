#include "physicaltestwindow.h"
#include "ui_physicaltestwindow.h"

#include <QFile>
#include <QTextStream>
#include <QMessageBox>

// --- Конструктор інтерфейсу ---

PhysicalTestWindow::PhysicalTestWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PhysicalTestWindow)
{
    ui->setupUi(this);
    ui->table->insertRow(0);

    connect(ui->saveButton, &QPushButton::clicked, this, &PhysicalTestWindow::savePhysicalData);
}

PhysicalTestWindow::~PhysicalTestWindow()
{
    delete ui;
}

// Зберігає дані з таблиці у файл
void PhysicalTestWindow::savePhysicalData()
{
    QFile file("profile.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);

    QTextStream out(&file);
    QTableWidget* table = ui->table;

    // Прохід по всіх колонках рядка
    for (int col = 0; col < table->columnCount(); ++col)
    {
        QTableWidgetItem* item = table->item(0, col);
        QString value = item ? item->text().trimmed() : "";

        // Перевірка на порожні значення
        if (value.isEmpty())
        {
            QMessageBox::warning(this, "Помилка", "Усі поля повинні бути заповнені.");
            return;
        }

        out << value;

        if (col != table->columnCount() - 1)
            out << " ";
    }

    file.close();
    this->close();
}

// Завантажує дані з файлу у таблицю
void PhysicalTestWindow::loadFromFile(const QString& filename)
{
    QFile file(filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream in(&file);

    // Зчитування значень у перший рядок таблиці
    for (int col = 0; col < ui->table->columnCount(); ++col)
    {
        QString value;
        in >> value;

        QTableWidgetItem* item = new QTableWidgetItem(value);
        ui->table->setItem(0, col, item);
    }

    file.close();
}
