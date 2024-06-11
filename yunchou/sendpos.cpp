#include "sendpos.h"
#include <stdlib.h>
#include <time.h>
#include "pos.h"

#define INF 100000000
using namespace std;

sendPos::sendPos()
{
    neighbnum = -1;
}

void sendPos::init(DES local)
{
    _location = local;
    pos tmp;
    tmp.init(local);
    neighbnum = tmp.neighbs.size();
    neighbs = tmp.neighbs;
    taskNum = 0;
}

void sendPos::regenerate()
{

    taskPool.clear();
    if (_location == C) {
        taskNum = GHBASE + rand() % GHOFFSET;
    }
    else {
        taskNum = TASKBASE + rand() % TASKOFFSET;
    }

    Task tmpTask;
    int j = 0;
    int i = 0;
    switch (_location) {
    case A: {
        for (i = 0; i < taskNum; i++) {
            tmpTask.init(I);
            tmpTask.startPos = _location;
            taskPool.push_back(tmpTask);
        }
        taskNum += GHBASE + rand() % GHOFFSET;
        for (i; i < taskNum; i++) {
            j = rand() % 2;
            tmpTask.init((j == 0) ? H : G);
            tmpTask.startPos = _location;
            taskPool.push_back(tmpTask);
        }
        break;
    }
    case B: {
        for (i = 0; i < taskNum; i++) {
            j = rand() % 3;
            tmpTask.init((j == 0) ? D : ((j == 1) ? E : F));
            tmpTask.startPos = _location;
            taskPool.push_back(tmpTask);
        }
        taskNum += GHBASE + rand() % GHOFFSET;
        for (i; i < taskNum; i++) {
            j = rand() % 2;
            tmpTask.init((j == 0) ? H : G);
            tmpTask.startPos = _location;
            taskPool.push_back(tmpTask);
        }
        break;
    }
    case C: {
        for (i = 0; i < taskNum; i++) {
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
    cout << _location << ' ' << taskNum << endl;
}

void sendPos::resetTask()
{
    for (int i = 0; i < taskNum; i++) {
        taskPool[i].reset();
    }
}

DES sendPos::find_nearest_neighbour()
{
    int min_dis = INF;
    DES min_n = _location;
    for (int i = 0; i < neighbnum; i++)
    {
        if (check_task(neighbs[i].first) && min_dis > neighbs[i].second)
        {
            min_dis = neighbs[i].second;
            min_n = neighbs[i].first;
        }
    }
    return min_n;
}

// check if there is a task in the destination first
bool sendPos::check_task(DES des)
{
    vector<Task> tmp;
    find_task_first(tmp, des);
    int size = tmp.size();
    for (int i = 0; i < size; i++) {
        if (tmp[i].check() == false) return true;
    }
    return false;
}

//find the task in the destination first
void sendPos::find_task_first(vector<Task>& taskList, DES target)
{
    vector<Task> tmpList;
    taskList.clear();
    for (int i = 0; i < taskNum; i++)
    {
        if (taskPool[i].destination == target && taskPool[i].startPos == _location)
        {
            tmpList.push_back(taskPool[i]);
        }
    }
    taskList = tmpList;
}
