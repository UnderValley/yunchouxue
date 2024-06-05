#include "task.h"
#include <stdlib.h>
#include <time.h>

Task::Task()
{
    volume = 0;
//    destination = A;
}

Task::Task(DES des, int secDes, int vol, DES start)
{
    destination = des;
    secondDes = secDes;
    volume = vol;
    startPos = start;
}

void Task::init(DES des)
{
    volume = rand() % MAXVOL + 1;
    int i =(rand() % 5 + 1) * (rand() % 100 > 97 ? 1 : 0); // 2% 的概率变成较远目的地
    i = (des - 4 + i) % 6 + 4;
    destination = (DES) i;
    switch (destination) {
    case D: {
        secondDes = rand() % 6; // 蓝田6栋
        break;
    }
    case E: {
        secondDes = rand() % 6; // 丹青不知道几栋
        break;
    }
    case F: {
        secondDes = rand() % 10; // 云峰10
        break;
    }
    case I: {
        secondDes = rand() % 10; // 银泉不知道
        break;
    }
    case H: {
        secondDes = rand() % 10; // 玉湖不知道
        break;
    }
    case G: {
        secondDes = rand() % 10; // 澄月不知道
        break;
    }
    default:
        break;
    }
}

void Task::setTask(DES des, int secDes, int vol, DES start)
{
    destination = des;
    secondDes = secDes;
    volume = vol;
    startPos = start;
}

void Task::finish()
{
    _settled = true;
}

void Task::carry()
{
    _carried = true;
}

void Task::download()
{
    _carried = false;
}
