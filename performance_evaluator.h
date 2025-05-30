#ifndef PERFORMANCE_EVALUATOR_H
#define PERFORMANCE_EVALUATOR_H

#include <string>
#include "physical_test.h"
#include "exercise.h"
#include "exercise_meta.h"

class PerformanceEvaluator {
public:
    PerformanceEvaluator(const PhysicalTest& test);

    // Повертає бал за конкретну вправу
    double EvaluateScore(const Exercise& actual, const ExerciseMeta& ideal) const;

private:
    PhysicalTest physical_test_;
};

#endif // PERFORMANCE_EVALUATOR_H
