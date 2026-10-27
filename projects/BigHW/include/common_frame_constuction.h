/* 2154146 吴金轩 计科 */
#pragma once

/* 菜单函数 */
char menu(const char* p_char[], char start_option, char end_option);

/* 参数获取和判断函数 */
void get_input(int* p_input, const char* value_char, int low_limit = 0, int high_limit = 0);

/* 随机数获取函数 */
int get_next_num(const bool new_seed = false, const unsigned int seed = 0);

/* 其他函数 */
void get_enter();
