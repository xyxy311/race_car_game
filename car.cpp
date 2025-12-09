#include "support.h"
#include "car.h"
#include "windows.h"
#include <iostream>
#include <string>

// 车的移动
void Car::move(int deltaX, int deltaY) {
    x += deltaX;  // 更新位置
    y += deltaY;

    // 防止越界
    if (x < 1)
        x = 1;
    if (x > 10)
        x = 10;
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
    x = 7; // 道路宽14时，车辆刚好在第3车道
    y = 16;
    width = 3;
    longth = 3;
    velocity = 17.0f;  //17.0代表17m/s 约等于 60km/h
    shape = "{^}|0|{_}";
    isexist = true;
}

// 玩家车控制函数
void Player::controlMove() {

    // 向左移动
        if (GetAsyncKeyState('A') & 0x8000)  // 检测A是否持续按下
            move(-1, 0);                     // 小幅持续移动
        if (GetAsyncKeyState('Q') & 0x0001)  // 检测Q是否刚被按下
            move(-3, 0);                     // 大幅一次性移动

    // 向右移动，和上面类似
        if (GetAsyncKeyState('D') & 0x8000)
            move(1, 0);
        if (GetAsyncKeyState('E') & 0x0001)
            move(3, 0);

    // 加速和减速
    if (GetAsyncKeyState('W') & 0x0001)
        velocity = velocity + 0.5f < 55.6f ? velocity + 0.5f : 55.6f; // 55.6为最大速度(200km/h)
    if (GetAsyncKeyState('S') & 0x0001)
        velocity = velocity - 3.5f > 10.0f ? velocity - 1.5f : 10.0f; // 10.0为最小速度(36km/h)

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
    x = 3 * num - 2; // 把车道序号(num)映射为x坐标
    y = 0;
    // 确定车型
    switch (type) {
        case 1:
            shape = "ioi(0)[_]";
            width = 3;
            longth = 3;
            relativeVelocity = 1;
            break;
        case 2:
            shape = "[|](0)[_]";
            width = 3;
            longth = 3;
            relativeVelocity = 2;
            break;
        case 3:
            shape = "o|0";
            width = 1;
            longth = 3;
            relativeVelocity = 3;
            x++;  // 确保摩托车在车道中间
            break;
    }
}

// 障碍车自动移动
void Obstacle::autoMove() {
    if (isexist) {
        move(0, relativeVelocity);
    }
}

// 销毁障碍车
void Obstacle::deleteObcar() {
    if (isexist) {
        clearShape();
        isexist = false;
    }
}