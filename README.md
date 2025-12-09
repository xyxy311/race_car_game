该项目使用utf-8编码  
只能在Windows系统中运行

# 介绍

这是一款赛车游戏，玩家需要驾驶一辆车躲避道路上随机出现的车，尽可能开得远  
在开始菜单可以使用 W 、 S 和 回车键 选择模式。  
- Normal 为正常模式，撞到障碍车会结束游戏，并显示你开了多少米。  
- No stop 为无敌模式，无视所有碰撞，想咋开就咋开。  

**键位说明**  
W：加速  
S：减速  
A/D：小幅左右移动  
Q/E：大幅左右移动  

# 项目结构

cc_car/

    CmakeLists.txt  
    README.md  

    bin/                    存放二进制文件
        ccracecar.exe           游戏的可执行文件  
    include/                存放头文件  
        car.h  
        game.h  
        map.h  
        menu.h  
        support.h  
    src/                    存放源文件  
        core/                   游戏主体
            game.cpp                Game对象  
            main.cpp                游戏入口  
        module/                 游戏的各个模块  
            car.cpp                 包括障碍车和玩家车  
            map.cpp                 车道对象、绘制道路函数  
            menu.cpp                进入游戏的主菜单
        tools/                  一些功能  
            support.cpp             如隐藏光标，设置光标位置等等

# 构建方式

使用MinGW构建方式如下：
在控制台中切换到cc_car目录，执行以下命令：
```
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
mingw32-make
```
运行后会在 bin 目录中生成 ccracecar.exe