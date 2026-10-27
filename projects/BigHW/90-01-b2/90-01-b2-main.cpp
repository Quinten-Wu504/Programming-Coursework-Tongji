/* 2154146 吴金轩 计科 */
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "../include/cmd_console_tools.h"
#include "../include/common_frame_constuction.h"
#include "90-01-b2.h"
using namespace std;

int main() {
	int num_of_steps = 0;
	const char* p_char[] = { "命令行找出可消除项并标识", "命令行完成一次消除（分步骤显示）", "命令行完成一关（分步骤显示）",
		"伪图形界面下用鼠标选择一个色块（无分隔线）", "伪图形界面下用鼠标选择一个色块（有分隔线）",
		"伪图形界面完成一次消除（分步骤）", "伪图形界面完整版", 0 };
	
	srand((unsigned int)(time(0)));

	while (1) {
		cct_setconsoleborder(85, 47, 500, 1000);
		char mode = '\0';
		int num_colunm = 0, num_row = 0, appointed_row = -1, appointed_colunm = -1;
		char star_array[12][12], temp_star_array[12][12];
		char mark_eliminate = 0;
		int count_star[100] = { 0 }, scores[100] = { 0 };
		num_of_steps = 0;

		init_star_array(star_array);
		init_temp_star_array(temp_star_array);

		cct_cls();
		mode = menu(p_char, 'A', 'Q');

		if (mode == 'Q') {
			cct_gotoxy(programme_end_X, programme_end_Y);
			break;
		}
		else if (mode == 'A' || mode == 'B' || mode == 'C' || mode == 'D' || mode == 'E' || mode == 'F' || mode == 'G') {
			get_colunm_and_row(&num_row, &num_colunm);
			rand_init_star_array(num_row, num_colunm, star_array);
			if (mode == 'A' || mode == 'B' || mode == 'C') {
				if (mode == 'A') {
					star_array_A(num_row, num_colunm, &appointed_row, &appointed_colunm, star_array, temp_star_array);
				}
				else if (mode == 'B') {
					star_array_B(num_row, num_colunm, &appointed_row, &appointed_colunm, star_array, temp_star_array, &mark_eliminate, count_star, scores);
				}
				else if (mode == 'C') {
					star_array_C(&num_row, &num_colunm, &appointed_row, &appointed_colunm, star_array, temp_star_array, count_star, scores, &mark_eliminate, &num_of_steps);
				}
				print_end_tips();
			}
			else if (mode == 'D' || mode == 'E' || mode == 'F' || mode == 'G') {
				if (mode == 'D' || mode == 'E') {
					star_array_D_or_E(num_row, num_colunm, &appointed_row, &appointed_colunm, star_array, temp_star_array, mode);
				}
				else if (mode == 'F') {
					star_array_F(num_row, num_colunm, &appointed_row, &appointed_colunm, star_array, temp_star_array, count_star, scores);
				}
				else if (mode == 'G') {
					star_array_G(num_row, num_colunm, &appointed_row, &appointed_colunm, star_array, temp_star_array, count_star, scores);
				}
				cct_setcursor(CURSOR_VISIBLE_NORMAL);
				print_end_tips();
			}
		}
	}

	return 0;
}
