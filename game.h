#include "car.h"

class Game {
    friend class test;
    public:
        void gameInit();
        void run();
        void close();

    private:
        Player playercar;
        Obstacle obcars[5] = {}; // 障碍车组
        int obcarsNum = 0;  // 障碍车数量
        int time = 0;  // time决定投放时机

        // 投放障碍车
        void giveCar();

        // 更新游戏
        void update(char input);

        // 碰撞检测
        bool isCollision();

};