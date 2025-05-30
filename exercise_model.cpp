#include "exercise_model.h"

using namespace std;

// --- Exercise ---

Exercise::Exercise(const string& name_key,
                   const string& name_ukr,
                   ExerciseCategory category,
                   int reps,
                   int sets)
    : name_key_(name_key),
    name_ukr_(name_ukr),
    category_(category),
    reps_(reps),
    sets_(sets)
{}

const string& Exercise::GetKeyName() const { return name_key_; }
const string& Exercise::GetDisplayName() const { return name_ukr_; }
ExerciseCategory Exercise::GetCategory() const { return category_; }
int Exercise::GetReps() const { return reps_; }
int Exercise::GetSets() const { return sets_; }

// --- Workout ---

Workout::Workout(const string& date)
    : date_(date)
{}

void Workout::AddExercise(const Exercise& exercise) {
    exercises_.push_back(exercise);
}

const vector<Exercise>& Workout::GetExercises() const {
    return exercises_;
}

const string& Workout::GetDate() const {
    return date_;
}
