#ifndef GAME
#define GAME

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
        int time = -10;     // time决定投放时机

        // 投放障碍车主函数
        void giveCar();

        // 从车组投放一辆障碍车，放在第num车道上
        void giveOneCar(int num);

        // 清除画面（只包括车）
        void clearScreen();

        // 更新游戏
        void update(char input);

        // 渲染画面（只包括车）
        void drawScreen();

        // 碰撞检测
        bool isCollision();

        // 测试用
        int n1=0,n2=0,n3=0;

};

#endif  // GAME