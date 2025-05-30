#pragma once
#include <string>
#include "exercise_model.h"

using namespace std;

struct PhysicalTest
{
    int weight;
    float height;
    int push_ups;
    int sit_downs;
    int plank;
    int flexibility;
    int Coopers_test;
    int front_jump;

    float GetMassIndex();          // ІМТ
    int GetPhysicalResult() const; // Загальна фізична форма (0–100)
};

// Оцінювання вправи — тепер звичайна функція
double EvaluateScore(const Exercise& actual, const ExerciseMeta& ideal, const PhysicalTest& test);
