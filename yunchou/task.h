#ifndef TASK_H
#define TASK_H

#include "worldModule.h""

namespace {
#define MAXVOL 100
}

class Task
{
public:
    Task();
    void init(DES des);
    DES destination;
    int volume;
};

#endif // TASK_H
