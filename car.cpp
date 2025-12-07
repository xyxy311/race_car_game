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

void Car::moveToXY(int x, int y) {
    this->x = x;
    this->y = y;
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
    shape = "{^}|0|{_}";
    isexist = true;
}

// 玩家车控制函数
void Player::controlMove(char input) {
    switch (input) {

    //小幅移动
    case 'a':
        move(-1, 0);
        break;
    case 'd':
        move(1, 0);
        break;

    //大幅移动
    case 'q':
        move(-3, 0);
        break;
    case 'e':
        move(3, 0);
        break;
    }
}

// 障碍车
Obstacle::Obstacle() {
    x = 1;
    y = 0;
    width = 3;
    longth = 3;
    relativeVelocity = 2;
    shape = "[|](0)[_]";
    isexist = false;

}

// 生成
void Obstacle::generate(int num, int type) {
    isexist = true;
    this->x = 3 * num - 2; // 把车道序号(num)映射为x坐标

    // 确定车型
    switch (type) {
        case 1:
            break;
        case 2:
            shape = "/*\\(0)[_]";
            relativeVelocity = 1;
            break;
        case 3:
            shape = "o|0";
            width = 1;
            longth = 3;
            relativeVelocity = 3;
    }

    y = 0;
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