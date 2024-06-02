#include "car.h"

Car::Car()
{

}

void Car::init(DES local)
{
    location = local;
}

void Car::download()
{
    for (int i = 0; i < bag.size(); i++) {
        if (bag[i].destination == location ) {

        };
    }
}
