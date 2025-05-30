#ifndef EXERCISE_FACTORY_H
#define EXERCISE_FACTORY_H

#include <memory>
#include <string>
#include "exercise.h"
#include "exercise_meta.h"

class ExerciseFactory {
public:
    static std::unique_ptr<Exercise> Create(const std::string& name_key,
                                            const ExerciseMeta& meta);
};

#endif // EXERCISE_FACTORY_H
