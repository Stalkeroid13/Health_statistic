#include <cmath>
#include <sstream>
#include "exercise.h"
#include "bios.h"

using namespace std;

// ---------------------------PERFORMANCE-EXERCISE----------------------------------------------------------------------

PerformanceExercise::PerformanceExercise(const string& name, const string& muscle_group,
                                         const PhysicalTest& physical_test, const BIOS& bios)
    : Exercise(name, muscle_group, 0, 0), physical_test_(physical_test)
{
    LoadIdealDataFromBIOS(bios);    // Завантаження ідеальних параметрів
    CalculateIdealParameters();    // Розрахунок параметрів для користувача
}

// Завантаження ідеальних параметрів із BIOS
void PerformanceExercise::LoadIdealDataFromBIOS(const BIOS& bios)
{
    vector<string> exercise_data = bios.GetValues("exercise_ideal_data");
    for (const auto& entry: exercise_data)
    {
        istringstream ss(entry);
        string exercise_name;
        int ideal_repetitions, ideal_sets;
        ss >> exercise_name >> ideal_repetitions >> ideal_sets;
        exercise_ideal_data_[exercise_name] = { ideal_repetitions, ideal_sets };
    }
}

// Розрахунок ідеальних параметрів для користувача
void PerformanceExercise::CalculateIdealParameters()
{
    auto it = exercise_ideal_data_.find(name_);
    if (it != exercise_ideal_data_.end())
    {
        // Використовуємо базові параметри з хеш-таблиці
        int base_repetitions = it->second.first;
        int base_sets = it->second.second;

        // Модифікація на основі фізичних тестів
        double fitness_multiplier = physical_test_.GetPhysicalResult() / 100.0; // Масштабування 0-1
        ideal_repetitions_ = static_cast<int>(base_repetitions * fitness_multiplier);
        ideal_sets_ = static_cast<int>(base_sets * fitness_multiplier);
    }
    else
    {
        ideal_repetitions_ = 10; // Значення за замовчуванням
        ideal_sets_ = 3;
    }
}

// Розрахунок оцінки виконання
double PerformanceExercise::CalculatePerformanceScore(int actual_repetitions, int actual_sets) const
{
    double score_reps = min(100.0, (actual_repetitions / static_cast<double>(ideal_repetitions_)) * 100.0);
    double score_sets = min(100.0, (actual_sets / static_cast<double>(ideal_sets_)) * 100.0);
    return (score_reps + score_sets) / 2.0; // Середня оцінка
}

// Запит параметрів у користувача
void PerformanceExercise::RequestUserData()
{
    cout << "Enter the number of repetitions: ";
    int user_repetitions;
    cin >> user_repetitions;

    cout << "Enter the number of sets: ";
    int user_sets;
    cin >> user_sets;

    performance_score_ = CalculatePerformanceScore(user_repetitions, user_sets);
}

void PerformanceExercise::Display()
{
    cout << "Performance Exercise: " << name_ << ", Muscle Group: " << muscle_group_ << endl;
}
