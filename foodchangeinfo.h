#ifndef FOODCHANGEINFO_H
#define FOODCHANGEINFO_H

#include <QDialog>
#include "foodstatistics.h"

namespace Ui {
class FoodChangeInfo;
}

class FoodChangeInfo : public QDialog
{
    Q_OBJECT

public:
    explicit FoodChangeInfo(FoodStatistics* stats, QWidget *parent = nullptr);
    ~FoodChangeInfo();

private slots:
    void deleteDiary();
    void deleteSpecificDiary();
    void changeDiary();
    void changeList();
    void deleteList();

private:
    Ui::FoodChangeInfo *ui;
    FoodStatistics* mainFoodObject;
};

#endif // FOODCHANGEINFO_H
