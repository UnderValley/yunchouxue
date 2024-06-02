#include "task.h"
#include <stdlib.h>
#include <time.h>

Task::Task()
{
    volume = 0;
//    destination = A;
}

void Task::init(DES des)
{
    volume = rand() % MAXVOL + 1;
    int i = des + (rand() % 3 + 1) * (rand() % 100 > 97 ? 1 : 0) - 1; // 2% 的概率变成较远目的地
    i = i % 4 + 1;
    destination = (DES) i;
}
