#include "pos.h"
#include "worldModule.h"

pos::pos() = default;

void pos::init(DES des)
{
    switch (des) {
    case A: {   // ��Ȫ���վ
      // neighbs.push_back(std::pair<DES, int> (D, 707));
        neighbs.push_back(std::pair<DES, int>(G, 1271));
        neighbs.push_back(std::pair<DES, int>(H, 900));
        neighbs.push_back(std::pair<DES, int>(I, 1));
        break;
    }
    case B: {    // ��ɳ��վ
        neighbs.push_back(std::pair<DES, int>(D, 2));
        neighbs.push_back(std::pair<DES, int>(E, 1));
        neighbs.push_back(std::pair<DES, int>(F, 3));
        neighbs.push_back(std::pair<DES, int>(G, 1569));
        neighbs.push_back(std::pair<DES, int>(H, 1706));
        break;
    }
    case C: {    // ����
        neighbs.push_back(std::pair<DES, int>(H, 1356));
        neighbs.push_back(std::pair<DES, int>(G, 691));
        break;
    }
    case D: {    // ����
        neighbs.push_back(std::pair<DES, int>(A, 707));
        neighbs.push_back(std::pair<DES, int>(B, 2));
        // neighbs.push_back(std::pair<DES, int> (E, 235));
        // neighbs.push_back(std::pair<DES, int> (F, 174));
        // neighbs.push_back(std::pair<DES, int> (G, 1400));
        sonDist.push_back(356);
        sonDist.push_back(358);
        sonDist.push_back(399);
        sonDist.push_back(424);
        sonDist.push_back(440);
        sonDist.push_back(474);
        break;
    }
    case E: {    // ����
        neighbs.push_back(std::pair<DES, int>(A, 945));
        neighbs.push_back(std::pair<DES, int>(B, 1));
        // neighbs.push_back(std::pair<DES, int> (D, 174));
        // neighbs.push_back(std::pair<DES, int> (F, 267));
        // neighbs.push_back(std::pair<DES, int> (G, 1500));
        sonDist.push_back(165);
        sonDist.push_back(166);
        sonDist.push_back(183);
        sonDist.push_back(211);
        sonDist.push_back(214);
        sonDist.push_back(251);
        sonDist.push_back(251);
        sonDist.push_back(259);
        sonDist.push_back(268);
        sonDist.push_back(286);

        break;
    }
    case F: {    // �Ʒ�
        neighbs.push_back(std::pair<DES, int>(A, 710));
        neighbs.push_back(std::pair<DES, int>(B, 3));
        // neighbs.push_back(std::pair<DES, int> (D, 174));
        // neighbs.push_back(std::pair<DES, int> (E, 267));
        // neighbs.push_back(std::pair<DES, int> (G, 1300));
        sonDist.push_back(301);
        sonDist.push_back(307);
        sonDist.push_back(312);
        sonDist.push_back(351);
        sonDist.push_back(360);
        sonDist.push_back(411);
        sonDist.push_back(419);
        sonDist.push_back(461);
        sonDist.push_back(465);
        sonDist.push_back(468);
        break;
    }
    case G: {    // ����
        neighbs.push_back(std::pair<DES, int>(A, 1271));
        neighbs.push_back(std::pair<DES, int>(B, 1569));
        neighbs.push_back(std::pair<DES, int>(C, 691));
        // neighbs.push_back(std::pair<DES, int> (D, 1400));
        // neighbs.push_back(std::pair<DES, int> (E, 1500));
        // neighbs.push_back(std::pair<DES, int> (F, 1300));
        // neighbs.push_back(std::pair<DES, int> (H, 790));
        sonDist.push_back(1);
        sonDist.push_back(2);
        sonDist.push_back(3);
        sonDist.push_back(4);
        sonDist.push_back(5);
        sonDist.push_back(6);
        sonDist.push_back(7);
        sonDist.push_back(8);
        sonDist.push_back(9);
        break;
    }
    case H: {    // ���
        neighbs.push_back(std::pair<DES, int>(A, 900));
        neighbs.push_back(std::pair<DES, int>(B, 1706));
        neighbs.push_back(std::pair<DES, int>(C, 1356));
        // neighbs.push_back(std::pair<DES, int> (I, 694));
        // neighbs.push_back(std::pair<DES, int> (G, 790));
        sonDist.push_back(1);
        sonDist.push_back(2);
        sonDist.push_back(3);
        sonDist.push_back(4);
        sonDist.push_back(5);
        sonDist.push_back(6);
        sonDist.push_back(7);
        break;
    }
    case I: {    // ��Ȫ
        neighbs.push_back(std::pair<DES, int>(A, 1));
        // neighbs.push_back(std::pair<DES, int> (H, 694));
        sonDist.push_back(61);
        sonDist.push_back(70);
        sonDist.push_back(126);
        sonDist.push_back(245);
        sonDist.push_back(258);
        sonDist.push_back(290);
        sonDist.push_back(441);
        sonDist.push_back(534);
        break;
    }
    }
    neighbnum = neighbs.size();
}

bool pos::find_task_second(std::vector<Task>& task_first, std::vector<Task>& task_second, int des_second) {
    bool flag = false;
    task_second.clear();
    for (int i = 0; i < task_first.size(); i++)
    {
        if (task_first[i].check() == false && task_first[i].secondDes == des_second)
        {
            task_second.push_back(task_first[i]);
            flag = true;
        }
    }
    return flag;
}

int pos::find_nearest_son(std::vector<Task>& task_first, std::vector<Task>& task_second) {
    int min_index;
    bool flag = false;
    for (int i = 0; i < sonDist.size(); i++) {
        if (find_task_second(task_first, task_second, i)) {
            if (flag == false) {
                min_index = i;
                flag = true;
            }
            else if (sonDist[i] < sonDist[min_index]) {
                min_index = i;
            }
        }
    }
    if (flag) {
        find_task_second(task_first, task_second, min_index);
        return min_index;
    }
    else return -1;
}
