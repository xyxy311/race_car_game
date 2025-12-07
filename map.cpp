#include "support.h"
#include "map.h"
#include <iostream>

// 绘制道路边界
void boundary() {
    for (int i = 0; i < 24; i++) {
        gotoXY(0, i);
        std::cout << "|";
        gotoXY(13, i);
        std::cout << "|";
    }
}

// 更新属性（随时间）
void Lane::updateByTime() {
    time++;
    switch (type) {
        case 1:
            if (time < 8)
                status = 0;
            else if (time < 14)
                status = 1;
            else if (time < 18)
                status = 2;
            else 
                status = 3;
            break;
        case 2:
            if (time < 3)
                status = 0;
            else if (time < 8)
                status = 2;
            else
                status = 3;
            break;
        case 3:
            if (time < 3)
                status = 0;
            else
                status = 3;
            break;
    }
}

void Lane::updateByOb(int type) {
    this->type = type;
    time = 0;
    status = 0;
}