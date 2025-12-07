#ifndef CAR
#define CAR

#include <string>

class Game; //前向声明

// 车的基类
class Car {
    friend class Game;

    public:
        
        // 绘制车的形状
        void drawShape();

        // 擦除车的形状
        void clearShape();

        // 汽车移动
        void move(int deltaX, int deltaY);
        void moveToXY(int x, int y);

    protected:
        int x;  // 位置以车辆左上处为准
        int y;
        int width;
        int longth;
        int relativeVelocity;
        std::string shape;
        bool isexist;  // 是否存在
};

// 玩家的赛车
class Player:public Car {
    public:
        Player();
        void controlMove(char input);
};

// 障碍车
class Obstacle:public Car {
    public:
        Obstacle();
        void generate(int num, int type = 1); // 生成障碍车
        void autoMove();
        void deleteObcar();  // 销毁障碍车
};

#endif //CAR