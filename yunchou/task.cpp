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
    volume =  10;
    int i = (rand() % 5 + 1) * (rand() % 100 > 97 ? 1 : 0); // 2% �ĸ��ʱ�ɽ�ԶĿ�ĵ�
    i = (des - 4 + i) % 6 + 4;
    destination = (DES)i;
    switch (destination) {
    case D: {
        secondDes = rand() % 6; // ����6��
        break;
    }
    case E: {
        secondDes = rand() % 10; // ����10��
        break;
    }
    case F: {
        secondDes = rand() % 10; // �Ʒ�10
        break;
    }
    case I: {
        secondDes = rand() % 8; // ��Ȫ��֪��
        break;
    }
    case H: {
        secondDes = rand() % 7; // �����֪��
        break;
    }
    case G: {
        secondDes = rand() % 9; // ���²�֪��
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

void Task::reset()
{
    _settled = false;
}

bool Task::check()
{
    return _settled;
}
