#include <cmath>
#include "exercise.h"

using namespace std;

PerformanceExercise::PerformanceExercise(const string& name, const string& muscle_group,
                                         const PhysicalTest& physical_test, const BIOS& bios)
    : Exercise(name, muscle_group, 0, 0), physical_test_(physical_test)
{
}

// Встановлення параметрів користувача
void PerformanceExercise::SetUserResult(int actual_reps, int actual_sets, double score)
{
    result_.actual_reps = actual_reps;
    result_.actual_sets = actual_sets;
    result_.score = score;
}

double PerformanceExercise::GetPerformanceScore() const
{
    return result_.score;
}

void PerformanceExercise::Display()
{
    cout << "Performance Exercise: " << name_ << ", Muscle Group: " << muscle_group_ << endl;
    cout << "User did " << result_.actual_reps << " reps and " << result_.actual_sets
         << " sets. Score: " << result_.score << "%" << endl;
}

