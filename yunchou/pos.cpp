#include "pos.h"
#include "worldModule.h"

pos::pos()
{
    ;
}

pos::pos(int location)
{
    switch (location) {
    case A:{   // 银泉快递站
        neighbs.push_back(std::pair<DES, int> (D, 707));
        neighbs.push_back(std::pair<DES, int> (E, 945));
        neighbs.push_back(std::pair<DES, int> (F, 710));
        neighbs.push_back(std::pair<DES, int> (I, 225));
        break;
        }
    case B:{    // 白沙驿站
        neighbs.push_back(std::pair<DES, int> (D, 431));
        neighbs.push_back(std::pair<DES, int> (E, 209));
        neighbs.push_back(std::pair<DES, int> (F, 411));
        neighbs.push_back(std::pair<DES, int> (C, 1200));
        break;
    }
    case C:{    // 东四
        neighbs.push_back(std::pair<DES, int> (B, 1200));
        neighbs.push_back(std::pair<DES, int> (G, 1100));
        break;
    }
    case D:{    // 蓝田
        neighbs.push_back(std::pair<DES, int> (A, 707));
        neighbs.push_back(std::pair<DES, int> (B, 431));
        neighbs.push_back(std::pair<DES, int> (E, 235));
        neighbs.push_back(std::pair<DES, int> (F, 174));
        neighbs.push_back(std::pair<DES, int> (G, 1400));
        sonDist = sonDistD;
        break;
    }
    case E:{    // 丹青
        neighbs.push_back(std::pair<DES, int> (A, 945));
        neighbs.push_back(std::pair<DES, int> (B, 209));
        neighbs.push_back(std::pair<DES, int> (D, 174));
        neighbs.push_back(std::pair<DES, int> (F, 267));
        neighbs.push_back(std::pair<DES, int> (G, 1500));
        sonDist = sonDistE;
        break;
    }
    case F:{    // 云峰
        neighbs.push_back(std::pair<DES, int> (A, 710));
        neighbs.push_back(std::pair<DES, int> (B, 411));
        neighbs.push_back(std::pair<DES, int> (D, 174));
        neighbs.push_back(std::pair<DES, int> (E, 267));
        neighbs.push_back(std::pair<DES, int> (G, 1300));
        sonDist = sonDistF;
        break;
        }
    case G:{    // 澄月
        neighbs.push_back(std::pair<DES, int> (C, 1100));
        neighbs.push_back(std::pair<DES, int> (D, 1400));
        neighbs.push_back(std::pair<DES, int> (E, 1500));
        neighbs.push_back(std::pair<DES, int> (F, 1300));
        neighbs.push_back(std::pair<DES, int> (H, 790));
        sonDist = sonDistG;
        break;
    }
    case H:{    // 玉湖
        neighbs.push_back(std::pair<DES, int> (I, 694));
        neighbs.push_back(std::pair<DES, int> (G, 790));
        sonDist = sonDistH;
        break;
    }
    case I:{    // 银泉
        neighbs.push_back(std::pair<DES, int> (A, 225));
        neighbs.push_back(std::pair<DES, int> (H, 694));
        sonDist = sonDistI;
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
