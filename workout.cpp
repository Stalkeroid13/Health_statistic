#include <cmath>
#include <utility>
#include "workout.h"

using namespace std;

// ---------------------------WORKOUT-----------------------------------------------------------------------------------

Workout::Workout(string date, vector<unique_ptr<Exercise>> exercise_list)
    : date_(std::move(date)), exercises_(std::move(exercise_list))
{}

void Workout::AddExercise(unique_ptr<Exercise> exercise)
{
    exercises_.push_back(std::move(exercise));
}

void Workout::Display() const
{
    cout << "Workout on " << date_ << ":\n";
    for (const auto& exercise: exercises_)
        exercise->Display();
}
