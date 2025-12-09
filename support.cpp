#include "support.h"
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <random>

// 设置窗口格式
void setWindowFormat(int cols, int lines) {
    system("title cc race car");  // 设置窗口标题

    char cmd[30];  // 设置缓冲区大小
    sprintf(cmd, "mode con cols=%d lines=%d", cols, lines);
    system(cmd);
}

// 隐藏光标
void hideCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  // 获取权限？

    CONSOLE_CURSOR_INFO cursorInfo;    // 读取当前光标配置，隐藏光标
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;

    SetConsoleCursorInfo(hConsole, &cursorInfo);   // 应用新配置
}

// 设置光标位置
void gotoXY(const int x, const int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position;
    position.X = static_cast<SHORT>(x); // 需要转化坐标值的类型
    position.Y = static_cast<SHORT>(y);
    SetConsoleCursorPosition(hConsole, position);
}

// 设置文本颜色
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// 读取按键（只用于菜单操作）
char readKey() {
    char key = getch();
        switch (key) {
            case 'w': // 上方向键
                return 'u';
            case 's': // 下方向键
                return 'd';
            case 13 : // 回车键
                return 'y';
        }
    return 'n';
}

// 生成[min, max]范围内的随机整数
int getRandomInt(int min, int max) {
    // 1. 静态随机数引擎和分布器（使用static确保只初始化一次）
    static std::random_device rd;                    // 硬件随机数种子（初始化引擎）
    static std::mt19937 rng(rd());                   // 随机数引擎（用硬件种子初始化）
    static std::uniform_int_distribution<int> dist;  // 均匀分布器（默认范围，后续调整）

    // 2. 调整分布器范围
    dist.param(std::uniform_int_distribution<int>::param_type(min, max));

    // 3. 生成随机整数
    return dist(rng);
}
