#include "recpos.h"
#include <stdlib.h>
#include <time.h>
#include "pos.h"

RecPos::RecPos()
{
    neighbnum = -1;
}

void RecPos::init(DES des)
{
    _des = des;
    pos tmp(des);
    neighbnum = tmp.neighbnum;
    neighbs = tmp.neighbs;
    taskNum = 0;
}

void RecPos::regenerate()
{
    taskPool.clear();
    taskNum = rand() % (MAXTASK - 10) + 10;
    Task tmpTask;
    for (int i = 0; i <= taskNum; i++) {
        tmpTask.init(_des);
        taskPool.push_back(tmpTask);
    }
}
