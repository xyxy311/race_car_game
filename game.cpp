#include "game.h"
#include "support.h"
#include "map.h"
#include "car.h"
#include "windows.h"
#include <iostream>

// 游戏主菜单界面
void Game::gameInit() {
    system("cls");
    hideCursor();

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
    playercar.move(0, 0);

    while (1) {
        update(readKey());
        if (isCollision()) {
            break;
        }
        Sleep(50);
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
    if (playercar.isexist) {
        switch (input) {
            case 'a':
                playercar.move(-1, 0);
                break;
            case 'd':
                playercar.move(1, 0);
                break;
        }
    }

    obcar.autoMove();
}

// 碰撞判断
bool Game::isCollision() {
    if (playercar.x == 0 || playercar.x == 11) {
        // 到了道路边界还左（右）移动则判断碰撞
        playercar.isexist = false;
        return true;
    }
    return false;
}
