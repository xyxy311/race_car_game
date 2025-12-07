#ifndef GAME
#define GAME

#include "car.h"

class Game {
    public:
        void gameInit();
        void run();
        void close();

    private:
        Player playercar;
        Obstacle obcars[3] = {}; // 障碍车组
        int obcarsNum = 0;     // 障碍车数量
        int time = 0;     // time决定投放时机

        // 投放障碍车主函数
        void giveCar();

        // 从车组投放一辆障碍车，放在第num车道上，速度为relativeVelocity
        void giveOneCar(int num, int relativeVelocity);

        // 更新游戏
        void update(char input);

        // 碰撞检测
        bool isCollision();

};

#endif  // GAME