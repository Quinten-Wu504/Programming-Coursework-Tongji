/* 2154146 吴金轩 计科 */
#include <iostream>
#include <string>
#include <iomanip>
#include "../include/common_string_process.h"
using namespace std;

int strlen_str(string str)
{
	int length = 0;

	for (length = 0; str[length] != '\0'; length++);

	return length;
}

int strcmp_str(const string str1, const string str2)
{
	int loc = -1;
	int i;

	for (i = 0; str1[i] != '\0' && str2[i] != '\0'; i++) {
		if (str1[i] != str2[i]) {
			loc = i;
			break;
		}
	}
	if (str1[i] != '\0' || str2[i] != '\0')
		loc = i;

	return loc;
}

int strcmp_str(const string str1, const string str2, const bool ignore_lower_upper_case)
{
	int loc = -1;
	int i;
	for (i = 0; str1[i] != '\0' && str2[i] != '\0'; i++) {
		char temp1 = str1[i], temp2 = str2[i];
		if (ignore_lower_upper_case)
		{
			if (str1[i] >= 'A' && str1[i] <= 'Z')
				temp1 = temp1 + 'a' - 'A';
			if (str2[i] >= 'A' && str2[i] <= 'Z')
				temp2 = temp2 + 'a' - 'A';
		}
		if (temp1 != temp2) {
			loc = i;
			break;
		}
	}

	if (str1[i] != '\0' || str2[i] != '\0')
		loc = i;

	return loc;
}

char* strcpy_tj(char* s1, const char* s2)
{
	char if_NULL[80] = "";
	char* temp_s1 = s1;

	if (s2 == NULL) {
		s2 = if_NULL;
	}

	if (s1 != NULL) {
		for (; *s2 != '\0'; s1++, s2++) {
			*s1 = *s2;
		}
		*s1 = '\0';
		s1 = temp_s1;
	}

	return s1;
}

int hex_to_num(char hex_num)
{
	int num = 0;

	if (hex_num >= '0' && hex_num <= '9')
		num = hex_num - '0';
	else if (hex_num >= 'a' && hex_num <= 'f')
		num = hex_num - 'a' + 10;
	else if (hex_num >= 'A' && hex_num <= 'F')
		num = hex_num - 'A' + 10;
	else
		num = 99;

	return num;
}


int char_to_int(const char arr[], int size)
{
	int dec_num = 0;
	for (int i = 0; i < size; i++)
	{
		dec_num |= (((unsigned int)((unsigned char)arr[i])) << (8 * i));
	}
	return dec_num;
}

int hex_str_to_dec_num(const char* str, int length)
{
	char dec_num = 0;

	for (int i = 0; i < length; i++)
		dec_num = dec_num * 16 + hex_to_num(str[i]);
	
	return dec_num;
}

string int_to_str(const int& num)
{
	string result = "";
	if (num == 0)
	{
		result = "0";
		return result;
	}
	else
	{
		int temp = num;
		while (temp != 0)
		{
			string result_tmp = "";
			result_tmp += (char)(temp % 10 + '0');
			result_tmp += result;
			result = result_tmp;
			temp /= 10;
		}
		return result;
	}
}

void print_hex_number(unsigned int dec_num, int num_of_digit)
{
	unsigned int base = 1;
	unsigned int temp = dec_num;
	for (int i = 0; i < num_of_digit - 1; i++) {
		base *= 16;
	}
	cout << hex;
	for (int i = 0; i < num_of_digit; i++) {
		cout << (temp / base) % 16;
		temp = temp % base;
		base = base / 16;
	}
	cout << dec;
}

string trim_blank(string line_str, bool right, bool left)
{
	if (!right && !left)
		return line_str;
	else {
		string temp_str = "";

		int length_of_str = strlen_str(line_str);
		int notblank_loc[2] = { 0, length_of_str - 1 };

		if (left)
			for (notblank_loc[0] = 0; line_str[notblank_loc[0]] == ' ' || line_str[notblank_loc[0]] == '\n' || line_str[notblank_loc[0]] == '\r' || line_str[notblank_loc[0]] == 9; notblank_loc[0]++);
		if (right) 
			for (notblank_loc[1] = length_of_str - 1; notblank_loc[1] >= notblank_loc[0] && (line_str[notblank_loc[1]] == ' ' || line_str[notblank_loc[1]] == '\n' || line_str[notblank_loc[1]] == '\r' || line_str[notblank_loc[1]] == 9); notblank_loc[1]--);

		for (int i = 0; notblank_loc[0] + i <= notblank_loc[1]; i++) {
			temp_str = temp_str + line_str[notblank_loc[0] + i];
		}

		return temp_str;
	}
}

void trim_blank(char** p_line_str, bool right, bool left)
{
	if (!right && !left)
		return;
	else {
		int length_of_str = strlen_str(*p_line_str);
		int notblank_loc[2] = { 0, length_of_str - 1 };

		if (left)
			for (notblank_loc[0] = 0; (*p_line_str)[notblank_loc[0]] == ' ' || (*p_line_str)[notblank_loc[0]] == '\n' || (*p_line_str)[notblank_loc[0]] == '\r' || (*p_line_str)[notblank_loc[0]] == 9; notblank_loc[0]++);
		if (right)
			for (notblank_loc[1] = length_of_str - 1; (notblank_loc[1] >= notblank_loc[0]) && ((*p_line_str)[notblank_loc[1]] == ' ' || (*p_line_str)[notblank_loc[1]] == '\n' || (*p_line_str)[notblank_loc[1]] == '\r' || (*p_line_str)[notblank_loc[1]] == 9); notblank_loc[1]--);

		char* temp_str = new(nothrow) char[notblank_loc[1] - notblank_loc[0] + 1 + 1];
		if (temp_str == NULL)
		{
			cout << "No Memory!" << endl;
			return;
		}

		memcpy(temp_str, &((*p_line_str)[notblank_loc[0]]), notblank_loc[1] - notblank_loc[0] + 1);

		temp_str[notblank_loc[1] - notblank_loc[0] + 1] = '\0';

		delete[](*p_line_str);

		*p_line_str = temp_str;
	}
}

void print_hex_line(string str, bool eof)
{
	int count = 0;
	int i = 0;
	char char_col[16] = { 0 };

	if (strlen_str(str) != 0 && str[0] != '\n' && str[0] != '\r') {
		while (str[i] != '\0') {
			if (count % 16 == 0) {
				print_hex_number(count, 8);
				cout << " : ";
			}

			if (count % 16 == 8) {
				cout << "- ";
			}

			char_col[count % 16] = str[i];
			print_hex_number(str[i], 2);
			cout << " ";

			count++;

			if (count % 16 == 0) {
				cout << " ";
				for (int i = 0; i < 16; i++) {
					if (char_col[i] >= 32 && char_col[i] <= 126)
						cout << char_col[i];
					else
						cout << ".";
				}
				cout << endl;
			}

			i++;
		}

		if (count % 16 != 0) {
			for (int i = 0; i < 16 - count % 16; i++) {
				cout << "   ";
			}
			if (count % 16 != 0 && count % 16 <= 8) {
				cout << "  ";
			}
			cout << " ";
			for (int i = 0; i < count % 16; i++) {
				if (char_col[i] >= 32 && char_col[i] <= 126)
					cout << char_col[i];
				else
					cout << ".";
			}
			cout << endl;
		}
	}
	else {
		if (eof)
			cout << "<EOF>" << endl;
		else
			cout << "<EMPTY>" << endl;
	}
}

void intercept_file_path(char* procname, const char* file_path)
{
	int record_loc = -1;

	for (int i = 0; file_path[i] != '\0'; i++) {
		if (file_path[i] == '\\')
			record_loc = i;
	}

	if (record_loc == -1)
		strcpy_tj(procname, "找不到可执行文件");
	else
		strcpy_tj(procname, &file_path[record_loc + 1]);
}

string get_file_n_line(ifstream& infile, int n)
{
	infile.clear();
	infile.seekg(0, ios::beg);

	char line_text[256] = { 0 };
	int line_num = 0;
	string n_unempty_line;
	while (!infile.fail())
	{
		infile.getline(line_text, 255);
		n_unempty_line = line_text;
		n_unempty_line = trim_blank(n_unempty_line, 1, 1);
		if (n_unempty_line[0] != '\0')
		{
			line_num++;
			if (line_num == n)
				break;
		}
	}

	return n_unempty_line;
}

bool is_UTF8(const string& line_text)
{
	int accuracy = 0;
	int asciibyte = 0;
	int utfbytes = 0;

	for (unsigned int i = 0; i < line_text.length(); i++)
	{
		if ((line_text[i] & 0x80) == 0)
		{
			asciibyte += 1;
			utfbytes += 1;
		}
		else if ((line_text[i] & 0xE0) == 0xC0 && i + 1 < line_text.length() 
				&& (line_text[i + 1] & 0xC0) == 0x80)
		{
			utfbytes += 2;
			i += 1;
		}
		else if ((line_text[i] & 0xF0) == 0xE0 && i + 2 < line_text.length() 
				&& (line_text[i + 1] & 0xC0) == 0x80 && (line_text[i + 2] & 0xC0) == 0x80)
		{
			utfbytes += 3;
			i += 2;
		}
		else if ((line_text[i] & 0xF8) == 0xF0 && i + 3 < line_text.length()
				&& (line_text[i + 1] & 0xC0) == 0x80 && (line_text[i + 2] & 0xC0) == 0x80
				&& (line_text[i + 3] & 0xC0) == 0x80)
		{
			utfbytes += 4;
			i += 3;
		}
		else if ((line_text[i] & 0xFC) == 0xF8 && i + 4 < line_text.length()
				&& (line_text[i + 1] & 0xC0) == 0x80 && (line_text[i + 2] & 0xC0) == 0x80
				&& (line_text[i + 3] & 0xC0) == 0x80 && (line_text[i + 4] & 0xC0) == 0x80)
		{
			utfbytes += 5;
			i += 4;
		}
		else if ((line_text[i] & 0xFE) == 0xFC && i + 5 < line_text.length()
				&& (line_text[i + 1] & 0xC0) == 0x80 && (line_text[i + 2] & 0xC0) == 0x80
				&& (line_text[i + 3] & 0xC0) == 0x80 && (line_text[i + 4] & 0xC0) == 0x80
				&& (line_text[i + 5] & 0xC0) == 0x80)
		{
			utfbytes += 6;
			i += 5;
		}
		else
		{
			return false;
		}
	}

	if (utfbytes > asciibyte)
		return true;
	else
		return false;
}

bool is_PDF(const string& line_text)
{
	string first8byte;
	if (line_text.length() >= 8)
	{
		for (int i = 0; i < 8; i++)
			first8byte += line_text[i];
		first8byte[7] = '5';

		if (first8byte == "%PDF-1.5")
			return true;
		else
			return false;
	}
	else
		return false;
}

bool check_comment(const string& line_text)
{
	if (line_text.length() >= 2 && line_text[0] == '/' && line_text[1] == '/')
		return true;
	else if (line_text.length() >= 4 && line_text[0] == '/' && line_text[1] == '*' && line_text[line_text.length() - 1] == '/' && line_text[line_text.length() - 2] == '*')
		return true;
	else
		return false;
}

int check_comment_item_num(const string& line_text)
{
	if (line_text.length() >= 2 && line_text[0] == '/' && line_text[1] == '/')
	{
		int count_item = 0;
		for (int i = 2; i < (int)line_text.length(); i++)
		{
			while ((line_text[i] == ' ' || line_text[i] == '\t') && i < (int)line_text.length())
				i++;

			if (i < (int)line_text.length())
			{
				while (line_text[i] != ' ' && line_text[i] != '\t' && i < (int)line_text.length())
					i++;
				count_item++;
			}
			else
				break;
		}

		return count_item;
	}
	else if (line_text.length() >= 4 && line_text[0] == '/' && line_text[1] == '*' && line_text[line_text.length() - 1] == '/' && line_text[line_text.length() - 2] == '*')
	{
		int count_item = 0;
		for (int i = 2; i < (int)line_text.length() - 2; i++)
		{
			while ((line_text[i] == ' ' || line_text[i] == '\t') && i < (int)line_text.length() - 2)
				i++;

			if (i < (int)line_text.length() - 2)
			{
				while (line_text[i] != ' ' && line_text[i] != '\t' && i < (int)line_text.length() - 2)
					i++;
				count_item++;
			}
			else
				break;
		}

		return count_item;
	}
	else
		return -1;
}

string get_filetype(const string& filename)
{
	int i = 0;
	for (i = (int)filename.length() - 1; i >= 0; i--)
	{
		if (filename[i] == '.')
			break;
	}

	if (i == -1)
		return "";
	else
	{
		string type = "";
		for (i = i + 1; i < (int)filename.length(); i++)
			type += filename[i];
		return type;
	}
}