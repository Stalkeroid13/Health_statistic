#ifndef TOGETHER_PROJECT_WORKOUT_H
#define TOGETHER_PROJECT_WORKOUT_H

//#include <iostream>
#include <vector>
//#include <unordered_map>
#include <memory>
#include "exercise.h"
#include "bios.h"

using namespace std;

// ---------------------------WORKOUT-----------------------------------------------------------------------------------

class Workout
{
private:
    vector<unique_ptr<Exercise>> exercises_;
    string date_;

public:
    Workout(string date, const BIOS& bios);

    unique_ptr<Exercise> ParseExercise(const string& exercise_data);

    void AddExercise(unique_ptr<Exercise> exercise);

    void LoadExercisesFromBIOS(const BIOS& bios);

    void Display() const;
};

#endif
