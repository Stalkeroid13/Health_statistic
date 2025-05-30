#ifndef WORKOUT_H
#define WORKOUT_H

#include <string>
#include <vector>
#include "exercise.h"

class Workout {
public:
    Workout(const std::string& date);

    void AddExercise(const Exercise& exercise);  // або Exercise ex by value
    const std::vector<Exercise>& GetExercises() const;
    const std::string& GetDate() const;

    void Display() const;

private:
    std::string date_;
    std::vector<Exercise> exercises_;
};

#endif // WORKOUT_H
