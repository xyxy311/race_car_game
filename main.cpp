#include "support.h"
#include "car.h"
#include <iostream>

// 玩家的车
int main() {
    hideCursor();
    SetWindowSize(50, 12);
    Player playercar;
    playercar.controll();
    gotoXY(5,5);
    system("pause");
}