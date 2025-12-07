#ifndef MAP
#define MAP
/* 
车道类：
    type：最后投放障碍车的类型，0为初始值
    time：用来计时，配合type改变status
    status只储存0、1、2、3
        0：不可投放障碍车
        1：可投 relativeVelocity(等于type)=1 的车
        2：可投 relativeVelocity=1或2 的车
        3：可投 任何车
*/
class Lane{

    public:
        int type = 0;
        int time = 0;
        int status = 3;
        
        // 更新属性（随时间更新、投放障碍车时更新）
        void updateByTime();
        void updateByOb(int type);
};
        
// 绘制道路边界
void boundary();

#endif //MAP