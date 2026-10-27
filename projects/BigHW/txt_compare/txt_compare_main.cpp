/* 2154146 吴金轩 计科 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <string>
#include "../include/class_aat.h"
#include "../include/common_string_process.h"
#include "../include/cmd_console_tools.h"
//按需加入需要的头文件 
using namespace std;

enum OPT_ARGS {
	OPT_ARGS_HELP = 0,
	OPT_ARGS_DEBUG,
	OPT_ARGS_FILE1,
	OPT_ARGS_FILE2,
	OPT_ARGS_TRIM,
	OPT_ARGS_LINE_SKIP,
	OPT_ARGS_LINE_OFFSET,
	OPT_ARGS_IGNORE_BLANK,
	OPT_ARGS_CR_CRLF_NOT_EQUAL,
	OPT_ARGS_MAX_DIFFNUM,
	OPT_ARGS_MAX_LINENUM,
	OPT_ARGS_DISPLAY
};

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
static void usage(const char* const argv0)
{
	char procname[256];

	/* 从"xx\\xx\\txt_compare.exe形式的argv[0]中截取txt_compare出来" */
	intercept_file_path(procname, argv0);

	ostringstream msg;
	const int wkey = 7 + strlen(procname) + 1;
	const int wopt = 7 + strlen(procname) + 4;
	cout << endl;

	msg << procname << " [Ver1.0.1]" << endl;
	msg << endl;

	msg << "Usage: " << procname << " --file1 xxx --file2 xxx [ --trim none/left/rigth/all | --lineskip 0..100 | --lineoffset -100..100 | --ignore_blank | --max_diff 0..100 | --display none/normal/detailed ]" << endl;

	msg << setw(wkey) << ' ' << "必选项：" << endl;
	msg << setw(wopt) << ' ' << "--file1 name1              : 指定要比较的第1个文件名（必选）" << endl;
	msg << setw(wopt) << ' ' << "--file2 name2              : 指定要比较的第2个文件名（必选）" << endl;
	msg << endl;

	msg << setw(wkey) << ' ' << "可选项：" << endl;
	msg << setw(wopt) << ' ' << "--trim none/left/right/all     : 指定每行的空格/tab的忽略方式（无此项则默认为none）" << endl;
	msg << setw(wopt) << ' ' << "\tnone   : 每行均严格匹配" << endl;
	msg << setw(wopt) << ' ' << "\tleft   : 每行均忽略头部空格" << endl;
	msg << setw(wopt) << ' ' << "\tright  : 每行均忽略尾部空格" << endl;
	msg << setw(wopt) << ' ' << "\tall    : 每行均忽略头尾空格" << endl;
	msg << setw(wopt) << ' ' << "--lineskip s                   : 指定文件的前s行不比较（无此项则s为0）" << endl;
	msg << setw(wopt) << ' ' << "\t取值[0..100]，表示同时跳过两个文件的前s行" << endl;
	msg << setw(wopt) << ' ' << "--lineoffset n                 : 指定文件错位的行数（无此项则n为0）" << endl;
	msg << setw(wopt) << ' ' << "\t取值[-100..100]，负数表示忽略file1的前n行，正数表示忽略file2的前n行" << endl;
	msg << setw(wopt) << ' ' << "--ignore_blank                 : 忽略文件中--trim后的所有空行(无此项则不忽略)" << endl;
	msg << setw(wopt) << ' ' << "--CR_CRLF_not_equal            : 不忽略Windows/Linux文件的换行符差异(无此项则忽略差异)" << endl;
	msg << setw(wopt) << ' ' << "--max_diff m                   : 指定文件错位的行数（无此项则m为0）" << endl;
	msg << setw(wopt) << ' ' << "\t取值[0..100]，表示满m个不同行则结束运行，不再进行后续的比较" << endl;
	msg << setw(wopt) << ' ' << "--max_line x                   : 指定文件比较的最大行数（无此项则x为0）" << endl;
	msg << setw(wopt) << ' ' << "\t取值[0..10000]，表示比较x行后则结束运行，不再进行后续的比较" << endl;
	msg << setw(wopt) << ' ' << "--display none/normal/detailed : 指定显示的信息（无此项则默认为none）" << endl;
	msg << setw(wopt) << ' ' << "\tnone     : 仅一行匹配与否的提示" << endl;
	msg << setw(wopt) << ' ' << "\tnormal   : 每个差异行给出差异信息" << endl;
	msg << setw(wopt) << ' ' << "\tdetailed : 每个差异行给出更详细的差异信息" << endl;
	msg << endl;

	msg << "e.g.   " << procname << " --file1 my.txt --file2 std.txt" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，全部匹配，仅一行输出" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --trim all" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，每行均去除头尾空格，仅一行输出" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --lineoffset -2" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，忽略my.txt的前2行(即my.txt的第3行与std.txt的第1行进行比较，每行严格匹配)，仅一行输出" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --trim left --lineoffset 3" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，忽略std.txt的前3行(即my.txt的第1行与std.txt的第4行进行比较)，每行去除头部空格，仅一行输出" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --ignore_blank" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，忽略文件中的所有空行，仅一行输出" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --lineskip 1" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，第一行不比较" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --ignore_blank --trim right" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，忽略文件中去除头尾空格后的所有空行，仅一行输出" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --max_diff 3" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，全部匹配，有3行不匹配后结束运行，仅一行输出" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --max_line 7" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，全部匹配，仅比较前7行，仅一行输出" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --CR_CRLF_not_queal" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，全部匹配，不忽略Windows/Linux的文件差异，仅一行输出" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --display normal" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，全部匹配，不匹配的行显示信息" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --display detailed" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，全部匹配，不匹配的行显示详细信息" << endl;
	msg << endl;

	/* 一次全部显示出来 */
	cout << msg.str() << endl;
}

int dec_num_to_string(int dec_num, string* p_num_string)
{
	int count = 0;

	*p_num_string = "";
	if (dec_num == 0) {
		(*p_num_string).insert(count, "0");
		count = 1;
	}
	else {
		bool mark_print = 0;

		for (int i = 8; i >= 0; i--) {
			int base = 1;
			for (int j = 0; j < i; j++)
				base *= 10;

			if (!mark_print && dec_num / base)
				mark_print = 1;

			if (mark_print) {
				(*p_num_string).insert(count, 1, dec_num / base + '0');
				count++;
			}
			dec_num %= base;
		}
	}

	return count;
}

string file_getline(ifstream& file, bool CR_CRLF_NOT_EQUAL)
{
	char temp_char = 0;
	string line_str = "";

	file.read(&temp_char, 1);
	if (CR_CRLF_NOT_EQUAL)
	{
		while (!file.fail())
		{
			line_str += temp_char;

			file.read(&temp_char, 1);

			if (temp_char == '\n')
				break;
		}
	}
	else
	{
		while (!file.fail())
		{
			line_str += temp_char;

			file.read(&temp_char, 1);

			if (temp_char == '\n' || temp_char == '\r')
				break;
		}

		if (temp_char == '\r')
			file.read(&temp_char, 1);
	}

	line_str += '\0';

	return line_str;
}

string print_instruction(int line_maxlen, int error_num, bool display_detailed, const char* title, const char* instruction[])
{
	const char** temp_char = instruction;
	int num_modes = 0;
	string temp_str;

	//分隔行===的宽度计算 
	int width = (line_maxlen / 10 + 1) * 10 + 8 + 2; //比---的标尺多2个：line_maxlen向上取10倍整数，8是"文件1 : "
	/* 如果加了hex输出，则最小宽度为80 */
	if (display_detailed && width < 80)
		width = 80;

	for (int i = 0; i < width; i++)
		temp_str = temp_str + '=';
#ifdef __linux__
	temp_str = temp_str + '\n';
#else
	temp_str = temp_str + "\r\n";
#endif

	temp_str = temp_str + "在指定检查条件下共";
	temp_str = temp_str + (char)(error_num + '0');
	temp_str = temp_str + "行有差异.";
#ifdef __linux__
	temp_str = temp_str + '\n';
#else
	temp_str = temp_str + "\r\n";
#endif

	temp_str = temp_str + title;
#ifdef __linux__
	temp_str = temp_str + '\n';
#else
	temp_str = temp_str + "\r\n";
#endif

	for (temp_char = instruction; ; temp_char++) {
		if (*temp_char == 0) {
			break;
		}
		temp_str = temp_str + (char)((temp_char - instruction) + '1');
		temp_str = temp_str + '.';
		temp_str = temp_str + *temp_char;
#ifdef __linux__
		temp_str = temp_str + '\n';
#else
		temp_str = temp_str + "\r\n";
#endif
	}

	for (int i = 0; i < width; i++)
		temp_str = temp_str + '=';
#ifdef __linux__
	temp_str = temp_str + '\n';
#else
	temp_str = temp_str + "\r\n";
#endif

	return temp_str;
}

string print_ruler(int strlen1, int strlen2)
{
	string temp_str;
	temp_str = temp_str + "        ";
	for (int i = 0; i < (max(strlen1, strlen2) + 9) / 10 * 10; i++)
		temp_str = temp_str + "-";
#ifdef __linux__
	temp_str = temp_str + '\n';
#else
	temp_str = temp_str + "\r\n";
#endif

	temp_str = temp_str + "        ";
	for (int i = 0; i < max(strlen1, strlen2) / 10 + 1; i++) {
		temp_str = temp_str + (char)(i + '0');
		temp_str = temp_str + "         ";
	}
#ifdef __linux__
	temp_str = temp_str + '\n';
#else
	temp_str = temp_str + "\r\n";
#endif

	temp_str = temp_str + "        ";
	for (int i = 0; i < (max(strlen1, strlen2) + 9) / 10 * 10; i++)
		temp_str = temp_str + (char)(i % 10 + '0');
#ifdef __linux__
	temp_str = temp_str + '\n';
#else
	temp_str = temp_str + "\r\n";
#endif

	temp_str = temp_str + "        ";
	for (int i = 0; i < (max(strlen1, strlen2) + 9) / 10 * 10; i++)
		temp_str = temp_str + '-';
#ifdef __linux__
	temp_str = temp_str + '\n';
#else
	temp_str = temp_str + "\r\n";
#endif

	return temp_str;
}

void print_error_normal(string str1, string str2, bool eof1, bool eof2)
{
	cout << "文件1 : ";
	if (str1[0] == '\r' || str1[0] == '\n') {
		cct_setcolor(COLOR_HYELLOW, COLOR_RED);
		cout << "<EMPTY>";
		cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	}
	else {
		for (int i = 0; str1[i] != '\0'; i++) {
			if (i + 1 > strlen_str(str2) || str1[i] != str2[i]) {
				/*if (str1[i] == '\r' || str1[i] == '\n') {
					while (str1[i] != '\0')
						i++;
					i--;
				}
				else {*/
					cct_setcolor(COLOR_HYELLOW, COLOR_RED);
					if (str1[i] == '\r' || str1[i] == '\n' || str1[i] == '\a' || str1[i] == '\b' || str1[i] == '\v')
						cout << "X";
					else
						cout << str1[i];
					cct_setcolor(COLOR_BLACK, COLOR_WHITE);
				/*}*/
			}
			else {
				if (str1[i] == '\r' || str1[i] == '\n' || str1[i] == '\a' || str1[i] == '\b' || str1[i] == '\v')
					cout << "X";
				/*else if (str1[i] == '\r' || str1[i] == '\n') {
					while (str1[i] != '\0')
						i++;
					i--;
				}*/
				else
					cout << str1[i];
			}
		}
	}
	if (eof1)
		cout << "<EOF>";
	else
		cout << "<CR>";
	cout << endl;

	cout << "文件2 : ";
	if (str2[0] == '\r' || str2[0] == '\n') {
		cct_setcolor(COLOR_HYELLOW, COLOR_RED);
		cout << "<EMPTY>";
		cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	}
	else {
		for (int i = 0; str2[i] != '\0'; i++) {
			if (i + 1 > strlen_str(str1) || str2[i] != str1[i]) {
				/*if (str2[i] == '\r' || str2[i] == '\n') {
					while (str2[i] != '\0')
						i++;
					i--;
				}
				else {*/
					cct_setcolor(COLOR_HYELLOW, COLOR_RED);
					if (str2[i] == '\r' || str2[i] == '\n' || str2[i] == '\a' || str2[i] == '\b' || str2[i] == '\v')
						cout << "X";
					else
						cout << str2[i];
					cct_setcolor(COLOR_BLACK, COLOR_WHITE);
				/*}*/
			}
			else {
				if (str2[i] == '\r' || str2[i] == '\n' || str2[i] == '\a' || str2[i] == '\b' || str2[i] == '\v')
					cout << "X";
				/*else if (str2[i] == '\r' || str2[i] == '\n') {
					while (str2[i] != '\0')
						i++;
					i--;
				}*/
				else
					cout << str2[i];
			}
		}
	}
	if (eof2)
		cout << "<EOF>";
	else
		cout << "<CR>";
	cout << endl;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int main(int argc, char** argv)
{
	/* 指定去除空格的方式 */
	const string TrimType[] = { "none",	"left",	"right",	"all", "" };
	const string DisplayType[] = { "none",	"normal",	"detailed", "" };

	args_analyse_tools args[] = {
		args_analyse_tools("--help",			ST_EXTARGS_TYPE::boolean, 0, false),
		args_analyse_tools("--debug",			ST_EXTARGS_TYPE::boolean, 0, false),
		args_analyse_tools("--file1",			ST_EXTARGS_TYPE::str, 1, string("")),
		args_analyse_tools("--file2",			ST_EXTARGS_TYPE::str, 1, string("")),
		args_analyse_tools("--trim",			ST_EXTARGS_TYPE::str_with_set_error, 1, 0, TrimType),
		args_analyse_tools("--lineskip",		ST_EXTARGS_TYPE::int_with_default,   1, 0, 0, 100),
		args_analyse_tools("--lineoffset",		ST_EXTARGS_TYPE::int_with_default,   1, 0, -100, 100),
		args_analyse_tools("--ignore_blank",	ST_EXTARGS_TYPE::boolean, 0, false),
		args_analyse_tools("--CR_CRLF_not_equal",ST_EXTARGS_TYPE::boolean, 0, false),
		args_analyse_tools("--max_diff",		ST_EXTARGS_TYPE::int_with_default,   1, 0, 0, 100),
		args_analyse_tools("--max_line",		ST_EXTARGS_TYPE::int_with_default,   1, 0, 0, 10000),
		args_analyse_tools("--display",			ST_EXTARGS_TYPE::str_with_set_error, 1, 0, DisplayType),
		args_analyse_tools()  //最后一个，用于结束
	};
	int cur_argc, ret = 0;

	//最后一个参数1，表示除选项参数外，还有其它参数
	if ((cur_argc = args_analyse_process(argc, argv, args, 0)) < 0) {
		//错误信息在函数中已打印
		args_analyse_print(args);
		usage(argv[0]);
		return -1;
	}

	/* 对help做特殊处理 */
	if (args[OPT_ARGS_HELP].existed()) {
		//只要有 --help，其它参数都忽略，显示帮助即可
		args_analyse_print(args);
		usage(argv[0]);
		return -1; //执行完成直接退出
	}

	if (args[OPT_ARGS_FILE1].existed() + args[OPT_ARGS_FILE2].existed() != 2) {
		usage(argv[0]);
		cout << "必须指定参数[" << args[OPT_ARGS_FILE1].get_name() << "和" << args[OPT_ARGS_FILE2].get_name() << "]" << endl;
		return -1;
	}

	if (args[OPT_ARGS_CR_CRLF_NOT_EQUAL].existed() && (args[OPT_ARGS_TRIM].get_string() == "right" || args[OPT_ARGS_TRIM].get_string() == "all")) {
		usage(argv[0]);
		cout << "参数[" << args[OPT_ARGS_CR_CRLF_NOT_EQUAL].get_name() << "]不能和[" << args[OPT_ARGS_TRIM].get_name() << " right/all]同时存在." << endl;
		return -1;
	}

	if (args[OPT_ARGS_DEBUG].existed())
		args_analyse_print(args);

	/* 进入实际的功能调用，完成相应的功能 */
	ifstream file1, file2;
	string line_str1 = "", line_str2 = "";
	string error_msg, temp_str;
	int line_maxlen = 0, count_error = 0, count_line[2] = { 0,0 }, error_loc = -1;
	int lines = 0, diff_lines = 0;
	bool mark = 1, ending_blank = 1;
	const char* instruction[] = { "空行用<EMPTY>标出", "文件结束用<EOF>标出", "两行相同列位置的差异字符用亮色标出",
								  "每行中的CR/LF/VT/BS/BEL用X标出(方便看清隐含字符)", "每行尾的多余的字符用亮色标出，CR/LF/VT/BS/BEL用亮色X标出(方便看清隐含字符)",
								  "每行最后用<CR>标出(方便看清隐含字符)", "中文因为编码问题，差异位置可能报在后半个汉字上，但整个汉字都亮色标出",
								  "用--display detailed可以得到更详细的信息", 0 };

	// 打开文件
	file1.open(args[OPT_ARGS_FILE1].get_string(), ios::in | ios::binary);
	if (file1.is_open() == 0) {
		cout << "第1个文件[" << args[OPT_ARGS_FILE1].get_string() << "]无法打开." << endl;
		return -1;
	}
	file2.open(args[OPT_ARGS_FILE2].get_string(), ios::in | ios::binary);
	if (file1.is_open() == 0) {
		cout << "第2个文件[" << args[OPT_ARGS_FILE2].get_string() << "]无法打开." << endl;
		file1.close();
		return -1;
	}

	// 跳过两个文件的前 n 行
	if (args[OPT_ARGS_LINE_SKIP].existed()) {
		int i = 0;
		while (!file1.fail() && !file2.fail() && i < args[OPT_ARGS_LINE_SKIP].get_int()) {
			line_str1 = file_getline(file1, args[OPT_ARGS_CR_CRLF_NOT_EQUAL].existed());
			line_str2 = file_getline(file2, args[OPT_ARGS_CR_CRLF_NOT_EQUAL].existed());
			i++;
		}
	}

	// 跳过其中一个文件的前 n 行
	if (args[OPT_ARGS_LINE_OFFSET].existed()) {
		int i = 0;
		if (args[OPT_ARGS_LINE_OFFSET].get_int() > 0) {
			while (!file1.fail() && !file2.fail() && i < args[OPT_ARGS_LINE_OFFSET].get_int()) {
				file_getline(file2, args[OPT_ARGS_CR_CRLF_NOT_EQUAL].existed());
				i++;
			}
		}
		else if (args[OPT_ARGS_LINE_OFFSET].get_int() < 0) {
			while (!file1.fail() && !file2.fail() && i < -1 * args[OPT_ARGS_LINE_OFFSET].get_int()) {
				file_getline(file1, args[OPT_ARGS_CR_CRLF_NOT_EQUAL].existed());
				i++;
			}
		}
	}

	while (!file1.fail() && !file2.fail())
	{
		// 两个文件分别读入一行
		line_str1 = file_getline(file1, args[OPT_ARGS_CR_CRLF_NOT_EQUAL].existed());
		if (args[OPT_ARGS_IGNORE_BLANK].existed())
		{
			while ((line_str1[0] == '\r' || line_str1[0] == '\n') && !file1.fail())
				line_str1 = file_getline(file1, args[OPT_ARGS_CR_CRLF_NOT_EQUAL].existed());
		}
		line_maxlen = max(line_maxlen, strlen_str(line_str1));

		line_str2 = file_getline(file2, args[OPT_ARGS_CR_CRLF_NOT_EQUAL].existed());
		if (args[OPT_ARGS_IGNORE_BLANK].existed())
		{
			while ((line_str2[0] == '\r' || line_str2[0] == '\n') && !file2.fail())
				line_str2 = file_getline(file2, args[OPT_ARGS_CR_CRLF_NOT_EQUAL].existed());
		}
		line_maxlen = max(line_maxlen, strlen_str(line_str2));

		// trim
		if (args[OPT_ARGS_TRIM].get_string() == "right")
		{
			line_str1 = trim_blank(line_str1, 1, 0);
			line_str2 = trim_blank(line_str2, 1, 0);
		}
		else if (args[OPT_ARGS_TRIM].get_string() == "left")
		{
			line_str1 = trim_blank(line_str1, 0, 1);
			line_str2 = trim_blank(line_str2, 0, 1);
		}
		else if (args[OPT_ARGS_TRIM].get_string() == "all")
		{
			line_str1 = trim_blank(line_str1, 1, 1);
			line_str2 = trim_blank(line_str2, 1, 1);
		}

		if (strcmp_str(line_str1, line_str2) != -1)
		{
			count_error++;
			diff_lines++;
			mark = 0;
		}
		lines++;

		if (args[OPT_ARGS_MAX_LINENUM].existed() && lines >= args[OPT_ARGS_MAX_LINENUM].get_int())
			break;

		if (args[OPT_ARGS_MAX_DIFFNUM].existed() && count_error >= args[OPT_ARGS_MAX_DIFFNUM].get_int())
			break;
	}

	if (file1.fail() + file2.fail() == 1)
	{
		if (!args[OPT_ARGS_IGNORE_BLANK].existed())
		{
			mark = 0;
			if (count_error == 0)
			{
				ending_blank = 0;
				count_error++;
				diff_lines++;
			}
		}
		else
		{
			if (!file1.fail())
			{
				while (!file1.fail())
				{
					line_str1 = file_getline(file1, args[OPT_ARGS_CR_CRLF_NOT_EQUAL].existed());
					if (args[OPT_ARGS_IGNORE_BLANK].existed())
					{
						while ((line_str1[0] == '\r' || line_str1[0] == '\n') && !file1.fail())
							line_str1 = file_getline(file1, args[OPT_ARGS_CR_CRLF_NOT_EQUAL].existed());
					}

					// trim
					if (args[OPT_ARGS_TRIM].get_string() == "right")
						line_str1 = trim_blank(line_str1, 1, 0);
					else if (args[OPT_ARGS_TRIM].get_string() == "left")
						line_str1 = trim_blank(line_str1, 0, 1);
					else if (args[OPT_ARGS_TRIM].get_string() == "all")
						line_str1 = trim_blank(line_str1, 1, 1);

					if (line_str1[0] != '\0' && line_str1[0] != '\r' && line_str1[0] != '\n')
						break;
				}

				if (!file1.fail())
				{
					mark = 0;
					if (count_error == 0)
					{
						ending_blank = 0;
						count_error++;
						diff_lines++;
					}
				} 
			}
			else if (!file2.fail())
			{
				while (!file2.fail())
				{
					line_str2 = file_getline(file2, args[OPT_ARGS_CR_CRLF_NOT_EQUAL].existed());
					if (args[OPT_ARGS_IGNORE_BLANK].existed())
					{
						while ((line_str2[0] == '\r' || line_str2[0] == '\n') && !file2.fail())
							line_str2 = file_getline(file2, args[OPT_ARGS_CR_CRLF_NOT_EQUAL].existed());
					}

					// trim
					if (args[OPT_ARGS_TRIM].get_string() == "right")
						line_str2 = trim_blank(line_str2, 1, 0);
					else if (args[OPT_ARGS_TRIM].get_string() == "left")
						line_str2 = trim_blank(line_str2, 0, 1);
					else if (args[OPT_ARGS_TRIM].get_string() == "all")
						line_str2 = trim_blank(line_str2, 1, 1);

					if (line_str2[0] != '\0' && line_str2[0] != '\r' && line_str2[0] != '\n')
						break;
				}

				if (!file2.fail())
				{
					mark = 0;
					if (count_error == 0)
					{
						ending_blank = 0;
						count_error++;
						diff_lines++;
					}
				}
			}
		}
	}
	
	if (!mark) {
		if (!args[OPT_ARGS_DISPLAY].existed() || args[OPT_ARGS_DISPLAY].get_string() == "none")
		{
			cout << "文件不同." << endl;
		}
		else
		{
			lines = 0;
			diff_lines = 0;

			cout << "比较结果输出：" << endl;
			int width = (line_maxlen / 10 + 1) * 10 + 8 + 2;
			  
			if (args[OPT_ARGS_DISPLAY].get_string() == "detailed" && width < 80)
				width = 80;
			for (int i = 0; i < width; i++)
				cout << "=";
			cout << endl;

			file1.clear();
			file2.clear();
			file1.seekg(0, ios::beg);
			file2.seekg(0, ios::beg);

			// LINE_SKIP
			if (args[OPT_ARGS_LINE_SKIP].existed()) {
				int i = 0;
				while (!file1.fail() && !file2.fail() && i < args[OPT_ARGS_LINE_SKIP].get_int()) {
					line_str1 = file_getline(file1, args[OPT_ARGS_CR_CRLF_NOT_EQUAL].existed());
					line_str2 = file_getline(file2, args[OPT_ARGS_CR_CRLF_NOT_EQUAL].existed());
					i++;
					count_line[0]++;
					count_line[1]++;
				}
			}

			// LINE_OFFSET
			if (args[OPT_ARGS_LINE_OFFSET].existed()) {
				int i = 0;
				if (args[OPT_ARGS_LINE_OFFSET].get_int() > 0) {
					while (!file1.fail() && !file2.fail() && i < args[OPT_ARGS_LINE_OFFSET].get_int()) {
						file_getline(file2, args[OPT_ARGS_CR_CRLF_NOT_EQUAL].existed());
						i++;
						count_line[1]++;
					}
				}
				else if (args[OPT_ARGS_LINE_OFFSET].get_int() < 0) {
					while (!file1.fail() && !file2.fail() && i < -args[OPT_ARGS_LINE_OFFSET].get_int()) {
						file_getline(file1, args[OPT_ARGS_CR_CRLF_NOT_EQUAL].existed());
						i++;
						count_line[0]++;
					}
				}
			}

			while (!file1.fail() && !file2.fail()) {
				count_line[0]++;
				count_line[1]++;

				// 从两个文件中读一行
				line_str1 = file_getline(file1, args[OPT_ARGS_CR_CRLF_NOT_EQUAL].existed());
				if (args[OPT_ARGS_IGNORE_BLANK].existed())
				{
					while ((line_str1[0] == '\r' || line_str1[0] == '\n') && !file1.fail())
						line_str1 = file_getline(file1, args[OPT_ARGS_CR_CRLF_NOT_EQUAL].existed());
				}

				line_str2 = file_getline(file2, args[OPT_ARGS_CR_CRLF_NOT_EQUAL].existed());
				if (args[OPT_ARGS_IGNORE_BLANK].existed())
				{
					while ((line_str2[0] == '\r' || line_str2[0] == '\n') && !file2.fail())
						line_str2 = file_getline(file2, args[OPT_ARGS_CR_CRLF_NOT_EQUAL].existed());
				}

				// trim
				if (args[OPT_ARGS_TRIM].get_string() == "right")
				{
					line_str1 = trim_blank(line_str1, 1, 0);
					line_str2 = trim_blank(line_str2, 1, 0);
				}
				else if (args[OPT_ARGS_TRIM].get_string() == "left")
				{
					line_str1 = trim_blank(line_str1, 0, 1);
					line_str2 = trim_blank(line_str2, 0, 1);
				}
				else if (args[OPT_ARGS_TRIM].get_string() == "all")
				{
					line_str1 = trim_blank(line_str1, 1, 1);
					line_str2 = trim_blank(line_str2, 1, 1);
				}

				if ((error_loc = strcmp_str(line_str1, line_str2)) != -1 || file1.fail() + file2.fail() == 1)
				{	
					if (file1.fail() + file2.fail() == 1 && !ending_blank) {
						if (file1.fail())
							cout << "第[" << count_line[0] << " / " << count_line[1] << "]行 - 文件1已结束/文件2仍有内容：" << endl;
						else if (file2.fail())
							cout << "第[" << count_line[0] << " / " << count_line[1] << "]行 - 文件1仍有内容/文件2已结束：" << endl;
					}
					else
					{
						cout << "第[" << count_line[0] << " / " << count_line[1] << "]行 - 第[" << error_loc << "]个字符开始有差异：" << endl;
						cout << print_ruler(strlen_str(line_str1), strlen_str(line_str2));
						print_error_normal(line_str1, line_str2, file1.fail(), file2.fail());

						cout << "文件1(HEX) : " << endl;
						print_hex_line(line_str1, file1.fail());
						cout << "文件2(HEX) : " << endl;
						print_hex_line(line_str2, file2.fail());
						cout << endl;
					}

					diff_lines++;
				}

				lines++;
				if (args[OPT_ARGS_MAX_LINENUM].existed() && lines >= args[OPT_ARGS_MAX_LINENUM].get_int())
					break;

				if (args[OPT_ARGS_MAX_DIFFNUM].existed() && count_error >= args[OPT_ARGS_MAX_DIFFNUM].get_int())
					break;
			}

			cout << print_instruction(line_maxlen, count_error, 1, "阅读提示：", instruction);
		}
	}
	else {
		if (!args[OPT_ARGS_DISPLAY].existed() || args[OPT_ARGS_DISPLAY].get_string() == "none") {
			cout << "文件相同." << endl;
		}
		else {
			cout << "比较结果输出：" << endl;
			int width = (line_maxlen / 10 + 1) * 10 + 8 + 2;
			if (args[OPT_ARGS_DISPLAY].get_string() == "detailed" && width < 80)
				width = 80;
			for (int i = 0; i < width; i++)
				cout << "=";
			cout << endl;
			cout << "在指定检查条件下完全一致." << endl;
			for (int i = 0; i < width; i++)
				cout << "=";
			cout << endl;
		}
	}


	file1.close();
	file2.close();

	return 0;
}
