/* 2154146 吴金轩 计科 */
#pragma once

//全局常量
const int image_resolution_star_X = 4;
const int image_resolution_star_Y = 3;
const int programme_end_X = 0;
const int programme_end_Y = 24;

//数字解与图像解共用的函数
void image_resolution_print_stars(int num_row, int num_colunm, char star_array[][12], bool mark_dividing_lines);
void image_resolution_print_frame(int num_row, int num_colunm, int* p_appointed_row, int* p_appointed_colunm, char star_array[][12], bool mark_dividing_lines);
void get_colunm_and_row(int* p_num_row, int* p_num_colunm);
void init_star_array(char star_array[][12]);
void init_temp_star_array(char temp_star_array[][12]);
void rand_init_star_array(int num_row, int num_colunm, char star_array[][12]);
void wait_for_enter();
bool scan_appointed_coordinate(int num_row, int num_colunm, int appointed_row, int appointed_colunm, char star_array[][12], char temp_star_array[][12]);
void print_end_tips();
void wait_for_enter_next_level(int num_row, int num_colunm, char star_array[][12]);
void sum_of_normal_scores(int count_star[], int scores[], int number_of_eliminations);
void sum_of_bonus_scores(int num_row, int num_colunm, char star_array[][12], int count_star[], int scores[], int* number_of_eliminations);
bool judge_game_over_or_not(int num_row, int num_colunm, char star_array[][12]);

//数字解相关函数
void digital_resolution_get_appointed_parameter(int num_row, int num_colunm, int* p_appointed_row, int* p_appointed_colunm, char star_array[][12]);
int digital_resolution_print_frame(int num_row, int num_colunm, char star_array[][12], char temp_star_array[][12], int stage);
void digital_resolution_judge_appointed_coordinate(int num_row, int num_colunm, int* p_appointed_row, int* p_appointed_colunm, char star_array[][12], char temp_star_array[][12]);
void digital_resolution_wait_for_enter_each_step();
void digital_resolution_modify_star_array(int num_row, int num_colunm, char star_array[][12], char temp_star_array[][12]);
void digital_resolution_eliminate_or_not(int appointed_row, int appointed_colunm, char* p_mark_eliminate);
void star_array_ABC_common(int num_row, int num_colunm, int* p_appointed_row, int* p_appointed_colunm, char star_array[][12], char temp_star_array[][12], char mode);
void star_array_A(int num_row, int num_colunm, int* p_appointed_row, int* p_appointed_colunm, char star_array[][12], char temp_star_array[][12]);
void star_array_B(int num_row, int num_colunm, int* p_appointed_row, int* p_appointed_colunm, char star_array[][12], char temp_star_array[][12], char* p_mark_eliminate, int count_star[], int scores[]);
void star_array_C(int* p_num_row, int* p_num_colunm, int* p_appointed_row, int* p_appointed_colunm, char star_array[][12], char temp_star_array[][12], int count_star[], int scores[], char* p_mark_eliminate, int* p_num_of_steps);

//图像解相关函数
void image_resolution_moved_by_arrow(int keycode2, int* p_appointed_row, int* p_appointed_colunm, int num_row, int num_colunm, char star_array[][12]);
void image_resolution_temp_print(int* p_appointed_row, int* p_appointed_colunm, int temp_appointed_row, int temp_appointed_colunm, char star_array[][12], bool mark_dividing_lines, int temp_print_mode);
bool image_resolution_get_appointed_parameter(int num_row, int num_colunm, int* p_appointed_row, int* p_appointed_colunm, char star_array[][12], char temp_star_array[][12], bool mark_dividing_lines, bool mark_init_or_not, char mode);
int image_resolution_star_eliminate(int num_row, int num_colunm, char star_array[][12], char temp_star_array[][12], bool mark_dividing_lines);
void image_resolution_star_downward(int num_row, int num_colunm, char star_array[][12], char temp_star_array[][12], bool mark_dividing_lines);
void star_array_D_or_E(int num_row, int num_colunm, int* p_appointed_row, int* p_appointed_colunm, char star_array[][12], char temp_star_array[][12], char mode);
void star_array_F(int num_row, int num_colunm, int* p_appointed_row, int* p_appointed_colunm, char star_array[][12], char temp_star_array[][12], int count_star[], int scores[]);
void star_array_G(int num_row, int num_colunm, int* p_appointed_row, int* p_appointed_colunm, char star_array[][12], char temp_star_array[][12], int count_star[], int scores[]);