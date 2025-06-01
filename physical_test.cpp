#include "physical_test.h"

using namespace std;

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
    if (ideal <= 0) return 0.0;

    double lower_bound = ideal * 0.9;
    double upper_bound = ideal * 1.5;

    if (actual >= lower_bound && actual <= upper_bound)
        return 100.0;

    // Нижче межі – шкала 0–100 за відхилення від 90% до 0%
    if (actual < lower_bound)
    {
        double severity = 1 - actual / ideal / 0.9;
        double penalty = severity * 100.0;
        return max(0.0, 100.0 - penalty);
    }

    // Вище межі – шкала 0–100 за відхилення від 150% до ∞
    if (actual > upper_bound)
    {
        double severity = actual / ideal / 1.5 - 1;
        double penalty = severity * 100.0;
        return max(0.0, 100.0 - penalty);
    }

    return 0.0;
}

double EvaluateScore(const Exercise& actual, const ExerciseMeta& ideal, const PhysicalTest& test)
{
    double scale = test.GetPhysicalResult() / 100.0;
    int scaled_reps = max(1, static_cast<int>(ideal.ideal_reps * scale));
    int scaled_sets = max(1, static_cast<int>(ideal.ideal_sets * scale));

    double reps_score = CalcScore(actual.GetReps(), scaled_reps);
    double sets_score = CalcScore(actual.GetSets(), scaled_sets);

    return (reps_score + sets_score) / 2.0;
}
