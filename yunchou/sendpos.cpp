#include "sendpos.h"
#include <stdlib.h>
#include <time.h>
#include "pos.h"

#define INF 100000000
using namespace std;

// sendPos类的默认构造函数
sendPos::sendPos()
{
    neighbnum = -1;
}

// 初始化函数，根据传入的DES类型设置位置和邻居信息
void sendPos::init(DES local)
{
    _location = local;
    pos tmp;
    tmp.init(local);
    neighbnum = tmp.neighbs.size();
    neighbs = tmp.neighbs;
    taskNum = 0;
}

// 重新生成任务池
void sendPos::regenerate()
{
    taskPool.clear();
    if (_location == C) {
        taskNum = GHBASE + rand() % GHOFFSET; // 如果位置是C，任务数在GHBASE和GHOFFSET之间
    }
    else {
        taskNum = TASKBASE + rand() % TASKOFFSET; // 其他位置，任务数在TASKBASE和TASKOFFSET之间
    }

    Task tmpTask;
    int j = 0;
    int i = 0;
    switch (_location) {
    case A: { // 如果位置是A
        for (i = 0; i < taskNum; i++) {
            tmpTask.init(I); // 初始化任务目标为I
            tmpTask.startPos = _location;
            taskPool.push_back(tmpTask);
        }
        taskNum += GHBASE + rand() % GHOFFSET;
        for (i; i < taskNum; i++) {
            j = rand() % 2;
            tmpTask.init((j == 0) ? H : G); // 初始化任务目标为H或G
            tmpTask.startPos = _location;
            taskPool.push_back(tmpTask);
        }
        break;
    }
    case B: { // 如果位置是B
        for (i = 0; i < taskNum; i++) {
            j = rand() % 3;
            tmpTask.init((j == 0) ? D : ((j == 1) ? E : F)); // 初始化任务目标为D、E或F
            tmpTask.startPos = _location;
            taskPool.push_back(tmpTask);
        }
        taskNum += GHBASE + rand() % GHOFFSET;
        for (i; i < taskNum; i++) {
            j = rand() % 2;
            tmpTask.init((j == 0) ? H : G); // 初始化任务目标为H或G
            tmpTask.startPos = _location;
            taskPool.push_back(tmpTask);
        }
        break;
    }
    case C: { // 如果位置是C
        for (i = 0; i < taskNum; i++) {
            j = rand() % 2;
            tmpTask.init((j == 0) ? H : G); // 初始化任务目标为H或G
            tmpTask.startPos = _location;
            taskPool.push_back(tmpTask);
        }
        break;
    }
    default:
        break;
    }
    cout << _location << ' ' << taskNum << endl; // 打印位置和任务数量
}

// 重置任务池中的所有任务
void sendPos::resetTask()
{
    for (int i = 0; i < taskNum; i++) {
        taskPool[i].reset();
    }
}

// 查找最近的邻居
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

// 检查指定位置是否有任务
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

// 查找指定位置的任务
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
