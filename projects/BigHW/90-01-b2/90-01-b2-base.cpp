/* 2154146 吴金轩 计科 */
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <Windows.h>
#include "../include/cmd_console_tools.h"
#include "90-01-b2.h"
using namespace std;

/***************************************************************************
   函数名称：digital_resolution_get_appointed_parameter
   功    能：获取指定的行数和列数
   输入参数：int num_row：星星的行数
			 int num_colunm：星星的列数
			 int* p_appointed_row：指定的行数的指针
			 int* p_appointed_colunm：指定的列数的指针
			 char star_array[][12]：星星数列
   返 回 值：无
   说    明：无
***************************************************************************/
void digital_resolution_get_appointed_parameter(int num_row, int num_colunm, int* p_appointed_row, int* p_appointed_colunm, char star_array[][12]) {
	char input_char_array[100] = { 0 };
	int temp_X_fault = 0, temp_Y_fault = 0;
	*p_appointed_row = 0;
	*p_appointed_colunm = 0;
	bool mark_get_appointed_parameter = 0;

	cout << "请以字母+数字形式[例：c2]输入矩阵坐标：";

	while (!mark_get_appointed_parameter) {
		cct_getxy(temp_X_fault, temp_Y_fault);
		cin.getline(input_char_array, 100);

		if (input_char_array[0] >= 'a' && input_char_array[0] <= 'z') {
			input_char_array[0] = input_char_array[0] + 'A' - 'a';
		}

		if (input_char_array[0] >= 'A' && input_char_array[0] < 'A' + num_row && input_char_array[1] >= '0' && input_char_array[1] < '0' + num_colunm) {
			mark_get_appointed_parameter = 1;
			*p_appointed_row = input_char_array[0] - 'A' + 1;
			*p_appointed_colunm = input_char_array[1] - '0' + 1;
			cout << "输入为" << input_char_array[0] << "行" << input_char_array[1] << "列" << endl;
			if (star_array[*p_appointed_row][*p_appointed_colunm] == '0') {
				cout << "输入的矩阵坐标位置为0（非法位置），请重新输入" << endl;
				digital_resolution_get_appointed_parameter(num_row, num_colunm, p_appointed_row, p_appointed_colunm, star_array);
			}
		}
		else {
			mark_get_appointed_parameter = 0;
			cct_setcursor(CURSOR_INVISIBLE);
			cout << "输入错误，请重新输入";
			Sleep(1000);
			cct_setcolor(0, 0);
			cct_gotoxy(0, temp_Y_fault + 1);
			cout << "                                                   ";
			cct_gotoxy(temp_X_fault, temp_Y_fault);
			cout << "                                                   ";
			cct_gotoxy(temp_X_fault, temp_Y_fault);
			cct_setcolor(0, 7);
			cct_setcursor(CURSOR_VISIBLE_NORMAL);
		}
	}
}

/***************************************************************************
   函数名称：digital_resolution_print_frame
   功    能：打印数字解的框架和内部数组
   输入参数：int num_row：星星的行数
			 int num_colunm：星星的列数
			 char star_array[][12]：星星数列
			 char temp_star_array[][12]：中间星星数列
			 int stage：阶段
   返 回 值：int count_star：消灭的星星的数量
   说    明：无
***************************************************************************/
int digital_resolution_print_frame(int num_row, int num_colunm, char star_array[][12], char temp_star_array[][12], int stage) {
	int count_star = 0;

	if (stage == 0) {
		cout << endl << "当前数组：" << endl;
	}
	else if (stage == 1) {
		cout << endl << "查找结果数组：" << endl;
	}
	else if (stage == 2) {
		cout << endl << "当前数组(不同色标识)：" << endl;
	}
	else if (stage == 3) {
		cout << endl << "相同值归并后的数组(不同色标记)：" << endl;
	}
	else if (stage == 4) {
		cout << endl << "下落后的数组：" << endl;
	}

	cout << "  |";
	for (int i = 0; i < num_colunm; i++) {
		cout << setw(3) << (char)('0' + i);
	}
	cout << endl;

	cout << "--+";
	for (int i = 0; i < num_colunm; i++) {
		cout << "---";
	}
	cout << "-" << endl;

	for (int i = 1; i <= num_row; i++) {
		cout << (char)(i - 1 + 'A') << " |";
		for (int j = 1; j <= num_colunm; j++) {
			int temp_X = 0, temp_Y = 0;
			cout << setw(3) << star_array[i][j];
			if (star_array[i][j] == '0') {
				cct_getxy(temp_X, temp_Y);
				if (stage == 0 || stage == 4) {
					cct_showch(temp_X - 1, temp_Y, '0', 14, 0, 1);
				}
				cct_setcolor(0, 7);
			}
			else if (temp_star_array[i][j] == '*') {
				cct_getxy(temp_X, temp_Y);
				if (stage == 2) {
					cct_showch(temp_X - 1, temp_Y, (char)(star_array[i][j]), 14, 0, 1);
				}
				else if (stage == 3) {
					cct_showch(temp_X - 1, temp_Y, '0', 14, 0, 1);
				}
				count_star++;
				cct_setcolor(0, 7);
			}
		}
		cout << endl;
	}
	cout << endl;

	return count_star;
}

/***************************************************************************
   函数名称：digital_resolution_judge_appointed_coordinate
   功    能：判断指定位置的周围是否有星星
   输入参数：int num_row：星星的行数
			 int num_colunm：星星的列数
			 int* p_appointed_row：指定的行数的指针
			 int* p_appointed_colunm：指定的列数的指针
			 char star_array[][12]：星星数列
			 char temp_star_array[][12]：中间星星数列
   返 回 值：无
   说    明：无
***************************************************************************/
void digital_resolution_judge_appointed_coordinate(int num_row, int num_colunm, int* p_appointed_row, int* p_appointed_colunm, char star_array[][12], char temp_star_array[][12]) {
	int temp_X_fault = 0, temp_Y_fault = 0;
	bool mark_scan_result = 0;

	while (!mark_scan_result) {
		mark_scan_result = scan_appointed_coordinate(num_row, num_colunm, *p_appointed_row, *p_appointed_colunm, star_array, temp_star_array);
		if (mark_scan_result) {
			temp_star_array[*p_appointed_row][*p_appointed_colunm] = '*';
			digital_resolution_print_frame(num_row, num_colunm, temp_star_array, star_array, 1);
		}
		else if (!mark_scan_result) {
			cout << "输入的矩阵坐标位置处无连续相同值，请重新输入" << endl;
			digital_resolution_get_appointed_parameter(num_row, num_colunm, p_appointed_row, p_appointed_colunm, star_array);
		}
	}
}

/***************************************************************************
  函数名称：digital_resolution_wait_for_enter_each_step
  功    能：给出提示并等待回车键
  输入参数：无
  返 回 值：无
  说    明：无
***************************************************************************/
void digital_resolution_wait_for_enter_each_step() {
	cout << "本次消除结束，按回车键继续新一次的消除...";
	while (_getch() != '\r');
	cout << endl;
}

/***************************************************************************
   函数名称：digital_resolution_modify_star_array
   功    能：调整星星数列
   输入参数：int num_row：星星的行数
			 int num_colunm：星星的列数
			 char star_array[][12]：星星数列
			 char temp_star_array[][12]：中间星星数列
   返 回 值：无
   说    明：无
***************************************************************************/
void digital_resolution_modify_star_array(int num_row, int num_colunm, char star_array[][12], char temp_star_array[][12]) {
	for (int i = 1; i <= num_colunm; i++) {
		for (int j = 1; j <= num_row; j++) {
			if (temp_star_array[j][i] == '*') {
				star_array[j][i] = '0';
				for (int k = j; k >= 1; k--) {
					star_array[k][i] = star_array[k - 1][i];
					star_array[k - 1][i] = '0';
					temp_star_array[k][i] = temp_star_array[k - 1][i];
					temp_star_array[k - 1][i] = '*';
				}
			}
		}
	}

	bool mark_colunm_empty[11] = { 0 };
	int zero_start_colunm = 0, zero_ending_colunm = 0;

	for (int i = 1; i <= num_colunm; i++) {
		for (int j = 1; j <= num_row; j++) {
			if (star_array[j][i] != '0') {
				mark_colunm_empty[i] = 1;
			}
		}
	}

	for (int i = 1; i <= num_colunm; i++) {
		zero_start_colunm = 0;
		zero_ending_colunm = 0;
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
				mark_colunm_empty[zero_start_colunm] = 1;
				mark_colunm_empty[zero_ending_colunm] = 0;
				for (int k = num_row; k >= 1; k--) {
					star_array[k][zero_start_colunm] = star_array[k][zero_ending_colunm];
					star_array[k][zero_ending_colunm] = '0';
					temp_star_array[k][zero_start_colunm] = temp_star_array[k][zero_ending_colunm];
					temp_star_array[k][zero_ending_colunm] = '*';
				}
			}
			else {
				break;
			}
		}
	}
}

/***************************************************************************
   函数名称：digital_resolution_eliminate_or_not
   功    能：打印结束提示
   输入参数：int appointed_row：指定的行数
			 int appointed_colunm：指定的列数
			 char* p_mark_eliminate：是否消除的参数的指针
   返 回 值：无
   说    明：无
***************************************************************************/
void digital_resolution_eliminate_or_not(int appointed_row, int appointed_colunm, char* p_mark_eliminate) {
	int temp_X = 0, temp_Y = 0;
	*p_mark_eliminate = 0;
	cout << "请确认是否把" << (char)(appointed_row - 1 + 'A') << (char)(appointed_colunm - 1 + '0') << "及周围的相同值消除(Y/N/Q)：";
	cct_getxy(temp_X, temp_Y);

	while (*p_mark_eliminate != 'Y' && *p_mark_eliminate != 'N' && *p_mark_eliminate != 'Q') {
		*p_mark_eliminate = _getche();
		cct_setcursor(CURSOR_INVISIBLE);

		if (*p_mark_eliminate >= 'a' && *p_mark_eliminate <= 'z') {
			*p_mark_eliminate = *p_mark_eliminate + 'A' - 'a';
		}

		if (*p_mark_eliminate != 'Y' && *p_mark_eliminate != 'N' && *p_mark_eliminate != 'Q') {
			cout << endl << "输入错误，请重新输入" << endl;
			Sleep(1000);
			cct_gotoxy(0, temp_Y + 1);
			cout << "                            ";
			cct_gotoxy(temp_X, temp_Y);
			cout << "  ";
			cct_gotoxy(temp_X, temp_Y);
		}

		cct_setcursor(CURSOR_VISIBLE_NORMAL);
	}

	cout << endl;
}

/***************************************************************************
  函数名称：star_array_ABC_common
  功    能：A/B/C模式下的共同操作
  输入参数：int num_row：星星的行数
			int num_colunm：星星的列数
			int* p_appointed_row：指定的行数的指针
			int* p_appointed_colunm：指定的列数的指针
			char star_array[][12]：星星数列
			char temp_star_array[][12]：中间星星数列
  返 回 值：无
  说    明：无
***************************************************************************/
void star_array_ABC_common(int num_row, int num_colunm, int* p_appointed_row, int* p_appointed_colunm, char star_array[][12], char temp_star_array[][12], char mode) {
	digital_resolution_print_frame(num_row, num_colunm, star_array, temp_star_array, 0);
	digital_resolution_get_appointed_parameter(num_row, num_colunm, p_appointed_row, p_appointed_colunm, star_array);
	digital_resolution_judge_appointed_coordinate(num_row, num_colunm, p_appointed_row, p_appointed_colunm, star_array, temp_star_array);
	digital_resolution_print_frame(num_row, num_colunm, star_array, temp_star_array, 2);
}

/***************************************************************************
  函数名称：star_array_A
  功    能：A模式下的操作
  输入参数：int num_row：星星的行数
			int num_colunm：星星的列数
			int* p_appointed_row：指定的行数的指针
			int* p_appointed_colunm：指定的列数的指针
			char star_array[][12]：星星数列
			char temp_star_array[][12]：中间星星数列
  返 回 值：无
  说    明：无
***************************************************************************/
void star_array_A(int num_row, int num_colunm, int* p_appointed_row, int* p_appointed_colunm, char star_array[][12], char temp_star_array[][12]) {
	star_array_ABC_common(num_row, num_colunm, p_appointed_row, p_appointed_colunm, star_array, temp_star_array, 'A');
}

/***************************************************************************
  函数名称：star_array_B
  功    能：B模式下的操作
  输入参数：int num_row：星星的行数
			int num_colunm：星星的列数
			int* p_appointed_row：指定的行数的指针
			int* p_appointed_colunm：指定的列数的指针
			char star_array[][12]：星星数列
			char temp_star_array[][12]：中间星星数列
			int count_star[]：记录每次消除星星数量的数组
			int scores[]：记录每次相除得分的总分数组
			int* p_mark_eliminations：星星消除模式的指针
  返 回 值：无
  说    明：无
***************************************************************************/
void star_array_B(int num_row, int num_colunm, int* p_appointed_row, int* p_appointed_colunm, char star_array[][12], char temp_star_array[][12], char* p_mark_eliminate, int count_star[], int scores[]) {
	init_temp_star_array(temp_star_array);
	star_array_ABC_common(num_row, num_colunm, p_appointed_row, p_appointed_colunm, star_array, temp_star_array, 'B');
	digital_resolution_eliminate_or_not(*p_appointed_row, *p_appointed_colunm, p_mark_eliminate);
	if (*p_mark_eliminate == 'Y') {
		count_star[1] = digital_resolution_print_frame(num_row, num_colunm, star_array, temp_star_array, 3);
		digital_resolution_modify_star_array(num_row, num_colunm, star_array, temp_star_array);
		sum_of_normal_scores(count_star, scores, 1);
		wait_for_enter();
		digital_resolution_print_frame(num_row, num_colunm, star_array, temp_star_array, 4);
	}
	else if (*p_mark_eliminate == 'N') {
		star_array_B(num_row, num_colunm, p_appointed_row, p_appointed_colunm, star_array, temp_star_array, p_mark_eliminate, count_star, scores);
	}
	else if (*p_mark_eliminate == 'Q') {
		cout << endl;
	}
}

/***************************************************************************
  函数名称：star_array_C
  功    能：C模式下的操作
  输入参数：int* p_num_row：星星的行数的指针
			int* p_num_colunm：星星的列数的指针
			int* p_appointed_row：指定的行数的指针
			int* p_appointed_colunm：指定的列数的指针
			char star_array[][12]：星星数列
			char temp_star_array[][12]：中间星星数列
			int count_star[]：记录每次消除星星数量的数组
			int scores[]：记录每次相除得分的总分数组
			int* p_mark_eliminations：星星消除模式的指针
			int* p_num_of_steps：已经消除的步数
  返 回 值：无
  说    明：无
***************************************************************************/
void star_array_C(int* p_num_row, int* p_num_colunm, int* p_appointed_row, int* p_appointed_colunm, char star_array[][12],
	char temp_star_array[][12], int count_star[], int scores[], char* p_mark_eliminate, int* p_num_of_steps) {
	while (1) {
		init_temp_star_array(temp_star_array);
		star_array_ABC_common(*p_num_row, *p_num_colunm, p_appointed_row, p_appointed_colunm, star_array, temp_star_array, 'C');
		digital_resolution_eliminate_or_not(*p_appointed_row, *p_appointed_colunm, p_mark_eliminate);
		if (*p_mark_eliminate == 'Y') {
			(*p_num_of_steps)++;
			count_star[*p_num_of_steps] = digital_resolution_print_frame(*p_num_row, *p_num_colunm, star_array, temp_star_array, 3);
			digital_resolution_modify_star_array(*p_num_row, *p_num_colunm, star_array, temp_star_array);
			sum_of_normal_scores(count_star, scores, *p_num_of_steps);
			wait_for_enter();
			digital_resolution_print_frame(*p_num_row, *p_num_colunm, star_array, temp_star_array, 4);
			if (!judge_game_over_or_not(*p_num_row, *p_num_colunm, star_array)) {
				digital_resolution_wait_for_enter_each_step();
			}
			else {
				wait_for_enter_next_level(*p_num_row, *p_num_colunm, star_array);
				break;
			}
		}
		else if (*p_mark_eliminate == 'N') {
			star_array_C(p_num_row, p_num_colunm, p_appointed_row, p_appointed_colunm, star_array, temp_star_array, count_star, scores, p_mark_eliminate, p_num_of_steps);
			break;
		}
		else if (*p_mark_eliminate == 'Q') {
			cout << endl;
			break;
		}
	}
}