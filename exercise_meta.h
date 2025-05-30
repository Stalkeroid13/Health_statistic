#ifndef EXERCISE_META_H
#define EXERCISE_META_H

#include <string>

// Категорії вправ — для аналітики, класифікації та генерації еталонів
enum class ExerciseCategory {
    Chest, Back, Legs, Shoulders, Arms,
    CoreDynamic, CoreIsometric,
    CardioLight, CardioIntense,
    EnduranceLower, EnduranceUpper,
    Flexibility, Balance, Reaction,
    Jumping, Speed, FullEndurance,
    CooperTest
};

// Структура, яка описує еталон для конкретної вправи
struct ExerciseMeta {
    std::string name_ukr;              // Назва для відображення (наприклад, "Відтискання")
    ExerciseCategory category;         // Категорія (наприклад, Chest)
    int ideal_reps;                    // Ідеальна кількість повторів
    int ideal_sets;                    // Ідеальна кількість підходів
};

#endif // EXERCISE_META_H
