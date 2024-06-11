#pragma once
#ifndef CAR_H
#define CAR_H
#include "worldModule.h"
#include <vector>
#include "task.h"

#define CAR_VOLUME 50

class Car
{
public:
    Car();
    Car(DES local) : location(local) {}
    int volume = 50;
    int time_sum = 0;
    int speed = 3;
    DES location;
    void init(DES local);
};

#endif // CAR_H
