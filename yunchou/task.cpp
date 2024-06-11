#include "task.h"
#include <stdlib.h>
#include <time.h>

// Task类的默认构造函数
Task::Task()
{
    volume = 0;
    // destination默认为A
}

// Task类的构造函数，带有参数
Task::Task(DES des, int secDes, int vol, DES start)
{
    destination = des;
    secondDes = secDes;
    volume = vol;
    startPos = start;
}

// 初始化任务
void Task::init(DES des)
{
    volume = 10; // 设置初始体积为10
    int i = (rand() % 5 + 1) * (rand() % 100 > 97 ? 1 : 0); // 2%的概率生成远距离目标
    i = (des - 4 + i) % 6 + 4;
    destination = (DES)i; // 设置目标位置
    switch (destination) {
    case D: {
        secondDes = rand() % 6; // 第二目标在0到5之间
        break;
    }
    case E: {
        secondDes = rand() % 10; // 第二目标在0到9之间
        break;
    }
    case F: {
        secondDes = rand() % 10; // 第二目标在0到9之间
        break;
    }
    case I: {
        secondDes = rand() % 8; // 第二目标在0到7之间
        break;
    }
    case H: {
        secondDes = rand() % 7; // 第二目标在0到6之间
        break;
    }
    case G: {
        secondDes = rand() % 9; // 第二目标在0到8之间
        break;
    }
    default:
        break;
    }
}

// 设置任务
void Task::setTask(DES des, int secDes, int vol, DES start)
{
    destination = des;
    secondDes = secDes;
    volume = vol;
    startPos = start;
}

// 完成任务
void Task::finish()
{
    _settled = true;
}

// 重置任务
void Task::reset()
{
    _settled = false;
}

// 检查任务是否完成
bool Task::check()
{
    return _settled;
}
