/* 2154146 吴金轩 计科 */
#pragma once

/* 允许按需加入需要的头文件等 */
#include <cstring>
#include <vector>
#include <fstream>
using namespace std;

/* 定义读配置文件类 */
class cfgfile_read_tools {
protected:
	string        cfgname; //配置文件名 
	ifstream      cfgfile;
	/* 允许按需加入需要的数据成员及成员函数 */

public:
	/* 构造和析构函数 */
	cfgfile_read_tools(const char* _cfgname = "");
	cfgfile_read_tools(const string& _cfgname);
	virtual ~cfgfile_read_tools();

	/* 判断配置文件是否打开成功 */
	bool is_open();

	/* 组读取函数，读出所有的，放在string型的vector中 */
	int get_all_group(vector <string>& ret);

	/* 项读取函数 - 取某个group的所有item，放在string型的vector中 */
	int get_all_item(const char* const group_name, vector <string>& ret, const bool ignore_lower_upper_case = false);	//测试函数中缺省区分大小写
	int get_all_item(const string& group_name, vector <string>& ret, const bool ignore_lower_upper_case = false);

	/* 项读取函数 - 取某个group的所有item，放在string中 */
	int get_one_item(const char* const group_name, const char* const item_name, string& ret, const bool ignore_lower_upper_case = false);
	int get_one_item(const string& group_name, const string& item_name, string& ret, const bool ignore_lower_upper_case = false);

	/* 项读取函数 - 按数据类型读取某个group的某个item，放在对应数据类型的变量中
		数据类型包括：int/double/string/char * /char */
	int item_get_value(const char* const group_name, const char* const item_name, const char* const def_str, char* str, const int str_maxlen, const bool ignore_lower_upper_case = true);
	int item_get_value(const char* const group_name, const char* const item_name, const char* const def_str, string& value, const bool ignore_lower_upper_case = true);
	int item_get_value(const char* const group_name, const char* const item_name, char& ch, const bool ignore_lower_upper_case = true);
	int item_get_value(const char* const group_name, const char* const item_name, const int min_value, const int max_value, const int def_value, int& value, const bool ignore_lower_upper_case = true);
	int item_get_value(const char* const group_name, const char* const item_name, const double min_value, const double max_value, const double def_value, double& value, const bool ignore_lower_upper_case = true);

	/* 允许按需加入需要的友元声明等 */

};

/* 忽略注释 */
void trim_annotation(char* line_str);

/* 获取一行中的有效信息（忽略前后空格及注释） */
void cfg_getline(ifstream& cfgfile, char** p_line_str);

/* 判断该行是否为组名 */
bool check_group(char* line_str);

/* 获取组名 */
string get_groupname(char* line_str);

/* 判断该行是否为项名 */
bool check_item(char* line_str);

/* 判断string是否为范围内的int */
bool check_int(string item_value_str, int& result, const int min_value, const int max_value);

/* 判断string是否为范围内的double */
bool check_double(string item_value_str, double& result, const double min_value, const double max_value);