/* 2154146 吴金轩 计科 */
#include <iostream>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include "../include/common_star_print.h"
#include "../include/common_frame_constuction.h"
#include "../include/common_math_tools.h"
#include "90-02-b1.h"
using namespace std;


/***************************************************************************
   函数名称：init_num_tetris
   功    能：初始化俄罗斯方块矩阵
   输入参数：bool num_tetris[][5]：俄罗斯方块矩阵
             int num：俄罗斯方块的数字
   返 回 值：无
   说    明：无
***************************************************************************/
void init_num_tetris(bool num_tetris[][5], int num)
{
	for (int i = 0; i < 5; i++) {
		for (int j = 1; j < 4; j++) {
			num_tetris[i][j] = 1;
		}
		num_tetris[i][0] = 0;
		num_tetris[i][4] = 0;
	}

	switch (num) {
	case 0:
		num_tetris[1][2] = 0;
		num_tetris[2][2] = 0;
		num_tetris[3][2] = 0;
		break;
	case 1:
		for (int i = 0; i < 5; i++) {
			num_tetris[i][1] = 0;
			num_tetris[i][3] = 0;
		}
		break;
	case 2:
		num_tetris[1][1] = 0;
		num_tetris[1][2] = 0;
		num_tetris[3][2] = 0;
		num_tetris[3][3] = 0;
		break;
	case 3:
		num_tetris[1][1] = 0;
		num_tetris[1][2] = 0;
		num_tetris[3][1] = 0;
		num_tetris[3][2] = 0;
		break;
	case 4:
		num_tetris[0][2] = 0;
		num_tetris[1][2] = 0;
		num_tetris[3][1] = 0;
		num_tetris[3][2] = 0;
		num_tetris[4][1] = 0;
		num_tetris[4][2] = 0;
		break;
	case 5:
		num_tetris[1][2] = 0;
		num_tetris[1][3] = 0;
		num_tetris[3][1] = 0;
		num_tetris[3][2] = 0;
		break;
	case 6:
		num_tetris[1][2] = 0;
		num_tetris[1][3] = 0;
		num_tetris[3][2] = 0;
		break;
	case 7:
		for (int i = 1; i < 5; i++) {
			num_tetris[i][1] = 0;
			num_tetris[i][2] = 0;
		}
		break;
	case 8:
		num_tetris[1][2] = 0;
		num_tetris[3][2] = 0;
		break;
	case 9:
		num_tetris[1][2] = 0;
		num_tetris[3][1] = 0;
		num_tetris[3][2] = 0;
		break;
	default:
		for (int i = 0; i < 5; i++) {
			for (int j = 1; j < 4; j++) {
				num_tetris[i][j] = 0;
			}
		}
		break;
	}
}

/***************************************************************************
   函数名称：set_star_color
   功    能：设置俄罗斯方块的颜色
   输入参数：int num：俄罗斯方块的数字
   返 回 值：int color：俄罗斯方块的颜色
   说    明：无
***************************************************************************/
int set_star_color(int num) 
{
	int color;
	switch (num) {
	case 0:
		color = COLOR_0;
		break;
	case 1:
		color = COLOR_1;
		break;
	case 2:
		color = COLOR_2;
		break;
	case 3:
		color = COLOR_3;
		break;
	case 4:
		color = COLOR_4;
		break;
	case 5:
		color = COLOR_5;
		break;
	case 6:
		color = COLOR_6;
		break;
	case 7:
		color = COLOR_7;
		break;
	case 8:
		color = COLOR_8;
		break;
	case 9:
		color = COLOR_9;
		break;
	case 10:
		color = COLOR_HWHITE;
		break;
	default:
		color = COLOR_BLACK;
		break;
	}
	return color;
}

/***************************************************************************
   函数名称：init_num_play_screen
   功    能：初始化游戏界面矩阵
   输入参数：int num_play_screen[][MAX_PLAY_SCREEN_WIDTH + 2]：游戏界面矩阵
		     int play_screen_cols：游戏界面星星列数
			 int play_screen_lines：游戏界面星星行数
   返 回 值：无
   说    明：无
***************************************************************************/
void init_num_play_screen(int num_play_screen[][MAX_PLAY_SCREEN_WIDTH + 2], int play_screen_cols, int play_screen_lines)
{
	//空位置处填入10
	for (int i = 0; i < MAX_PLAY_SCREEN_HEIGHT + 4; i++) {
		for (int j = 0; j < MAX_PLAY_SCREEN_WIDTH + 2; j++) {
			num_play_screen[i][j] = 10;
		}
	}

	//非法位置填入11
	for (int i = 0; i < MAX_PLAY_SCREEN_WIDTH + 2; i++) {
		num_play_screen[0][i] = 11;
	}

	for (int i = 1; i <= play_screen_lines + 3; i++) {
		num_play_screen[i][0] = 11;
		for (int j = play_screen_cols + 1; j < MAX_PLAY_SCREEN_WIDTH + 2; j++) {
			num_play_screen[i][j] = 11;
		}
	}

	for (int i = play_screen_lines + 4; i < MAX_PLAY_SCREEN_HEIGHT + 4; i++) {
		for (int j = 0; j < MAX_PLAY_SCREEN_WIDTH + 2; j++) {
			num_play_screen[i][j] = 11;
		}
	}
}

/***************************************************************************
   函数名称：print_num_tetris
   功    能：打印数字俄罗斯方块
   输入参数：bool num_tetris[][5]：数字俄罗斯方块矩阵
             int tetris_center_X：数字俄罗斯方块的中心星星的X坐标
			 int tetris_center_Y：数字俄罗斯方块的中心星星的Y坐标
			 int color：数字俄罗斯方块的颜色
   返 回 值：无
   说    明：无
***************************************************************************/
void print_num_tetris(bool num_tetris[][5], int tetris_center_X, int tetris_center_Y, int color)
{
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (num_tetris[i][j]) {
				if (tetris_center_Y - 3 + i >= 0) {
					print_stars(color, (tetris_center_X - 3 + j) * 6, (tetris_center_Y - 3 + i) * 3);
				}
			}
		}
	}
}

/***************************************************************************
   函数名称：print_play_screen
   功    能：打印游戏界面
   输入参数：int screen_width：游戏界面的宽度
             int screen_height：游戏界面的高度
   返 回 值：无
   说    明：无
***************************************************************************/
void print_play_screen(int screen_width, int screen_height)
{
	cct_setcolor(COLOR_HWHITE, COLOR_HWHITE);
	for (int i = 0; i < screen_height; i++) {
		cct_gotoxy(0, i);
		for (int j = 0; j < screen_width; j++) {
			cout << " ";
		}
	}
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
}


/***************************************************************************
   函数名称：set_console_size
   功    能：设置游戏窗口大小
   输入参数：int* p_play_screen_width：游戏界面的宽度的指针
			 int* p_play_screen_height：游戏界面的高度的指针
   返 回 值：无
   说    明：无
***************************************************************************/
void set_console_size(int* p_play_screen_width, int* p_play_screen_height, int info_console_width)
{
	cct_cls();
	get_input(p_play_screen_width, "游戏窗口宽度，需为3的倍数", 12, 21);
	while (*p_play_screen_width%3) {
		get_input(p_play_screen_width, "游戏窗口宽度，需为3的倍数", 12, 21);
	}
	get_input(p_play_screen_height, "游戏窗口高度", 18, 26);
	cct_cls();
	*p_play_screen_width *= 6;
	*p_play_screen_height *= 3;
	cct_setconsoleborder(*p_play_screen_width + info_console_width, *p_play_screen_height + 3, *p_play_screen_width + info_console_width, *p_play_screen_height + 3);
	print_play_screen(*p_play_screen_width, *p_play_screen_height);
}

/***************************************************************************
   函数名称：print_game_info
   功    能：打印游戏界面的信息内容
   输入参数：int play_screen_width：游戏界面的宽度
   返 回 值：无
   说    明：无
***************************************************************************/
void print_game_info(int play_screen_width)
{
	cct_gotoxy(play_screen_width + 2, 0);
	cout << "数字俄罗斯方块";
	cct_gotoxy(play_screen_width + 2, 3);
	cout << "有胆你就来！！！";
	cct_gotoxy(play_screen_width + 2, 6);
	cout << "得分：";
	cout << "0" << endl;
	cct_gotoxy(play_screen_width + 2, 9);
	cout << "等级：";
	cout << "0" << endl;
	cct_gotoxy(play_screen_width + 2, 12);
	cout << "下一个方块：";
}

/***************************************************************************
   函数名称：print_next_tetris
   功    能：打印下一个俄罗斯方块的提示
   输入参数：bool num_tetris[][5]：数字俄罗斯方块
             int rand_num_tetris：随机数列
			 int play_screen_width：游戏界面的宽度
   返 回 值：无
   说    明：无
***************************************************************************/
void print_next_tetris(bool num_tetris[][5], int rand_num_tetris, int play_screen_width)
{
	int color = 0;
	color = set_star_color(rand_num_tetris);
	init_num_tetris(num_tetris, rand_num_tetris);
	print_num_tetris(num_tetris, play_screen_width / 6 + 3, 8, color);
}

/***************************************************************************
   函数名称：update_next_tetris
   功    能：更新下一个俄罗斯方块的提示
   输入参数：int play_screen_width：游戏界面的宽度
             bool temp_num_tetris[][5]：下一个数字俄罗斯方块
			 int rand_num_tetris：随机数列
			 int no_tetris：目前进行到第几个俄罗斯方块
   返 回 值：无
   说    明：无
***************************************************************************/
void update_next_tetris(int play_screen_width, bool temp_num_tetris[][5], int rand_num_tetris[], int no_tetris)
{
	for (int i = 0; i < 3 * 6; i++) {
		for (int j = 0; j < 5 * 3; j++) {
			cct_gotoxy(play_screen_width + 6 + i, 15 + j);
			cct_setcolor();
			cout << " ";
		}
	}
	print_next_tetris(temp_num_tetris, rand_num_tetris[no_tetris + 1], play_screen_width);
}

/***************************************************************************
   函数名称：update_score
   功    能：更新分数
   输入参数：int score：分数
			 int play_screen_width：游戏界面的宽度
   返 回 值：无
   说    明：无
***************************************************************************/
void update_score(int score, int play_screen_width)
{
	cct_gotoxy(play_screen_width + 8, 6);
	cout << score;
}

/***************************************************************************
   函数名称：update_level
   功    能：更新等级
   输入参数：int level：等级
			 int play_screen_width：游戏界面的宽度
   返 回 值：无
   说    明：无
***************************************************************************/
void update_level(int level, int play_screen_width)
{
	cct_gotoxy(play_screen_width + 8, 9);
	cout << level;
}

/***************************************************************************
   函数名称：eliminate_lines
   功    能：消除行
   输入参数：bool eliminate[]：记录第几行可消除的数组
             int num_play_screen[][MAX_PLAY_SCREEN_WIDTH + 2]：游戏界面矩阵
			 int play_screen_cols：游戏界面星星列数
			 int play_screen_lines：游戏界面星星行数
   返 回 值：无
   说    明：无
***************************************************************************/
void eliminate_lines(bool eliminate[], int num_play_screen[][MAX_PLAY_SCREEN_WIDTH + 2], int play_screen_cols, int play_screen_lines)
{
	int color = 0;
	int temp_int = 0;
	bool temp_bool = 0;
	int temp_num_play_screen[MAX_PLAY_SCREEN_HEIGHT + 4][MAX_PLAY_SCREEN_WIDTH + 2] = { 0 };

	for (int i = 0; i < MAX_PLAY_SCREEN_HEIGHT + 4; i++) {
		for (int j = 0; j < MAX_PLAY_SCREEN_WIDTH + 2; j++) {
			temp_num_play_screen[i][j] = num_play_screen[i][j];
		}
	}

	for (int i = 1; i <= play_screen_lines; i++) {
		if (eliminate[i]) {
			for (int j = 1; j <= play_screen_cols; j++) {
				temp_num_play_screen[i][j] = 10;
			}

			for (int k = i; k <= play_screen_lines + 2; k++) {
				for (int j = 1; j <= play_screen_cols; j++) {
					temp_int = temp_num_play_screen[k + 1][j];
					temp_num_play_screen[k + 1][j] = temp_num_play_screen[k][j];
					temp_num_play_screen[k][j] = temp_int;
				}
			}

			eliminate[i] = 0;
			for (int j = i; j <= play_screen_lines - 1; j++) {
				temp_bool = eliminate[j + 1];
				eliminate[j + 1] = eliminate[j];
				eliminate[j] = temp_bool;
			}
		}
	}

	for (int i = 1; i <= play_screen_lines; i++) {
		for (int j = 1; j <= play_screen_cols; j++) {
			if (temp_num_play_screen[i][j] != num_play_screen[i][j]) {
				color = set_star_color(temp_num_play_screen[i][j]);
				print_stars(color, (j - 1) * 6, (play_screen_lines - i) * 3);
				num_play_screen[i][j] = temp_num_play_screen[i][j];
			}
		}
	}
}

/***************************************************************************
   函数名称：digit_tetris_move
   功    能：在内部数组中实现俄罗斯方块的移动
   输入参数：bool num_tetris[][5]：数字俄罗斯方块矩阵
			 int num_play_screen[][MAX_PLAY_SCREEN_WIDTH + 2]：游戏界面矩阵
			 int* p_tetris_center_X：数字俄罗斯方块的中心星星的X坐标的指针
			 int* p_tetris_center_Y：数字俄罗斯方块的中心星星的Y坐标的指针
			 int* p_sleep_time：移动一行的时间的指针
   返 回 值：bool move：是否可移动的标志，可移动返回1，不可移动返回0
   说    明：无
***************************************************************************/
bool digit_tetris_move(int num_play_screen[][MAX_PLAY_SCREEN_WIDTH + 2], bool num_tetris[][5], int* p_tetris_center_X, int* p_tetris_center_Y, int* p_sleep_time)
{
	int keycode1 = 0, keycode2 = 0;
	int temp_X = 0, temp_Y = 0;
	bool move = 0, temp_tetris[5][5] = { 0 };
	keycode1 = _getch();
	keycode2 = _getch();

	if (keycode1 == 224) {
		temp_X = *p_tetris_center_X;
		temp_Y = *p_tetris_center_Y;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				temp_tetris[i][j] = num_tetris[i][j];
			}
		}

		if (keycode2 == 75 || keycode2 == 77 || keycode2 == 72) {
			if (keycode2 == 75) {
				temp_X -= 1;
			}
			else if (keycode2 == 77) {
				temp_X += 1;
			}
			else if (keycode2 == 72) {
				rotate_matrix(temp_tetris[0], 5);
			}

			if (!judge_move_or_not(num_play_screen, temp_tetris, temp_X, temp_Y)) {
				move = 1;
				if (keycode2 == 75) {
					*p_tetris_center_X -= 1;
				}
				else if (keycode2 == 77) {
					*p_tetris_center_X += 1;
				}
				else if (keycode2 == 72) {
					rotate_matrix(num_tetris[0], 5);
				}
			}
		}
		else if (keycode2 == 80) {
			*p_sleep_time = 50;
		}
	}

	return move;
}

/***************************************************************************
   函数名称：image_tetris_move
   功    能：在伪图形界面中实现俄罗斯方块的移动
   输入参数：int num_play_screen[][MAX_PLAY_SCREEN_WIDTH + 2]：游戏界面矩阵
             int num：数字俄罗斯方块代表的数字
             bool temp_num_tetris[][5]：变化前的数字俄罗斯方块矩阵
			 int temp_X：变化前的数字俄罗斯方块的中心星星的X坐标
			 int temp_Y：变化前的数字俄罗斯方块的中心星星的Y坐标
			 bool num_tetris[][5]：变化后的数字俄罗斯方块矩阵
			 int tetris_center_X：变化后的数字俄罗斯方块的中心星星的X坐标
			 int tetris_center_Y：变化后的数字俄罗斯方块的中心星星的Y坐标
			 int play_screen_cols：游戏界面星星列数
			 int play_screen_lines：游戏界面星星行数
   返 回 值：无
   说    明：无
***************************************************************************/
void image_tetris_move(int num_play_screen[][MAX_PLAY_SCREEN_WIDTH+2], int num, bool temp_num_tetris[][5], int temp_X, int temp_Y, bool num_tetris[][5], int tetris_center_X, int tetris_center_Y, int play_screen_cols, int play_screen_lines)
{
	int temp_num_play_screen_1[MAX_PLAY_SCREEN_HEIGHT + 4][MAX_PLAY_SCREEN_WIDTH + 2] = { 0 };
	int temp_num_play_screen_2[MAX_PLAY_SCREEN_HEIGHT + 4][MAX_PLAY_SCREEN_WIDTH + 2] = { 0 };
	int color = 0;

	for (int i = 0; i < MAX_PLAY_SCREEN_HEIGHT + 4; i++) {
		for (int j = 0; j < MAX_PLAY_SCREEN_WIDTH + 2; j++) {
			temp_num_play_screen_1[i][j] = num_play_screen[i][j];
			temp_num_play_screen_2[i][j] = num_play_screen[i][j];
		}
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (temp_num_tetris[i][j]) {
				temp_num_play_screen_1[temp_Y + 2 - i][temp_X - 2 + j] = num;
			}
			if (num_tetris[i][j]) {
				temp_num_play_screen_2[tetris_center_Y + 2 - i][tetris_center_X - 2 + j] = num;
			}
		}
	}
	
	for (int i = 1; i <= play_screen_lines; i++) {
		for (int j = 1; j <= play_screen_cols; j++) {
			if (temp_num_play_screen_1[i][j] != temp_num_play_screen_2[i][j]) {
				color = set_star_color(temp_num_play_screen_2[i][j]);
				print_stars(color, (j - 1) * 6, (play_screen_lines - i) * 3);
			}
		}
	}
}

/***************************************************************************
   函数名称：num_tetris_A
   功    能：A模式功能实现
   输入参数：bool num_tetris[][5]：数字俄罗斯方块矩阵
   返 回 值：无
   说    明：无
***************************************************************************/
void num_tetris_A(bool num_tetris[][5])
{
	for (int i = 0; i <= 9; i++) {
		int color = 0;
		cct_cls();
		color = set_star_color(i);
		init_num_tetris(num_tetris, i);
		print_num_tetris(num_tetris, 3, 3, color);
		cct_gotoxy(0, 20);
		cout << "输入回车以继续...";
		get_enter();
	}
	cct_gotoxy(0, 22);
	print_end_tips();
}

/***************************************************************************
   函数名称：num_tetris_B
   功    能：B模式功能实现
   输入参数：bool num_tetris[][5]：数字俄罗斯方块矩阵
   返 回 值：无
   说    明：无
***************************************************************************/
void num_tetris_B(bool num_tetris[][5])
{
	int color = 0;
	for (int i = 0; i <= 9; i++) {
		cct_cls();
		color = set_star_color(i);
		init_num_tetris(num_tetris, i);
		print_num_tetris(num_tetris, 3, 3, color);
		cct_gotoxy(0, 20);
		cout << "输入回车以继续...";
		get_enter();

		cct_cls();
		rotate_matrix(&num_tetris[0][0], 5);
		print_num_tetris(num_tetris, 3, 3, color);
		cct_gotoxy(0, 20);
		cout << "输入回车以继续...";
		get_enter();

		cct_cls();
		rotate_matrix(&num_tetris[0][0], 5);
		print_num_tetris(num_tetris, 3, 3, color);
		cct_gotoxy(0, 20);
		cout << "输入回车以继续...";
		get_enter();

		cct_cls();
		rotate_matrix(&num_tetris[0][0], 5);
		print_num_tetris(num_tetris, 3, 3, color);
		cct_gotoxy(0, 20);
		cout << "输入回车以继续...";
		get_enter();
	}
	cct_gotoxy(0, 22);
	print_end_tips();
}

/***************************************************************************
   函数名称：num_tetris_C
   功    能：C模式功能实现
   输入参数：int play_screen_width：游戏界面的宽度
			 int play_screen_height：游戏界面的高度
             bool num_tetris[][5]：数字俄罗斯方块矩阵
			 int num：俄罗斯方块代表的数字
   返 回 值：无
   说    明：无
***************************************************************************/
void num_tetris_C(int play_screen_width, int play_screen_height, bool num_tetris[][5], int num)
{
	cct_setcursor(CURSOR_INVISIBLE);
	print_next_tetris(num_tetris, num, play_screen_width);
	cct_gotoxy(0, play_screen_height + 2);
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
	print_end_tips();
}

/***************************************************************************
   函数名称：num_tetris_D
   功    能：D模式功能实现
   输入参数：int num_play_screen[][MAX_PLAY_SCREEN_WIDTH + 2]：游戏界面矩阵
			 bool num_tetris[][5]：数字俄罗斯方块矩阵
			 int rand_num_tetris[]：随机数组
             int play_screen_width：游戏界面的宽度
			 int play_screen_height：游戏界面的高度
   返 回 值：无
   说    明：无
***************************************************************************/
void num_tetris_D(int num_play_screen[][MAX_PLAY_SCREEN_WIDTH + 2], bool num_tetris[][5], int rand_num_tetris[], int play_screen_width, int play_screen_height)
{
	int temp_X = 0, temp_Y = 0, tetris_center_X = play_screen_width / 6 / 2, tetris_center_Y = play_screen_height / 3 + 1;
	int score = 0, color = 0;
	int count_sleep = 0;
	bool temp_num_tetris[5][5] = { 0 };
	int sleep_time = 1000;
	bool move = 0;

	cct_setcursor(CURSOR_INVISIBLE);
	init_num_play_screen(num_play_screen, play_screen_width / 6, play_screen_height / 3);
	init_num_tetris(num_tetris, rand_num_tetris[0]);
	color = set_star_color(rand_num_tetris[0]);
	update_next_tetris(play_screen_width, temp_num_tetris, rand_num_tetris, 0);
	print_num_tetris(num_tetris, tetris_center_X, play_screen_height / 3 - tetris_center_Y + 1, color);

	while (1) {
		move = 0;
		count_sleep = 0;
		temp_X = 0;
		temp_Y = 0;
		while (sleep_time != 50) {
			if (_kbhit()) {
				temp_X = tetris_center_X;
				temp_Y = tetris_center_Y;
				for (int j = 0; j < 5; j++) {
					for (int k = 0; k < 5; k++) {
						temp_num_tetris[j][k] = num_tetris[j][k];
					}
				}
				move = digit_tetris_move(num_play_screen, num_tetris, &tetris_center_X, &tetris_center_Y, &sleep_time);
				if (move) {
					image_tetris_move(num_play_screen, rand_num_tetris[0], temp_num_tetris, temp_X, temp_Y, num_tetris, tetris_center_X, tetris_center_Y, play_screen_width / 6, play_screen_height / 3);
				}
			}
			Sleep(50);
			count_sleep++;
			if (sleep_time <= count_sleep * 50)
				break;
		}

		temp_X = tetris_center_X, temp_Y = tetris_center_Y;
		temp_Y--;
		if (!judge_move_or_not(num_play_screen, num_tetris, temp_X, temp_Y)) {
			image_tetris_move(num_play_screen, rand_num_tetris[0], num_tetris, tetris_center_X, tetris_center_Y, num_tetris, tetris_center_X, tetris_center_Y - 1, play_screen_width / 6, play_screen_height / 3);
			tetris_center_Y--;
		}
		else {
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					if (num_tetris[i][j]) {
						num_play_screen[tetris_center_Y + 2 - i][tetris_center_X - 2 + j] = rand_num_tetris[0];
					}
				}
			}
			break;

		}
	}
	cct_setcursor(CURSOR_VISIBLE_NORMAL);

	cct_gotoxy(0, play_screen_height);
	print_end_tips();
}

/***************************************************************************
   函数名称：num_tetris_E
   功    能：E模式功能实现
   输入参数：int num_play_screen[][MAX_PLAY_SCREEN_WIDTH + 2]：游戏界面矩阵
			 bool num_tetris[][5]：数字俄罗斯方块矩阵
			 int rand_num_tetris[]：随机数组
			 int play_screen_width：游戏界面的宽度
			 int play_screen_height：游戏界面的高度
   返 回 值：无
   说    明：无
***************************************************************************/
void num_tetris_E(int num_play_screen[][MAX_PLAY_SCREEN_WIDTH+2], bool num_tetris[][5], int rand_num_tetris[], int play_screen_width, int play_screen_height)
{
	int temp_X = 0, temp_Y = 0, tetris_center_X = play_screen_width / 6 / 2, tetris_center_Y = play_screen_height / 3 + 1 - 3;
	int score = 0, temp_sleep_time = 0, level = 0, color = 0;
	int count_sleep = 0, no_tetris = 0, count_eliminate_lines = 0;
	bool temp_num_tetris[5][5] = { 0 };
	int sleep_time[] = { 1000,900,800,700,600,500,400,300 };
	int get_score[] = { 1,3,6,10,15 };
	bool move = 0, eliminate[MAX_PLAY_SCREEN_HEIGHT + 1] = { 0 };

	cct_setcursor(CURSOR_INVISIBLE);
	init_num_play_screen(num_play_screen, play_screen_width / 6, play_screen_height / 3);
	while (1) {
		temp_sleep_time = sleep_time[level];
		temp_X = 0, temp_Y = 0, tetris_center_X = play_screen_width / 6 / 2, tetris_center_Y = play_screen_height / 3 + 1;
		count_eliminate_lines = 0;

		init_num_tetris(num_tetris, rand_num_tetris[no_tetris]);
		color = set_star_color(rand_num_tetris[no_tetris]);

		update_next_tetris(play_screen_width, temp_num_tetris, rand_num_tetris, no_tetris);

		if (!judge_move_or_not(num_play_screen, num_tetris, tetris_center_X, tetris_center_Y)) {
			print_num_tetris(num_tetris, tetris_center_X, play_screen_height / 3 - tetris_center_Y + 1, color);

			while (1) {
				move = 0;
				count_sleep = 0;
				temp_X = 0;
				temp_Y = 0;
				while (temp_sleep_time != 50) {
					if (_kbhit()) {
						temp_X = tetris_center_X;
						temp_Y = tetris_center_Y;
						for (int j = 0; j < 5; j++) {
							for (int k = 0; k < 5; k++) {
								temp_num_tetris[j][k] = num_tetris[j][k];
							}
						}
						move = digit_tetris_move(num_play_screen, num_tetris, &tetris_center_X, &tetris_center_Y, &temp_sleep_time);
						if (move) {
							image_tetris_move(num_play_screen, rand_num_tetris[no_tetris], temp_num_tetris, temp_X, temp_Y, num_tetris, tetris_center_X, tetris_center_Y, play_screen_width / 6, play_screen_height / 3);
						}
					}
					Sleep(50);
					count_sleep++;
					if (temp_sleep_time <= count_sleep * 50)
						break;
				}

				temp_X = tetris_center_X, temp_Y = tetris_center_Y;
				temp_Y--;
				if (!judge_move_or_not(num_play_screen, num_tetris, temp_X, temp_Y)) {
					image_tetris_move(num_play_screen, rand_num_tetris[no_tetris], num_tetris, tetris_center_X, tetris_center_Y, num_tetris, tetris_center_X, tetris_center_Y - 1, play_screen_width / 6, play_screen_height / 3);
					tetris_center_Y--;
				}
				else {
					for (int i = 0; i < 5; i++) {
						for (int j = 0; j < 5; j++) {
							if (num_tetris[i][j]) {
								num_play_screen[tetris_center_Y + 2 - i][tetris_center_X - 2 + j] = rand_num_tetris[no_tetris];
							}
						}
					}
					break;
				}
			}

			no_tetris++;
			for (int i = 1; i <= play_screen_height / 3; i++) {
				if (line_eliminate_or_not(i, num_play_screen, play_screen_width / 6)) {
					eliminate[i] = 1;
					count_eliminate_lines++;
				}
			}
			if (count_eliminate_lines) {
				eliminate_lines(eliminate, num_play_screen, play_screen_width / 6, play_screen_height / 3);
				score += get_score[count_eliminate_lines - 1];
				update_score(score, play_screen_width);
				if (score < 120)
					level = score / 15;
				else
					level = 7;
				update_level(level, play_screen_width);
			}
			if (judge_end_or_not(num_play_screen, play_screen_width / 6, play_screen_height / 3)) {
				break;
			}
		}
		else {
			break;
		}
		
	}
	cct_gotoxy(0, play_screen_height);
	cout << "你死啦！哈哈！下次加油！" << endl;

	cct_setcursor(CURSOR_VISIBLE_NORMAL);
	print_end_tips();
}