#ifndef EXERCISE_H
#define EXERCISE_H

#include <string>
#include "exercise_meta.h"

class Exercise {
public:
    Exercise(const std::string& name_key,
             const std::string& name_ukr,
             ExerciseCategory category,
             int reps,
             int sets);

    void Display() const;

    // Доступ до основних полів
    const std::string& GetKeyName() const;
    const std::string& GetDisplayName() const;
    ExerciseCategory GetCategory() const;
    int GetReps() const;
    int GetSets() const;

private:
    std::string name_key_;      // Англійська назва (наприклад: pushups)
    std::string name_ukr_;      // Назва для UI ("Відтискання")
    ExerciseCategory category_; // Категорія (Chest, CardioIntense тощо)
    int reps_;
    int sets_;
};

#endif // EXERCISE_H
