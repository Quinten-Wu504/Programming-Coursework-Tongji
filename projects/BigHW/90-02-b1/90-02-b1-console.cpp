/* 2154146 吴金轩 计科 */
#include <iostream>
#include "../include/common_star_print.h"
#include "../include/common_frame_constuction.h"
#include "../include/common_math_tools.h"
#include "90-02-b1.h"
using namespace std;


/***************************************************************************
   函数名称：print_end_tips
   功    能：打印结束提示
   输入参数：无
   返 回 值：无
   说    明：无
***************************************************************************/
void print_end_tips() 
{
	char input_char[100] = { 0 };
	while (input_char[0] != 'E' || input_char[1] != 'N' || input_char[2] != 'D') {
		cout << "本次功能已结束，输入END进行下一次功能选择...";
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
   函数名称：judge_end_or_not
   功    能：判断游戏是否结束
   输入参数：int num_play_screen[][MAX_PLAY_SCREEN_WIDTH + 2]：游戏界面矩阵
             int play_screen_cols：游戏界面星星列数
			 int play_screen_lines：游戏界面星星行数
   返 回 值：bool exceed：游戏是否结束的标志，结束返回1，不结束返回0
   说    明：无
***************************************************************************/
bool judge_end_or_not(int num_play_screen[][MAX_PLAY_SCREEN_WIDTH + 2], int play_screen_cols, int play_screen_lines)
{
	bool exceed = 0;
	for (int i = 1; i <= play_screen_cols; i++) {
		if (num_play_screen[play_screen_lines + 1][i] >= 0 && num_play_screen[play_screen_lines + 1][i] <= 9) {
			exceed = 1;
			break;
		}
	}
	return exceed;
}

/***************************************************************************
   函数名称：judge_move_or_not
   功    能：判断俄罗斯方块是否可按指定操作移动
   输入参数：int num_play_screen[][MAX_PLAY_SCREEN_WIDTH + 2]：游戏界面矩阵
             bool num_tetris[][5]：数字俄罗斯方块矩阵
			 int tetris_center_X：变化后的数字俄罗斯方块的中心星星的X坐标
			 int tetris_center_Y：变化后的数字俄罗斯方块的中心星星的Y坐标
   返 回 值：bool cant_move：俄罗斯方块是否可按指定操作移动的标志，不可移动返回1，可移动返回0
   说    明：无
***************************************************************************/
bool judge_move_or_not(int num_play_screen[][MAX_PLAY_SCREEN_WIDTH + 2], bool num_tetris[][5], int tetris_center_X, int tetris_center_Y)
{
	bool cant_move = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (num_play_screen[tetris_center_Y + 2 - i][tetris_center_X - 2 + j] != 10 && num_tetris[i][j]) {
				cant_move = 1;
				break;
			}
		}
		if (cant_move)
			break;
	}

	return cant_move;
}

/***************************************************************************
   函数名称：judge_eliminate_or_not
   功    能：判断是否有可消除行
   输入参数：int num_line：需要判断的行
             int num_play_screen[][MAX_PLAY_SCREEN_WIDTH + 2]：游戏界面矩阵
			 int play_screen_cols：游戏界面星星列数
   返 回 值：bool exceed：游戏是否结束的标志，结束返回1，不结束返回0
   说    明：无
***************************************************************************/
bool line_eliminate_or_not(int num_line, int num_play_screen[][MAX_PLAY_SCREEN_WIDTH + 2], int play_screen_cols)
{
	bool eliminate = 1;
	for (int i = 1; i <= play_screen_cols; i++) {
		if (num_play_screen[num_line][i] < 0 || num_play_screen[num_line][i] > 9) {
			eliminate = 0;
			break;
		}
	}
	return eliminate;
}

