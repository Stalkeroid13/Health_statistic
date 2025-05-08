#include "exercisefactory.h"
#include <sstream>
#include <stdexcept>

using namespace std;

unique_ptr<Exercise> ExerciseFactory::Create(const string& exercise_data)
{
    istringstream stream(exercise_data);
    string name, muscle_group;
    int repetitions, sets;

    if (!(stream >> name >> muscle_group >> repetitions >> sets))
        throw invalid_argument("Invalid exercise format: " + exercise_data);

    if (muscle_group == "Chest" || muscle_group == "Back" || muscle_group == "Core" ||
        muscle_group == "Legs" || muscle_group == "Shoulders" || muscle_group == "Arms")
        return make_unique<StrengthExercise>(name, muscle_group, repetitions, sets);
    else if (muscle_group == "Cardio")
        return make_unique<CardioExercise>(name, muscle_group, repetitions, sets);
    else
        throw invalid_argument("Unknown exercise type: " + muscle_group);
}
