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
    DES startPos;
    int volume;
    void finish();
    void carry();
    void download();

private:
    bool _settled = false;
    bool _carried = false;
};

#endif // TASK_H
