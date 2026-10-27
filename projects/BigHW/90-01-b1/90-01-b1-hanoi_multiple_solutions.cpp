/* 2154146 吴金轩 计科 */
#include <iostream>
#include <Windows.h>
#include <iomanip>
#include <conio.h>
#include "../include/cmd_console_tools.h"
using namespace std;

extern int num;
extern int sleep_time;
extern int top[3];
extern int stack[3][10];

/***************************************************************************
  函数名称：get_parameter
  功    能：输入汉诺塔的各项参数
  输入参数：int *n：层数的指针
            char *src：起始柱的指针
            char *dst：目标柱的指针
            char *temp：中间柱的指针
            char mode：选择的模式
  返 回 值：
  说    明：
***************************************************************************/
void get_parameter(int* n, char* src, char* dst, char* temp, char mode) {
    cout << endl << endl;
    cout << "请输入汉诺塔的层数(1-10)" << endl;
    cin >> *n;

    while (cin.fail() || (*n < 1) || (*n > 10)) {
        cin.clear();
        cin.ignore(65535, '\n');
        cout << "请输入汉诺塔的层数(1-10)" << endl;
        cin >> *n;
    }

    cin.ignore(65535, '\n');

    cout << "请输入起始柱(A-C)" << endl;
    cin >> *src;

    while (cin.fail() || (*src != 'A' && *src != 'B' && *src != 'C' && *src != 'a' && *src != 'b' && *src != 'c')) {
        cin.clear();
        cin.ignore(65535, '\n');
        cout << "请输入起始柱(A-C)" << endl;
        cin >> *src;
    }

    cin.ignore(65535, '\n');

    if (*src >= 'a' && *src <= 'c') {
        *src = *src - 32;
    }

    cout << "请输入目标柱(A-C)" << endl;
    cin >> *dst;

    if (*dst >= 'a' && *dst <= 'c') {
        *dst = *dst - 32;
    }

    while (cin.fail() || (*dst != 'A' && *dst != 'B' && *dst != 'C' && *dst != 'a' && *dst != 'b' && *dst != 'c') || *src == *dst) {
        cin.clear();
        cin.ignore(65535, '\n');
        if (*src == *dst) {
            cout << "目标柱(" << src << ")不能与起始柱(" << dst << ")相同" << endl;
        }
        cout << "请输入目标柱(A-C)" << endl;
        cin >> *dst;
        if (*dst >= 'a' && *dst <= 'c') {
            *dst = *dst - 32;
        }
    }

    cin.ignore(65535, '\n');

    *temp = 'A' + 'B' + 'C' - *src - *dst;

    if (mode == '4' || mode == '8') {
        cout << "请输入移动速度(0-5: 0-按回车单步演示 1-延时最长 5-延时最短)" << endl;
        cin >> sleep_time;

        while (cin.fail() || sleep_time > 5 || sleep_time < 0) {
            cin.clear();
            cin.ignore(65535, '\n');
            cout << "请输入移动速度(0-5: 0-按回车单步演示 1-延时最长 5-延时最短)" << endl;
            cin >> sleep_time;
        }
    }
}

/***************************************************************************
  函数名称：init_stack
  功    能：初始化起始柱的数组
  输入参数：int n：层数
            char src：起始柱
  返 回 值：
  说    明：
***************************************************************************/
void init_stack(int n, char src) {
    for (int i = 0; i <= (n - 1); i++) {
        stack[(int)(src - 'A')][i] = n - i;
    }

    top[(int)(src - 'A')] = n;
}

/***************************************************************************
  函数名称：print_stack_horizontal
  功    能：横向打印各柱上的盘号
  输入参数：int n：层数
            char src：起始柱
            char dst：目标柱
            char mode：选择的模式
  返 回 值：
  说    明：
***************************************************************************/
void print_stack_horizontal(int n, char src, char dst, char mode) {
    int space[3] = { 0 };
    char ch[3] = { 'A','B','C' };

    if (num == 0 && (mode == '4' || mode == '8' || mode == '9')) {
        cout << "初始:                 ";
    }
    else {
        if (mode != '1') {
            cout << "第" << setw(4) << num << " 步(";
        }
        cout << setw(2) << n << "#: " << src;
        if (mode == '1') {
            cout << "--";
        }
        cout << "-->" << dst;
        if (mode != '1') {
            cout << ") ";
        }
    }

    if (mode == '3' || mode == '4' || mode == '8' || mode == '9') {
        for (int k = 0; k < 3; k++) {
            cout << " " << ch[k] << ":";
            for (int i = 0; i < top[k]; i++) {
                cout << setw(2) << stack[k][i];
            }

            space[k] = 20 - 2 * top[k];
            for (int i = 0; i < space[k]; i++) {
                cout << " ";
            }
        }
    }
}

/***************************************************************************
  函数名称：print_stack_vertical
  功    能：纵向打印指定柱上的盘号
  输入参数：int n：层数
            char column：指定柱
            const int X：移动光标的X坐标
            const int Y：移动光标的Y坐标
  返 回 值：
  说    明：
***************************************************************************/
void print_stack_vertical(int n, char column, const int X, const int Y) {
    cct_gotoxy(X, Y);
    cout << "=========================" << endl;
    cct_gotoxy(X + 2, Y + 1);
    cout << "A         B         C";

    cct_gotoxy(X + 2 + 10 * (column - 'A'), Y - 1);

    for (int i = 0; i < top[(int)(column - 'A')]; i++) {
        cct_gotoxy(X + 2 + 10 * (column - 'A'), Y - 1 - i);
        cout << stack[(int)(column - 'A')][i];
    }
}

/***************************************************************************
  函数名称：modify_stack_vertical
  功    能：纵向打印各柱上的盘号
  输入参数：int n：层数
            char src：起始柱
            char dst：目标柱
            const int X：移动光标的X坐标
            const int Y：移动光标的Y坐标
  返 回 值：
  说    明：
***************************************************************************/
void modify_stack_vertical(int n, char src, char dst, const int X, const int Y) {
    char top_src = 0, top_dst = 0;

    top_src = top[(int)(src - 'A')];

    cct_gotoxy(X + 2 + 10 * (src - 'A'), Y - 1 - top_src);
    cout << " ";

    top_dst = top[(int)(dst - 'A')];
    cct_gotoxy(X + 2 + 10 * (dst - 'A'), Y - top_dst);
    cout << stack[(int)(dst - 'A')][top_dst - 1];
}

/***************************************************************************
  函数名称：step_by_step_operation_of_hanoi
  功    能：逐步操作汉诺塔
  输入参数：char src：起始柱
            char dst：目标柱
  返 回 值：
  说    明：
***************************************************************************/
void step_by_step_operation_of_hanoi(char src, char dst) {
    int temp_src = 0;

    temp_src = stack[(int)(src - 'A')][--top[(int)(src - 'A')]];
    stack[(int)(dst - 'A')][top[(int)(dst - 'A')]++] = temp_src;
}

/***************************************************************************
  函数名称：print_first_line
  功    能：打印空屏首行
  输入参数：int n：层数
            char src：起始柱
            char dst：目标柱
            char mode：选择的模式
  返 回 值：
  说    明：
***************************************************************************/
void print_first_line(int n, char src, char dst, char mode) {
    cout << "从 " << src << " 移动到 " << dst << "，共 " << n << " 层";
    if (mode != '9' && mode != '6' && mode != '7') {
        cout << "，延时设置为 " << sleep_time;
    }
}

/***************************************************************************
  函数名称：print_column
  功    能：打印三个柱
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void print_column() {
    for (int i = 0; i < 3; i++) {
        cct_showch(1 + i * 32, 15, ' ', 14, 14, 23);
        cct_setcolor(0, 7);
        cout << "         ";
    }
    for (int j = 0; j < 12; j++) {
        for (int k = 0; k < 3; k++) {
            cct_showch(12 + k * 32, 14 - j, ' ', 14, 14, 1);
            Sleep(50);
        }
    }
    cct_setcolor(0, 7);
}

/***************************************************************************
  函数名称：print_plate
  功    能：初始化打印盘子
  输入参数：int n：层数
            char src：起始柱
  返 回 值：
  说    明：
***************************************************************************/
void print_plate(int n, char src) {
    for (int i = 0; i < n; i++) {
        cct_showch(12 + (src - 'A') * 32 - (n - i), 14 - i, ' ', n - i, n - i, 2 * (n - i) + 1);
        Sleep(50);
    }
    cct_setcolor(0, 7);
}

/***************************************************************************
  函数名称：print_pause
  功    能：打印暂停
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void print_pause()
{
    cct_setcolor(0, 0);
    if (sleep_time == 0) {
        while (getchar() != '\n');
    }
    else {
        Sleep((6 - sleep_time) * 100);
    }
    cct_setcolor(0, 7);
}

/***************************************************************************
  函数名称：modify_plate
  功    能：移动盘子
  输入参数：char src：起始柱
            char dst：目标柱
            const int X：移动光标的X坐标
            const int Y：移动光标的Y坐标
  返 回 值：
  说    明：
***************************************************************************/
void modify_plate(char src, char dst, const int X, const int Y) {
    cct_setcursor(CURSOR_INVISIBLE);
    int top_src = 0, top_dst = 0;
    int top_element_src = 0;

    top_src = top[(int)(src - 'A')] + 1;
    top_dst = top[(int)(dst - 'A')] - 1;
    top_element_src = stack[(int)(dst - 'A')][top_dst];

    cct_setcolor(0, 0);
    for (int i = 0; i < Y - 1 - top_src; i++) {
        if (i < Y - 2 - top_src) {
            cct_showch(X - top_element_src + (src - 'A') * 32, Y - top_src - i, ' ', 0, 0, top_element_src);
            cct_showch(X + (src - 'A') * 32, Y - top_src - i, ' ', 14, 14, 1);
            cct_showch(X + 1 + (src - 'A') * 32, Y - top_src - i, ' ', 0, 0, top_element_src);
        }
        else {
            cct_showch(X - top_element_src + (src - 'A') * 32, Y - top_src - i, ' ', 0, 0, 2 * top_element_src + 1);
        }
        cct_showch(X - top_element_src + (src - 'A') * 32, Y - 1 - top_src - i, ' ', top_element_src, top_element_src, 2 * top_element_src + 1);
        Sleep(60 - sleep_time * 10);
    }
    cct_setcolor(0, 7);

    if (dst > src) {
        for (int i = 0; i < (dst - src) * 32; i++) {
            cct_showch(12 - top_element_src + (src - 'A') * 32 + i, 1, ' ', 0, 0, 2 * top_element_src + 1);
            cct_showch(12 - top_element_src + (src - 'A') * 32 + i + 1, 1, ' ', top_element_src, top_element_src, 2 * top_element_src + 1);
            Sleep(60 - sleep_time * 10);
        }
    }
    else {
        for (int i = 0; i < (src - dst) * 32; i++) {
            cct_showch(12 - top_element_src + (src - 'A') * 32 - i, 1, ' ', 0, 0, 2 * top_element_src + 1);
            cct_showch(12 - top_element_src + (src - 'A') * 32 - i - 1, 1, ' ', top_element_src, top_element_src, 2 * top_element_src + 1);
            Sleep(60 - sleep_time * 10);
        }
    }

    for (int i = 1; i < Y - top_dst - 1; i++) {
        if (i > 2) {
            cct_showch(12 - top_element_src + (dst - 'A') * 32, i, ' ', 0, 0, top_element_src);
            cct_showch(12 + (dst - 'A') * 32, i, ' ', 14, 14, 1);
            cct_showch(12 + 1 + (dst - 'A') * 32, i, ' ', 0, 0, top_element_src);
        }
        else {
            cct_showch(12 - top_element_src + (dst - 'A') * 32, i, ' ', 0, 0, 2 * top_element_src + 1);
        }
        cct_showch(12 - top_element_src + (dst - 'A') * 32, i + 1, ' ', top_element_src, top_element_src, 2 * top_element_src + 1);
        Sleep(60 - sleep_time * 10);
    }

    cct_setcolor(0, 7);
}

/***************************************************************************
  函数名称：hanoi_process
  功    能：汉诺塔过程
  输入参数：int n：层数
            char src：起始柱
            char tmp：中间柱
            char dst：目标柱
            char mode：选择模式
  返 回 值：
  说    明：
***************************************************************************/
void hanoi_process(int n, char src, char tmp, char dst, char mode)
{
    num++;
    if (mode == '1' || mode == '2' || mode == '3') {
        step_by_step_operation_of_hanoi(src, dst);
        print_stack_horizontal(n, src, dst, mode);
        cout << endl;
    }
    else if (mode == '4') {
        step_by_step_operation_of_hanoi(src, dst);
        cct_gotoxy(0, 17);
        print_stack_horizontal(n, src, dst, mode);
        modify_stack_vertical(n, src, dst, 9, 12);
        print_pause();
    }
    else if (mode == '8') {
        step_by_step_operation_of_hanoi(src, dst);
        cct_gotoxy(0, 32);
        print_stack_horizontal(n, src, dst, mode);
        modify_stack_vertical(n, src, dst, 9, 27);
        modify_plate(src, dst, 12, 15);
        print_pause();
    }
}

/***************************************************************************
  函数名称：hanoi
  功    能：打印n层汉诺塔的移动顺序
  输入参数：int n：层数
            char src：起始柱
            char tmp：中间柱
            char dst：目标柱
            char mode：选择模式
  返 回 值：
  说    明：
***************************************************************************/
void hanoi(int n, char src, char tmp, char dst, char mode)
{
    if (n == 1) {
        hanoi_process(n, src, tmp, dst, mode);
    }
    else {
        hanoi(n - 1, src, dst, tmp, mode);
        hanoi_process(n, src, tmp, dst, mode);
        hanoi(n - 1, tmp, src, dst, mode);
    }
}

/***************************************************************************
  函数名称：hanoi_1_2_3
  功    能：基本解、基本解(步数记录)、内部数组显示(横向)模式下的汉诺塔操作
  输入参数：int n：层数
            char src：起始柱
            char tmp：中间柱
            char dst：目标柱
            char mode：选择模式
  返 回 值：
  说    明：
***************************************************************************/
void hanoi_1_2_3(int n, char src, char tmp, char dst, char mode)
{
    get_parameter(&n, &src, &dst, &tmp, mode);
    init_stack(n, src);
    cout << endl;
    hanoi(n, src, tmp, dst, mode);
    cout << endl;
}

/***************************************************************************
  函数名称：hanoi_4
  功    能：内部数组显示(纵向+横向)模式下的汉诺塔操作
  输入参数：int n：层数
            char src：起始柱
            char tmp：中间柱
            char dst：目标柱
            char mode：选择模式
  返 回 值：
  说    明：
***************************************************************************/
void hanoi_4(int n, char src, char tmp, char dst, char mode)
{
    int temp_getchar;
    get_parameter(&n, &src, &dst, &tmp, mode);
    cct_cls();
    init_stack(n, src);
    cct_setcursor(CURSOR_INVISIBLE);
    print_first_line(n, src, dst, mode);
    cct_gotoxy(0, 17);
    print_stack_horizontal(n, src, dst, mode);
    temp_getchar = getchar();
    print_stack_vertical(n, src, 9, 12);
    print_pause();
    hanoi(n, src, tmp, dst, mode);
    cct_gotoxy(0, 39);
}

/***************************************************************************
  函数名称：hanoi_7
  功    能：图形解-预备-第一次移动模式下的汉诺塔操作
  输入参数：int n：层数
            char src：起始柱
            char tmp：中间柱
            char dst：目标柱
            char mode：选择模式
  返 回 值：
  说    明：
***************************************************************************/
void hanoi_7(int n, char src, char tmp, char dst, char mode)
{
    char temp_dst = 0;
    if (n % 2 == 1) {
        temp_dst = dst;
    }
    else if (n % 2 == 0) {
        temp_dst = tmp;
    }
    cct_cls();
    init_stack(n, src);
    cct_setcursor(CURSOR_INVISIBLE);
    print_first_line(n, src, dst, mode);
    print_column();
    print_plate(n, src);
    step_by_step_operation_of_hanoi(src, temp_dst);
    Sleep(500);
    modify_plate(src, temp_dst, 12, 15);
}

/***************************************************************************
  函数名称：hanoi_8
  功    能：图形解-自动移动版本模式下的汉诺塔操作
  输入参数：int n：层数
            char src：起始柱
            char tmp：中间柱
            char dst：目标柱
            char mode：选择模式
  返 回 值：
  说    明：
***************************************************************************/
void hanoi_8(int n, char src, char tmp, char dst, char mode)
{
    int temp_getchar;
    cct_cls();
    cct_setcursor(CURSOR_INVISIBLE);
    init_stack(n, src);
    print_first_line(n, src, dst, mode);
    cct_gotoxy(0, 32);
    print_stack_horizontal(n, src, dst, mode);
    print_stack_vertical(n, src, 9, 27);
    print_column();
    print_plate(n, src);
    temp_getchar = getchar();
    print_pause();
    hanoi(n, src, tmp, dst, mode);
}

/***************************************************************************
  函数名称：hanoi_9
  功    能：图形解-游戏版模式下的汉诺塔操作
  输入参数：int n：层数
            char src：起始柱
            char tmp：中间柱
            char dst：目标柱
            char mode：选择模式
  返 回 值：
  说    明：
***************************************************************************/
void hanoi_9(int n, char src, char tmp, char dst, char mode)
{
    int X, Y;
    int mark_step = 0;
    char temp_dst = 0, temp_src = 0;
    cct_cls();
    cct_setcursor(CURSOR_INVISIBLE);
    init_stack(n, src);
    print_first_line(n, src, dst, mode);
    cct_gotoxy(0, 32);
    print_stack_horizontal(n, src, dst, mode);
    print_stack_vertical(n, src, 9, 27);
    print_column();
    print_plate(n, src);
    cct_gotoxy(0, 34);
    cct_setcursor(CURSOR_VISIBLE_NORMAL);
    cout << "请输入移动的柱号(命令形式：AC=A顶端的盘子移动到C，Q=退出) ：";
    cct_getxy(X, Y);
    while (top[(int)(src - 'A')] != 0 || top[(int)(tmp - 'A')] != 0) {
        char temp[100] = { 0 };
        temp_dst = 0, temp_src = 0, mark_step = 0;
        for (int i = 0; i < 100; i++) {
            mark_step++;
            int step = 0;
            temp[i] = _getch();
            if ((int)temp[i] == -32) {
                step = _getch();
                temp[i] = 0;
                i--, mark_step--;
                continue;
            }
            if ((int)temp[i] != -32) {
                if (temp[i] <= 32 && temp[i] != 13) {
                    i--, mark_step--;
                }
                else {
                    cct_gotoxy(X + i, Y);
                    if (temp[i] == 13) {
                        break;
                    }
                    else {
                        cout << temp[i];
                    }
                }
            }
        }
        if (mark_step == 3 && temp[2] == 13) {
            temp_src = temp[0];
            temp_dst = temp[1];
        }
        else if (mark_step == 2 && temp[1] == 13 && (temp[0] == 'q' || temp[0] == 'Q')) {
            cct_gotoxy(0, 35);
            cout << "游戏终止！！！";
            break;
        }

        if (temp_src >= 'a' && temp_src <= 'c') {
            temp_src = temp_src - 32;
        }
        if (temp_dst >= 'a' && temp_dst <= 'c') {
            temp_dst = temp_dst - 32;
        }

        if (temp_src >= 'A' && temp_src <= 'C' && temp_dst >= 'A' && temp_dst <= 'C') {
            if (stack[(int)(temp_src - 'A')][top[(int)(temp_src - 'A')] - 1] == 0 || top[(int)(temp_dst - 'A')] != 0 && (stack[(int)(temp_src - 'A')][top[(int)(temp_src - 'A')] - 1] > stack[(int)(temp_dst - 'A')][top[(int)(temp_dst - 'A')] - 1])) {
                cct_gotoxy(0, 35);
                cct_setcursor(CURSOR_INVISIBLE);
                if (stack[(int)(temp_src - 'A')][top[(int)(temp_src - 'A')] - 1] == 0) {
                    cout << "原柱为空!";
                }
                else if (top[(int)(temp_dst - 'A')] != 0 && (stack[(int)(temp_src - 'A')][top[(int)(temp_src - 'A')] - 1] > stack[(int)(temp_dst - 'A')][top[(int)(temp_dst - 'A')] - 1])) {
                    cout << "大盘压小盘，非法移动!" << endl;
                }
                Sleep(1000);
                cct_gotoxy(0, 35);
                cout << "                         ";
                cct_setcursor(CURSOR_VISIBLE_NORMAL);
            }
            else {
                num++;
                step_by_step_operation_of_hanoi(temp_src, temp_dst);
                cct_gotoxy(0, 32);
                print_stack_horizontal(n, src, dst, mode);
                modify_stack_vertical(n, temp_src, temp_dst, 9, 27);
                modify_plate(temp_src, temp_dst, 12, 15);
            }
        }
        cct_gotoxy(X, Y);
        cout << "                                   ";
        cct_setcursor(CURSOR_VISIBLE_NORMAL);
        cct_gotoxy(X, Y);
    }
    if (mark_step != 2) {
        cct_gotoxy(0, 35);
        cout << "游戏结束！！！真是泰裤辣！！！";
    }
}
