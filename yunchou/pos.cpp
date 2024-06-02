#include "pos.h"

pos::pos()
{
    ;
}

pos::pos(int location)
{
    switch (location) {
    case 1:{    // 三大学园
        neighbs.push_back(std::pair<DES, int> (B, 12));
        neighbs.push_back(std::pair<DES, int> (C, 12));
        neighbs.push_back(std::pair<DES, int> (E, 12));
        neighbs.push_back(std::pair<DES, int> (F, 12));
        break;
        }
    case 2:{    // 医学院
        neighbs.push_back(std::pair<DES, int> (A, 12));
        neighbs.push_back(std::pair<DES, int> (D, 12));
        neighbs.push_back(std::pair<DES, int> (G, 12));
        break;
    }
    case 3:{    // 银泉生活区
        neighbs.push_back(std::pair<DES, int> (A, 12));
        neighbs.push_back(std::pair<DES, int> (D, 12));
        neighbs.push_back(std::pair<DES, int> (E, 12));
        break;
    }
    case 4:{    // 玉湖
        neighbs.push_back(std::pair<DES, int> (A, 12));
        neighbs.push_back(std::pair<DES, int> (D, 12));
        neighbs.push_back(std::pair<DES, int> (E, 12));
        break;
    }
    case 5:{    // 银泉快递站
        neighbs.push_back(std::pair<DES, int> (A, 12));
        neighbs.push_back(std::pair<DES, int> (C, 12));
        break;
    }
    case 6:{    // 白沙驿站
        neighbs.push_back(std::pair<DES, int> (A, 12));
        neighbs.push_back(std::pair<DES, int> (G, 12));
        break;
    }
    case 7:{    // 东四
        neighbs.push_back(std::pair<DES, int> (B, 12));
        neighbs.push_back(std::pair<DES, int> (F, 12));
        break;
    }

    default:
        break;
    }
}

void pos::init(DES des)
{
    pos tmp(des);
    neighbnum = tmp.neighbnum;
    neighbs = tmp.neighbs;
}
