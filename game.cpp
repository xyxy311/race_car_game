#include "game.h"
#include "support.h"
#include "map.h"
#include "car.h"
#include "windows.h"
#include <iostream>

// 游戏初始化
void Game::gameInit() {
    system("cls");
    hideCursor(); // 隐藏光标

    gotoXY(4,11);
    std::cout << "CC飞车";

    gotoXY(4,15);
    std::cout << "按回车键开始游戏";
    getchar();
}

// 游戏运行中
void Game::run() {

    // 地图绘制
    system("cls");
    boundary();

    // 初始化玩家车
    playercar.moveToXY(6, 16);
    playercar.drawShape();

    // 初始化障碍车
    for (auto &obcar : obcars) {
        obcar.isexist = false;
    }

    // 主循环
    while (1) {
        update(readKey());
        if (isCollision()) {
            break;
        }
        Sleep(100);
    }

}

// 游戏结束
void Game::close() {
    Sleep(1000);
    system("cls");
    gotoXY(3,11);
    std::cout << "GAME OVER!" << std::endl;
    system("pause");
}

// 更新游戏
void Game::update(char input) {

    // 移动玩家车
    if (playercar.isexist) {
        playercar.controlMove(input);
    }

    // 投放障碍车
    giveCar();

    // 移动障碍车
    for (auto& obcar : obcars) {
        if (obcar.isexist) {
            obcar.autoMove();
        }
    }

    /*-------测试---------*/
    obcarsNum = 0;
    for (auto& obcar : obcars) {
        if (obcar.isexist) {
            obcarsNum++;
        }
    gotoXY(20,12);
    std::cout << "障碍车数量" << obcarsNum;
    }
    /*-------测试---------*/
}

// 投放一辆障碍车
void Game::giveOneCar(int num, int type) {
    for (auto& obcar : obcars) {
        if (!obcar.isexist) {
            obcar.generate(num, type);
            break;
        }
    }
}

// 投放障碍车
void Game::giveCar() {
    if (time == 10) {  // time积累到10时投放
        switch (getRandomInt(1, 3)) {

            // 2/3的概率投放1量车
            case 1:
            case 2:
                giveOneCar(getRandomInt(1, 4), getRandomInt(1, 3));
                time = 0;
                break;

            // 1/3的概率投放2量车
            case 3:
                for (int i = 0, j, k; i < 2; i++) {

                    // 确定投放车道j、k的值
                    switch (j = getRandomInt(1, 4)) {
                        case 1:
                        case 2:
                            k = getRandomInt(j + 1, 4);
                            break;
                        case 3:
                        case 4:
                            k = getRandomInt(1, j - 1);
                            break;    
                    }
                    giveOneCar(j, getRandomInt(1, 3));
                    giveOneCar(k, getRandomInt(1, 3));
                }
                time = -5;
                break;
        }
    }
    time++; // 积累time
}

// 碰撞判断
bool Game::isCollision() {

    // 判断是否与路边护栏碰撞
    if (playercar.x == 0 || playercar.x == 11) {
        // 到了道路边界还左（右）移动则判断碰撞
        playercar.isexist = false;
        return true;
    }

    // 判断是否与障碍车碰撞
    int pL = playercar.x;  // 玩家车左边界
    int pR = playercar.x + playercar.width - 1;
    int pU = playercar.y;   // 玩家车上边界
    int pD = playercar.y + playercar.longth - 1;
    
    for (auto& obcar : obcars) { //遍历障碍车以判断碰撞
        if (obcar.isexist) {
            int oL = obcar.x;  // 障碍车左边界
            int oR = obcar.x + obcar.width - 1;
            int oU = obcar.y;
            int oD = obcar.y + obcar.longth - 1;

            if (pL <= oR && pR >= oL && pU <= oD && pD >= oU) {
                return true;
            }
        }
    }
    return false;
}
