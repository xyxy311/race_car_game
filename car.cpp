#include "support.h"
#include "car.h"
#include "windows.h"
#include <iostream>
#include <string>

// 车的移动
void Car::move(int deltaX, int deltaY) {
    clearShape();
    x += deltaX;  // 更新位置
    y += deltaY;
    drawShape();
}

// 绘制车的形状
void Car::drawShape() {
    for (int i = 0; i < longth; i++) {
        gotoXY(x, y + i); // 定位到第 i 行
        std::cout << shape.substr(i * width, width) << std::flush;
    }
}

// 擦除车的形状
void Car::clearShape() {
    gotoXY(x, y);
    for (int i = 0; i < longth; i++) {
        gotoXY(x, y + i);
        std::cout << std::string(width, ' ') << std::flush;
    }
}


// 玩家车的构造函数
Player::Player(){
            x = 6; // 道路宽14时，车辆刚好在中间位置
            y = 16;
            width = 3;
            longth = 3;
            relativeVelocity = 0;
            isexist = true;
            shape = "{^}|0|{_}";
        }

// 障碍车
Obstacle::Obstacle() {
    y = 0;
    width = 3;
    longth = 3;
    relativeVelocity = 1;
    shape = "[|](0)[_]";

    switch (getRandomInt(1,4)) {
        case 1:
            x = 1;
            break;
        case 2:
            x = 4;
            break;
        case 3:
            x = 7;
            break;
        case 4:
            x = 10;
            break;
    }
}

// 障碍车自动移动
void Obstacle::autoMove() {
    if (isexist) {
        move(0, relativeVelocity);
        if (y >= 23) {
            clearShape(); // 超出道路则销毁
            isexist = false;
        }
    }
}