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
    Task(DES des, int secDes, int vol, DES start);
    void init(DES des);
    DES destination;
    int secondDes;
    DES startPos;
    int volume;
    void finish();
    void carry();
    void download();
    void setTask(DES des, int secDes, int vol, DES start);

private:
    bool _settled = false;
    bool _carried = false;
};

#endif // TASK_H
