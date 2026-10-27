/* 2154146 吴金轩 计科 */
#pragma once

#define COLOR_0		12	//亮红
#define COLOR_1		1	//蓝
#define COLOR_2		2	//绿
#define COLOR_3		3	//青
#define COLOR_4		4	//红
#define COLOR_5		5	//粉
#define COLOR_6		6	//黄
#define COLOR_7		11	//亮青
#define COLOR_8		13	//亮粉
#define COLOR_9		14	//亮黄

#define MAX_PLAY_SCREEN_WIDTH	21
#define MAX_PLAY_SCREEN_HEIGHT	26

/* 程序关键节点控制函数 */
void print_end_tips();
bool judge_end_or_not(int num_play_screen[][MAX_PLAY_SCREEN_WIDTH + 2], int play_screen_cols, int play_screen_lines);
bool judge_move_or_not(int num_play_screen[][MAX_PLAY_SCREEN_WIDTH + 2], bool num_tetris[][5], int tetris_center_X, int tetris_center_Y);
bool line_eliminate_or_not(int num_line, int num_play_screen[][MAX_PLAY_SCREEN_WIDTH + 2], int play_screen_cols);

/* 初始化函数 */
void init_num_tetris(bool num_tetris[][5], int num = 0);
void init_num_play_screen(int num_play_screen[][MAX_PLAY_SCREEN_WIDTH + 2], int play_screen_cols, int play_screen_lines);

/* 打印伪图形函数 */
int set_star_color(int num);
void print_num_tetris(bool num_tetris[][5], int tetris_center_X = 0, int tetris_center_Y = 0, int color = 0);
void print_play_screen(int screen_width = 0, int screen_height = 0);

/* 游戏页面打印函数 */
void set_console_size(int* p_play_screen_width, int* p_play_screen_height, int info_console_width);
void print_game_info(int play_screen_width);
void print_next_tetris(bool num_tetris[][5], int rand_num_tetris, int play_screen_width);
void update_next_tetris(int play_screen_width, bool temp_num_tetris[][5], int rand_num_tetris[], int no_tetris);
void update_score(int score, int play_screen_width);
void update_level(int level, int play_screen_width);

/* 俄罗斯方块的移动与消除 */
void eliminate_lines(bool eliminate[], int num_play_screen[][MAX_PLAY_SCREEN_WIDTH + 2], int play_screen_cols, int play_screen_lines);
bool digit_tetris_move(int num_play_screen[][MAX_PLAY_SCREEN_WIDTH + 2], bool num_tetris[][5], int* p_tetris_center_X, int* p_tetris_center_Y, int* p_sleep_time);
void image_tetris_move(int num_play_screen[][MAX_PLAY_SCREEN_WIDTH + 2], int num, bool temp_num_tetris[][5], int temp_X, int temp_Y, bool num_tetris[][5], int tetris_center_X, int tetris_center_Y, int play_screen_cols, int play_screen_lines);

/* 模式函数 */
void num_tetris_A(bool num_tetris[][5]);
void num_tetris_B(bool num_tetris[][5]);
void num_tetris_C(int play_screen_width, int play_screen_height, bool num_tetris[][5], int num);
void num_tetris_D(int num_play_screen[][MAX_PLAY_SCREEN_WIDTH + 2], bool num_tetris[][5], int rand_num_tetris[], int play_screen_width, int play_screen_height);
void num_tetris_E(int num_play_screen[][MAX_PLAY_SCREEN_WIDTH + 2], bool num_tetris[][5], int rand_num_tetris[], int play_screen_width, int play_screen_height);