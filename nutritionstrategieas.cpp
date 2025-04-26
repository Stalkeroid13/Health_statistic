#include "nutritionstrategieas.h"

float GainWeight::Proficit()
{
    return 500.f;
}

float GainWeight::GetStatistics(int sex, int weight, int high, int age, int activity_score, string starTime, string endTime)
{
    vector<float> temp;
    float norm=NormOfCalories(sex, weight, high, age, activity_score)+Proficit();

    if(starTime==endTime)
    {
        temp=OneDayAnalysis(starTime);
        return temp[0]*100/norm;
    }

    temp=AnalysisOfNutritionAccordingToTime(starTime, endTime);
    int numberOfDays=1;//додатково обрахувати
    return temp[0]*100/norm/numberOfDays;
}

float LoseWeight::Deficit()
{
    return 500.f;
}

float LoseWeight::GetStatistics(int sex, int weight, int high, int age, int activity_score, string starTime, string endTime)
{
    vector<float> temp;
    float norm=NormOfCalories(sex, weight, high, age, activity_score)-Deficit();

    if(starTime==endTime)
    {
        temp=OneDayAnalysis(starTime);
        return temp[0]*100/norm;
    }

    temp=AnalysisOfNutritionAccordingToTime(starTime, endTime);
    int numberOfDays=1;//додатково обрахувати
    return temp[0]*100/norm/numberOfDays;
}

float MaintainWeight::GetStatistics(int sex, int weight, int high, int age, int activity_score, string starTime, string endTime)
{
    vector<float> temp;
    float norm=NormOfCalories(sex, weight, high, age, activity_score)-500;

    if(starTime==endTime)
    {
        temp=OneDayAnalysis(starTime);
        return temp[0]*100/norm;
    }

    temp=AnalysisOfNutritionAccordingToTime(starTime, endTime);
    int numberOfDays=1;//додатково обрахувати
    return temp[0]*100/norm/numberOfDays;
}
