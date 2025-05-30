#ifndef FOODFORM_H
#define FOODFORM_H

#include <QDialog>
#include "bios.h"
#include "foodlist.h"
#include "foodchangeinfo.h"
#include "foodstatistics.h"

namespace Ui {
class foodform;
}

class foodform : public QDialog
{
    Q_OBJECT

public:
    explicit foodform(int sex, int height, int weight, int age, QWidget *parent = nullptr);
    ~foodform();

private slots:
    void updateList();
    void updateDiary();
    void addNoteToList();
    void toChangeForm();
    void addNoteToDiary();
    float generateTotalScore();
    void closeWindow();

private:
    Ui::foodform *ui;
    FoodChangeInfo *foodChangeInfoWindow;
    FoodStatistics food_list_object;
    void updateTable();
    void updateDiaryTable();
    int m_sex, m_height, m_weight, m_age;
};

#endif // FOODFORM_H
