/* 2154146 吴金轩 计科 */
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <Windows.h>
#include "../include/cmd_console_tools.h"
#include "90-01-b2.h"
using namespace std;

/***************************************************************************
  函数名称：image_resolution_print_stars
  功    能：图形解打印星星
  输入参数：int num_row：星星的行数
			int num_colunm：星星的列数
			char star_array[][12]：星星数列
			bool mark_dividing_lines：是否显示分割线的标志
  返 回 值：无
  说    明：无
***************************************************************************/
void image_resolution_print_stars(int num_row, int num_colunm, char star_array[][12], bool mark_dividing_lines) {
	for (int i = 1; i <= num_row; i++) {
		for (int j = 1; j <= num_colunm; j++) {
			cct_setcolor(8 + (int)(star_array[i][j] - '0'), 0);
			cct_gotoxy(image_resolution_star_X + (j - 1) * (6 + 2 * mark_dividing_lines), image_resolution_star_Y + (i - 1) * (3 + mark_dividing_lines));
			cout << "╔═╗";
			cct_gotoxy(image_resolution_star_X + (j - 1) * (6 + 2 * mark_dividing_lines), image_resolution_star_Y + (i - 1) * (3 + mark_dividing_lines) + 1);
			cout << "║★║";
			cct_gotoxy(image_resolution_star_X + (j - 1) * (6 + 2 * mark_dividing_lines), image_resolution_star_Y + (i - 1) * (3 + mark_dividing_lines) + 2);
			cout << "╚═╝";
			cct_setcolor(0, 7);
		}
	}
}

/***************************************************************************
  函数名称：image_resolution_print_frame
  功    能：打印图像解框架
  输入参数：int num_row：星星的行数
			int num_colunm：星星的列数
			char star_array[][12]：星星数列
			bool mark_dividing_lines：是否显示分割线的标志
  返 回 值：无
  说    明：无
***************************************************************************/
void image_resolution_print_frame(int num_row, int num_colunm, int* p_appointed_row, int* p_appointed_colunm, char star_array[][12], bool mark_dividing_lines) {
	cct_setcursor(CURSOR_INVISIBLE);
	cct_cls();
	int row_of_window = 0, colunm_of_window = 0;
	row_of_window = num_row * (3 + mark_dividing_lines) + 8 - mark_dividing_lines;
	colunm_of_window = num_colunm * (6 + 2 * mark_dividing_lines) + 7 - 2 * mark_dividing_lines;
	cct_setconsoleborder(colunm_of_window, row_of_window, colunm_of_window, row_of_window);

	cout << endl << " ";
	for (int i = 0; i < num_colunm; i++) {
		if (mark_dividing_lines && i != 0) {
			cout << "  ";
		}
		cout << setw(6) << i;
	}

	cct_setcolor(15, 8);
	cct_gotoxy(image_resolution_star_X - 2, image_resolution_star_Y - 1);
	cout << "╔";
	Sleep(1);
	for (int i = 0; i < num_colunm; i++) {
		cout << "═══";
		if (mark_dividing_lines && i != num_colunm - 1) {
			cout << "╦";
		}
		Sleep(1);
	}
	cout << "╗" << endl;
	Sleep(1);

	if (!mark_dividing_lines) {
		for (int i = 0; i < num_row * 3; i++) {
			if (i % 3 == 1) {
				cct_setcolor(0, 7);
				cout << char('A' + i / 3);
				Sleep(1);
				cct_setcolor(15, 8);
			}
			cct_gotoxy(image_resolution_star_X - 2, image_resolution_star_Y + i);
			cout << "║";
			Sleep(1);
			for (int j = 0; j < num_colunm; j++) {
				cout << "      ";
				Sleep(1);
			}
			cout << "║" << endl;
			Sleep(1);
		}
	}
	else {
		for (int i = 0; i < num_row * 4 - 1; i++) {
			if (i % 4 == 1) {
				cct_setcolor(0, 7);
				cout << char('A' + i / 4);
				Sleep(1);
				cct_setcolor(15, 8);
			}
			cct_gotoxy(image_resolution_star_X - 2, image_resolution_star_Y + i);
			if (i % 4 != 3) {
				cout << "║";
				Sleep(1);
				for (int j = 0; j < num_colunm; j++) {
					cout << "      ";
					if (j != num_colunm - 1) {
						cout << "║";
					}
					Sleep(1);
				}
				cout << "║" << endl;
				Sleep(1);
			}
			else if (i % 4 == 3) {
				cout << "╠";
				Sleep(1);
				for (int j = 0; j < num_colunm; j++) {
					cout << "═══";
					if (j != num_colunm - 1) {
						cout << "╬";
					}
					Sleep(1);
				}
				cout << "╣" << endl;
				Sleep(1);
			}
		}
	}

	cct_gotoxy(image_resolution_star_X - 2, image_resolution_star_Y + num_row * (3 + mark_dividing_lines) - mark_dividing_lines);
	cout << "╚";
	Sleep(1);
	for (int i = 0; i < num_colunm; i++) {
		cout << "═══";
		if (mark_dividing_lines && i != num_colunm - 1) {
			cout << "╩";
		}
		Sleep(1);
	}
	cout << "╝" << endl;
	Sleep(1);

	cct_setcolor(0, 7);

	image_resolution_print_stars(num_row, num_colunm, star_array, mark_dividing_lines);

	cct_gotoxy(0, 0);
	cout << "屏幕当前设置为：" << row_of_window << "行" << colunm_of_window << "列";
	cct_gotoxy(0, row_of_window - 4);
	cout << "箭头键/鼠标移动，回车键/单击左键选择并结束";
}

/***************************************************************************
  函数名称：image_resolution_moved_by_arrow
  功    能：以方向键方式移动
  输入参数：int keycode2：读入的第二个键盘参数
			int* p_appointed_row：指定的行数的指针
			int* p_appointed_row：指定的列数的指针
			int num_row：星星的行数
			int num_colunm：星星的列数
			char star_array[][12]：星星数列
  返 回 值：无
  说    明：无
***************************************************************************/
void image_resolution_moved_by_arrow(int keycode2, int* p_appointed_row, int* p_appointed_colunm, int num_row, int num_colunm, char star_array[][12]) {
	if (keycode2 == 72) {
		if (*p_appointed_row != 1) {
			*p_appointed_row -= 1;
		}
		else if (*p_appointed_row == 1) {
			*p_appointed_row = num_row;
		}
		while (star_array[*p_appointed_row][*p_appointed_colunm] == '0') {
			if (*p_appointed_row != 1) {
				*p_appointed_row -= 1;
			}
			else if (*p_appointed_row == 1) {
				*p_appointed_row = num_row;
			}
		}
	}
	else if (keycode2 == 80) {
		if (*p_appointed_row != num_row) {
			*p_appointed_row += 1;
		}
		else if (*p_appointed_row == num_row) {
			*p_appointed_row = 1;
		}
		while (star_array[*p_appointed_row][*p_appointed_colunm] == '0') {
			if (*p_appointed_row != num_row) {
				*p_appointed_row += 1;
			}
			else if (*p_appointed_row == num_row) {
				*p_appointed_row = 1;
			}
		}
	}
	else if (keycode2 == 75) {
		if (*p_appointed_colunm != 1) {
			*p_appointed_colunm -= 1;
		}
		else if (*p_appointed_colunm == 1) {
			*p_appointed_colunm = num_colunm;
		}
		while (star_array[*p_appointed_row][*p_appointed_colunm] == '0') {
			if (*p_appointed_colunm != 1) {
				*p_appointed_colunm -= 1;
			}
			else if (*p_appointed_colunm == 1) {
				*p_appointed_colunm = num_colunm;
			}
		}
	}
	else if (keycode2 == 77) {
		if (*p_appointed_colunm != num_colunm) {
			*p_appointed_colunm += 1;
		}
		else if (*p_appointed_colunm == num_colunm) {
			*p_appointed_colunm = 1;
		}
		while (star_array[*p_appointed_row][*p_appointed_colunm] == '0') {
			if (*p_appointed_colunm != num_colunm) {
				*p_appointed_colunm += 1;
			}
			else if (*p_appointed_colunm == num_colunm) {
				*p_appointed_colunm = 1;
			}
		}
	}
}

/***************************************************************************
  函数名称：image_resolution_temp_print
  功    能：变化过程中打印星星
  输入参数：int* p_appointed_row：指定的行数的指针
			int* p_appointed_row：指定的列数的指针
			int temp_appointed_row：前一次操作读取的列数的指针
			int temp_appointed_colunm：前一次操作读取的列数的指针
			char star_array[][12]：星星数组
			bool mark_dividing_lines：是否有分割线
			int temp_print_mode：打印模式
  返 回 值：无
  说    明：无
***************************************************************************/
void image_resolution_temp_print(int* p_appointed_row, int* p_appointed_colunm, int temp_appointed_row, int temp_appointed_colunm, char star_array[][12], bool mark_dividing_lines, int temp_print_mode) {
	if (temp_print_mode == 0) {
		cct_setcolor(8 + (int)(star_array[temp_appointed_row][temp_appointed_colunm] - '0'), 0);
		cct_gotoxy(image_resolution_star_X + (temp_appointed_colunm - 1) * (6 + 2 * mark_dividing_lines), image_resolution_star_Y + (temp_appointed_row - 1) * (3 + mark_dividing_lines));
		cout << "╔═╗";
		cct_gotoxy(image_resolution_star_X + (temp_appointed_colunm - 1) * (6 + 2 * mark_dividing_lines), image_resolution_star_Y + (temp_appointed_row - 1) * (3 + mark_dividing_lines) + 1);
		cout << "║★║";
		cct_gotoxy(image_resolution_star_X + (temp_appointed_colunm - 1) * (6 + 2 * mark_dividing_lines), image_resolution_star_Y + (temp_appointed_row - 1) * (3 + mark_dividing_lines) + 2);
		cout << "╚═╝";
	}
	else if (temp_print_mode == 1) {
		cct_setcolor(8 + (int)(star_array[*p_appointed_row][*p_appointed_colunm] - '0'), 15);
		cct_gotoxy(image_resolution_star_X + (*p_appointed_colunm - 1) * (6 + 2 * mark_dividing_lines), image_resolution_star_Y + (*p_appointed_row - 1) * (3 + mark_dividing_lines));
		cout << "╔═╗";
		cct_gotoxy(image_resolution_star_X + (*p_appointed_colunm - 1) * (6 + 2 * mark_dividing_lines), image_resolution_star_Y + (*p_appointed_row - 1) * (3 + mark_dividing_lines) + 1);
		cout << "║★║";
		cct_gotoxy(image_resolution_star_X + (*p_appointed_colunm - 1) * (6 + 2 * mark_dividing_lines), image_resolution_star_Y + (*p_appointed_row - 1) * (3 + mark_dividing_lines) + 2);
		cout << "╚═╝";
	}
	else if (temp_print_mode == 2) {
		cct_setcolor(8 + (int)(star_array[temp_appointed_row][temp_appointed_colunm] - '0'), 7);
		cct_gotoxy(image_resolution_star_X + (temp_appointed_colunm - 1) * (6 + 2 * mark_dividing_lines), image_resolution_star_Y + (temp_appointed_row - 1) * (3 + mark_dividing_lines));
		cout << "╔═╗";
		cct_gotoxy(image_resolution_star_X + (temp_appointed_colunm - 1) * (6 + 2 * mark_dividing_lines), image_resolution_star_Y + (temp_appointed_row - 1) * (3 + mark_dividing_lines) + 1);
		cout << "║★║";
		cct_gotoxy(image_resolution_star_X + (temp_appointed_colunm - 1) * (6 + 2 * mark_dividing_lines), image_resolution_star_Y + (temp_appointed_row - 1) * (3 + mark_dividing_lines) + 2);
		cout << "╚═╝";
	}
}

/***************************************************************************
  函数名称：image_resolution_get_appointed_parameter
  功    能：图像解键鼠操作获取指定坐标
  输入参数：int num_row：星星的行数
			int num_colunm：星星的列数
			int* p_appointed_row：指定的行数的指针
			int* p_appointed_colunm：指定的列数的指针
			char star_array[][12]：星星数列
			bool mark_dividing_lines：是否有分割线的标志
			bool mark_init_or_not：是否是初始化的标志
  返 回 值：无
  说    明：无
***************************************************************************/
bool image_resolution_get_appointed_parameter(int num_row, int num_colunm, int* p_appointed_row, int* p_appointed_colunm, char star_array[][12],
	char temp_star_array[][12], bool mark_dividing_lines, bool mark_init_or_not, char mode) {
	int temp_X = 0, temp_Y = 0, buffer_colunm = 0, buffer_row = 0;
	int Mouse_X = 0, Mouse_Y = 0, Mouse_Action = -1, keycode1 = 0, keycode2 = 0;
	int temp_appointed_row, temp_appointed_colunm;
	bool mark_scan_result = 0, mark_end_directly = 0;
	cct_getconsoleborder(temp_X, temp_Y, buffer_colunm, buffer_row);
	temp_Y = temp_Y - 4;

	if (mark_init_or_not) {
		*p_appointed_row = 1, * p_appointed_colunm = 1;
		if (star_array[1][1] != '0') {
			image_resolution_temp_print(p_appointed_row, p_appointed_colunm, 0, 0, star_array, mark_dividing_lines, 1);
		}
	}
	temp_appointed_row = *p_appointed_row, temp_appointed_colunm = *p_appointed_colunm;

	cct_enable_mouse();
	cct_read_keyboard_and_mouse(Mouse_X, Mouse_Y, Mouse_Action, keycode1, keycode2);
	cct_enable_mouse();

	while (1) {
		if ((Mouse_Action == MOUSE_LEFT_BUTTON_CLICK || keycode1 == 13) &&
			temp_appointed_row >= 1 && temp_appointed_row <= num_row && temp_appointed_colunm >= 1 && temp_appointed_colunm <= num_colunm &&
			star_array[*p_appointed_row][*p_appointed_colunm] != '0') {
			if (mode == 'F') {
				mark_scan_result = scan_appointed_coordinate(num_row, num_colunm, *p_appointed_row, *p_appointed_colunm, star_array, temp_star_array);
				if (mark_scan_result) {
					temp_star_array[*p_appointed_row][*p_appointed_colunm] = '*';
					cct_setcolor(0, 7);
					cct_gotoxy(0, temp_Y);
					cout << "箭头键/鼠标移动取消当前选择，回车键/单击左键合成                                 ";
					cct_gotoxy(0, temp_Y);
					break;
				}
				else {
					cct_setcolor(0, 14);
					cct_gotoxy(0, temp_Y);
					cout << "周围无同颜色星星，";
					cct_setcolor(0, 7);
					cout << "箭头/鼠标移动，回车/左键选择，Q/右键结束";
					while (temp_appointed_row == *p_appointed_row && temp_appointed_colunm == *p_appointed_colunm) {
						cct_read_keyboard_and_mouse(Mouse_X, Mouse_Y, Mouse_Action, keycode1, keycode2);
						if (Mouse_Action == MOUSE_RIGHT_BUTTON_CLICK || keycode1 == (int)('Q') || keycode1 == (int)('q')) {
							mark_end_directly = 1;
							cct_gotoxy(0, temp_Y);
							cout << "                                                             ";
							break;
						}
						else if (keycode1 == 224) {
							image_resolution_moved_by_arrow(keycode2, p_appointed_row, p_appointed_colunm, num_row, num_colunm, star_array);
						}
						else if (keycode1 != 224) {
							if (!mark_dividing_lines) {
								*p_appointed_row = (Mouse_Y - image_resolution_star_Y + 3) / 3;
								*p_appointed_colunm = (Mouse_X - image_resolution_star_X + 6) / 6;
							}
							else {
								if ((Mouse_Y - image_resolution_star_Y) % 4 == 3 || (Mouse_X - image_resolution_star_X) % 8 == 6 || (Mouse_X - image_resolution_star_X) % 8 == 7) {
									*p_appointed_row = 0;
									*p_appointed_colunm = 0;
								}
								else {
									*p_appointed_row = (Mouse_Y - image_resolution_star_Y + 4) / 4;
									*p_appointed_colunm = (Mouse_X - image_resolution_star_X + 8) / 8;
								}
							}
						}
					}

					if (mark_end_directly == 1) {
						break;
					}

					init_temp_star_array(temp_star_array);
				}
			}
			else if (mode == 'D' || mode == 'E') {
				cct_setcolor(0, 7);
				cct_gotoxy(0, temp_Y);
				cout << "选中了" << (char)('A' + *p_appointed_row - 1) << "行" << (char)('0' + *p_appointed_colunm - 1) << "列                                   ";
				cct_gotoxy(0, temp_Y);
				break;
			}
		}
		else if (keycode1 == 224) {
			cct_disable_mouse();
			if (!(temp_appointed_row >= 1 && temp_appointed_row <= num_row && temp_appointed_colunm >= 1 && temp_appointed_colunm <= num_colunm)) {
				*p_appointed_row = 1;
				*p_appointed_colunm = 1;
			}
			image_resolution_moved_by_arrow(keycode2, p_appointed_row, p_appointed_colunm, num_row, num_colunm, star_array);
		}
		else if (keycode1 != 224) {
			if (!mark_dividing_lines) {
				*p_appointed_row = (Mouse_Y - image_resolution_star_Y + 3) / 3;
				*p_appointed_colunm = (Mouse_X - image_resolution_star_X + 6) / 6;
			}
			else {
				if ((Mouse_Y - image_resolution_star_Y) % 4 == 3 || (Mouse_X - image_resolution_star_X) % 8 == 6 || (Mouse_X - image_resolution_star_X) % 8 == 7) {
					*p_appointed_row = 0;
					*p_appointed_colunm = 0;
				}
				else {
					*p_appointed_row = (Mouse_Y - image_resolution_star_Y + 4) / 4;
					*p_appointed_colunm = (Mouse_X - image_resolution_star_X + 8) / 8;
				}
			}
		}

		if ((*p_appointed_colunm != temp_appointed_colunm || *p_appointed_row != temp_appointed_row)) {
			if (*p_appointed_row >= 1 && *p_appointed_row <= num_row && *p_appointed_colunm >= 1 && *p_appointed_colunm <= num_colunm &&
				star_array[*p_appointed_row][*p_appointed_colunm] != '0') {
				image_resolution_temp_print(p_appointed_row, p_appointed_colunm, temp_appointed_row, temp_appointed_colunm, star_array, mark_dividing_lines, 1);
			}
			if (temp_appointed_row >= 1 && temp_appointed_row <= num_row && temp_appointed_colunm >= 1 && temp_appointed_colunm <= num_colunm &&
				star_array[temp_appointed_row][temp_appointed_colunm] != '0') {
				image_resolution_temp_print(p_appointed_row, p_appointed_colunm, temp_appointed_row, temp_appointed_colunm, star_array, mark_dividing_lines, 0);
			}
			cct_setcolor(0, 7);
		}

		cct_gotoxy(0, temp_Y);
		if (*p_appointed_colunm != temp_appointed_colunm || *p_appointed_row != temp_appointed_row) {
			if (*p_appointed_row >= 1 && *p_appointed_row <= num_row && *p_appointed_colunm >= 1 && *p_appointed_colunm <= num_colunm &&
				star_array[*p_appointed_row][*p_appointed_colunm] != '0') {
				cct_setcolor(0, 7);
				cout << "[当前鼠标] " << (char)('A' + *p_appointed_row - 1) << "行" << (char)('0' + *p_appointed_colunm - 1) << "列                                    ";
			}
			else {
				cct_setcolor(0, 7);
				cout << "[当前鼠标] 位置非法                                                    ";
			}
		}

		temp_appointed_row = *p_appointed_row, temp_appointed_colunm = *p_appointed_colunm;
		cct_enable_mouse();
		cct_read_keyboard_and_mouse(Mouse_X, Mouse_Y, Mouse_Action, keycode1, keycode2);
		cct_enable_mouse();
	}

	cct_gotoxy(0, temp_Y + 1);
	cout << endl;

	return mark_end_directly;
}

/***************************************************************************
  函数名称：image_resolution_star_eliminate
  功    能：图像解消除星星
  输入参数：int num_row：星星的行数
			int num_colunm：星星的列数
			char star_array[][12]：星星数列
			char temp_star_array[][12]：中间星星数列
			bool mark_dividing_lines：是否有分割线的标志
  返 回 值：无
  说    明：无
***************************************************************************/
int image_resolution_star_eliminate(int num_row, int num_colunm, char star_array[][12], char temp_star_array[][12], bool mark_dividing_lines) {
	int window_colunm = 0, window_row = 0, buffer_colunm = 0, buffer_row = 0;
	int count_star = 0;

	for (int i = 1; i <= num_row; i++) {
		for (int j = 1; j <= num_colunm; j++) {
			if (temp_star_array[i][j] == '*') {
				star_array[i][j] = '0';
				count_star++;
				cct_setcolor(15, 15);
				cct_gotoxy(image_resolution_star_X + (j - 1) * (6 + 2 * mark_dividing_lines), image_resolution_star_Y + (i - 1) * (3 + mark_dividing_lines));
				cout << "      ";
				cct_gotoxy(image_resolution_star_X + (j - 1) * (6 + 2 * mark_dividing_lines), image_resolution_star_Y + (i - 1) * (3 + mark_dividing_lines) + 1);
				cout << "      ";
				cct_gotoxy(image_resolution_star_X + (j - 1) * (6 + 2 * mark_dividing_lines), image_resolution_star_Y + (i - 1) * (3 + mark_dividing_lines) + 2);
				cout << "      ";
				cct_setcolor(0, 7);
			}
		}
	}

	cct_getconsoleborder(window_colunm, window_row, buffer_colunm, buffer_row);
	cct_gotoxy(0, window_row - 4);
	if (!mark_dividing_lines) {
		cout << "合成完成，回车键/单击左键下落0                                     ";

		int Mouse_X = 0, Mouse_Y = 0, Mouse_Action = -1, keycode1 = 0, keycode2 = 0;
		while (Mouse_Action != MOUSE_LEFT_BUTTON_CLICK && keycode1 != 13) {
			cct_read_keyboard_and_mouse(Mouse_X, Mouse_Y, Mouse_Action, keycode1, keycode2);
		}

	}

	return count_star;
}

/***************************************************************************
  函数名称：image_resolution_star_downward
  功    能：图像解星星下落
  输入参数：int num_row：星星的行数
			int num_colunm：星星的列数
			char star_array[][12]：星星数列
			char temp_star_array[][12]：中间星星数列
			bool mark_dividing_lines：是否有分割线的标志
  返 回 值：无
  说    明：无
***************************************************************************/
void image_resolution_star_downward(int num_row, int num_colunm, char star_array[][12], char temp_star_array[][12], bool mark_dividing_lines) {
	int zero_start_row = num_row, zero_ending_row = 0;
	int zero_start_colunm = num_colunm, zero_ending_colunm = 0;
	int window_colunm = 0, window_row = 0, buffer_colunm = 0, buffer_row = 0;
	int mark_colunm_empty[11] = { 0 };

	cct_getconsoleborder(window_colunm, window_row, buffer_colunm, buffer_row);

	for (int i = 1; i <= num_colunm; i++) {
		for (int j = num_row; j >= 1; j--) {
			if (star_array[j][i] == '0') {
				zero_start_row = j;
				int k = 0;
				for (k = j; k >= 1; k--) {
					if (star_array[k][i] != '0') {
						zero_ending_row = k;
						break;
					}
				}

				if (k != 0) {
					for (int p = 0; p < (3 + mark_dividing_lines) * (zero_start_row - zero_ending_row); p++) {
						cct_setcolor(15, 0);
						cct_gotoxy(image_resolution_star_X + (i - 1) * (6 + 2 * mark_dividing_lines), image_resolution_star_Y + (zero_ending_row - 1) * (3 + mark_dividing_lines) + p);
						if (!mark_dividing_lines) {
							cout << "      ";
						}
						else {
							if (p % 4 == 3) {
								cout << "═══";
							}
							else {
								cout << "      ";
							}
						}
						cct_gotoxy(image_resolution_star_X + (i - 1) * (6 + 2 * mark_dividing_lines), image_resolution_star_Y + (zero_ending_row - 1) * (3 + mark_dividing_lines) + p + 1);
						if (!mark_dividing_lines) {
							cout << "      ";
						}
						else {
							if (p % 4 == 2) {
								cout << "═══";
							}
							else {
								cout << "      ";
							}
						}
						cct_gotoxy(image_resolution_star_X + (i - 1) * (6 + 2 * mark_dividing_lines), image_resolution_star_Y + (zero_ending_row - 1) * (3 + mark_dividing_lines) + p + 2);
						if (!mark_dividing_lines) {
							cout << "      ";
						}
						else {
							if (p % 4 == 1) {
								cout << "═══";
							}
							else {
								cout << "      ";
							}
						}
						cct_setcolor(8 + (int)(star_array[zero_ending_row][i] - '0'), 0);
						cct_gotoxy(image_resolution_star_X + (i - 1) * (6 + 2 * mark_dividing_lines), image_resolution_star_Y + (zero_ending_row - 1) * (3 + mark_dividing_lines) + p + 1);
						cout << "╔═╗";
						cct_gotoxy(image_resolution_star_X + (i - 1) * (6 + 2 * mark_dividing_lines), image_resolution_star_Y + (zero_ending_row - 1) * (3 + mark_dividing_lines) + p + 2);
						cout << "║★║";
						cct_gotoxy(image_resolution_star_X + (i - 1) * (6 + 2 * mark_dividing_lines), image_resolution_star_Y + (zero_ending_row - 1) * (3 + mark_dividing_lines) + p + 3);
						cout << "╚═╝";
						cct_setcolor(0, 7);
						Sleep(10);
					}

					star_array[zero_start_row][i] = star_array[zero_ending_row][i];
					star_array[zero_ending_row][i] = '0';
					temp_star_array[zero_start_row][i] = '0';
					temp_star_array[zero_ending_row][i] = '*';
				}
			}
		}
	}

	for (int i = 1; i <= num_colunm; i++) {
		for (int j = 1; j <= num_row; j++) {
			if (star_array[j][i] != '0') {
				mark_colunm_empty[i] = 1;
			}
		}
	}

	for (int i = 1; i <= num_colunm; i++) {
		if (mark_colunm_empty[i] == 0) {
			zero_start_colunm = i;
			int j = 0;
			for (j = i; j <= num_colunm; j++) {
				if (mark_colunm_empty[j] == 1) {
					zero_ending_colunm = j;
					break;
				}
			}

			if (j != num_colunm + 1) {
				for (int k = num_row; k >= 1; k--) {
					if (star_array[k][zero_ending_colunm] != '0') {
						for (int p = 0; p < (6 + 2 * mark_dividing_lines) * (zero_ending_colunm - zero_start_colunm); p++) {
							cct_setcolor(15, 0);
							cct_gotoxy(image_resolution_star_X + (zero_ending_colunm - 1) * (6 + 2 * mark_dividing_lines) - p, image_resolution_star_Y + (k - 1) * (3 + mark_dividing_lines));
							if (!mark_dividing_lines) {
								cout << "      ";
							}
							else {
								if (p % 8 == 7) {
									cout << "     ║";
								}
								else {
									cout << "      ";
								}
							}
							cct_gotoxy(image_resolution_star_X + (zero_ending_colunm - 1) * (6 + 2 * mark_dividing_lines) - p, image_resolution_star_Y + (k - 1) * (3 + mark_dividing_lines) + 1);
							if (!mark_dividing_lines) {
								cout << "      ";
							}
							else {
								if (p % 8 == 7) {
									cout << "     ║";
								}
								else {
									cout << "      ";
								}
							}
							cct_gotoxy(image_resolution_star_X + (zero_ending_colunm - 1) * (6 + 2 * mark_dividing_lines) - p, image_resolution_star_Y + (k - 1) * (3 + mark_dividing_lines) + 2);
							if (!mark_dividing_lines) {
								cout << "      ";
							}
							else {
								if (p % 8 == 7) {
									cout << "     ║";
								}
								else {
									cout << "      ";
								}
							}

							cct_setcolor(8 + (int)(star_array[k][zero_ending_colunm] - '0'), 0);
							cct_gotoxy(image_resolution_star_X + (zero_ending_colunm - 1) * (6 + 2 * mark_dividing_lines) - p - 1, image_resolution_star_Y + (k - 1) * (3 + mark_dividing_lines));
							cout << "╔═╗";
							cct_gotoxy(image_resolution_star_X + (zero_ending_colunm - 1) * (6 + 2 * mark_dividing_lines) - p - 1, image_resolution_star_Y + (k - 1) * (3 + mark_dividing_lines) + 1);
							cout << "║★║";
							cct_gotoxy(image_resolution_star_X + (zero_ending_colunm - 1) * (6 + 2 * mark_dividing_lines) - p - 1, image_resolution_star_Y + (k - 1) * (3 + mark_dividing_lines) + 2);
							cout << "╚═╝";
							cct_setcolor(0, 7);
							Sleep(1);
						}
					}
					star_array[k][zero_start_colunm] = star_array[k][zero_ending_colunm];
					star_array[k][zero_ending_colunm] = '0';
					temp_star_array[k][zero_start_colunm] = temp_star_array[k][zero_ending_colunm];
					temp_star_array[k][zero_ending_colunm] = '*';
				}

				mark_colunm_empty[zero_start_colunm] = 1;
				mark_colunm_empty[zero_ending_colunm] = 0;
			}
			else {
				break;
			}
		}
	}

	for (int i = 1; i <= num_colunm; i++) {
		if (mark_colunm_empty[i] == 1) {
			zero_start_colunm = i;
			int j = 0;
			for (j = i; j <= num_colunm; j++) {
				if (mark_colunm_empty[j] == 0) {
					zero_ending_colunm = j;
					break;
				}
			}

			if (j != num_colunm + 1) {

			}
		}
	}

	if (!mark_dividing_lines) {
		cct_gotoxy(0, window_row - 4);
		cct_setcolor(0, 14);
		cout << "本次合成结束，按C/单击左键继续新一次的合成             ";
		int Mouse_X = 0, Mouse_Y = 0, Mouse_Action = -1, keycode1 = 0, keycode2 = 0;
		while (Mouse_Action != MOUSE_LEFT_BUTTON_CLICK && keycode1 != (int)('C') && keycode1 != (int)('c')) {
			cct_read_keyboard_and_mouse(Mouse_X, Mouse_Y, Mouse_Action, keycode1, keycode2);
		}
	}

	cct_gotoxy(0, window_row - 2);
	cct_setcolor(0, 7);
}

/***************************************************************************
  函数名称：star_array_D_or_E
  功    能：D或E模式下的操作
  输入参数：int num_row：星星的行数
			int num_colunm：星星的列数
			int* p_appointed_row：指定的行数的指针
			int* p_appointed_colunm：指定的列数的指针
			char star_array[][12]：星星数列
			char mode：模式
  返 回 值：无
  说    明：无
***************************************************************************/
void star_array_D_or_E(int num_row, int num_colunm, int* p_appointed_row, int* p_appointed_colunm, char star_array[][12], char temp_star_array[][12], char mode) {
	image_resolution_print_frame(num_row, num_colunm, p_appointed_row, p_appointed_colunm, star_array, mode - 'D');
	image_resolution_get_appointed_parameter(num_row, num_colunm, p_appointed_row, p_appointed_colunm, star_array, temp_star_array, mode - 'D', 1, mode);
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
}

/***************************************************************************
  函数名称：star_array_F
  功    能：F模式下的操作
  输入参数：int num_row：星星的行数
			int num_colunm：星星的列数
			int* p_appointed_row：指定的行数的指针
			int* p_appointed_colunm：指定的列数的指针
			char star_array[][12]：星星数列
			char temp_star_array[][12]：中间星星数列
			int count_star[]：记录每次消除星星数量的数组
			int scores[]：记录每次相除得分的总分数组
  返 回 值：无
  说    明：无
***************************************************************************/
void star_array_F(int num_row, int num_colunm, int* p_appointed_row, int* p_appointed_colunm, char star_array[][12], char temp_star_array[][12], int count_star[], int scores[]) {
	int window_colunm = 0, window_row = 0, buffer_colunm = 0, buffer_row = 0;
	int Mouse_X = 0, Mouse_Y = 0, Mouse_Action = -1, keycode1 = 0, keycode2 = 0;
	int temp_appointed_row = 0, temp_appointed_colunm = 0;
	bool mark_end_directly;
	image_resolution_print_frame(num_row, num_colunm, p_appointed_row, p_appointed_colunm, star_array, 0);
	cct_getconsoleborder(window_colunm, window_row, buffer_colunm, buffer_row);
	mark_end_directly = image_resolution_get_appointed_parameter(num_row, num_colunm, p_appointed_row, p_appointed_colunm, star_array, temp_star_array, 0, 1, 'F');

	while (!mark_end_directly) {
		temp_appointed_row = *p_appointed_row, temp_appointed_colunm = *p_appointed_colunm;
		for (int i = 1; i <= num_row; i++) {
			for (int j = 1; j <= num_colunm; j++) {
				if ((i != *p_appointed_row || j != *p_appointed_colunm) && temp_star_array[i][j] == '*') {
					image_resolution_temp_print(0, 0, i, j, star_array, 0, 2);
				}
			}
		}

		while (temp_appointed_row == *p_appointed_row && temp_appointed_colunm == *p_appointed_colunm) {
			cct_enable_mouse();
			Mouse_X = 0, Mouse_Y = 0, Mouse_Action = -1, keycode1 = 0, keycode2 = 0;
			cct_read_keyboard_and_mouse(Mouse_X, Mouse_Y, Mouse_Action, keycode1, keycode2);
			if ((Mouse_Action == MOUSE_LEFT_BUTTON_CLICK || keycode1 == 13) &&
				*p_appointed_row >= 1 && *p_appointed_row <= num_row && *p_appointed_colunm >= 1 && *p_appointed_colunm <= num_colunm) {
				break;
			}
			else if (keycode1 == 224) {
				cct_disable_mouse();
				image_resolution_moved_by_arrow(keycode2, p_appointed_row, p_appointed_colunm, num_row, num_colunm, star_array);
			}
			else if (keycode1 != 224) {
				*p_appointed_row = (Mouse_Y - image_resolution_star_Y + 3) / 3;
				*p_appointed_colunm = (Mouse_X - image_resolution_star_X + 6) / 6;
			}
		}

		for (int i = 1; i <= num_row; i++) {
			for (int j = 1; j <= num_colunm; j++) {
				if (temp_star_array[i][j] == '*') {
					image_resolution_temp_print(0, 0, i, j, star_array, 0, 0);
				}
			}
		}

		if ((Mouse_Action == MOUSE_LEFT_BUTTON_CLICK || keycode1 == 13) &&
			*p_appointed_row >= 1 && *p_appointed_row <= num_row && *p_appointed_colunm >= 1 && *p_appointed_colunm <= num_colunm) {
			cct_gotoxy(0, window_row - 3);
			cct_setcolor(0, 7);
			break;
		}
		else if (temp_appointed_row != *p_appointed_row || temp_appointed_colunm != *p_appointed_colunm) {
			if (*p_appointed_row >= 1 && *p_appointed_row <= num_row && *p_appointed_colunm >= 1 && *p_appointed_colunm <= num_colunm) {
				image_resolution_temp_print(p_appointed_row, p_appointed_colunm, 0, 0, star_array, 0, 1);
				cct_gotoxy(0, window_row - 4);
				cct_setcolor(0, 7);
				cout << "[当前鼠标] " << (char)('A' + *p_appointed_row - 1) << "行" << (char)('0' + *p_appointed_colunm - 1) << "列                                    ";
			}
			else {
				cct_gotoxy(0, window_row - 4);
				cct_setcolor(0, 7);
				cout << "[当前鼠标] 位置非法                                                    ";
			}
		}

		init_temp_star_array(temp_star_array);
	}

	if (!mark_end_directly) {
		count_star[1] = image_resolution_star_eliminate(num_row, num_colunm, star_array, temp_star_array, 0);
		cct_gotoxy(0, 0);
		sum_of_normal_scores(count_star, scores, 1);
		image_resolution_star_downward(num_row, num_colunm, star_array, temp_star_array, 0);
	}
}

/***************************************************************************
  函数名称：star_array_G
  功    能：G模式下的操作
  输入参数：int num_row：星星的行数
			int num_colunm：星星的列数
			int* p_appointed_row：指定的行数的指针
			int* p_appointed_colunm：指定的列数的指针
			char star_array[][12]：星星数列
			char temp_star_array[][12]：中间星星数列
			int count_star[]：记录每次消除星星数量的数组
			int scores[]：记录每次相除得分的总分数组
  返 回 值：无
  说    明：无
***************************************************************************/
void star_array_G(int num_row, int num_colunm, int* p_appointed_row, int* p_appointed_colunm, char star_array[][12], char temp_star_array[][12], int count_star[], int scores[]) {
	int window_colunm = 0, window_row = 0, buffer_colunm = 0, buffer_row = 0;
	int Mouse_X = 0, Mouse_Y = 0, Mouse_Action = -1, keycode1 = 0, keycode2 = 0;
	int temp_appointed_row = 0, temp_appointed_colunm = 0;
	bool mark_end_directly = 0;
	int steps = 0;
	cct_getconsoleborder(window_colunm, window_row, buffer_colunm, buffer_row);

	while (1) {
		image_resolution_print_frame(num_row, num_colunm, p_appointed_row, p_appointed_colunm, star_array, 1);
		mark_end_directly = image_resolution_get_appointed_parameter(num_row, num_colunm, p_appointed_row, p_appointed_colunm, star_array, temp_star_array, 1, 1, 'F');

		while (1) {
			steps++;

			while (!mark_end_directly) {
				temp_appointed_row = *p_appointed_row, temp_appointed_colunm = *p_appointed_colunm;
				for (int i = 1; i <= num_row; i++) {
					for (int j = 1; j <= num_colunm; j++) {
						if ((i != *p_appointed_row || j != *p_appointed_colunm) && temp_star_array[i][j] == '*') {
							image_resolution_temp_print(0, 0, i, j, star_array, 1, 2);
						}
					}
				}

				while (temp_appointed_row == *p_appointed_row && temp_appointed_colunm == *p_appointed_colunm) {
					cct_enable_mouse();
					Mouse_X = 0, Mouse_Y = 0, Mouse_Action = -1, keycode1 = 0, keycode2 = 0;
					cct_read_keyboard_and_mouse(Mouse_X, Mouse_Y, Mouse_Action, keycode1, keycode2);
					if ((Mouse_Action == MOUSE_LEFT_BUTTON_CLICK || keycode1 == 13) &&
						*p_appointed_row >= 1 && *p_appointed_row <= num_row && *p_appointed_colunm >= 1 && *p_appointed_colunm <= num_colunm) {
						break;
					}
					else if (keycode1 == 224) {
						cct_disable_mouse();
						image_resolution_moved_by_arrow(keycode2, p_appointed_row, p_appointed_colunm, num_row, num_colunm, star_array);
					}
					else if (keycode1 != 224) {
						if ((Mouse_Y - image_resolution_star_Y) % 4 == 3 || (Mouse_X - image_resolution_star_X) % 8 == 6 || (Mouse_X - image_resolution_star_X) % 8 == 7) {
							*p_appointed_row = 0;
							*p_appointed_colunm = 0;
						}
						else {
							*p_appointed_row = (Mouse_Y - image_resolution_star_Y + 4) / 4;
							*p_appointed_colunm = (Mouse_X - image_resolution_star_X + 8) / 8;
						}
					}
				}

				for (int i = 1; i <= num_row; i++) {
					for (int j = 1; j <= num_colunm; j++) {
						if (temp_star_array[i][j] == '*') {
							image_resolution_temp_print(0, 0, i, j, star_array, 1, 0);
						}
					}
				}

				if ((Mouse_Action == MOUSE_LEFT_BUTTON_CLICK || keycode1 == 13) &&
					*p_appointed_row >= 1 && *p_appointed_row <= num_row && *p_appointed_colunm >= 1 && *p_appointed_colunm <= num_colunm &&
					star_array[*p_appointed_row][*p_appointed_colunm] != '0') {
					cct_gotoxy(0, window_row - 3);
					cct_setcolor(0, 7);
					break;
				}
				else if (temp_appointed_row != *p_appointed_row || temp_appointed_colunm != *p_appointed_colunm) {
					if (*p_appointed_row >= 1 && *p_appointed_row <= num_row && *p_appointed_colunm >= 1 && *p_appointed_colunm <= num_colunm &&
						star_array[*p_appointed_row][*p_appointed_colunm] != '0') {
						image_resolution_temp_print(p_appointed_row, p_appointed_colunm, 0, 0, star_array, 1, 1);
						cct_getconsoleborder(window_colunm, window_row, buffer_colunm, buffer_row);
						cct_gotoxy(0, window_row - 4);
						cct_setcolor(0, 7);
						cout << "[当前鼠标] " << (char)('A' + *p_appointed_row - 1) << "行" << (char)('0' + *p_appointed_colunm - 1) << "列                                    ";
					}
					else {
						cct_getconsoleborder(window_colunm, window_row, buffer_colunm, buffer_row);
						cct_gotoxy(0, window_row - 4);
						cct_setcolor(0, 7);
						cout << "[当前鼠标] 位置非法                                                    ";
					}
				}

				init_temp_star_array(temp_star_array);
				mark_end_directly = image_resolution_get_appointed_parameter(num_row, num_colunm, p_appointed_row, p_appointed_colunm, star_array, temp_star_array, 1, 0, 'F');
			}

			if (!mark_end_directly) {
				count_star[steps] = image_resolution_star_eliminate(num_row, num_colunm, star_array, temp_star_array, 1);
				image_resolution_star_downward(num_row, num_colunm, star_array, temp_star_array, 1);
				cct_gotoxy(0, 0);
				if (judge_game_over_or_not(num_row, num_colunm, star_array)) {
					sum_of_bonus_scores(num_row, num_colunm, star_array, count_star, scores, &steps);
					cct_getconsoleborder(window_colunm, window_row, buffer_colunm, buffer_row);
					cct_gotoxy(0, window_row - 4);
					wait_for_enter_next_level(num_row, num_colunm, star_array);
					cct_gotoxy(0, window_row - 2);
					cct_setcolor(0, 7);
					cct_setcursor(CURSOR_VISIBLE_NORMAL);
					print_end_tips();
					rand_init_star_array(num_row, num_colunm, star_array);
					init_temp_star_array(temp_star_array);
					break;
				}
				else {
					sum_of_normal_scores(count_star, scores, steps);
				}
			}
			else {
				break;
			}
			init_temp_star_array(temp_star_array);
			mark_end_directly = image_resolution_get_appointed_parameter(num_row, num_colunm, p_appointed_row, p_appointed_colunm, star_array, temp_star_array, 1, 1, 'F');
		}

		if (mark_end_directly) {
			break;
		}
	}
}
