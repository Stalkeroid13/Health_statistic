#pragma once

#include <string>
#include <vector>

using namespace std;

// Категорії вправи
enum class ExerciseCategory
{
    Chest, Back, Legs, Shoulders, Arms,
    CoreDynamic, CoreIsometric, CardioLight, CardioIntense,
    EnduranceLower, EnduranceUpper, Flexibility, Balance,
    Reaction, Jumping, Speed, FullEndurance, CooperTest
};

// Еталонні значення для вправи
struct ExerciseMeta
{
    string name_ukr;
    ExerciseCategory category;
    int ideal_reps;
    int ideal_sets;
};

// Один запис вправи користувача
class Exercise
{
    // Основні характеристики вправи
    string name_key_;
    string name_ukr_;
    ExerciseCategory category_;
    int reps_;
    int sets_;

public:
    // Конструктор
    Exercise(const string& name_key,
             const string& name_ukr,
             ExerciseCategory category,
             int reps,
             int sets);

    // Доступ до полів
    const string& GetKeyName() const;
    const string& GetDisplayName() const;
    ExerciseCategory GetCategory() const;
    int GetReps() const;
    int GetSets() const;
};

// Тренування з кількох вправ
class Workout
{
    // Дата та список вправ
    string date_;
    vector<Exercise> exercises_;

public:
    // Конструктор
    Workout(const string& date);

    // Додавання вправи
    void AddExercise(const Exercise& exercise);

    // Отримання даних
    const vector<Exercise>& GetExercises() const;
    const string& GetDate() const;
};
