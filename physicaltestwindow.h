#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class PhysicalTestWindow; }
QT_END_NAMESPACE

// Вікно для введення фізичних даних користувача
class PhysicalTestWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PhysicalTestWindow(QWidget *parent = nullptr);
    ~PhysicalTestWindow();

    // Зберігає дані з таблиці у файл
    void savePhysicalData();

    // Завантажує дані з файлу у таблицю
    void loadFromFile(const QString& filename = "profile.txt");

private:
    Ui::PhysicalTestWindow *ui;
};
