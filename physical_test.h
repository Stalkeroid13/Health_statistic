#ifndef PHYSICAL_TEST_H
#define PHYSICAL_TEST_H

struct PhysicalTest
{
    float weight;    //kilograms
    float height;    //meters

    int push_ups;        //count per 1 min
    int sit_downs;       //count per 1 min
    int plank;           //sec
    int Coopers_test;    //min
    int flexibility;     //3 steps
    int front_jump;      //cm

    float GetMassIndex();
    int GetPhysicalResult() const;
};

#endif
