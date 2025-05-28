#include "nutritionstrategieas.h"

float GainWeight::Proficit()
{
    return 500.f;
}

float GainWeight::GetStatistics(int sex, int weight, int high, int age, string starTime, string endTime)
{
    vector<float> temp;
    float norm=NormOfCalories(sex, weight, high, age)+Proficit();

    if(starTime==endTime)
    {
        temp=OneDayAnalysis(starTime);
        return temp[0]*100/norm;
    }

    int numberOfDays=1;//додатково обрахувати
    temp=AnalysisOfNutritionAccordingToTime(starTime, endTime, numberOfDays);
    return temp[0]*100/norm/numberOfDays;
}

float LoseWeight::Deficit()
{
    return 500.f;
}

float LoseWeight::GetStatistics(int sex, int weight, int high, int age, string starTime, string endTime)
{
    vector<float> temp;
    float norm=NormOfCalories(sex, weight, high, age)-Deficit();

    if(starTime==endTime)
    {
        temp=OneDayAnalysis(starTime);
        return temp[0]*100/norm;
    }

    int numberOfDays=1;//додатково обрахувати
    temp=AnalysisOfNutritionAccordingToTime(starTime, endTime, numberOfDays);
    return temp[0]*100/norm/numberOfDays;
}

float MaintainWeight::GetStatistics(int sex, int weight, int high, int age, string starTime, string endTime)
{
    vector<float> temp;
    float norm=NormOfCalories(sex, weight, high, age)-500;

    if(starTime==endTime)
    {
        temp=OneDayAnalysis(starTime);
        return temp[0]*100/norm;
    }

    int numberOfDays=1;//додатково обрахувати
    temp=AnalysisOfNutritionAccordingToTime(starTime, endTime, numberOfDays);
    return temp[0]*100/norm/numberOfDays;
}
