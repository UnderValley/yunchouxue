#include "recpos.h"
#include <stdlib.h>
#include <time.h>
#include "pos.h"

sendPos::sendPos()
{
    neighbnum = -1;
}

void sendPos::init(DES des)
{
    _des = des;
    pos tmp(des);
    neighbnum = tmp.neighbnum;
    neighbs = tmp.neighbs;
    taskNum = 0;
}

void sendPos::regenerate()
{
    taskPool.clear();
    taskNum = rand() % (MAXTASK - 10) + 10;
    Task tmpTask;
    for (int i = 0; i <= taskNum; i++) {
        tmpTask.init(_des);
        tmpTask.startPos = _des;
        taskPool.push_back(tmpTask);
    }
}
