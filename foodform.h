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
    explicit foodform(QWidget *parent = nullptr);
    ~foodform();

private slots:
    void updateList();
    void updateDiary();
    void addNoteToList();
    void toChangeForm();
    void addNoteToDiary();
    void generateTotalScore();

private:
    Ui::foodform *ui;
    FoodChangeInfo *foodChangeInfoWindow;
    FoodStatistics food_list_object;
    void updateTable();
    void updateDiaryTable();
};

#endif // FOODFORM_H
