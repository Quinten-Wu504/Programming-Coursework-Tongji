/* 2154146 吴金轩 计科 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include "../include/class_aat.h"
//如有必要，可以加入其它头文件
using namespace std;

#if !ENABLE_LIB_COMMON_TOOLS //不使用lib才有效

/* ---------------------------------------------------------------
	 允许加入其它需要static函数（内部工具用）
   ---------------------------------------------------------------- */

static int strlen_str(const string str)
{
	int count = 0;
	for (int i = 0; str[i] != '\0'; i++)
		count++;
	return count;
}

static bool strcmp_str(const char* s1, const string s2)
{
	bool same_or_not = 1;
	for (int i = 0; s1[i] != '\0' || s2[i] != '\0'; i++) {
		if (s1[i] != s2[i]) {
			same_or_not = 0;
			break;
		}
	}
	return same_or_not;
}

static int intset_count(const int* set)
{
	int count = 0;

	int i;
	for (i = 0; set[i] != INVALID_INT_VALUE_OF_SET; i++)
		count++;

	return count + 1;
}

static int hashtype_count(const string* set)
{
	int count = 0;

	int i;
	for (i = 0; set[i] != ""; i++)
		count++;

	return count + 1;
}

static void intset_copy(int dst[], const int* src)
{
	int i;
	for (i = 0; src[i] != INVALID_INT_VALUE_OF_SET; i++)
		dst[i] = src[i];
	dst[i] = INVALID_INT_VALUE_OF_SET;
}

static void hashtype_copy(string dst[], const string* src)
{
	int i;
	for (i = 0; src[i] != ""; i++)
		dst[i].insert(0, src[i]);
	dst[i].insert(0, "");
}

static int type_to_int(const ST_EXTARGS_TYPE type)
{
	if (type == ST_EXTARGS_TYPE::null)
		return 0;
	else if (type == ST_EXTARGS_TYPE::boolean)
		return 1;
	else if (type == ST_EXTARGS_TYPE::int_with_default)
		return 2;
	else if (type == ST_EXTARGS_TYPE::int_with_error)
		return 3;
	else if (type == ST_EXTARGS_TYPE::int_with_set_default)
		return 4;
	else if (type == ST_EXTARGS_TYPE::int_with_set_error)
		return 5;
	else if (type == ST_EXTARGS_TYPE::str)
		return 6;
	else if (type == ST_EXTARGS_TYPE::str_with_set_default)
		return 7;
	else if (type == ST_EXTARGS_TYPE::str_with_set_error)
		return 8;
	else if (type == ST_EXTARGS_TYPE::ipaddr_with_default)
		return 9;
	else if (type == ST_EXTARGS_TYPE::ipaddr_with_error)
		return 10;
	else
		return 11;
}

static string type_to_typestr(const ST_EXTARGS_TYPE type)
{
	string typestr = "";

	if (type == ST_EXTARGS_TYPE::null)
		typestr = "";
	else if (type == ST_EXTARGS_TYPE::boolean)
		typestr = "Bool";
	else if (type == ST_EXTARGS_TYPE::int_with_default)
		typestr = "IntWithDefault";
	else if (type == ST_EXTARGS_TYPE::int_with_error)
		typestr = "IntWithError";
	else if (type == ST_EXTARGS_TYPE::int_with_set_default)
		typestr = "IntSETWithDefault";
	else if (type == ST_EXTARGS_TYPE::int_with_set_error)
		typestr = "IntSETWithError";
	else if (type == ST_EXTARGS_TYPE::str)
		typestr = "String";
	else if (type == ST_EXTARGS_TYPE::str_with_set_default)
		typestr = "StringSETWithDefault";
	else if (type == ST_EXTARGS_TYPE::str_with_set_error)
		typestr = "StringSETWithError";
	else if (type == ST_EXTARGS_TYPE::ipaddr_with_default)
		typestr = "IPAddrWithDefault";
	else if (type == ST_EXTARGS_TYPE::ipaddr_with_error)
		typestr = "IPAddrWithError";

	return typestr;
}

static int dec_num_to_string(int dec_num, string* p_num_string)
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

static string value_to_valstr(bool bool_default)
{
	if (bool_default == true)
		return "true";
	else
		return "false";
}

static string value_to_valstr(int int_default)
{
	string str;
	dec_num_to_string(int_default, &str);
	return str;
}

static string value_to_valstr(string extargs_ipaddr_default)
{
	if (extargs_ipaddr_default != "")
		return extargs_ipaddr_default;
	else
		return "/";
}


static string range_to_str(int extargs_int_min, int  extargs_int_max)
{
	string str = "";
	string temp = "";
	int len = 0;

	str.insert(0, 1, '[');
	len += 1;
	
	dec_num_to_string(extargs_int_min, &temp);
	str.insert(len, temp);	
	len += strlen_str(temp);
	
	str.insert(len, "..");
	len += 2;

	dec_num_to_string(extargs_int_max, &temp);
	str.insert(len, temp);
	len += strlen_str(temp);

	str.insert(len, "]\0");

	return str;
}

static string range_to_str(int *extargs_int_set)
{
	string str = "";
	string temp = "";
	int len = 0;

	for (int i = 0; extargs_int_set[i] != INVALID_INT_VALUE_OF_SET; i++) {
		dec_num_to_string(extargs_int_set[i], &temp);
		str.insert(len, temp);
		len += strlen_str(temp);
		if (extargs_int_set[i + 1] != INVALID_INT_VALUE_OF_SET) {
			str.insert(len, 1, '/');
			len += 1;
		}
	}
	str[len] = '\0';

	return str;
}

static string range_to_str(string* extargs_string_set)
{
	string str = "";
	int len = 0;

	for (int i = 0; extargs_string_set[i] != ""; i++) {
		str.insert(len, extargs_string_set[i]);
		len += strlen_str(extargs_string_set[i]);
		if (extargs_string_set[i + 1] != "") {
			str.insert(len, 1, '/');
			len += 1;
		}
	}
	str[len] = '\0';

	return str;
}

bool check_IP(const string char_IP, unsigned int *p_IP_u_int32)
{
	bool mark_IP = 1;
	int dot_location[3] = { 0 }, count_dot = 0;

	for (int i = 0; char_IP[i] != '\0'; i++) {
		if (char_IP[i] == '.' || (char_IP[i] >= '0' && char_IP[i] <= '9')) {
			mark_IP = 1;
			if (char_IP[i] == '.') {
				if (count_dot < 3) {
					dot_location[count_dot] = i;
					count_dot++;
				}
				else {
					mark_IP = 0;
					break;
				}
			}
		}
		else {
			mark_IP = 0;
			break;
		}
	}

	if (mark_IP) {
		if (dot_location[2] != 0 && dot_location[0] != 0 && char_IP[dot_location[2] + 1] != '\0') {
			for (int i = 1; i < 3; i++) {
				if (dot_location[i] - dot_location[i - 1] == 1 || dot_location[i] - dot_location[i - 1] > 4) {
					mark_IP = 0;
					break;
				}
			}

			int count_secdot_to_end = 0;
			for (int i = 0; char_IP[dot_location[2] + 1 + i] != '\0'; i++)
				count_secdot_to_end++;
			if (count_secdot_to_end > 3)
				mark_IP = 0;


			if (mark_IP) {
				char sub_IP[4][4] = { 0 };
				int num_sub_IP[4] = { 0 };
				int i = 0;

				for (i = 0; i < dot_location[0]; i++) {
					sub_IP[0][i] = char_IP[0 + i];
				}
				sub_IP[0][i] = '\0';

				for (i = 0; i < dot_location[1] - dot_location[0] - 1; i++) {
					sub_IP[1][i] = char_IP[dot_location[0] + 1 + i];
				}
				sub_IP[1][i] = '\0';

				for (i = 0; i < dot_location[2] - dot_location[1] - 1; i++) {
					sub_IP[2][i] = char_IP[dot_location[1] + 1 + i];
				}
				sub_IP[2][i] = '\0';

				for (i = 0; char_IP[dot_location[2] + 1 + i] != '\0'; i++) {
					sub_IP[3][i] = char_IP[dot_location[2] + 1 + i];
				}
				sub_IP[3][i] = '\0';

				for (i = 0; i < 4; i++) {
					num_sub_IP[i] = atoi(sub_IP[i]);
					if (num_sub_IP[i] < 0 || num_sub_IP[i] > 255) {
						mark_IP = 0;
						break;
					}
				}

				if (mark_IP) {
					*p_IP_u_int32 = 0;
					for (i = 0; i < 4; i++) {
						*p_IP_u_int32 |= ((unsigned int)num_sub_IP[i] << (8 * (4 - i - 1)));
					}
				}
			}
		}
		else
			mark_IP = 0;
	}
	
	return mark_IP;
}

   /***************************************************************************
	 函数名称：
	 功    能：
	 输入参数：
	 返 回 值：
	 说    明：null
	***************************************************************************/
args_analyse_tools::args_analyse_tools()
{
	args_name = "";
	extargs_type = ST_EXTARGS_TYPE::null;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：boolean：仅需要返回0/1，表示是否存在，例如：--help
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const bool def)
{
	if (type == ST_EXTARGS_TYPE::boolean) {
		args_name = name;
		extargs_type = type;
		extargs_num = ext_num;

		extargs_bool_default = def;

		args_existed = 0;
		extargs_bool_value = extargs_bool_default;
	}
	else {
		cout << "args_analyse构造函数类型错1(type = " << type_to_int(type) << ")" << endl;
	}
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：int_with_default：附加参数为整型，介于 min..max之间，有缺省值，若置超过上下限，则置缺省值
			int_with_error：附加参数为整型，介于 min..max之间，有缺省值，若置超过上下限，则返回错误
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const int def, const int _min, const int _max)
{
	if (type == ST_EXTARGS_TYPE::int_with_default || type == ST_EXTARGS_TYPE::int_with_error) {
		args_name = name;
		extargs_type = type;
		extargs_num = ext_num;

		extargs_int_default = def;
		extargs_int_min = _min;
		extargs_int_max = _max;

		args_existed = 0;
		extargs_int_value = extargs_int_default;
	}
	else {
		cout << "args_analyse构造函数类型错2(type = " << type_to_int(type) << ")" << endl;
	}
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：int_with_set_default：附加参数为整型，只能属于一个有若干元素的集合[11/22/33]，有缺省值，若值不在集合中，则置缺省值
			int_with_set_error：附加参数为整型，只能属于一个有若干元素的集合[11/22/33]，有缺省值，若值不在集合中，则返回错误
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const enum ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const int* const set)
{
	if (type == ST_EXTARGS_TYPE::int_with_set_default || type == ST_EXTARGS_TYPE::int_with_set_error) {
		args_name = name;
		extargs_type = type;
		extargs_num = ext_num;

		int num_of_elem = intset_count(set);
		if (type == ST_EXTARGS_TYPE::int_with_set_default) {
			if (def_of_set_pos <= num_of_elem && def_of_set_pos >= 0)
				extargs_int_default = set[def_of_set_pos];
			else
				extargs_int_default = set[0];
		}

		extargs_int_set = new(nothrow) int[num_of_elem];
		if (extargs_int_set == NULL) {
			cout << "内存空间不足！" << endl;
			exit(-1);
		}
		intset_copy(extargs_int_set, set);

		args_existed = 0;
		extargs_int_value = extargs_int_default;
	}
	else {
		cout << "args_analyse构造函数类型错3(type = " << type_to_int(type) << ")" << endl;
	}
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：str：附加参数为字符串
			ipaddr_with_default：附加参数为IP地址，有缺省值，返回一个u_int32
			ipaddr_with_error：附加参数为IP地址，无缺省值，返回错误
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const string def)
{
	if (type == ST_EXTARGS_TYPE::str || type == ST_EXTARGS_TYPE::ipaddr_with_default || type == ST_EXTARGS_TYPE::ipaddr_with_error) {
		args_name = name;
		extargs_type = type;
		extargs_num = ext_num;

		if (type == ST_EXTARGS_TYPE::str)
			extargs_string_default = def;
		else if (type == ST_EXTARGS_TYPE::ipaddr_with_default) {
			check_IP(def, &extargs_ipaddr_default);
			int num_sub_IP[4] = { 0 };
			unsigned int operator_int = 0xff;
			string str_IP = "", temp_str = "";
			int count_char = 0, sub_str_len = 0;

			for (int i = 0; i < 4; i++) {
				num_sub_IP[i] = (extargs_ipaddr_default & operator_int << (8 * (4 - 1 - i))) >> (8 * (4 - 1 - i));
				sub_str_len = dec_num_to_string(num_sub_IP[i], &temp_str);
				str_IP.insert(count_char, temp_str);
				count_char += sub_str_len;

				if (i != 3) {
					str_IP.insert(count_char, ".", 1);
					count_char++;
				}
			}

			extargs_string_default = str_IP;
		}

		args_existed = 0;
		if (type == ST_EXTARGS_TYPE::str)
			extargs_string_value = def;
		else if (type == ST_EXTARGS_TYPE::ipaddr_with_default)
			extargs_ipaddr_value = extargs_ipaddr_default;
		else if (type == ST_EXTARGS_TYPE::ipaddr_with_error)
			extargs_ipaddr_value = 0;
	}
	else {
		cout << "args_analyse构造函数类型错4(type = " << type_to_int(type) << ")" << endl;
	}
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：str_with_set_default、str_with_set_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const string* const set)
{
	if (type == ST_EXTARGS_TYPE::str_with_set_default || type == ST_EXTARGS_TYPE::str_with_set_error) {
		args_name = name;
		extargs_type = type;
		extargs_num = ext_num;

		int num_of_elem = hashtype_count(set);
		if (type == ST_EXTARGS_TYPE::str_with_set_default) {
			if (def_of_set_pos <= num_of_elem && def_of_set_pos >= 0)
				extargs_string_default = set[def_of_set_pos];
			else
				extargs_string_default = set[0];
		}

		extargs_string_set = new(nothrow) string[num_of_elem];
		if (extargs_int_set == NULL) {
			cout << "内存空间不足！" << endl;
			exit(-1);
		}
		hashtype_copy(extargs_string_set, set);

		args_existed = 0;
		extargs_string_value = extargs_string_default;
	}
	else {
		cout << "args_analyse构造函数类型错5(type = " << type_to_int(type) << ")" << endl;
	}
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
args_analyse_tools::~args_analyse_tools()
{
	if (extargs_type == ST_EXTARGS_TYPE::int_with_set_default || extargs_type == ST_EXTARGS_TYPE::int_with_set_error)
		delete[]extargs_int_set;
	else if (extargs_type == ST_EXTARGS_TYPE::str_with_set_default || extargs_type == ST_EXTARGS_TYPE::str_with_set_error)
		delete[]extargs_string_set;
}

/* ---------------------------------------------------------------
	 允许AAT中自定义成员函数的实现（private）
   ---------------------------------------------------------------- */

   /***************************************************************************
	 函数名称：
	 功    能：
	 输入参数：
	 返 回 值：
	 说    明：已实现，不要动
	***************************************************************************/
const string args_analyse_tools::get_name() const
{
	return this->args_name;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：加!!后，只能是0/1
			已实现，不要动
 ***************************************************************************/
const int args_analyse_tools::existed() const
{
	return !!this->args_existed;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const int args_analyse_tools::get_int() const
{
	return this->extargs_int_value;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const string args_analyse_tools::get_string() const
{
	return this->extargs_string_value;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const unsigned int args_analyse_tools::get_ipaddr() const
{
	return this->extargs_ipaddr_value;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：将 extargs_ipaddr_value 的值从 0x7f000001 转为 "127.0.0.1"
 ***************************************************************************/
const string args_analyse_tools::get_str_ipaddr() const
{
	int num_sub_IP[4] = { 0 };
	unsigned int operator_int = 0xff;
	string str_IP = "", temp_str = "";
	int count_char = 0, sub_str_len = 0;
	for (int i = 0; i < 4; i++) {
		num_sub_IP[i] = (extargs_ipaddr_value & (operator_int << (8 * (4 - 1 - i)))) >> (8 * (4 - 1 - i));
		
		sub_str_len = dec_num_to_string(num_sub_IP[i], &temp_str);
		for (int i = 0; i < sub_str_len; i++) {
			str_IP.insert(count_char + i, 1, temp_str[i]);
		}
		count_char += sub_str_len;

		if (i != 3) {
			str_IP.insert(count_char, 1, '.');
			count_char++;
		}
		else {
			str_IP.insert(count_char, 1, '\0');
			count_char++;
		}
	}
	return str_IP;
}

static string type_of_data(const ST_EXTARGS_TYPE type)
{
	if (type == ST_EXTARGS_TYPE::boolean)
		return "bool";
	else if (type == ST_EXTARGS_TYPE::int_with_default || type == ST_EXTARGS_TYPE::int_with_error || type == ST_EXTARGS_TYPE::int_with_set_default || type == ST_EXTARGS_TYPE::int_with_set_error)
		return "int";
	else if (type == ST_EXTARGS_TYPE::str || type == ST_EXTARGS_TYPE::str_with_set_default || type == ST_EXTARGS_TYPE::str_with_set_error)
		return "string";
	else if (type == ST_EXTARGS_TYPE::ipaddr_with_default || type == ST_EXTARGS_TYPE::ipaddr_with_error)
		return "IP地址";
	else
		return "";
}

static bool check_int(const char int_char[])
{
	bool check_mark = 1;
	for (int i = 0; int_char[i] != '\0'; i++) {
		if (i == 0) {
			if (int_char[0] != '-' && (int_char[i] < '0' || int_char[i] > '9')) {
				check_mark = 0;
				break;
			}
		}
		else {
			if (int_char[i] < '0' || int_char[i] > '9') {
				check_mark = 0;
				break;
			}
		}
	}
	return check_mark;
}

static int int_default_or_error(string name, ST_EXTARGS_TYPE type, int int_default, int min, int max, const char *temp_char, int* p_mark_result)
{
	int value = 0;
	int temp = atoi(temp_char);
	if (type == ST_EXTARGS_TYPE::int_with_default) {
		if (temp >= min && temp <= max)
			value = temp;
		else
			value = int_default;
	}
	else if (type == ST_EXTARGS_TYPE::int_with_error) {
		if (temp >= min && temp <= max)
			value = temp;
		else {
			*p_mark_result = -1;
			cout << "参数[" << name << "]的附加参数值(" << temp_char << ")非法. (类型:" << type_of_data(type);
			cout << ", 范围" << range_to_str(min, max) << ")" << endl;
		}
	}
	return value;
}

static int int_set_default_or_error(string name, ST_EXTARGS_TYPE type, int int_default, int *set, const char* temp_char, int* p_mark_result)
{
	int value = 0;
	int temp = atoi(temp_char);
	bool check_range = 0;

	for (int i = 0; set[i] != INVALID_INT_VALUE_OF_SET; i++) {
		if (set[i] == temp) {
			check_range = 1;
			break;
		}
	}

	if (type == ST_EXTARGS_TYPE::int_with_set_default) {
		if (check_range)
			value = temp;
		else
			value = int_default;
	}
	else if (type == ST_EXTARGS_TYPE::int_with_set_error) {
		if (check_range)
			value = temp;
		else {
			*p_mark_result = -1;
			cout << "参数[" << name << "]的附加参数值(" << temp_char << ")非法. (类型:" << type_of_data(type);
			cout << ", 可取值[" << range_to_str(set) << "])" << endl;
		}
	}
	return value;
}

static string str_set_default_or_error(string name, ST_EXTARGS_TYPE type, string str_default, string* set, const char* temp_char, int* p_mark_result)
{
	string value = "";
	bool check_range = 0;

	for (int i = 0; set[i] != ""; i++) {
		if (set[i] == temp_char) {
			check_range = 1;
			break;
		}
	}

	if (type == ST_EXTARGS_TYPE::str_with_set_default) {
		if (check_range)
			value = temp_char;
		else
			value = str_default;
	}
	else if (type == ST_EXTARGS_TYPE::str_with_set_error) {
		if (check_range)
			value = temp_char;
		else {
			*p_mark_result = -1;
			cout << "参数[" << name << "]的附加参数值(" << temp_char << ")非法. (类型:" << type_of_data(type);
			cout << ", 可取值[" << range_to_str(set) << "])" << endl;
		}
	}
	return value;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：follow_up_args：是否有后续参数
			0  ：无后续参数
			1  ：有后续参数
  返 回 值：
  说    明：友元函数
***************************************************************************/
int args_analyse_process(const int argc, const char* const* const argv, args_analyse_tools* const args, const int follow_up_args)
{
	int check_result = 0;
	int param_num = 0;
	for (param_num = 0; args[param_num].get_name() != ""; param_num++);

	for (int i = 1; i <= argc - 1; i++) {
		int no_of_param = -1;

		if (argv[i][0] != '-' || argv[i][1] != '-') {
			if (!follow_up_args) {
				cout << "参数[" << argv[i] << "]格式非法(不是--开头的有效内容)." << endl;
				check_result = -1;
			}
			else {
				check_result = i;
			}
			break;
		}
		else {
			for (int j = 0; j < param_num; j++) {
				if (strcmp_str(argv[i], args[j].get_name())) {
					no_of_param = j;
					break;
				}
			}

			if (no_of_param != -1) {
				if (!args[no_of_param].existed()) {
					if (args[no_of_param].extargs_num == 0) {
						if (type_of_data(args[no_of_param].extargs_type) == "bool")
							args[no_of_param].args_existed = 1;
					}
					else {
						if (i != argc - 1) {
							if (argv[i + 1][0] == '-' && argv[i + 1][1] == '-') {
								cout << "参数[" << args[no_of_param].args_name << "]缺少附加参数. (类型:" << type_of_data(args[no_of_param].extargs_type);

								if (args[no_of_param].extargs_type == ST_EXTARGS_TYPE::int_with_default || args[no_of_param].extargs_type == ST_EXTARGS_TYPE::int_with_error)
									cout << ", 范围" << range_to_str(args[no_of_param].extargs_int_min, args[no_of_param].extargs_int_max);
								else if (args[no_of_param].extargs_type == ST_EXTARGS_TYPE::int_with_set_default || args[no_of_param].extargs_type == ST_EXTARGS_TYPE::int_with_set_error)
									cout << ", 范围[" << range_to_str(args[no_of_param].extargs_int_set) << "]";
								else if (args[no_of_param].extargs_type == ST_EXTARGS_TYPE::str_with_set_default || args[no_of_param].extargs_type == ST_EXTARGS_TYPE::str_with_set_error)
									cout << ", 范围[" << range_to_str(args[no_of_param].extargs_string_set) << "]";

								if (args[no_of_param].extargs_type == ST_EXTARGS_TYPE::int_with_default || args[no_of_param].extargs_type == ST_EXTARGS_TYPE::int_with_set_default)
									cout << " 缺省:" << value_to_valstr(args[no_of_param].extargs_int_default);
								else if (args[no_of_param].extargs_type == ST_EXTARGS_TYPE::str || args[no_of_param].extargs_type == ST_EXTARGS_TYPE::str_with_set_default || args[no_of_param].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_default)
									cout << " 缺省:" << value_to_valstr(args[no_of_param].extargs_string_default);

								cout << ")" << endl;

								check_result = -1;
								break;
							}
							else {
								args[no_of_param].args_existed = 1;
								if (type_of_data(args[no_of_param].extargs_type) == "int") {
									if (check_int(argv[i + 1])) {
										if (args[no_of_param].extargs_type == ST_EXTARGS_TYPE::int_with_default || args[no_of_param].extargs_type == ST_EXTARGS_TYPE::int_with_error) {
											args[no_of_param].extargs_int_value = int_default_or_error(args[no_of_param].args_name, args[no_of_param].extargs_type, args[no_of_param].extargs_int_default, args[no_of_param].extargs_int_min, args[no_of_param].extargs_int_max, argv[i + 1], &check_result);
											if (check_result == -1)
												break;
											else
												i++;
										}
										else if (args[no_of_param].extargs_type == ST_EXTARGS_TYPE::int_with_set_default || args[no_of_param].extargs_type == ST_EXTARGS_TYPE::int_with_set_error) {
											args[no_of_param].extargs_int_value = int_set_default_or_error(args[no_of_param].args_name, args[no_of_param].extargs_type, args[no_of_param].extargs_int_default, args[no_of_param].extargs_int_set, argv[i + 1], &check_result);
											if (check_result == -1)
												break;
											else
												i++;
										}
									}
									else {
										cout << "参数[" << args[no_of_param].args_name << "]的附加参数不是整数. (类型:" << type_of_data(args[no_of_param].extargs_type);

										if (args[no_of_param].extargs_type == ST_EXTARGS_TYPE::int_with_default || args[no_of_param].extargs_type == ST_EXTARGS_TYPE::int_with_error)
											cout << ", 可取值" << range_to_str(args[no_of_param].extargs_int_min, args[no_of_param].extargs_int_max);
										else if (args[no_of_param].extargs_type == ST_EXTARGS_TYPE::int_with_set_default || args[no_of_param].extargs_type == ST_EXTARGS_TYPE::int_with_set_error)
											cout << ", 可取值[" << range_to_str(args[no_of_param].extargs_int_set) << "]";
										else if (args[no_of_param].extargs_type == ST_EXTARGS_TYPE::str_with_set_default || args[no_of_param].extargs_type == ST_EXTARGS_TYPE::str_with_set_error)
											cout << ", 可取值[" << range_to_str(args[no_of_param].extargs_string_set) << "]";

										cout << ")" << endl;

										check_result = -1;
										break;
									}
								}
								else if (type_of_data(args[no_of_param].extargs_type) == "string") {
									if (args[no_of_param].extargs_type == ST_EXTARGS_TYPE::str) {
										args[no_of_param].extargs_string_value = argv[i + 1];
										i++;
									}
									if (args[no_of_param].extargs_type == ST_EXTARGS_TYPE::str_with_set_default || args[no_of_param].extargs_type == ST_EXTARGS_TYPE::str_with_set_error) {
										args[no_of_param].extargs_string_value = str_set_default_or_error(args[no_of_param].args_name, args[no_of_param].extargs_type, args[no_of_param].extargs_string_default, args[no_of_param].extargs_string_set, argv[i + 1], &check_result);
										if (check_result == -1)
											break;
										else
											i++;
									}
								}
								else if (type_of_data(args[no_of_param].extargs_type) == "IP地址") {
									if (args[no_of_param].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_default || args[no_of_param].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_error) {
										unsigned int temp = 0;
										check_result = (check_IP(argv[i + 1], &temp) == 0) ? -1 : 0;
										if (check_result == -1) {
											if (args[no_of_param].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_error)
												cout << "参数[" << args[no_of_param].args_name << "]的附加参数值(" << argv[i + 1] << ")非法. (类型:" << type_of_data(args[no_of_param].extargs_type) << ")" << endl;
											else if (args[no_of_param].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_default) {
												i++;
												check_result = 0;
												args[no_of_param].extargs_ipaddr_value = args[no_of_param].extargs_ipaddr_default;
											}
											break;
										}
										else {
											i++;
											args[no_of_param].extargs_ipaddr_value = temp;
										}
									}
								}
							}
						}
						else {
							cout << "参数[" << args[no_of_param].args_name << "]的附加参数不足. (类型:" << type_of_data(args[no_of_param].extargs_type);

							if (args[no_of_param].extargs_type == ST_EXTARGS_TYPE::int_with_default || args[no_of_param].extargs_type == ST_EXTARGS_TYPE::int_with_error)
								cout << ", 范围" << range_to_str(args[no_of_param].extargs_int_min, args[no_of_param].extargs_int_max);
							else if (args[no_of_param].extargs_type == ST_EXTARGS_TYPE::int_with_set_default || args[no_of_param].extargs_type == ST_EXTARGS_TYPE::int_with_set_error)
								cout << ", 范围[" << range_to_str(args[no_of_param].extargs_int_set) << "]";
							else if (args[no_of_param].extargs_type == ST_EXTARGS_TYPE::str_with_set_default || args[no_of_param].extargs_type == ST_EXTARGS_TYPE::str_with_set_error)
								cout << ", 范围[" << range_to_str(args[no_of_param].extargs_string_set) << "]";

							if (args[no_of_param].extargs_type == ST_EXTARGS_TYPE::int_with_default || args[no_of_param].extargs_type == ST_EXTARGS_TYPE::int_with_set_default)
								cout << " 缺省:" << value_to_valstr(args[no_of_param].extargs_int_default);
							else if (args[no_of_param].extargs_type == ST_EXTARGS_TYPE::str || args[no_of_param].extargs_type == ST_EXTARGS_TYPE::str_with_set_default || args[no_of_param].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_default)
								cout << " 缺省:" << value_to_valstr(args[no_of_param].extargs_string_default);

							cout << ")" << endl;

							check_result = -1;
							break;
						}
					}

				}
				else {
					cout << "参数[" << args[no_of_param].get_name() << "]重复." << endl;
					check_result = -1;
					break;
				}
			}
			else {
				cout << "参数[" << argv[i] << "]非法." << endl;
				check_result = -1;
				break;
			}
		}
	}

	if (check_result == -1)
		return -1;
	else if (check_result == 0 && follow_up_args)
		return argc;
	else if (check_result > 0)
		return check_result;
	else
		return 0x7fffffff;
}


/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：友元函数
***************************************************************************/
int args_analyse_print(const args_analyse_tools* const args)
{
	int maxlen_name = 0;
	int maxlen_type = 0;
	int maxlen_default = 0;
	int maxlen_value = 0;
	int maxlen_range = 0;

	// 寻找最长字符串
	for (int i = 0; args[i].args_name != ""; i++) {
		// name
		maxlen_name = max(maxlen_name, strlen_str(args[i].args_name));
		// type
		maxlen_type = max(maxlen_type, strlen_str(type_to_typestr(args[i].extargs_type)));
		// default
		if (args[i].extargs_type == ST_EXTARGS_TYPE::boolean)
			maxlen_default = max(maxlen_default, strlen_str(value_to_valstr(args[i].extargs_bool_default)));
		else if (args[i].extargs_type == ST_EXTARGS_TYPE::int_with_default || args[i].extargs_type == ST_EXTARGS_TYPE::int_with_set_default)
			maxlen_default = max(maxlen_default, strlen_str(value_to_valstr(args[i].extargs_int_default)));
		else if (args[i].extargs_type == ST_EXTARGS_TYPE::str || args[i].extargs_type == ST_EXTARGS_TYPE::str_with_set_default || args[i].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_default)
			maxlen_default = max(maxlen_default, strlen_str(value_to_valstr(args[i].extargs_string_default)));
		else if (args[i].extargs_type == ST_EXTARGS_TYPE::int_with_error || args[i].extargs_type == ST_EXTARGS_TYPE::int_with_set_error || args[i].extargs_type == ST_EXTARGS_TYPE::str_with_set_error || args[i].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_error)
			maxlen_default = max(maxlen_default, strlen_str("default"));
		// value
		if (args[i].extargs_type == ST_EXTARGS_TYPE::boolean)
			maxlen_value = max(maxlen_value, strlen_str(value_to_valstr(args[i].extargs_bool_default)));
		else if (args[i].extargs_type == ST_EXTARGS_TYPE::int_with_default || args[i].extargs_type == ST_EXTARGS_TYPE::int_with_set_default || args[i].extargs_type == ST_EXTARGS_TYPE::int_with_error || args[i].extargs_type == ST_EXTARGS_TYPE::int_with_set_error)
			maxlen_value = max(maxlen_value, strlen_str(value_to_valstr(args[i].extargs_int_value)));
		else if (args[i].extargs_type == ST_EXTARGS_TYPE::str || args[i].extargs_type == ST_EXTARGS_TYPE::str_with_set_default || args[i].extargs_type == ST_EXTARGS_TYPE::str_with_set_error)
			maxlen_value = max(maxlen_value, strlen_str(value_to_valstr(args[i].extargs_string_value)));
		else if (args[i].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_default || args[i].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_error)
			maxlen_value = max(maxlen_value, strlen_str(value_to_valstr(args[i].get_str_ipaddr())));
		maxlen_value = max(maxlen_value, 5);
		// range/set
		if (args[i].extargs_type == ST_EXTARGS_TYPE::int_with_default || args[i].extargs_type == ST_EXTARGS_TYPE::int_with_error)
			maxlen_range = max(maxlen_range, strlen_str(range_to_str(args[i].extargs_int_min, args[i].extargs_int_max)));
		else if (args[i].extargs_type == ST_EXTARGS_TYPE::int_with_set_default || args[i].extargs_type == ST_EXTARGS_TYPE::int_with_set_error)
			maxlen_range = max(maxlen_range, strlen_str(range_to_str(args[i].extargs_int_set)));
		else if (args[i].extargs_type == ST_EXTARGS_TYPE::str_with_set_default || args[i].extargs_type == ST_EXTARGS_TYPE::str_with_set_error)
			maxlen_range = max(maxlen_range, strlen_str(range_to_str(args[i].extargs_string_set)));
		else if (args[i].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_default || args[i].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_error || args[i].extargs_type == ST_EXTARGS_TYPE::boolean || args[i].extargs_type == ST_EXTARGS_TYPE::str)
			maxlen_range = max(maxlen_range, strlen_str("/"));
		maxlen_range = max(maxlen_range, 9);
	}

	// 打印
	// 打印表头
	cout << setiosflags(ios::left);
	for (int i = 0; i < 6 + maxlen_name + maxlen_type + maxlen_default + 7 + maxlen_value + maxlen_range; i++)
		cout << "=";
	cout << endl;
	cout << " " << setw(maxlen_name + 1) << "name" << setw(maxlen_type + 1) << "type";
	cout << setw(maxlen_default + 1) << "default" << setw(7) << "exists";
	cout << setw(maxlen_value + 1) << "value" << setw(maxlen_range + 1) << "range/set" << endl;
	for (int i = 0; i < 6 + maxlen_name + maxlen_type + maxlen_default + 7 + maxlen_value + maxlen_range; i++)
		cout << "=";
	cout << endl;
	// 打印内容
	for (int i = 0; args[i].args_name != ""; i++) {
		// name
		cout << " " << setw(maxlen_name + 1) << args[i].args_name;
		// type
		cout << setw(maxlen_type + 1) << type_to_typestr(args[i].extargs_type);
		// default
		cout << setw(maxlen_default + 1);
		if (args[i].extargs_type == ST_EXTARGS_TYPE::boolean)
			cout << value_to_valstr(args[i].extargs_bool_default);
		else if (args[i].extargs_type == ST_EXTARGS_TYPE::int_with_default || args[i].extargs_type == ST_EXTARGS_TYPE::int_with_set_default)
			cout << value_to_valstr(args[i].extargs_int_default);
		else if (args[i].extargs_type == ST_EXTARGS_TYPE::str || args[i].extargs_type == ST_EXTARGS_TYPE::str_with_set_default || args[i].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_default) {
			cout << value_to_valstr(args[i].extargs_string_default);
		}
		else if (args[i].extargs_type == ST_EXTARGS_TYPE::int_with_error || args[i].extargs_type == ST_EXTARGS_TYPE::int_with_set_error || args[i].extargs_type == ST_EXTARGS_TYPE::str_with_set_error || args[i].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_error)
			cout << "/";
		// exists
		cout << setw(7) << args[i].args_existed;
		// value
		cout << setw(maxlen_value + 1);
		if (!args[i].args_existed)
			cout << "/";
		else {
			if (args[i].extargs_type == ST_EXTARGS_TYPE::boolean)
				cout << value_to_valstr(true);
			else if (args[i].extargs_type == ST_EXTARGS_TYPE::int_with_default || args[i].extargs_type == ST_EXTARGS_TYPE::int_with_error || args[i].extargs_type == ST_EXTARGS_TYPE::int_with_set_default || args[i].extargs_type == ST_EXTARGS_TYPE::int_with_set_error)
				cout << value_to_valstr(args[i].extargs_int_value);
			else if (args[i].extargs_type == ST_EXTARGS_TYPE::str || args[i].extargs_type == ST_EXTARGS_TYPE::str_with_set_default || args[i].extargs_type == ST_EXTARGS_TYPE::str_with_set_error) {
				cout << value_to_valstr(args[i].extargs_string_value);
			}
			else if (args[i].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_default || args[i].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_error) {
				cout << value_to_valstr(args[i].get_str_ipaddr());
			}
		}
		// range/set
		cout << setw(maxlen_range + 1);
		if (args[i].extargs_type == ST_EXTARGS_TYPE::int_with_default || args[i].extargs_type == ST_EXTARGS_TYPE::int_with_error)
			cout << range_to_str(args[i].extargs_int_min, args[i].extargs_int_max);
		else if (args[i].extargs_type == ST_EXTARGS_TYPE::int_with_set_default || args[i].extargs_type == ST_EXTARGS_TYPE::int_with_set_error)
			cout << range_to_str(args[i].extargs_int_set);
		else if (args[i].extargs_type == ST_EXTARGS_TYPE::str_with_set_default || args[i].extargs_type == ST_EXTARGS_TYPE::str_with_set_error)
			cout << range_to_str(args[i].extargs_string_set);
		else if (args[i].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_default || args[i].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_error || args[i].extargs_type == ST_EXTARGS_TYPE::boolean || args[i].extargs_type == ST_EXTARGS_TYPE::str)
			cout << "/";

		cout << endl;
	}
	// 打印表尾
	for (int i = 0; i < 6 + maxlen_name + maxlen_type + maxlen_default + 7 + maxlen_value + maxlen_range; i++)
		cout << "=";
	cout << endl << endl;

	return 0; //此句根据需要修改
}

#endif // !ENABLE_LIB_COMMON_TOOLS