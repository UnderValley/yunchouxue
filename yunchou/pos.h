#pragma once

#ifndef POS_H
#define POS_H

#include <utility>
#include <vector>
#include "worldModule.h"
#include "task.h"

class pos
{
public:
    pos();
    std::vector<std::pair<DES, int> > neighbs;
    int neighbnum;
    std::vector<int> sonDist;
    void init(DES des);
    int find_nearest_son(std::vector<Task>& task_first, std::vector<Task>& task_second);
    bool find_task_second(std::vector<Task>& task_first, std::vector<Task>& task_second, int des_second);
};

#endif // POS_H
