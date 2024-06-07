#ifndef SENDPOS_H
#define SENDPOS_H
#include <vector>
#include "task.h"
#include "worldModule.h"

namespace {
#define MAXTASK 30
#define MAXOFFSETHG 10
}

class sendPos
{
public:
    sendPos();
    void init(DES des);
    std::vector<Task> taskPool;
    int taskNum;
    void regenerate();
    std::vector<std::pair<DES, int>> neighbs;
    int neighbnum;

private:
    DES _location;
};

#endif // SENDPOS_H
