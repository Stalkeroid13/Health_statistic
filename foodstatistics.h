#ifndef FOODSTATISTICS_H
#define FOODSTATISTICS_H
//#include <iostream>
//#include <unordered_map>
#include <vector>
#include  <ctime>

#include "FoodList.h"
#include "BIOS.h"
using namespace std;

class DiaryManager
{
public:
    //adding, reading, changing and deleting info in diary
    void AddNoteAboutFood(string time, string object);
    vector<string> ReadNoteAboutFood(string time);
    bool ChangeNoteAboutFood(string time, string old_object, string new_object);
    void DeleteNotesAboutFood(string time);
    void DeleteOneNoteAboutFood(string time, string object);
    BIOS diary_;
    FoodList list_;
};

class FoodStatistics
{
public:
    Product NutritionValueOfMeal(int weight, string nameOfProduct);
    vector<float> AnalysisOfNutritionAccordingToTime(string starTime, string endTime);//доробити
    float NormOfCalories(int sex, int weight, int high, int age, int activity_score);
    vector<float> OneDayAnalysis(string time);
    virtual float GetStatistics(int sex, int weight, int high, int age, int activity_score, string starTime, string endTime);
private:
    DiaryManager nutrition_diary_;
};

#endif //FOODSTATISTICS_H
