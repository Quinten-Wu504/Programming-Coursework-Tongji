/* 2154146 吴金轩 计科 */
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

void print_reminder()
{
	cerr << "文件名以下形式均可以:" << endl;
	cerr << "    a.txt                     : 不带路径形式" << endl;
	cerr << "    ..\\data\\b.dat             : 相对路径形式" << endl;
	cerr << "    C:\\Windows\\System32\\c.dat : 绝对相对路径形式" << endl;
	cerr << "请输入文件名 : ";
}

void print_hex_number(unsigned int dec_num, int num_of_digit)
{
	unsigned int base = 1;
	unsigned int temp = dec_num;
	for (int i = 0; i < num_of_digit - 1; i++) {
		base *= 16;
	}
	cout << hex << setiosflags(ios::uppercase);
	for (int i = 0; i < num_of_digit; i++) {
		cout << (temp / base) % 16;
		temp = temp % base;
		base = base / 16;
	}
	cout << dec;
	cout << resetiosflags(ios::uppercase);
}

int main()
{
	char temp_char = 0, file_name[260] = { 0 }, char_col[16] = { 0 };
	int count = 0;
	print_reminder();
	cin >> file_name;

	ifstream in_file;
	in_file.open(file_name, ios::in | ios::binary);
	if (in_file.is_open() == 0) {
		cout << "输入文件" << file_name << "打开失败!" << endl;
		return -1;
	}

	in_file.read(&temp_char, 1);
	while (in_file.fail() != 1) {
		if (count % 16 == 0) {
			print_hex_number(count, 8);
			cout << ":  ";
		}

		if (count % 16 == 8) {
			cout << "- ";
		}

		char_col[count % 16] = temp_char;
		print_hex_number(temp_char, 2);
		cout << " ";

		count++;

		if (count % 16 == 0) {
			cout << " ";
			for (int i = 0; i < 16; i++) {
				if (char_col[i] >= 33 && char_col[i] <= 126)
					cout << char_col[i];
				else
					cout << ".";
			}
			cout << endl;
		}

		in_file.read(&temp_char, 1);
	}

	for (int i = 0; i < 16 - count % 16; i++) {
		cout << "   ";
	}
	if (count % 16 != 0 && count % 16 <= 8) {
		cout << "  ";
	}
	cout << " ";
	for (int i = 0; i < count % 16; i++) {
		if (char_col[i] >= 33 && char_col[i] <= 126)
			cout << char_col[i];
		else
			cout << ".";
	}
	cout << endl;

	in_file.close();

	return 0;
}