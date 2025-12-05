#include "car.h"

class Game {
    public:
        void gameInit();
        void run();
        void close();

    private:
        Player playercar;
        Obstacle obcar;

        // 更新游戏
        void update(char input);

        // 碰撞检测
        bool isCollision();

};