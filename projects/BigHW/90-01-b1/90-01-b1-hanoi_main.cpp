/* 2154146 吴金轩 计科 */
#include <iostream>
#include "../include/cmd_console_tools.h"
#include "../include/common_frame_constuction.h"
#include "90-01-b1-hanoi.h"
using namespace std;

int num = 0;
int sleep_time = 0;
int top[3] = { 0 };
int stack[3][10] = {};

/***************************************************************************
  函数名称：main
  功    能：初始化屏幕、调用菜单函数（hanoi_menu.cpp中）并返回选项、根据选项调用菜单各项对应的hanoi_multiple_solutions.cpp中的执行函数
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int main()
{
	cct_setconsoleborder(120, 40, 120, 9000);

	char mode;
	int n = 0;
	char src = 1, tmp = 1, dst = 1;
	const int bg_color = 0;
	const int fg_color = 6;
	const char* p_char[] = { "基本解", "基本解(步数记录)", "内部数组显示(横向)",
		"内部数组显示(纵向+横向)", "图形解-预备-画三个圆柱", "图形解-预备-在起始柱上画n个盘子",
		"图形解-预备-第一次移动", "图形解-自动移动版本", "图形解-游戏版", 0 };

	while (1) {
		cct_cls();

		mode = menu(p_char, '1', '0');

		if (mode == '0') {
			cct_gotoxy(0, 39);
			break;
		}
		else if (mode == '1' || mode == '2' || mode == '3' || mode == '4') {
			if (mode == '1' || mode == '2' || mode == '3') {
				hanoi_1_2_3(n, src, tmp, dst, mode);
			}
			else if (mode == '4') {
				hanoi_4(n, src, tmp, dst, mode);
			}
		}
		else if (mode == '5' || mode == '6' || mode == '7' || mode == '8' || mode == '9') {
			if (mode == '5') {
				cct_cls();
				cct_setcursor(CURSOR_INVISIBLE);
				print_column();
			}
			else if (mode == '6' || mode == '7' || mode == '8' || mode == '9') {
				get_parameter(&n, &src, &dst, &tmp, mode);
				if (mode == '6') {
					cct_cls();
					cct_setcursor(CURSOR_INVISIBLE);
					print_first_line(n, src, dst, mode);
					print_column();
					init_stack(n, src);
					print_plate(n, src);
				}
				else if (mode == '7') {
					hanoi_7(n, src, tmp, dst, mode);
				}
				else if (mode == '8') {
					hanoi_8(n, src, tmp, dst, mode);
				}
				else if (mode == '9') {
					hanoi_9(n, src, tmp, dst, mode);
				}
			}
			cct_gotoxy(0, 39);
		}
		cct_setcursor(CURSOR_VISIBLE_NORMAL);
		cout << "按回车键继续";
		char pause_char = getchar();

		num = 0;
		sleep_time = 0;
		for (int i = 0; i < 3; i++) {
			top[i] = 0;
			for (int j = 0; j < 10; j++) {
				stack[i][j] = 0;
			}
		}
	}

	return 0;
}
