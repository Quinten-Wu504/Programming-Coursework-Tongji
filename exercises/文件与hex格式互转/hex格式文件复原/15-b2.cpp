/* 2154146 吴金轩 计科 */
/* 2150792 牛禄阳 2253214 李闯 1950617 罗楠 2251190 周怡婧 2253895 冯晨 2253631 杨泽昊 2152768 袁锐声 */
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

void print_reminder(char in_file_name[], char out_file_name[])
{
	cerr << "文件名以下形式均可以:" << endl;
	cerr << "    a.hex                     : 不带路径形式" << endl;
	cerr << "    ..\\data\\b.txt             : 相对路径形式" << endl;
	cerr << "    C:\\Windows\\System32\\c.hex : 绝对相对路径形式" << endl;
	cerr << "请输入要转换的hex格式文件名 : ";
	cin >> in_file_name;
	cerr << "请输入转换后的文件名        : ";
	cin >> out_file_name;
}

int hex_to_num(char hex_num)
{
	int num = 0;
	switch (hex_num) {
	case '0':
		num = 0;
		break;
	case '1':
		num = 1;
		break;
	case '2':
		num = 2;
		break;
	case '3':
		num = 3;
		break;
	case '4':
		num = 4;
		break;
	case '5':
		num = 5;
		break;
	case '6':
		num = 6;
		break;
	case '7':
		num = 7;
		break;
	case '8':
		num = 8;
		break;
	case '9':
		num = 9;
		break;
	case 'A':
		num = 10;
		break;
	case 'B':
		num = 11;
		break;
	case 'C':
		num = 12;
		break;
	case 'D':
		num = 13;
		break;
	case 'E':
		num = 14;
		break;
	case 'F':
		num = 15;
		break;
	default:
		num = 99;
		break;
	}
	return num;
}

char hex_to_dec_num(char hex_num[])
{
	char dec_num = 0;
	for (int i = 0; hex_num[i] != '\0'; i++) {
		dec_num = dec_num * 16 + hex_to_num(hex_num[i]);
	}
	return dec_num;
}

int main()
{
	char in_file_name[260] = { 0 }, out_file_name[260] = { 0 };
	char hex_char16[16][3] = {0}, temp_char = 0;
	int count = -1;
	print_reminder(in_file_name, out_file_name);

	ifstream in_file;
	ofstream out_file;
	in_file.open(in_file_name, ios::in | ios::binary);
	if (in_file.is_open() == 0) {
		cout << "输入文件" << in_file_name << "打开失败!" << endl;
		return -1;
	}
	out_file.open(out_file_name, ios::out | ios::binary);
	if (out_file.is_open() == 0) {
		cout << "输出文件" << out_file_name << "打开失败!" << endl;
		in_file.close();
		return -1;
	}


	while (1) {
		in_file.seekg(11, ios::cur);
		count = -1;
		for (int i = 0; i < 16; i++) {
			if (i == 8) {
				in_file.seekg(2, ios::cur);
			}
			in_file.read(hex_char16[i], 3);
			hex_char16[i][2] = '\0';
			if (!((hex_char16[i][0] >= 48 && hex_char16[i][0] <= 57) || (hex_char16[i][0] >= 65 && hex_char16[i][0] <= 70))) {
				count = i;
				break;
			}
			temp_char = hex_to_dec_num(hex_char16[i]);
			out_file.write(&temp_char, 1);
		}

		if (count == -1) {
			in_file.seekg(1, ios::cur);
			in_file.seekg(16, ios::cur);
			in_file.read(&temp_char, 1);
			while (temp_char == 13 || temp_char == 10) {
				in_file.read(&temp_char, 1);
			}
			in_file.seekg(-1, ios::cur);
		}
		else {
			break;
		}
	}

	in_file.close();
	out_file.close();

	return 0;
}