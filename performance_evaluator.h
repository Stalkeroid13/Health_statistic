#ifndef PERFORMANCE_EVALUATOR_H
#define PERFORMANCE_EVALUATOR_H

#include <string>
#include <unordered_map>
#include "physical_test.h"

using namespace std;

class PerformanceEvaluator
{
public:
    PerformanceEvaluator(const PhysicalTest& physical_test, const unordered_map<string,
                        pair<int, int>>& ideal_data);

    pair<int, int> GetIdealParameters(const string& exercise_name) const;

    double EvaluateScore(const string& exercise_name, int actual_reps, int actual_sets) const;

private:
    PhysicalTest physical_test_;
    unordered_map<string, pair<int, int>> ideal_data_;
};

#endif
