#include "exercisefactory.h"

using namespace std;

unique_ptr<Exercise> ExerciseFactory::Create(const string& name_key, const ExerciseMeta& meta)
{
    return make_unique<Exercise>(
        name_key,
        meta.name_ukr,
        meta.category,
        meta.ideal_reps,
        meta.ideal_sets
        );
}
