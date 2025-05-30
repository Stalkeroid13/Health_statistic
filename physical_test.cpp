#include "physical_test.h"
#include <cmath>
#include <algorithm>

using namespace std;

float PhysicalTest::GetMassIndex()
{
    if (height >= 100)
        height /= 100;
    return weight / pow(height, 2);
}

int PhysicalTest::GetPhysicalResult() const
{
    int result_coef = 0;
    int mid_coef;

    // Відтискання
    int PU_coef = 20;
    mid_coef = push_ups < 30 ? PU_coef * push_ups / 30 : PU_coef;
    result_coef += mid_coef;

    // Присідання
    int SD_coef = 20;
    mid_coef = sit_downs < 40 ? SD_coef * sit_downs / 40 : SD_coef;
    result_coef += mid_coef;

    // Планка
    int P_coef = 15;
    mid_coef = plank < 90 ? P_coef * plank / 90 : P_coef;
    result_coef += mid_coef;

    // Купера
    int CT_coef = 25;
    mid_coef = Coopers_test > 6 ? CT_coef * 6 / Coopers_test : CT_coef;
    result_coef += mid_coef;

    // Гнучкість
    int F_coef = 10;
    switch (flexibility)
    {
    case 1: mid_coef = F_coef / 3; break;
    case 2: mid_coef = F_coef / 2; break;
    case 3: mid_coef = F_coef; break;
    }
    result_coef += mid_coef;

    // Стрибок
    int FJ_coef = 10;
    mid_coef = front_jump < 200 ? FJ_coef * front_jump / 200 : FJ_coef;
    result_coef += mid_coef;

    return result_coef;
}

// --- Оцінювання результату вправи ---
static double CalcScore(int actual, int ideal)
{
    if (ideal == 0) return 0.0;
    double deviation = abs(actual - ideal);
    double allowed = ideal * 0.1;

    if (deviation <= allowed)
        return 100.0;

    double penalty = (deviation - allowed) / (ideal * 0.02);
    return max(0.0, 100.0 - penalty);
}

double EvaluateScore(const Exercise& actual, const ExerciseMeta& ideal, const PhysicalTest& test)
{
    double scale = test.GetPhysicalResult() / 100.0;
    int scaled_reps = static_cast<int>(ideal.ideal_reps * scale);
    int scaled_sets = static_cast<int>(ideal.ideal_sets * scale);

    double reps_score = CalcScore(actual.GetReps(), scaled_reps);
    double sets_score = CalcScore(actual.GetSets(), scaled_sets);

    return (reps_score + sets_score) / 2.0;
}
