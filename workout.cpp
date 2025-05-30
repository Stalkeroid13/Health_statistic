#include "workout.h"
#include <iostream>

using namespace std;

Workout::Workout(const string& date)
    : date_(date)
{}

void Workout::AddExercise(const Exercise& exercise)
{
    exercises_.push_back(exercise);  // копія, бо Exercise — легкий обʼєкт
}

const vector<Exercise>& Workout::GetExercises() const
{
    return exercises_;
}

const string& Workout::GetDate() const
{
    return date_;
}

void Workout::Display() const
{
    cout << "Тренування за " << date_ << ":\n";
    for (const auto& ex : exercises_)
        ex.Display();
}
