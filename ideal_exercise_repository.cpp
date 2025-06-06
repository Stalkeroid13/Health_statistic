#include "ideal_exercise_repository.h"
#include "string_utils.h"

#include <fstream>
#include <sstream>

using namespace std;

// --- Парсинг категорії з тексту ---

static ExerciseCategory ParseCategory(const string& cat)
{
    if (cat == "Chest") return ExerciseCategory::Chest;
    if (cat == "Back") return ExerciseCategory::Back;
    if (cat == "Legs") return ExerciseCategory::Legs;
    if (cat == "Shoulders") return ExerciseCategory::Shoulders;
    if (cat == "Arms") return ExerciseCategory::Arms;
    if (cat == "CoreDynamic") return ExerciseCategory::CoreDynamic;
    if (cat == "CoreIsometric") return ExerciseCategory::CoreIsometric;
    if (cat == "CardioLight") return ExerciseCategory::CardioLight;
    if (cat == "CardioIntense") return ExerciseCategory::CardioIntense;
    if (cat == "EnduranceLower") return ExerciseCategory::EnduranceLower;
    if (cat == "EnduranceUpper") return ExerciseCategory::EnduranceUpper;
    if (cat == "Flexibility") return ExerciseCategory::Flexibility;
    if (cat == "Balance") return ExerciseCategory::Balance;
    if (cat == "Reaction") return ExerciseCategory::Reaction;
    if (cat == "Jumping") return ExerciseCategory::Jumping;
    if (cat == "Speed") return ExerciseCategory::Speed;
    if (cat == "FullEndurance") return ExerciseCategory::FullEndurance;
    if (cat == "CooperTest") return ExerciseCategory::CooperTest;

    throw invalid_argument("Unknown category: " + cat);
}

// Завантаження еталонів з файлу
bool IdealExerciseRepository::LoadFromFile(const string& file_name)
{
    ifstream file(file_name);
    if (!file.is_open())
        return false;

    // Очищення хеш-таблиці перед новим завантаженням
    meta_map_.clear();
    string line;

    // Зчитування рядків з файлу
    while (getline(file, line))
    {
        istringstream ss(line);
        string key, name_ukr, cat_str;
        int reps, sets;

        // Пропуск рядка, якщо формат некоректний
        if (!(ss >> key >> name_ukr >> cat_str >> reps >> sets))
            continue;

        // Перетворення категорії у значення enum
        ExerciseCategory category = ParseCategory(cat_str);

        // Додавання запису у хеш-таблицю
        meta_map_[key] = ExerciseMeta{ name_ukr, category, reps, sets };
    }

    return true;
}

// Пошук еталона за ключем
const ExerciseMeta* IdealExerciseRepository::Get(const string& exercise_name) const
{
    auto it = meta_map_.find(exercise_name);
    if (it != meta_map_.end())
        return &it->second;
    return nullptr;
}

// Отримати всю таблицю еталонів
const unordered_map<string, ExerciseMeta>& IdealExerciseRepository::GetAll() const
{
    return meta_map_;
}

// Знайти ключ за українською назвою вправи
string IdealExerciseRepository::GetKeyByUkrName(const string& name_ukr) const
{
    string normalized = NormalizeUkrainianName(name_ukr);
    for (const auto& [key, meta] : meta_map_)
    {
        if (NormalizeUkrainianName(meta.name_ukr) == normalized)
            return key;
    }
    return "";
}
