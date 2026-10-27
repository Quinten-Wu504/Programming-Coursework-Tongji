/* 2154146 吴金轩 计科 */
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <Windows.h>
#include "../include/cmd_console_tools.h"
#include "../include/common_star_print.h"
using namespace std;

/***************************************************************************
  函数名称：print_stars
  功    能：伪图形界面打印星星
  输入参数：int star_color：星星的颜色，默认为COLOR_BLACK
            int star_start_X：星星开始打印的X坐标，默认为0
			int star_start_Y：星星开始打印的Y坐标，默认为0
  返 回 值：无
  说    明：无
***************************************************************************/
void print_stars(int star_color, int star_start_X, int star_start_Y) {
	cct_setcolor(star_color, COLOR_HWHITE);
	cct_gotoxy(star_start_X, star_start_Y);
	cout << "╔═╗";
	cct_gotoxy(star_start_X, star_start_Y + 1);
	cout << "║★║";
	cct_gotoxy(star_start_X, star_start_Y + 2);
	cout << "╚═╝";
	cct_setcolor(0, COLOR_WHITE);
}