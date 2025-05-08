#ifndef TOGETHER_PROJECT_EXERCISE_H
#define TOGETHER_PROJECT_EXERCISE_H

#include <iostream>
#include <unordered_map>
#include "bios.h"

// ---------------------------ADDITIONAL FUNCTIONS----------------------------------------------------------------------

struct PhysicalTest
{
    float weight;    //kilograms
    float height;    //meters

    int push_ups;        //count per 1 min
    int sit_downs;       //count per 1 min
    int plank;           //sec
    int Coopers_test;    //min
    int flexibility;     //3 steps
    int front_jump;      //cm

    float GetMassIndex();

    int GetPhysicalResult() const;
};

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

class PerformanceExercise : public Exercise
{
private:

    PhysicalTest physical_test_; // Фізичні тести користувача
    int ideal_repetitions_{};      // Ідеальна кількість повторень
    int ideal_sets_{};             // Ідеальна кількість підходів
    double performance_score_{};   // Оцінка виконання вправи

    // Хеш-таблиця ідеальних параметрів вправ
    unordered_map<string, pair<int, int>> exercise_ideal_data_;

    // Завантаження ідеальних параметрів вправ з BIOS
    void LoadIdealDataFromBIOS(const BIOS& bios);

    // Розрахунок ідеальних параметрів для користувача
    void CalculateIdealParameters();

    // Розрахунок оцінки виконання
    double CalculatePerformanceScore(int actual_repetitions, int actual_sets) const;

public:
    PerformanceExercise(const string& name, const string& muscle_group, const PhysicalTest& physical_test,
                        const BIOS& bios);

    // Запит параметрів у користувача
    void RequestUserData();

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
