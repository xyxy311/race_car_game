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
    system("cls");
    boundary();
    playercar.move(0, 0);  // 先显示玩家车

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

// 投放障碍车
void Game::giveCar() {
    if (time == 5) {  // time积累到5时投放
        time = 0;
        for (auto& obcar : obcars) {
            if (!obcar.isexist) {
                obcar.generate(getRandomInt(1, 4));
                return;
            }
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
