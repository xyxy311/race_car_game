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

    // 显示玩家车
    playercar.drawShape();

    // 主循环
    while (1) {
        clearScreen();
        update(readKey());  // 在这里使用缓冲输入方便测试
        drawScreen();
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

// 清除画面（只包括车）
void Game::clearScreen() {
    playercar.clearShape();
    for (auto& obcar : obcars) {
        if (obcar.isexist) {
            obcar.clearShape();
        }
    }
}

// 更新游戏
void Game::update(char input) {

    // 移动玩家车
    if (playercar.isexist) {
        playercar.controlMove(input);
    }
    
    // 更新道路状态
    for (auto& lane : lanes) {
        lane.updateByTime();
    }

    // 投放障碍车
    giveCar();

    // 移动障碍车
    for (auto& obcar : obcars) {
        if (obcar.isexist) {
            obcar.autoMove();
            if (obcar.y > 22) {  // 如果超出道路下边界则销毁
                obcar.deleteObcar();
            }
        }
    }

    /*-------测试---------测试---------测试---------测试---------测试---------*/
    // int obcarsNum = 0;
    // for (auto& obcar : obcars) {
    //     if (obcar.isexist) {
    //         obcarsNum++;
    //     }
    // }
    // gotoXY(20,12);
    // std::cout << "障碍车数量" << obcarsNum;
    // gotoXY(20,13);
    // printf("time = %2d",time);
    // gotoXY(20,14);
    // std::cout << "status type time";
    // for (int i = 0; i < 4; i++) {
    //     gotoXY(20, 15+i);
    //     printf("%2d : %2d、%2d、%2d",i+1,lanes[i].status,lanes[i].type,lanes[i].time);
    // }
    // n1++;
    // gotoXY(20, 20);
    // std::cout << "update: " << n1;
    /*-------测试---------测试---------测试---------测试---------测试---------*/
}

// 渲染画面（只包括车）
void Game::drawScreen() {
    playercar.drawShape();
    for (auto& obcar : obcars) {
        if (obcar.isexist) {
            obcar.drawShape();
        }
    }
}

// 投放障碍车
void Game::giveCar() {

    /*-----测试-----测试-----测试-----测试-----测试-----*/
    // n3++;
    // gotoXY(20, 22);
    // printf("giveCar : %3d",n3);
    /*-----测试-----测试-----测试-----测试-----测试-----*/

    time++;
    if (time >= 3) {
        switch (getRandomInt(1, 3)) {

            // 2/3的概率投放1量车
            case 1:
            case 2:
                giveOneCar(getRandomInt(1, 4));
                break;

            // 1/3的概率投放2量车
            case 3:
                giveOneCar(getRandomInt(1, 4));
                giveOneCar(getRandomInt(1, 4));
                break;
        }
        time = 0;
    }
}

// 投放一辆障碍车
void Game::giveOneCar(int num) {
    switch (lanes[num-1].status) {
        case 0:
            break;

        case 1:
            for (auto& obcar : obcars) {
                if (!obcar.isexist) {
                    int obtype = 1;
                    obcar.generate(num, obtype);
                    lanes[num-1].updateByOb(obtype);
                    break;
                }
            }

        case 2:
            for (auto& obcar : obcars) {
                if (!obcar.isexist) {
                    int obtype = getRandomInt(1, 2);
                    obcar.generate(num, obtype);
                    lanes[num-1].updateByOb(obtype);
                    break;
                }
            }

        case 3:
            for (auto& obcar : obcars) {
                if (!obcar.isexist) {
                    int obtype = getRandomInt(1, 3);
                    obcar.generate(num, obtype);
                    lanes[num-1].updateByOb(obtype);
                    break;
                }
            }
    }
}

// 碰撞判断
bool Game::isCollision() {

    // 判断是否与路边护栏碰撞
    if (playercar.x <= 0 || playercar.x >= 11) {
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
                playercar.isexist = false;
                obcar.isexist = false;
                return true;
            }
        }
    }
    return false;
}
