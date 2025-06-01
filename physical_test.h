#pragma once

#include "exercise_model.h"

using namespace std;

// Фізичні показники користувача
struct PhysicalTest
{
    int push_ups;
    int sit_downs;
    int plank;
    int flexibility;
    int Coopers_test;
    int front_jump;

    // Загальна оцінка фізичної форми (0–100)
    int GetPhysicalResult() const;
};

// Оцінка відповідності вправи еталону з урахуванням фізичних даних
double EvaluateScore(const Exercise& actual, const ExerciseMeta& ideal, const PhysicalTest& test);
