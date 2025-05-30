#pragma once
#include <string>
#include <vector>

using namespace std;

enum class ExerciseCategory {
    Chest, Back, Legs, Shoulders, Arms,
    CoreDynamic, CoreIsometric, CardioLight, CardioIntense,
    EnduranceLower, EnduranceUpper, Flexibility, Balance,
    Reaction, Jumping, Speed, FullEndurance, CooperTest
};

struct ExerciseMeta {
    string name_ukr;
    ExerciseCategory category;
    int ideal_reps;
    int ideal_sets;
};

class Exercise {
    string name_key_;
    string name_ukr_;
    ExerciseCategory category_;
    int reps_;
    int sets_;
public:
    Exercise(const string& name_key,
             const string& name_ukr,
             ExerciseCategory category,
             int reps,
             int sets);

    const string& GetKeyName() const;
    const string& GetDisplayName() const;
    ExerciseCategory GetCategory() const;
    int GetReps() const;
    int GetSets() const;
};

class Workout {
    string date_;
    vector<Exercise> exercises_;
public:
    Workout(const string& date);
    void AddExercise(const Exercise& exercise);
    const vector<Exercise>& GetExercises() const;
    const string& GetDate() const;
};
