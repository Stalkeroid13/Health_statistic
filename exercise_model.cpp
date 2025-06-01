#include "exercise_model.h"

using namespace std;

// --- Exercise ---

// Ініціалізація об'єкта вправи
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

// Отримати технічний ключ
const string& Exercise::GetKeyName() const
{
    return name_key_;
}

// Отримати українську назву
const string& Exercise::GetDisplayName() const
{
    return name_ukr_;
}

// Отримати категорію вправи
ExerciseCategory Exercise::GetCategory() const
{
    return category_;
}

// Отримати кількість повторень
int Exercise::GetReps() const
{
    return reps_;
}

// Отримати кількість підходів
int Exercise::GetSets() const
{
    return sets_;
}

// --- Workout ---

// Ініціалізація об'єкта тренування з датою
Workout::Workout(const string& date): date_(date)
{}

// Додати вправу до тренування
void Workout::AddExercise(const Exercise& exercise)
{
    exercises_.push_back(exercise);
}

// Отримати всі вправи
const vector<Exercise>& Workout::GetExercises() const
{
    return exercises_;
}

// Отримати дату тренування
const string& Workout::GetDate() const
{
    return date_;
}
