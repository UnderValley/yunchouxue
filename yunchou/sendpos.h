#pragma once
#ifndef SENDPOS_H
#define SENDPOS_H
#include <vector>
#include "task.h"
#include "worldModule.h"
#include <iostream>
enum {
    TASKBASE = 20000,
    TASKOFFSET = 3000,
    GHBASE = 8000,
    GHOFFSET = 1000
};


class sendPos
{
public:
    std::vector<Task> taskPool;
    int taskNum;
    std::vector<std::pair<DES, int> > neighbs;
    int neighbnum;

    sendPos();
    void init(DES des);
    void regenerate();
    void resetTask();
    void find_task_first(std::vector<Task>& taskList, DES target);
    DES find_nearest_neighbour();
    bool check_task(DES des);
private:
    DES _location;
};

#endif // SENDPOS_H
