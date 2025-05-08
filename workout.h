#ifndef TOGETHER_PROJECT_WORKOUT_H
#define TOGETHER_PROJECT_WORKOUT_H

#include <vector>
#include <memory>
#include "exercise.h"

using namespace std;

// ---------------------------WORKOUT-----------------------------------------------------------------------------------

class Workout
{
private:
    vector<unique_ptr<Exercise>> exercises_;
    string date_;

public:
    Workout(string date, vector<unique_ptr<Exercise>> exercise_list);

    void AddExercise(unique_ptr<Exercise> exercise);

    void Display() const;
};

#endif
