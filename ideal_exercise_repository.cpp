#include "ideal_exercise_repository.h"
#include <fstream>
#include <sstream>
#include <QDebug>

using namespace std;

static string NormalizeUkrainianName(const string& input)
{
    QString qstr = QString::fromStdString(input).trimmed().toLower().replace(" ", "_");
    return qstr.toStdString();
}

static ExerciseCategory ParseCategory(const string& raw)
{
    if (raw == "Chest") return ExerciseCategory::Chest;
    if (raw == "Back") return ExerciseCategory::Back;
    if (raw == "Legs") return ExerciseCategory::Legs;
    if (raw == "Shoulders") return ExerciseCategory::Shoulders;
    if (raw == "Arms") return ExerciseCategory::Arms;
    if (raw == "CoreDynamic") return ExerciseCategory::CoreDynamic;
    if (raw == "CoreIsometric") return ExerciseCategory::CoreIsometric;
    if (raw == "CardioLight") return ExerciseCategory::CardioLight;
    if (raw == "CardioIntense") return ExerciseCategory::CardioIntense;
    if (raw == "EnduranceLower") return ExerciseCategory::EnduranceLower;
    if (raw == "EnduranceUpper") return ExerciseCategory::EnduranceUpper;
    if (raw == "Flexibility") return ExerciseCategory::Flexibility;
    if (raw == "Balance") return ExerciseCategory::Balance;
    if (raw == "Reaction") return ExerciseCategory::Reaction;
    if (raw == "Jumping") return ExerciseCategory::Jumping;
    if (raw == "Speed") return ExerciseCategory::Speed;
    if (raw == "FullEndurance") return ExerciseCategory::FullEndurance;
    if (raw == "CooperTest") return ExerciseCategory::CooperTest;

    throw invalid_argument("Unknown category: " + raw);
}

bool IdealExerciseRepository::LoadFromFile(const string& file_name)
{
    ifstream file(file_name);
    if (!file.is_open()) return false;

    meta_map_.clear();
    string line;

    while (getline(file, line))
    {
        istringstream ss(line);
        string key, name_ukr, cat_str;
        int reps, sets;

        if (!(ss >> key >> name_ukr >> cat_str >> reps >> sets))
            continue;

        try {
            ExerciseCategory category = ParseCategory(cat_str);
            meta_map_[key] = ExerciseMeta{ name_ukr, category, reps, sets };
        }
        catch (const invalid_argument&) {
            continue; // пропускаємо помилкову категорію
        }
    }

    return true;
}

const ExerciseMeta* IdealExerciseRepository::Get(const string& exercise_name) const
{
    auto it = meta_map_.find(exercise_name);
    if (it != meta_map_.end())
        return &it->second;
    return nullptr;
}

const unordered_map<string, ExerciseMeta>& IdealExerciseRepository::GetAll() const
{
    return meta_map_;
}

string IdealExerciseRepository::GetKeyByUkrName(const string& name_ukr) const {
    string normalized = NormalizeUkrainianName(name_ukr);
    for (const auto& [key, meta] : meta_map_)
    {
        if (NormalizeUkrainianName(meta.name_ukr) == normalized)
            return key;
    }
    return "";
}
