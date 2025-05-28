//#include "foodlist.h"
#include "foodstatistics.h"

#ifndef NUTRITIONSTRATEGIES_H
#define NUTRITIONSTRATEGIES_H

class GainWeight : public FoodStatistics
{
public:
    float Proficit();
    virtual float GetStatistics(int sex, int weight, int high, int age, string starTime, string endTime);
};

class LoseWeight : public FoodStatistics
{
public:
    float Deficit();
    virtual float GetStatistics(int sex, int weight, int high, int age, string starTime, string endTime);
};

class MaintainWeight : public FoodStatistics
{
public:
    virtual float GetStatistics(int sex, int weight, int high, int age, string starTime, string endTime);
};
#endif //NUTRITIONSTRATEGIES_H
