#include "sendpos.h"
#include <stdlib.h>
#include <time.h>
#include "pos.h"

sendPos::sendPos()
{
    neighbnum = -1;
}

void sendPos::init(DES local)
{
    _location = local;
    pos tmp(local);
    neighbnum = tmp.neighbnum;
    neighbs = tmp.neighbs;
    taskNum = 0;
}

void sendPos::regenerate()
{
    taskPool.clear();
    taskNum = rand() % (MAXTASK - 10) + 10;
    Task tmpTask;
    int j = 0;
    switch (_location) {
    case A:{
        for (int i = 0; i <= taskNum; i++) {
            tmpTask.init(I);
            tmpTask.startPos = _location;
            taskPool.push_back(tmpTask);
        }
        break;
    }
    case B:{
        for (int i = 0; i <= taskNum; i++) {
            j = rand() % 3;
            tmpTask.init((j == 0) ? D : ((j == 1) ? E : F));
            tmpTask.startPos = _location;
            taskPool.push_back(tmpTask);
        }
        break;
    }
    case C:{
        for (int i = 0; i <= taskNum; i++) {
            j = rand() % 2;
            tmpTask.init((j == 0) ? H : G);
            tmpTask.startPos = _location;
            taskPool.push_back(tmpTask);
        }
        break;
    }
    default:
        break;
    }

}
