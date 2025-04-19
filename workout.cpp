#include <cmath>
#include <utility>
#include <sstream>
#include "workout.h"
#include "bios.h"

using namespace std;

// ---------------------------WORKOUT-----------------------------------------------------------------------------------

Workout::Workout(string date, const BIOS& bios) : date_(std::move(date))
{
    LoadExercisesFromBIOS(bios);
}

void Workout::AddExercise(unique_ptr<Exercise> exercise)
{
    exercises_.push_back(move(exercise));
}

void Workout::LoadExercisesFromBIOS(const BIOS& bios)
{
    vector<string> entries = bios.GetValues(date_);
    for (const auto& entry: entries)
        exercises_.push_back(ParseExercise(entry));
}

void Workout::Display() const
{
    cout << "Workout on " << date_ << ":\n";
    for (const auto& exercise: exercises_)
        exercise->Display();
}

// ---------------------------ADDITIONAL FUNCTIONS----------------------------------------------------------------------

float PhysicalTest::GetMassIndex()
{
    if (height >= 100)
        height /= 100;
    return (float)(weight / pow(height, 2));
    // - 18.5 - 25 - 30 -
}

int PhysicalTest::GetPhysicalResult() const
{
    int result_coef;
    int mid_coef;

    //розрахунок коефіцієнту для відтискань
    int PU_coef = 20;
    if (push_ups < 30)
        mid_coef = PU_coef * (push_ups / 30);
    else
        mid_coef = PU_coef;
    result_coef += mid_coef;

    //розрахунок коефіцієнту для присідань
    int SD_coef = 20;
    if (sit_downs < 40)
        mid_coef = SD_coef * (sit_downs / 40);
    else
        mid_coef = SD_coef;
    result_coef += mid_coef;

    //розрахунок коефіцієнту для тримання планки
    int P_coef = 15;
    if (plank < 90)
        mid_coef = P_coef * (plank / 90);
    else
        mid_coef = P_coef;
    result_coef += mid_coef;

    //розрахунок коефіцієнту для тесут Купера
    int CT_coef = 25;
    if (Coopers_test > 6)
        mid_coef = CT_coef * (6 / Coopers_test);
    else
        mid_coef = CT_coef;
    result_coef += mid_coef;

    //розрахунок коефіцієнту для гнучкості
    int F_coef = 10;
    switch (flexibility)
    {
    case 1:
        mid_coef = F_coef / 3;
        break;
    case 2:
        mid_coef = F_coef / 2;
        break;
    case 3:
        mid_coef = F_coef;
        break;
    }
    result_coef += mid_coef;

    //розрахунок коефіцієнту для стрибку в довжину
    int FJ_coef = 10;
    if (front_jump < 200)
        mid_coef = FJ_coef * (front_jump / 200);
    else
        mid_coef = FJ_coef;
    result_coef += mid_coef;

    return result_coef;
}
