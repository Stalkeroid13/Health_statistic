#ifndef IDEAL_EXERCISE_REPOSITORY_H
#define IDEAL_EXERCISE_REPOSITORY_H

#include <unordered_map>
#include <string>
#include "bios.h"

using namespace std;

class IdealExerciseRepository {
public:
    IdealExerciseRepository(const BIOS& bios);

    const unordered_map<string, pair<int, int>>& GetAll() const;

private:
    unordered_map<string, pair<int, int>> ideal_data_;

    void LoadFromBIOS(const BIOS& bios);
};

#endif
