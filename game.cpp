#include "game.h"
#include "support.h"
#include "map.h"
#include "car.h"
#include "menu.h"
#include <windows.h>
#include <iostream>

// 游戏初始化
void Game::gameInit() {
    notNoStop = (showMenu() == 'u' ? true : false);
}

// 游戏运行中
void Game::run() {
    // 地图绘制
    system("cls");
    boundary();

    // 无敌模式下的提示信息
    if (!notNoStop) {
        gotoXY(16, 1);
        std::cout << "Enjoy your drive!";
        gotoXY(16, 2);
        std::cout << "Ctrl+C to quit";
    }

    // 显示玩家车
    playercar.drawShape();

    // 主循环
    while (1) {
        clearScreen();
        update();  // 在这里使用缓冲输入方便测试
        drawScreen();
        panel();
        if (notNoStop && isCollision()) {
            break;
        }
        Sleep(1 / playercar.velocity * 1000);
    }

}

// 游戏结束
void Game::close() {
    Sleep(1000);
    system("cls");
    gotoXY(3,11);
    std::cout << "GAME OVER!";
    gotoXY(3,12);
    std::cout << "You've driven " << s << " meters" << std::endl;
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
void Game::update() {

    // 移动玩家车
    if (playercar.isexist) {
        playercar.controlMove();
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
    time++;
    if (time >= timeTo) {
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

// 速度仪表
void Game::panel() {
    int speed = (int) (playercar.velocity * 3.6);
    
    // 显示车速数值
    gotoXY(16, 27);
    printf("%4dkm/h", speed);

    // 显示图形表示车速
    gotoXY(16, 26);
    std::cout << "speed";
    for (int i = 0; i < speed/10; i++) {
        gotoXY(16, 25 - i);
        std::cout<<"▇";
    }
    for (int i = speed/10; i < 20; i++) {
        gotoXY(16, 25 - i);
        std::cout<<" ";
    }

    // 显示里程
    gotoXY(16, 28);
    printf("%4dm", s++);
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
