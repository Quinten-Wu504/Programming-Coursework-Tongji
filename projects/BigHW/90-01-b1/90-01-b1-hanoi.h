/* 2154146 吴金轩 计科 */
#pragma once

/* ------------------------------------------------------------------------------------------------------

	 本文件功能：
	1、为了保证 hanoi_main.cpp/hanoi_menu.cpp/hanoi_multiple_solutions.cpp 能相互访问函数的函数声明
	2、一个以上的cpp中用到的宏定义（#define）或全局只读（const）变量，个数不限
	3、可以参考 cmd_console_tools.h 的写法（认真阅读并体会）
   ------------------------------------------------------------------------------------------------------ */
void get_parameter(int* n, char* src, char* dst, char* temp, char mode);
void init_stack(int n, char src);
void print_stack_horizontal(int n, char src, char dst, char mode);
void print_stack_vertical(int n, char column, const int X, const int Y);
void modify_stack_vertical(int n, char src, char dst, const int X, const int Y);
void step_by_step_operation_of_hanoi(char src, char dst);
void print_first_line(int n, char src, char dst, char mode);
void print_pause();
void print_column();
void print_plate(int n, char src);
void modify_plate(char src, char dst, const int X, const int Y);
void hanoi_process(int n, char src, char tmp, char dst, char mode);
void hanoi(int n, char src, char tmp, char dst, char mode);
void hanoi_1_2_3(int n, char src, char tmp, char dst, char mode);
void hanoi_4(int n, char src, char tmp, char dst, char mode);
void hanoi_7(int n, char src, char tmp, char dst, char mode);
void hanoi_8(int n, char src, char tmp, char dst, char mode);
void hanoi_9(int n, char src, char tmp, char dst, char mode);

