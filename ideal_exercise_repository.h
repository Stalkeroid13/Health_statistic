#ifndef IDEAL_EXERCISE_REPOSITORY_H
#define IDEAL_EXERCISE_REPOSITORY_H

#include <unordered_map>
#include <string>
#include "exercise_meta.h"

using namespace std;

class IdealExerciseRepository
{
public:
    bool LoadFromFile(const string& file_name);

    // Отримати еталон для вправи
    const ExerciseMeta* Get(const string& exercise_name) const;

    // Уся мапа вправ
    const unordered_map<string, ExerciseMeta>& GetAll() const;

private:
    unordered_map<string, ExerciseMeta> meta_map_;
};

#endif // IDEAL_EXERCISE_REPOSITORY_H
