/* 2154146 吴金轩 计科 */
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "../include/cmd_console_tools.h"
#include "90-01-b2.h"
using namespace std;

/***************************************************************************
   函数名称：get_colunm_and_row
   功    能：获取星星的行数和列数
   输入参数：int* p_num_row：星星的行数的指针
			 int* p_num_colunm：星星的列数的指针
   返 回 值：无
   说    明：无
***************************************************************************/
void get_colunm_and_row(int* p_num_row, int* p_num_colunm) {
	cct_cls();
	cout << "请输入行数(8-10)：" << endl;
	cin >> *p_num_row;

	while (cin.fail() || *p_num_row < 8 || *p_num_row > 10) {
		cin.clear();
		cin.ignore(65535, '\n');
		cout << "请输入行数(8-10)：" << endl;
		cin >> *p_num_row;
	}

	cout << "请输入列数(8-10)：" << endl;
	cin >> *p_num_colunm;

	while (cin.fail() || *p_num_colunm < 8 || *p_num_colunm > 10) {
		cin.clear();
		cin.ignore(65535, '\n');
		cout << "请输入列数(8-10)：" << endl;
		cin >> *p_num_colunm;
	}
	char temp_input[100] = { 0 };
	cin.getline(temp_input, 100);
}

/***************************************************************************
   函数名称：init_star_array
   功    能：初始化星星数列
   输入参数：int num_row：星星的行数
			 int num_colunm：星星的列数
			 char star_array[][12]：星星数列
   返 回 值：无
   说    明：无
***************************************************************************/
void init_star_array(char star_array[][12]) {
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			star_array[j][i] = '0';
		}
	}
}

/***************************************************************************
   函数名称：init_temp_star_array
   功    能：初始化中间星星数列
   输入参数：int num_row：星星的行数
			 int num_colunm：星星的列数
			 char temp_star_array[][12]：中间星星数列
   返 回 值：无
   说    明：无
***************************************************************************/
void init_temp_star_array(char temp_star_array[][12]) {
	for (int i = 0; i < 12; i++) {
		temp_star_array[0][i] = '*';
		temp_star_array[11][i] = '*';
	}

	for (int i = 1; i <= 10; i++) {
		for (int j = 1; j <= 10; j++) {
			temp_star_array[j][i] = '0';
		}
	}
}

/***************************************************************************
   函数名称：rand_init_star_array
   功    能：随机化赋值星星数列
   输入参数：int num_row：星星的行数
			 int num_colunm：星星的列数
			 char star_array[][12]：星星数列
   返 回 值：无
   说    明：无
***************************************************************************/
void rand_init_star_array(int num_row, int num_colunm, char star_array[][12]) {
	for (int i = 1; i <= num_colunm; i++) {
		for (int j = 1; j <= num_row; j++) {
			star_array[j][i] = rand() % 5 + '1';
		}
	}
}

/***************************************************************************
  函数名称：wait_for_enter
  功    能：给出提示并等待回车键
  输入参数：无
  返 回 值：无
  说    明：无
***************************************************************************/
void wait_for_enter() {
	cout << endl << "按回车键进行数组下落操作...";
	while (_getch() != '\r');
	cout << endl;
}

/***************************************************************************
   函数名称：scan_appointed_coordinate
   功    能：扫描指定位置的周围是否有可消除项
   输入参数：int num_row：星星的行数
			 int num_colunm：星星的列数
			 int appointed_row：指定的行数
			 int appointed_colunm：指定的列数
			 char star_array[][12]：星星数列
			 char temp_star_array[][12]：中间星星数列
   返 回 值：bool mark_scan_result：扫描结果
   说    明：无
***************************************************************************/
bool scan_appointed_coordinate(int num_row, int num_colunm, int appointed_row, int appointed_colunm, char star_array[][12], char temp_star_array[][12]) {
	bool mark_scan_result = 0;

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if ((i != 0 || j != 0) && i * j != 1 && i * j != -1) {
				if (star_array[appointed_row][appointed_colunm] == star_array[appointed_row + i][appointed_colunm + j] && temp_star_array[appointed_row + i][appointed_colunm + j] != '*') {
					mark_scan_result = 1;
					temp_star_array[appointed_row + i][appointed_colunm + j] = '*';
					scan_appointed_coordinate(num_row, num_colunm, appointed_row + i, appointed_colunm + j, star_array, temp_star_array);
				}
			}
		}
	}

	return mark_scan_result;
}

/***************************************************************************
   函数名称：print_end_tips
   功    能：打印结束提示
   输入参数：无
   返 回 值：无
   说    明：无
***************************************************************************/
void print_end_tips() {
	char input_char[100] = { 0 };
	while (input_char[0] != 'E' || input_char[1] != 'N' || input_char[2] != 'D') {
		cout << "本小题结束，请输入End继续...";
		cin.getline(input_char, 100);
		for (int i = 0; i < 3; i++) {
			if (input_char[i] >= 'a' && input_char[i] <= 'z') {
				input_char[i] = input_char[i] + 'A' - 'a';
			}
		}
		if (input_char[0] != 'E' || input_char[1] != 'N' || input_char[2] != 'D') {
			cout << "输入错误，请重新输入" << endl;
		}
	}
}

/***************************************************************************
  函数名称：wait_for_enter_each_step
  功    能：给出提示并等待回车键
  输入参数：int* p_num_row：星星的行数的指针
			int* p_num_colunm：星星的列数的指针
			int* p_appointed_row：指定的行数的指针
			int* p_appointed_colunm：指定的列数的指针
			char star_array[][12]：星星数列
  返 回 值：无
  说    明：无
***************************************************************************/
void wait_for_enter_next_level(int num_row, int num_colunm, char star_array[][12]) {
	int count_remained_stars = 0;
	for (int i = 1; i <= num_row; i++) {
		for (int j = 1; j <= num_colunm; j++) {
			if (star_array[i][j] != '0') {
				count_remained_stars++;
			}
		}
	}
	cct_setcolor(0, 7);
	cout << "                                               " << endl;
	int temp_X = 0, temp_Y = 0;
	cct_getxy(temp_X, temp_Y);
	cct_setcolor(14, 4);
	cout << "剩余" << count_remained_stars << "个不可消除项，本关结束";
	cct_setcolor(0, 7);
	cout << endl << endl;
}

/***************************************************************************
   函数名称：sum_of_normal_scores
   功    能：分数计算
   输入参数：int count_star[]：记录每次消除星星数量的数组
			 int scores[]：记录每次相除得分的总分数组
			 int number_of_eliminations：已经进行的消除的次数
   返 回 值：无
   说    明：无
***************************************************************************/
void sum_of_normal_scores(int count_star[], int scores[], int number_of_eliminations) {
	scores[number_of_eliminations] = scores[number_of_eliminations - 1] + count_star[number_of_eliminations] * count_star[number_of_eliminations] * 5;
	cout << "本次得分：" << scores[number_of_eliminations] - scores[number_of_eliminations - 1] << " 总得分：" << scores[number_of_eliminations];
}

/***************************************************************************
   函数名称：sum_of_bonus_scores
   功    能：分数计算
   输入参数：int count_star[]：记录每次消除星星数量的数组
			 int scores[]：记录每次相除得分的总分数组
			 int number_of_eliminations：已经进行的消除的次数
   返 回 值：无
   说    明：无
***************************************************************************/
void sum_of_bonus_scores(int num_row, int num_colunm, char star_array[][12], int count_star[], int scores[], int* number_of_eliminations) {
	scores[*number_of_eliminations] = scores[*number_of_eliminations - 1] + count_star[*number_of_eliminations] * count_star[*number_of_eliminations] * 5;
	(*number_of_eliminations)++;
	int count = 0, bonus_scores = 0;
	for (int i = 1; i <= num_row; i++) {
		for (int j = 1; j <= num_colunm; j++) {
			if (star_array[i][j] != '0') {
				count++;
			}
		}
	}

	if (count < 10) {
		bonus_scores = (10 - count) * 180;
	}
	else {
		bonus_scores = 0;
	}

	count_star[*number_of_eliminations] = 0;
	scores[*number_of_eliminations] = scores[*number_of_eliminations - 1] + bonus_scores;
	cct_gotoxy(0, 0);
	cout << "本次得分：" << scores[*number_of_eliminations - 1] - scores[*number_of_eliminations - 2] << " 奖励分：" << bonus_scores << " 总得分：" << scores[*number_of_eliminations];
}

/***************************************************************************
   函数名称：judge_game_over_or_not
   功    能：判断游戏是否结束
   输入参数：int num_row：星星的行数
			 int num_colunm：星星的列数
			 char star_array[][12]：星星数列
   返 回 值：bool mark_game_over：判断游戏是否结束的标志
   说    明：无
***************************************************************************/
bool judge_game_over_or_not(int num_row, int num_colunm, char star_array[][12]) {
	bool mark_game_over = 1;

	for (int i = 0; i <= num_row; i++) {
		for (int j = 0; j <= num_colunm; j++) {
			if (star_array[i][j] != '0') {
				for (int k = -1; k <= 1; k++) {
					for (int p = -1; p <= 1; p++) {
						if ((k != 0 || p != 0) && k * p != 1 && k * p != -1) {
							if (star_array[i][j] == star_array[i + k][j + p]) {
								mark_game_over = 0;
							}
						}
					}
				}
			}
		}
	}

	return mark_game_over;
}