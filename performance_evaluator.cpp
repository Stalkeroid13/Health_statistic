#include "performance_evaluator.h"
#include <algorithm>

using namespace std;

PerformanceEvaluator::PerformanceEvaluator(const PhysicalTest& physical_test,
                                           const unordered_map<string, pair<int, int>>& ideal_data)
    : physical_test_(physical_test), ideal_data_(ideal_data)
{
}

pair<int, int> PerformanceEvaluator::GetIdealParameters(const string& exercise_name) const
{
    auto it = ideal_data_.find(exercise_name);
    if (it != ideal_data_.end())
    {
        double multiplier = physical_test_.GetPhysicalResult() / 100.0;
        int ideal_reps = static_cast<int>(it->second.first * multiplier);
        int ideal_sets = static_cast<int>(it->second.second * multiplier);
        return { ideal_reps, ideal_sets };
    }
     // Значення за замовчуванням
    return { 13, 4 };
}

double PerformanceEvaluator::EvaluateScore(const string& exercise_name,
                                           int actual_reps, int actual_sets) const
{
    auto [ideal_reps, ideal_sets] = GetIdealParameters(exercise_name);

    double score_reps = min(100.0, (actual_reps / static_cast<double>(ideal_reps)) * 100.0);
    double score_sets = min(100.0, (actual_sets / static_cast<double>(ideal_sets)) * 100.0);

    return (score_reps + score_sets) / 2.0;
}
