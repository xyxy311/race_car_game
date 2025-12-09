#ifndef SUPPORT_H
#define SUPPORT_H

// 设置窗口格式
void setWindowFormat(int cols, int lines);

// 隐藏光标
void hideCursor();

// 设置光标位置
void gotoXY(const int x, const int y);

// 设置文本颜色
void setColor(int color);

// 读取按键
char readKey();

// 生成随机数
int getRandomInt(int min, int max);

# endif // SUPPORT_H