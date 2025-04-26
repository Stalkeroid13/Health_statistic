#include "foodlist.h"
#include "foodstatistics.h"
//#include <iostream>
#include <string>
//#include <fstream>

float FoodStatistics::NormOfCalories(int sex, int weight, int high, int age, int activity_score)
{
    float result = (weight * 10) + (high * 6.25) - (age * 5);
    if (sex == 1) result -= 161;
    else result += 5;
    return result * (1.2 + (activity_score / 20 * 0.175));
}

//counting characteristics according to time
vector<float> FoodStatistics::AnalysisOfNutritionAccordingToTime(string starTime, string endTime)
{
    vector<float> result;
    Product temp;
    //
    return result;
}
vector<float> FoodStatistics::OneDayAnalysis(string time)
{
    vector<float> result;
    return result;
}
float FoodStatistics::GetStatistics(int sex, int weight, int high, int age, int activity_score, string starTime, string endTime)
{
    return 0;
}

Product FoodStatistics::NutritionValueOfMeal(int weight, string nameOfProduct)
{
    Product resultProduct, readProduct;

    //read info about product
    string info = nutrition_diary_.list_.Read(nameOfProduct);
    readProduct = readProduct.StringToProduct(info);

    //counting values
    int proportions = weight / readProduct.weight;
    resultProduct.caloriesInFood = readProduct.caloriesInFood * proportions;
    resultProduct.proteins = readProduct.proteins * proportions;
    resultProduct.fats = readProduct.fats * proportions;
    resultProduct.carbohydrates = readProduct.carbohydrates;

    return resultProduct;
}


//adding, reading, changing and deleting info in diary
void DiaryManager::AddNoteAboutFood(string time, string object)
{
    diary_.AddEntry(time, object);
}

vector<string> DiaryManager::ReadNoteAboutFood(string time)
{
    vector<string> values=diary_.GetValues(time);
    return values;
}

bool DiaryManager::ChangeNoteAboutFood(string time, string old_object, string new_object)
{
    return diary_.UpdateEntry(time, old_object, new_object);
}

void DiaryManager::DeleteNotesAboutFood(string time)
{
    diary_.RemoveEntry(time);
}

void DiaryManager::DeleteOneNoteAboutFood(string time, string object)
{
    diary_.RemoveSpecificEntry(time, object);
}
