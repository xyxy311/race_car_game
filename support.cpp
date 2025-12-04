#include "support.h"
#include <windows.h>
#include <iostream>
#include <conio.h>

// 设置窗口格式
void SetWindowSize(int cols, int lines) {
    system("title cc飞车");  // 设置窗口标题

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

// 获得键盘输入
char readKey() {
    if (_kbhit()) {
        return _getch();
    }
    return '\0'; // 无按键
}