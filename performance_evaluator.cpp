#include "performance_evaluator.h"
#include <cmath>
#include <algorithm>

using namespace std;

PerformanceEvaluator::PerformanceEvaluator(const PhysicalTest& test)
    : physical_test_(test)
{}

// Допускаємо відхилення в 10% без штрафу
static double CalculateScore(int actual, int ideal)
{
    if (ideal == 0) return 0.0;

    double deviation = abs(actual - ideal);
    double allowed = ideal * 0.1;

    if (deviation <= allowed)
        return 100.0;

    double over_penalty = (deviation - allowed) / (ideal * 0.02); // 1% штраф за кожні 2% поза зоною
    return max(0.0, 100.0 - over_penalty);
}

double PerformanceEvaluator::EvaluateScore(const Exercise& actual, const ExerciseMeta& ideal) const
{
    // Враховуємо масштабування на основі фізичного тесту
    double multiplier = physical_test_.GetPhysicalResult() / 100.0;
    int scaled_reps = static_cast<int>(ideal.ideal_reps * multiplier);
    int scaled_sets = static_cast<int>(ideal.ideal_sets * multiplier);

    double score_reps = CalculateScore(actual.GetReps(), scaled_reps);
    double score_sets = CalculateScore(actual.GetSets(), scaled_sets);

    return (score_reps + score_sets) / 2.0;
}
