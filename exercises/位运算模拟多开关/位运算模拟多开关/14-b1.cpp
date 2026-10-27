/* 2154146 吴金轩 计科1班 */
#include <iostream>
using namespace std;

bool strcmp_tj(const char* s1, const char* s2)
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

void get_command(int* p_num_of_switch, int* set_on_or_off)
{
	char switch_num = 0, command[100] = { 0 };
	const char switch_command[2][4] = { "ON","OFF" };
	
	cin >> switch_num;
	if (switch_num >= 'a' && switch_num <= 'z') {
		switch_num = switch_num + 'A' - 'a';
	}
	
	cin >> command;
	for (int i = 0; command[i] != '\0'; i++) {
		if (command[i] >= 'a' && command[i] <= 'z') {
			command[i] = command[i] + 'A' - 'a';
		}
	}
	
	if (switch_num >= 'A' && switch_num <= 'J')
		*p_num_of_switch = int(switch_num - 'A' + 1);
	else if (switch_num == 'Q')
		*p_num_of_switch = 11;
	else
		*p_num_of_switch = -1;

	for (int i = 0; i < 2; i++) {
		if (strcmp_tj(command, switch_command[i])) {
			if (i == 0)
				*set_on_or_off = 1;
			else
				*set_on_or_off = 0;
			break;
		}
		else
			*set_on_or_off = -1;
	}
}

void set_on_off_switch(short* p_on_off_switch, int num_of_switch, bool set_on_or_off)
{
	short set_var = 1;
	for (int i = 0; i < num_of_switch - 1; i++) {
		set_var *= 2;
	}

	if (set_on_or_off) {
		*p_on_off_switch = *p_on_off_switch | set_var;
	}
	else {
		set_var = ~set_var;
		*p_on_off_switch &= set_var;
	}
}

void print_switch_status(short on_off_switch)
{
	short temp_switch = 1;
	const char switch_char[] = "ABCDEFGHIJ";

	for (int i = 0; i < 10; i++) {
		cout << switch_char[i] << "   ";
	}
	cout << endl;

	for (int i = 0; i < 10; i++) {
		temp_switch = 1;
		for (int j = 0; j < i; j++)
			temp_switch *= 2;

		if (on_off_switch & temp_switch)
			cout << "ON  ";
		else
			cout << "OFF ";
	}
	cout << endl << endl;
}

void print_hex_num(short dec_num) {
	short temp_num = dec_num;
	cout << "0";
	cout << hex << (dec_num >> 8);
	temp_num &= 240;
	cout << hex << (temp_num >> 4);
	temp_num = dec_num;
	temp_num &= 15;
	cout << hex << temp_num << endl;
	cout << dec;
}

int main()
{
	short on_off_switch = 0;
	char input_reminder[62] = "请以(\"A On / J Off\"形式输入，输入\"Q on / off\"退出)";
	int num_of_switch = 0, set_on_or_off = 0;
	cout << "初始状态：0x";
	print_hex_num(on_off_switch);
	print_switch_status(on_off_switch);

	while (1) {
		cout << input_reminder << endl;
		get_command(&num_of_switch, &set_on_or_off);
		if (num_of_switch == -1 || set_on_or_off == -1) {
			num_of_switch = 0;
			set_on_or_off = 0;
			continue;
		}
		else if (num_of_switch >= 1 && num_of_switch <= 10) {
			set_on_off_switch(&on_off_switch, num_of_switch, set_on_or_off);
			cout << "当前状态：0x";
			print_hex_num(on_off_switch);
			print_switch_status(on_off_switch);
		}
		else if (num_of_switch == 11) {
			break;
		}
	}
	
	return 0;
}