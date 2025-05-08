#include "physical_test.h"

#include <cmath>

float PhysicalTest::GetMassIndex()
{
    if (height >= 100)
        height /= 100;
    return (float)(weight / pow(height, 2));
    // - 18.5 - 25 - 30 -
}

int PhysicalTest::GetPhysicalResult() const
{
    int result_coef;
    int mid_coef;

    //розрахунок коефіцієнту для відтискань
    int PU_coef = 20;
    if (push_ups < 30)
        mid_coef = PU_coef * (push_ups / 30);
    else
        mid_coef = PU_coef;
    result_coef += mid_coef;

    //розрахунок коефіцієнту для присідань
    int SD_coef = 20;
    if (sit_downs < 40)
        mid_coef = SD_coef * (sit_downs / 40);
    else
        mid_coef = SD_coef;
    result_coef += mid_coef;

    //розрахунок коефіцієнту для тримання планки
    int P_coef = 15;
    if (plank < 90)
        mid_coef = P_coef * (plank / 90);
    else
        mid_coef = P_coef;
    result_coef += mid_coef;

    //розрахунок коефіцієнту для тесут Купера
    int CT_coef = 25;
    if (Coopers_test > 6)
        mid_coef = CT_coef * (6 / Coopers_test);
    else
        mid_coef = CT_coef;
    result_coef += mid_coef;

    //розрахунок коефіцієнту для гнучкості
    int F_coef = 10;
    switch (flexibility)
    {
    case 1:
        mid_coef = F_coef / 3;
        break;
    case 2:
        mid_coef = F_coef / 2;
        break;
    case 3:
        mid_coef = F_coef;
        break;
    }
    result_coef += mid_coef;

    //розрахунок коефіцієнту для стрибку в довжину
    int FJ_coef = 10;
    if (front_jump < 200)
        mid_coef = FJ_coef * (front_jump / 200);
    else
        mid_coef = FJ_coef;
    result_coef += mid_coef;

    return result_coef;
}
