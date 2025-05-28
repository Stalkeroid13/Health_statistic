#include "foodlist.h"
#include "foodstatistics.h"
#include <string>
#include <ctime>
#include <sstream>
#include <QDebug>

//Розрахунок формули Міфліна-Сан Жеора
float FoodStatistics::NormOfCalories(int sex, int weight, int high, int age)
{
    float result = (weight * 10) + (high * 6.25) - (age * 5);
    if (sex == 1) return result - 161;//woman
    return result += 5;//man
}

tm ConvertToTime(string& day)
{
    //витягуємо дані з дати-рядка
    int d, m, y;
    char del1, del2;
    istringstream iss(day);
    iss >> d >> del1 >> m >> del2 >> y;

    //збираємо дату в структуру
    tm date={};
    date.tm_mday = d;
    date.tm_mon = m-1;
    date.tm_year = y-1900;
    return date;
}

string ConvertToTime(tm* day)
{
    char buffer[11]; // "dd/mm/yyyy\0"
    strftime(buffer, sizeof(buffer), "%d/%m/%Y", day);
    return string(buffer);
}

//counting characteristics according to time
vector<float> FoodStatistics::AnalysisOfNutritionAccordingToTime(string starTime, string endTime, int& day_counter)
{
    vector<float> result = {0,0,0,0};

    //перетворюємо дати-рядки, щоб ітеруватися по днях
    tm time_start_tm = ConvertToTime(starTime);
    tm time_end_tm = ConvertToTime(endTime);
    time_t t1 = mktime(&time_start_tm);
    time_t t2 = mktime(&time_end_tm);

    //перевіряємо, щоб дата початку й кінця була в правильному порядку
    if(t1>t2) swap(t1,t2);

    const int seconds_in_day = 60*60*24;
    for(time_t t = t1; t <= t2; t += seconds_in_day)
    {
        day_counter++;
        //перетворюємо дату на рядок, щоб мати змогу зчитати дані за день
        tm* current = localtime(&t);
        string current_in_str = ConvertToTime(current);

        //отримуємо аналіз по одному дню
        vector<float> one_day_data = OneDayAnalysis(current_in_str);

        //додаємо до загальних результатів
        for(int i =0; i<4; i++)result[i]+=one_day_data[i];
    }
    return result;
}

vector<float> FoodStatistics::OneDayAnalysis(string time)
{
    vector<float> result={0,0,0,0};
    //зчитуємо всі дані за день
    vector<string> one_day_data = nutrition_diary_.ReadNoteAboutFood(time);
    //для кожного запису
    for(size_t i = 0; i < one_day_data.size(); i++)
    {
        //витягуємо назву та масу
        //qDebug() << "one_day_data[i] " << one_day_data[i];
        int weight;
        string nameOfProduct, temp;
        istringstream iss(one_day_data[i]);
        iss>>nameOfProduct>>weight;

        //обраховуємо поживність відносно щоденнику харчування
        Product one_meal=NutritionValueOfMeal(weight, nameOfProduct);
        result[0]+=one_meal.caloriesInFood;
        result[1]+=one_meal.proteins;
        result[2]+=one_meal.fats;
        result[3]+=one_meal.carbohydrates;
    }
    qDebug() << "кількість калорій: " << result[0];
    return result;
}

float FoodStatistics::GetStatistics(int sex, int weight, int high, int age, string starTime, string endTime, int strategy)
{

    vector<float> temp;
    float norm_calories=NormOfCalories(sex, weight, high, age);

    //за потреби корегуємо норму калорій
    if(strategy == 1)
        norm_calories-=300;
    else if(strategy == 3)
        norm_calories+=300;

    //у залежності норми калорій рахуємо кількості поживних речовин
    float norm_proteins = 0.35*norm_calories;
    float norm_fats = 0.20*norm_calories;
    float norm_carbohydrates = 0.45*norm_calories;

    /*qDebug() << "кількість калорій: " << norm_calories;
    qDebug() << "norm_proteins " << norm_proteins;
    qDebug() << "norm_fats " << norm_fats;
    qDebug() << "norm_carbohydrates " << norm_carbohydrates;*/

    //обраховуємо кількості спожитих речовин за час
    int numberOfDays=0;
    temp=AnalysisOfNutritionAccordingToTime(starTime, endTime, numberOfDays);
    float calories_score, proteins_score, fats_score, carbohydrates_score;

    //розраховуємо оцінку для калорій
    if(temp[0]<norm_calories)
        calories_score = temp[0]/norm_calories;
    else
        calories_score = 2 - temp[0]/norm_calories;

    //розраховуємо оцінку для білків
    if(temp[1]<norm_proteins)
        proteins_score = temp[1]/norm_proteins;
    else
        proteins_score = 2 - temp[1]/norm_proteins;

    //розраховуємо оцінку для жирів
    if(temp[2]<norm_fats)
        fats_score = temp[2]/norm_fats;
    else
        fats_score = 2 - temp[2]/norm_fats;

    //розраховуємо оцінку для вуглеводів
    if(temp[3]<norm_carbohydrates)
        carbohydrates_score = temp[3]/norm_carbohydrates;
    else
        carbohydrates_score = 2 - temp[3]/norm_carbohydrates;

    /*qDebug() << "calories_score " << calories_score;
    qDebug() << "proteins_score " << proteins_score;
    qDebug() << "fats_score " << fats_score;
    qDebug() << "carbohydrates_score " << carbohydrates_score;*/

    //загальна оцінка - середнє арифметичне, поділене на кількість днів у відсотках
    return (calories_score+proteins_score+fats_score+carbohydrates_score)*100/4/numberOfDays;
}

Product FoodStatistics::NutritionValueOfMeal(int weight, string nameOfProduct)
{
    Product resultProduct, readProduct;

    //read info about product
    string info = nutrition_diary_.list_.Read(nameOfProduct);
    readProduct = readProduct.StringToProduct(info);

    //counting values
    float proportions = weight / readProduct.weight;
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
