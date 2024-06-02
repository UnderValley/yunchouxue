#ifndef CAR_H
#define CAR_H
#include "worldModule.h"

class Car
{
public:
    Car();
    Car(DES local): location(local){}
    const int volume = 100;
    const int speed = 2;
    const int runTime = 50; // 续航
    const int chareTime = 10; // 充电时间
    DES location;
    void init(DES local);
};

#endif // CAR_H
