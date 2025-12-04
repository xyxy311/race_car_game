#include "car.h"
#include "support.h"
#include <iostream>
#include <string>

void Car::controll() {
            while (1) {
                switch (readKey()) {
                    case 'a':
                        move(-1, 0);
                        continue;
                    case 'd':
                        move(1, 0);
                        continue;
                    default:
                        continue;
                }
            }
        }
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
            x = 5; // 道路宽12时，车辆刚好在中间位置
            y = 4;
            width = 3;
            longth = 3;
            shape = "{^}|0|{_}";
        }