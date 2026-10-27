/* 2154146 吴金轩 计科 */
#include <iostream>
#include <conio.h>
#include "../include/cmd_console_tools.h"
using namespace std;


/***************************************************************************
   函数名称：menu
   功    能：打印菜单，并向用户索要模式类型
   输入参数：const char* p_char[]：需要打印的菜单内容组成的数组
			 char start_option：第一个选项的字符
			 char end_option：结束程序的字符
   返 回 值：char mode：选择的参数类型
   说    明：无
***************************************************************************/
char menu(const char* p_char[], char start_option, char end_option)
{
	char mode;
	const char** temp_char = p_char;
	int num_modes = 0;
	cout << "---------------------------------" << endl;
	for (temp_char = p_char; ; temp_char++) {
		if (*temp_char == 0) {
			break;
		}
		cout << (char)((temp_char - p_char) + start_option) << "." << *temp_char << endl;
	}
	cout << end_option << ".退出" << endl;
	cout << "---------------------------------" << endl;
	cout << "[请选择]: ";
	num_modes = temp_char - p_char;
	mode = _getche();
	if (mode >= 'a' && mode <= 'z') {
		mode = mode + 'A' - 'a';
	}
	while (mode != end_option && (mode < start_option || mode > start_option + num_modes - 1)) {
		cct_setcursor(CURSOR_INVISIBLE);
		cct_gotoxy(10, num_modes + 3);
		cout << "                    ";
		cct_gotoxy(10, num_modes + 3);
		cct_setcursor(CURSOR_VISIBLE_NORMAL);
		mode = _getche();
	}
	return mode;
}

/***************************************************************************
   函数名称：get_input
   功    能：获取输入值并判断输入范围
   输入参数：int* p_input：需要输入的值的指针
			 const char* value_char：需要输入的值的名称
			 int low_limit：输入值的下限值
			 int high_limit：输入值的上限值
   返 回 值：无
   说    明：无
***************************************************************************/
void get_input(int* p_input, const char* value_char, int low_limit = 0, int high_limit = 0)
{
	cout << "请输入" << value_char;
	if (low_limit != 0 || high_limit != 0) {
		cout << "(" << low_limit << "-" << high_limit << ")";
	}
	cout << "：" << endl;
	cin >> *p_input;

	while (cin.fail() || ((low_limit != 0 || high_limit != 0) && (*p_input < low_limit || *p_input > high_limit))) {
		cin.clear();
		cin.ignore(65535, '\n');
		cout << "请输入" << value_char;
		if (low_limit != 0 || high_limit != 0) {
			cout << "(" << low_limit << "-" << high_limit << ")";
		}
		cout << "：" << endl;
		cin >> *p_input;
	}

	char temp_input[100] = { 0 };
	cin.getline(temp_input, 100);
}

/***************************************************************************
   函数名称：get_next_num
   功    能：随机数表生成
   输入参数：const bool new_seed：是否生成数的标志，默认为false
             const unsigned int seed：种子数，默认为0
   返 回 值：char mode：选择的参数类型
   说    明：无
***************************************************************************/
int get_next_num(const bool new_seed = false, const unsigned int seed = 0)
{
	if (new_seed)
		srand(seed);

	return rand() % 10;
}

/***************************************************************************
   函数名称：get_enter
   功    能：暂停程序，直至读入回车
   输入参数：无
   返 回 值：无
   说    明：无
***************************************************************************/
void get_enter() 
{
	char input_char = 0 ;
	while (input_char!= 10&&input_char!=13) {
		input_char = getchar();
	}
}
