#include "support.h"
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