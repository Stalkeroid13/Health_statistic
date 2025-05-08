#include "ideal_exercise_repository.h"
#include <sstream>

IdealExerciseRepository::IdealExerciseRepository(const BIOS& bios)
{
    LoadFromBIOS(bios);
}

void IdealExerciseRepository::LoadFromBIOS(const BIOS& bios)
{
    vector<string> exercise_data = bios.GetValues("exercise_ideal_data");
    for (const auto& entry: exercise_data)
    {
        istringstream ss(entry);
        string exercise_name;
        int ideal_reps, ideal_sets;
        ss >> exercise_name >> ideal_reps >> ideal_sets;
        ideal_data_[exercise_name] = { ideal_reps, ideal_sets };
    }
}

const unordered_map<string, pair<int, int>>& IdealExerciseRepository::GetAll() const
{
    return ideal_data_;
}
