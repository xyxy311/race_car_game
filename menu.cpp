#ifndef MENU_H
#define MENU_H

#include "menu.h"
#include "support.h"
#include <iostream>
#include <windows.h>

#define C_BULE 23        // C表示颜色，这是白色蓝底
#define C_NORMAL 7       // 这是正常文本颜色，白色
#define C_HIGHLIGHT 103  // 高亮文本颜色

// 展示菜单
char showMenu() {
    
    system("cls");
    setWindowFormat(30, 40);
    hideCursor(); // 隐藏光标

    gotoXY(4,5);
    setColor(C_BULE);
    std::cout << "Welcome to CC Race Car!";
    setColor(C_NORMAL);

    gotoXY(10,10);
    std::cout << "Please select the mode";

    gotoXY(20,13);
    std::cout << "Normal";
    gotoXY(20,15);
    std::cout << "No stop";

    char choice = 0; // 记录用户选择的选项
    char c;          // 记录键盘输入
    while (1) {

        char c = readKey();
        if (choice && c == 'y') {
            break;
        }

        choice = (c == 'n' || c== 'y') ? choice : c;  // 无按键按下或按回车时choice不变

        if (choice == 'u') {
            setColor(C_HIGHLIGHT);
        }
        gotoXY(20,13);
        std::cout << "Normal";
        setColor(C_NORMAL);

        if (choice == 'd') {
            setColor(C_HIGHLIGHT);
        }
        gotoXY(20,15);
        std::cout << "No stop";
        setColor(C_NORMAL);
    }
    return choice;

}

#endif // MENU_H