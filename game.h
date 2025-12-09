#ifndef GAME_H
#define GAME_H

#include "car.h"
#include "map.h"

class Game {
    public:
        void gameInit();
        void run();
        void close();

    private:
        Player playercar;

        Lane lanes[4];  // 四个车道
        
        Obstacle obcars[3]; // 障碍车组，3为最大数量
        int time = -10;     // time用来计时，和timeTo共同决定投放时机
        int timeTo = 3;     // time积累到timeTo时可投放障碍车，timeTo反映障碍车投放最小距离

        bool notNoStop;  // 是否为无敌模式

        // 投放障碍车主函数
        void giveCar();

        // 从车组投放一辆障碍车，放在第num车道上
        void giveOneCar(int num);

        // 清除画面（只包括车）
        void clearScreen();

        // 更新游戏
        void update();

        // 渲染画面（只包括车）
        void drawScreen();

        // 碰撞检测
        bool isCollision();

        // 仪表
        void panel();

        // 记录玩家车行驶里程（m）
        int s = 0;

};

#endif  // GAME_H