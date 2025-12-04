#ifndef CAR
#define CAR

#include <string>

// 车的基类
class Car {
    public:
        int x;  // 位置以车辆左上处为准
        int y;
        int width;
        int longth;
        int relativeVelocity;
        std::string shape;

        void controll();
        void move(int deltaX, int deltaY);
    protected:

        // 绘制车的形状
        void drawShape();

        // 擦除车的形状
        void clearShape();
        
};

// 玩家的赛车
class Player:public Car {
    public:
        Player();
    private:

};

#endif //CAR