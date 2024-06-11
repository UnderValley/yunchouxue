#pragma once
#ifndef TASK_H
#define TASK_H

#include "worldModule.h"

namespace {
#define MAXVOL 10
}

class Task
{
public:
    Task();
    Task(DES des, int secDes, int vol, DES start);
    void init(DES des);
    DES destination;
    int secondDes;
    DES startPos;
    int volume;
    void finish();
    void reset();
    bool check();
    void setTask(DES des, int secDes, int vol, DES start);

private:
    bool _settled = false;
};

#endif // TASK_H
