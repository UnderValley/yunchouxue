#ifndef RECPOS_H
#define RECPOS_H
#include <vector>
#include "task.h"
#include "worldModule.h"

namespace {
#define MAXTASK 100
}

class RecPos
{
public:
    RecPos();
    void init(DES des);
    std::vector<Task> taskPool;
    int taskNum;
    void regenerate();
    std::vector<std::pair<DES, int>> neighbs;
    int neighbnum;

private:
    DES _des;
};

#endif // RECPOS_H
