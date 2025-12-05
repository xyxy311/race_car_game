#ifndef SUPPORT
#define SUPPORT
// 设置窗口格式
void SetWindowSize(int cols, int lines);

// 隐藏光标
void hideCursor();

// 设置光标位置
void gotoXY(const int x, const int y);

// 获得键盘输入
char readKey();

// 生成随机数
int getRandomInt(int min, int max);

# endif // SUPPORT