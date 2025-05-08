#ifndef EXERCISEFACTORY_H
#define EXERCISEFACTORY_H

#include <memory>
#include <string>
#include "exercise.h"

using namespace std;

class ExerciseFactory
{
public:
    static unique_ptr<Exercise> Create(const string& exercise_data);
};

#endif // EXERCISEFACTORY_H
