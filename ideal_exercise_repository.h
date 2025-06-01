#pragma once

#include <unordered_map>
#include <string>
#include "exercise_model.h"

using namespace std;

// Репозиторій з еталонними вправами
class IdealExerciseRepository
{
public:
    // Завантаження еталонів з файлу
    bool LoadFromFile(const string& file_name);

    // Пошук еталона за ключем
    const ExerciseMeta* Get(const string& exercise_name) const;

    // Отримати всю таблицю еталонів
    const unordered_map<string, ExerciseMeta>& GetAll() const;

    // Знайти ключ за українською назвою вправи
    string GetKeyByUkrName(const string& name_ukr) const;

private:
    // Мапа (ключ - еталон вправи)
    unordered_map<string, ExerciseMeta> meta_map_;
};
