#ifndef POS_H
#define POS_H

#include <utility>
#include <vector>
#include "worldModule.h"

class pos
{
public:
    pos();
    pos(int location);
    std::vector<std::pair<DES, int>> neighbs;
    int neighbnum;
    double* sonDist;
    void init(DES des);
};

#endif // POS_H
