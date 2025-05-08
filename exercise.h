#ifndef TOGETHER_PROJECT_EXERCISE_H
#define TOGETHER_PROJECT_EXERCISE_H

#include <iostream>
#include "bios.h"
#include "physical_test.h"

// ---------------------------EXERCISE----------------------------------------------------------------------------------

class Exercise
{
protected:
    string name_;         // Назва вправи
    string muscle_group_; // Група м'язів
    int repetitions_;     // Кількість повторень
    int sets_;            // Кількість підходів

    Exercise(string name, string muscle_group, int repetitions, int sets)
        : name_(std::move(name)), muscle_group_(std::move(muscle_group)), repetitions_(repetitions), sets_(sets)
    {
    }

public:
    virtual ~Exercise() = default;

    string GetName() const
    {
        return name_;
    }

    string GetMuscleGroup() const
    {
        return muscle_group_;
    }

    int GetRepetitions() const
    {
        return repetitions_;
    }

    int GetSets() const
    {
        return sets_;
    }

    virtual void Display() const = 0;
};

// ---------------------------PERFORMANCE-EXERCISE----------------------------------------------------------------------

struct ExerciseResult
{
    int actual_reps = 0;
    int actual_sets = 0;
    double score = 0.0;
};

class PerformanceExercise : public Exercise
{
private:
    PhysicalTest physical_test_; // Фізичні тести користувача
    double performance_score_{};   // Оцінка виконання вправи
    ExerciseResult result_; // фактичні дані + оцінка

public:
    PerformanceExercise(const string& name, const string& muscle_group, const PhysicalTest& physical_test,
                        const BIOS& bios);

    // Встановлення параметрів користувача
    void SetUserResult(int actual_reps, int actual_sets, double score);
    double GetPerformanceScore() const;

    // Виведення результатів
    void Display();
};

// ---------------------------TYPES-OF-EXERCISES------------------------------------------------------------------------

class StrengthExercise : public Exercise
{
public:
    StrengthExercise(string name, string muscle_group, int repetitions, int sets)
        : Exercise(std::move(name), std::move(muscle_group), repetitions, sets)
    {
    }

    void Display() const override
    {
        cout << "Strength Exercise: " << name_ << ", Muscle Group: " << muscle_group_
             << ", Repetitions: " << repetitions_ << ", Sets: " << sets_ << endl;
    }
};

class CardioExercise : public Exercise
{
public:
    CardioExercise(string name, string muscle_group, int repetitions, int sets)
        : Exercise(std::move(name), std::move(muscle_group), repetitions, sets)
    {
    }

    void Display() const override
    {
        cout << "Cardio Exercise: " << name_ << ", Muscle Group: " << muscle_group_
             << ", Duration: " << repetitions_ << " minutes, Intensity: " << sets_ << " level" << endl;
    }
};

#endif
