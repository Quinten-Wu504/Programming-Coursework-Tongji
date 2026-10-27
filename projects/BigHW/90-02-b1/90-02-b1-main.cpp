/* 2154146 吴金轩 计科 */
#include <iostream>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include "../include/cmd_console_tools.h"
#include "../include/common_frame_constuction.h"
#include "../include/common_star_print.h"
#include "../include/common_math_tools.h"
#include "90-02-b1.h"
using namespace std;

int main()
{
	char mode = '\0';
	int play_screen_width = 0, play_screen_height = 0;
	bool num_tetris[5][5] = { 0 };
	int rand_num_tetris[100] = { 0 };
	int num_play_screen[MAX_PLAY_SCREEN_HEIGHT + 4][MAX_PLAY_SCREEN_WIDTH + 2] = { 0 };
	int info_console_width = 30;
	const char* p_char[] = { "打印初始姿态的1-9数字俄罗斯方块","打印四种旋转姿态下的1-9数字俄罗斯方块",
		"游戏窗口初始化","伪图形界面单次下落","伪图形界面游戏完整版",0 };

	while (1) {
		cct_cls();
		cct_gotoxy(0, 0);
		mode = '\0';
		play_screen_width = 0, play_screen_height = 0;

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				num_tetris[i][j] = 0;
			}
		}
		
		for (int i = 0; i < 100; i++) {
			rand_num_tetris[i] = 0;
		}
		
		for (int i = 0; i < MAX_PLAY_SCREEN_HEIGHT + 4; i++) {
			for (int j = 0; j < MAX_PLAY_SCREEN_WIDTH + 2; j++) {
				num_play_screen[i][j] = 0;
			}
		}
		
		mode = menu(p_char, 'A', 'Q');

		if (mode == 'Q') {
			cct_gotoxy(0, 24);
			break;
		}
		else if (mode >= 'A' && mode <= 'E') {
			if (mode == 'A') {
				//打印初始姿态的1-9数字俄罗斯方块
				num_tetris_A(num_tetris);
			}
			else if (mode == 'B') {
				//打印四种旋转姿态的1-9数字俄罗斯方块
				num_tetris_B(num_tetris);
			}
			else if (mode >= 'C' && mode <= 'E') {
				rand_num_tetris[0] = get_next_num(true, (unsigned int)time(0));
				for (int i = 1; i < 100; i++)
					rand_num_tetris[i] = get_next_num();
				set_console_size(&play_screen_width, &play_screen_height, info_console_width);
				print_game_info(play_screen_width);
				if (mode == 'C') {
					//打印游戏窗口
					num_tetris_C(play_screen_width, play_screen_height, num_tetris, rand_num_tetris[1]);
				}
				else if (mode == 'D') {
					//数字俄罗斯方块单次下落
					num_tetris_D(num_play_screen, num_tetris, rand_num_tetris, play_screen_width, play_screen_height);
				}
				else if (mode == 'E') {
					//数字俄罗斯方块游戏完整版
					num_tetris_E(num_play_screen, num_tetris, rand_num_tetris, play_screen_width, play_screen_height);
				}
			}
		}
	}
	return 0;
}
