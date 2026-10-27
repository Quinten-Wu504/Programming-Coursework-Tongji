/* 2154146 吴金轩 计科 */
#include <iostream>
#include "../include/class_crt.h"
#include "../include/common_string_process.h"
using namespace std;

/* 允许加入需要的头文件，给出 cfgfile_read_tools类的实现 */


/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
/* 构造和析构函数 */
cfgfile_read_tools::cfgfile_read_tools(const char* _cfgname)
{
	cfgname = _cfgname;
	cfgfile.open(_cfgname, ios::in);
}

cfgfile_read_tools::cfgfile_read_tools(const string& _cfgname)
{
	cfgname = _cfgname;
	cfgfile.open(cfgname, ios::in);
}

cfgfile_read_tools::~cfgfile_read_tools()
{
	cfgfile.close();
}

/* 判断配置文件是否打开成功 */
bool cfgfile_read_tools::is_open()
{
	if (cfgfile.is_open())
		return 1;
	else
		return 0;
}

/* 组读取函数，读出所有的，放在string型的vector中 */
int cfgfile_read_tools::get_all_group(vector <string>& ret)
{
	if (cfgfile.is_open())
	{
		ret.clear();

		string groupname;
		while (!cfgfile.eof())
		{
			char* temp = new(nothrow) char[65536];
			if (temp == NULL)
			{
				cout << "No Memory!" << endl;
				return 0;
			}

			cfg_getline(cfgfile, &temp);
			if (check_group(temp))
			{
				groupname = get_groupname(temp);
				ret.push_back(groupname);
			}

			delete[]temp;
		}

		cfgfile.clear();
		cfgfile.seekg(0, ios::beg);

		return ret.size();
	}
	else
		return -1;
}

/* 项读取函数 - 取某个group的所有item，放在string型的vector中 */
int cfgfile_read_tools::get_all_item(const char* const group_name, vector <string>& ret, const bool ignore_lower_upper_case)
{
	if (cfgfile.is_open())
	{
		ret.clear();
		bool mark = 0;
		string temp_groupname;
		if (group_name != NULL)
		{
			string appointed_groupname = group_name;
			while (!cfgfile.eof())
			{
				char* temp1 = new(nothrow) char[65536];
				if (temp1 == NULL)
				{
					cout << "No Memory!" << endl;
					return 0;
				}

				cfg_getline(cfgfile, &temp1);
				if (check_group(temp1))
				{
					temp_groupname = get_groupname(temp1);/*
					cout << temp_groupname << "*" << endl;*/
					if (strcmp_str(temp_groupname, appointed_groupname, ignore_lower_upper_case) == -1)
					{
						mark = 1;
						break;
					}
				}

				delete[]temp1;
			}
		}
		else
			mark = 1;

		while (!cfgfile.eof())
		{
			char* temp2 = new(nothrow) char[65536];
			if (temp2 == NULL)
			{
				cout << "No Memory!" << endl;
				return 0;
			}

			cfg_getline(cfgfile, &temp2);
			if (check_item(temp2))
			{
				string temp_string = temp2;
				ret.push_back(temp_string);
			}

			if (check_group(temp2) && group_name != NULL)
				break;

			delete[]temp2;
		}

		cfgfile.clear();
		cfgfile.seekg(0, ios::beg);

		return -(!mark);
	}
	else
		return -1;
}

int cfgfile_read_tools::get_all_item(const string& group_name, vector <string>& ret, const bool ignore_lower_upper_case)
{
	if (cfgfile.is_open())
	{
		ret.clear();
		bool mark = 0;
		string temp_groupname;
		string appointed_groupname = group_name;
		while (!cfgfile.eof())
		{
			char* temp1 = new(nothrow) char[65536];
			if (temp1 == NULL)
			{
				cout << "No Memory!" << endl;
				return 0;
			}

			cfg_getline(cfgfile, &temp1);
			if (check_group(temp1))
			{
				temp_groupname = get_groupname(temp1);
				if (strcmp_str(temp_groupname, appointed_groupname, ignore_lower_upper_case) == -1)
				{
					mark = 1;
					break;
				}
			}

			delete[]temp1;
		}

		while (!cfgfile.eof())
		{
			char* temp2 = new(nothrow) char[65536];
			if (temp2 == NULL)
			{
				cout << "No Memory!" << endl;
				return 0;
			}

			cfg_getline(cfgfile, &temp2);
			if (check_item(temp2))
			{
				string temp_string = temp2;
				ret.push_back(temp_string);
			}

			if (check_group(temp2))
				break;

			delete[]temp2;
		}

		cfgfile.clear();
		cfgfile.seekg(0, ios::beg);

		return -(!mark);
	}
	else
		return -1;
}

/* 项读取函数 - 取某个group的所有item，放在string中 */
int cfgfile_read_tools::get_one_item(const char* const group_name, const char* const item_name, string& ret, const bool ignore_lower_upper_case)
{
	if (cfgfile.is_open())
	{
		ret.clear();
		bool mark = 0;
		string temp_groupname;
		string appointed_groupname = group_name;
		while (!cfgfile.eof())
		{
			char* temp1 = new(nothrow) char[65536];
			if (temp1 == NULL)
			{
				cout << "No Memory!" << endl;
				return 0;
			}

			cfg_getline(cfgfile, &temp1);
			if (check_group(temp1))
			{
				temp_groupname = get_groupname(temp1);
				if (strcmp_str(temp_groupname, appointed_groupname, ignore_lower_upper_case) == -1)
					break;
			}

			delete[]temp1;
		}

		while (!cfgfile.eof())
		{
			char* temp2 = new(nothrow) char[65536];
			if (temp2 == NULL)
			{
				cout << "No Memory!" << endl;
				return 0;
			}

			cfg_getline(cfgfile, &temp2);
			if (check_item(temp2))
			{
				int i = 0;
				string temp_item_name;
				for (i = 0; temp2[i] != '\0'; i++)
				{
					if (temp2[i] == '=')
						break;
					else
						temp_item_name += temp2[i];
				}
				temp_item_name = trim_blank(temp_item_name, 1, 1);

				string str_item_name;
				str_item_name = item_name;
				str_item_name = trim_blank(str_item_name, 1, 1);

				if (strcmp_str(temp_item_name, str_item_name, ignore_lower_upper_case) == -1)
				{
					ret = temp2;
					mark = 1;
				}
			}

			if (check_group(temp2))
				break;

			delete[]temp2;
		}

		cfgfile.clear();
		cfgfile.seekg(0, ios::beg);

		return -(!mark);
	}
	else
		return -1;
}

int cfgfile_read_tools::get_one_item(const string& group_name, const string& item_name, string& ret, const bool ignore_lower_upper_case)
{
	if (cfgfile.is_open())
	{
		ret.clear();
		bool mark = 0;
		string temp_groupname;
		string appointed_groupname = group_name;
		while (!cfgfile.eof())
		{
			char* temp1 = new(nothrow) char[65536];
			if (temp1 == NULL)
			{
				cout << "No Memory!" << endl;
				return 0;
			}

			cfg_getline(cfgfile, &temp1);
			if (check_group(temp1))
			{
				temp_groupname = get_groupname(temp1);
				if (strcmp_str(temp_groupname, appointed_groupname, ignore_lower_upper_case) == -1)
					break;
			}

			delete[]temp1;
		}

		while (!cfgfile.eof())
		{
			char* temp2 = new(nothrow) char[65536];
			if (temp2 == NULL)
			{
				cout << "No Memory!" << endl;
				return 0;
			}

			cfg_getline(cfgfile, &temp2);
			if (check_item(temp2))
			{
				int i = 0;
				string temp_item_name;
				for (i = 0; temp2[i] != '\0'; i++)
				{
					if (temp2[i] == '=')
						break;
					else
						temp_item_name += temp2[i];
				}
				temp_item_name = trim_blank(temp_item_name, 1, 1);

				string str_item_name;
				str_item_name = item_name;
				str_item_name = trim_blank(str_item_name, 1, 1);

				if (strcmp_str(temp_item_name, str_item_name, ignore_lower_upper_case) == -1)
				{
					ret = temp2;
					mark = 1;
				}
			}

			if (check_group(temp2))
				break;

			delete[]temp2;
		}

		cfgfile.clear();
		cfgfile.seekg(0, ios::beg);

		return -(!mark);
	}
	else
		return -1;
}

/* 项读取函数 - 按数据类型读取某个group的某个item，放在对应数据类型的变量中
	数据类型包括：int/double/string/char * /char */
int cfgfile_read_tools::item_get_value(const char* const group_name, const char* const item_name, const char* const def_str, char* str, const int str_maxlen, const bool ignore_lower_upper_case)
{
	string temp;
	int mark = 0;
	mark = get_one_item(group_name, item_name, temp, ignore_lower_upper_case);

	if (mark == 0)
	{
		int i = 0;
		for (i = 0; temp[i] != '\0'; i++)
		{
			if (temp[i] == '=')
				break;
		}

		string item_value;
		for (int j = i + 1; temp[j] != '\0'; j++)
		{
			item_value += temp[j];
		}
		item_value = trim_blank(item_value, 1, 1);

		if (item_value.length() == 0)
		{
			int i = 0;
			for (i = 0; i < str_maxlen - 1 && def_str[i] != '\0'; i++)\
			{
				if (def_str[i] != ' ' && def_str[i] != '\t')
					str[i] = def_str[i];
				else
					break;
			}
			str[i] = '\0';
		}
		else
		{
			int i = 0;
			for (i = 0; i < str_maxlen - 1 && item_value[i] != '\0'; i++)
			{
				if (item_value[i] != ' ' && item_value[i] != '\t')
					str[i] = item_value[i];
				else
					break;
			}
			str[i] = '\0';
		}
	}

	return mark;
}

int cfgfile_read_tools::item_get_value(const char* const group_name, const char* const item_name, const char* const def_str, string& value, const bool ignore_lower_upper_case)
{
	string temp;
	int mark = 0;
	mark = get_one_item(group_name, item_name, temp, ignore_lower_upper_case);

	if (mark == 0)
	{
		int i = 0;
		for (i = 0; temp[i] != '\0'; i++)
		{
			if (temp[i] == '=')
				break;
		}

		string item_value;
		for (int j = i + 1; temp[j] != '\0'; j++)
		{
			item_value += temp[j];
		}
		item_value = trim_blank(item_value, 1, 1);

		if (item_value.length() == 0)
			value = def_str;
		else
			value = item_value;
	}

	return mark;
}

int cfgfile_read_tools::item_get_value(const char* const group_name, const char* const item_name, char& ch, const bool ignore_lower_upper_case)
{
	string temp;
	int mark = 0;
	mark = get_one_item(group_name, item_name, temp, ignore_lower_upper_case);

	if (mark == 0)
	{
		int i = 0;
		for (i = 0; temp[i] != '\0'; i++)
		{
			if (temp[i] == '=')
				break;
		}

		string item_value;
		for (int j = i + 1; temp[j] != '\0'; j++)
		{
			item_value += temp[j];
		}
		item_value = trim_blank(item_value, 1, 1);

		if (item_value.length() == 0)
			ch = ' ';
		else
			ch = item_value[0];
	}

	return mark;
}

int cfgfile_read_tools::item_get_value(const char* const group_name, const char* const item_name, const int min_value, const int max_value, const int def_value, int& value, const bool ignore_lower_upper_case)
{
	string temp;
	int mark = 0;
	mark = get_one_item(group_name, item_name, temp, ignore_lower_upper_case);

	if (mark == 0)
	{
		int i = 0;
		for (i = 0; temp[i] != '\0'; i++)
		{
			if (temp[i] == '=')
				break;
		}

		string item_value;
		for (int j = i + 1; temp[j] != '\0'; j++)
		{
			item_value += temp[j];
		}
		item_value = trim_blank(item_value, 1, 1);

		if (!check_int(item_value, value, min_value, max_value))
			value = def_value;
	}

	return mark;
}

int cfgfile_read_tools::item_get_value(const char* const group_name, const char* const item_name, const double min_value, const double max_value, const double def_value, double& value, const bool ignore_lower_upper_case)
{
	string temp;
	int mark = 0;
	mark = get_one_item(group_name, item_name, temp, ignore_lower_upper_case);

	if (mark == 0)
	{
		int i = 0;
		for (i = 0; temp[i] != '\0'; i++)
		{
			if (temp[i] == '=')
				break;
		}

		string item_value;
		for (int j = i + 1; temp[j] != '\0'; j++)
		{
			item_value += temp[j];
		}
		item_value = trim_blank(item_value, 1, 1);

		if (!check_double(item_value, value, min_value, max_value))
			value = def_value;
	}

	return mark;

}







void trim_annotation(char* line_str)
{
	for (int i = 0; line_str[i] != '\0'; i++)
	{
		if (line_str[i] == '#' || line_str[i] == ';')
		{
			line_str[i] = 0;
			break;
		}
	}
}

void cfg_getline(ifstream& cfgfile, char**p_line_str)
{
	cfgfile.getline(*p_line_str , 65535);
	trim_annotation(*p_line_str);
	trim_blank(p_line_str, 1, 1);
}

bool check_group(char* line_str)
{
	if (strlen(line_str) != 0)
		return (line_str[0] == '[' && line_str[strlen(line_str) - 1] == ']');
	else
		return 0;
}


bool check_item(char* line_str)
{
	int i = 0;
	string item_name;
	for (i = 0; line_str[i] != '\0'; i++)
	{
		if (line_str[i] == '=')
			break;
		else
			item_name += line_str[i];
	}

	item_name = trim_blank(item_name, 1, 1);

	if (line_str[i] == '=' && item_name.length() != 0)
	{
		/*int k = 0;
		for (k = i + 1; line_str[k] != '\0'; k++)
		{
			if (line_str[k] == '=' || line_str[k] == '[' || line_str[k] == ']')
				break;
		}

		if (line_str[k] == '\0')
			return 1;
		else
			return 0;*/
		return 1;
	}
	else
		return 0;
}


string get_groupname(char* line_str)
{
	string temp1;
	for (unsigned int i = 1; i < strlen(line_str) - 1; i++)
		temp1 += line_str[i];
	temp1 = trim_blank(temp1, 1, 1);

	return '[' + temp1 + ']';
}

bool check_int(string item_value_str, int& result, const int min_value, const int max_value)
{
	bool mark = 1;
	int dot_loc = -1;
	result = 0;

	if (item_value_str.length() == 0)
		mark = 0;
	else
	{
		for (unsigned int i = 0; i < item_value_str.length(); i++)
		{
			if (item_value_str[i] != '.' && (item_value_str[i] < '0' || item_value_str[i] > '9'))
			{
				mark = 0;
				break;
			}
			else if (item_value_str[i] == '.')
			{
				if (dot_loc != -1)
				{
					mark = 0;
					break;
				}
				else
					dot_loc = i;
			}
			else
			{
				if (dot_loc == -1)
					result = result * 10 + (item_value_str[i] - '0');
			}
		}
	}

	if (mark)
	{
		if (result < min_value || result > max_value)
		{
			result = 0;
			mark = 0;
		}
	}
	else
		result = 0;

	return mark;
}

bool check_double(string item_value_str, double& result, const double min_value, const double max_value)
{
	bool mark = 1;
	int dot_loc = -1;
	int count = 0;
	result = 0;

	if (item_value_str.length() == 0)
		mark = 0;
	else
	{
		for (unsigned int i = 0; i < item_value_str.length(); i++)
		{
			if (item_value_str[i] != '.' && (item_value_str[i] < '0' || item_value_str[i] > '9'))
			{
				mark = 0;
				break;
			}
			else if (item_value_str[i] == '.')
			{
				if (dot_loc != -1)
				{
					mark = 0;
					break;
				}
				else
					dot_loc = i;
			}
			else
			{
				if (dot_loc == -1)
					result = result * 10 + (item_value_str[i] - '0');
				else
				{
					count++;
					double temp = item_value_str[i] - '0';
					for (int i = 0; i < count; i++)
						temp /= 10;
					result += temp;
				}
			}
		}
	}

	if (mark)
	{
		if (result < min_value || result > max_value)
		{
			result = 0;
			mark = 0;
		}
	}
	else
		result = 0;

	return mark;
}