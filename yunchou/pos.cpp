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
        neighbs.push_back(std::pair<DES, int> (D, 12));
        neighbs.push_back(std::pair<DES, int> (E, 12));
        neighbs.push_back(std::pair<DES, int> (F, 12));
        neighbs.push_back(std::pair<DES, int> (I, 12));
        break;
        }
    case B:{    // 白沙驿站
        neighbs.push_back(std::pair<DES, int> (D, 12));
        neighbs.push_back(std::pair<DES, int> (E, 12));
        neighbs.push_back(std::pair<DES, int> (F, 12));
        neighbs.push_back(std::pair<DES, int> (C, 12));
        break;
    }
    case C:{    // 东四
        neighbs.push_back(std::pair<DES, int> (B, 12));
        neighbs.push_back(std::pair<DES, int> (G, 12));
        break;
    }
    case D:{    // 蓝田
        neighbs.push_back(std::pair<DES, int> (A, 12));
        neighbs.push_back(std::pair<DES, int> (B, 12));
        neighbs.push_back(std::pair<DES, int> (E, 12));
        neighbs.push_back(std::pair<DES, int> (F, 12));
        neighbs.push_back(std::pair<DES, int> (G, 12));
        sonDist = sonDistD;
        break;
    }
    case E:{    // 丹青
        neighbs.push_back(std::pair<DES, int> (A, 12));
        neighbs.push_back(std::pair<DES, int> (B, 12));
        neighbs.push_back(std::pair<DES, int> (D, 12));
        neighbs.push_back(std::pair<DES, int> (F, 12));
        neighbs.push_back(std::pair<DES, int> (G, 12));
        sonDist = sonDistE;
        break;
    }
    case F:{    // 三大学园
        neighbs.push_back(std::pair<DES, int> (A, 12));
        neighbs.push_back(std::pair<DES, int> (B, 12));
        neighbs.push_back(std::pair<DES, int> (D, 12));
        neighbs.push_back(std::pair<DES, int> (E, 12));
        neighbs.push_back(std::pair<DES, int> (G, 12));
        sonDist = sonDistF;
        break;
        }
    case G:{    // 澄月
        neighbs.push_back(std::pair<DES, int> (C, 12));
        neighbs.push_back(std::pair<DES, int> (D, 12));
        neighbs.push_back(std::pair<DES, int> (E, 12));
        neighbs.push_back(std::pair<DES, int> (F, 12));
        neighbs.push_back(std::pair<DES, int> (H, 12));
        sonDist = sonDistG;
        break;
    }
    case H:{    // 玉湖
        neighbs.push_back(std::pair<DES, int> (I, 12));
        neighbs.push_back(std::pair<DES, int> (G, 12));
        sonDist = sonDistH;
        break;
    }
    case I:{    // 银泉
        neighbs.push_back(std::pair<DES, int> (A, 12));
        neighbs.push_back(std::pair<DES, int> (H, 12));
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
