/* 2154146 吴金轩 计科1班 */
#include <iostream>
#include <iomanip>
using namespace std;

struct parameter {
	char p[5];
	char descrip[21];
	int num_of_p;
	int lower_bound;
	int upper_bound;
	int default_val;
	int value = default_val;
};

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

int length_of_num(int num)
{
	int i = 0;
	int div = 1;

	if (num == 0) {
		i = 1;
	}
	else {
		for (i = 0; num / div != 0; i++) {
			div *= 10;
		}
	}
	
	return i;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int usage(const char* const procname, parameter param[])
{
	cout << "Usage: " << procname << " ";
	for (int i = 0; param[i].p[0] != '\0'; i++) {
		cout << "[-" << param[i].p;
		if (param[i].descrip[0] != '\0') {
			cout << " " << param[i].descrip;
		}
		cout << "] ";
	}
	cout << "IP地址" << endl;
	cout << "       " << "=====================================" << endl;
	cout << "       " << " 参数 附加参数 范围           默认值 " << endl;
	cout << "       " << "=====================================" << endl;

	cout << setiosflags(ios::left);
	for (int i = 0; param[i].p[0] != '\0'; i++) {
		cout << "        -" << setw(4) << param[i].p << setw(9) << param[i].num_of_p;
		cout << "[" << param[i].lower_bound << ".." << param[i].upper_bound << "]";
		for (int j = 0; j < (15 - 4 - length_of_num(param[i].lower_bound) - length_of_num(param[i].upper_bound)); j++) {
			cout << " ";
		}
		cout << param[i].default_val << endl;
	}
	cout << setiosflags(ios::right);

	cout << "       " << "=====================================" << endl;

	return 0;
}

bool check_IP(const char* char_IP) 
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
					if (num_sub_IP[i] < 0 || num_sub_IP[i]>255) {
						mark_IP = 0;
						break;
					}
				}

			}
		}
		else
			mark_IP = 0;
	}

	return mark_IP;
}

bool match_requirement(parameter *param, const char* argv_char)
{
	bool mark_match = 1;

	if (param->num_of_p != 0) {
		if (argv_char[0] == '-') {
			mark_match = 0;
		}
		else {
			int getin_int = atoi(argv_char);
			mark_match = 1;
			if (getin_int < param->lower_bound || getin_int > param->upper_bound)
				param->value = param->default_val;
			else
				param->value = getin_int;
		}
	}
	else {
		mark_match = 1;
		param->value = 1;
	}

	return mark_match;
}

bool check_param(parameter param[], int argc, char*argv[])
{
	bool check_result = 0;
	int param_num = 0;
	for (param_num = 0; param[param_num].p[0] != '\0'; param_num++);

	for (int i = 1; i < argc - 1; i++) {
		int no_of_param = -1;

		if (argv[i][0] != '-') {
			check_result = 0;
			cout << "参数" << argv[i] << "不是以-开头的合法参数" << endl;
			break;
		}
		else {
			for (int j = 0; j < param_num; j++) {
				if (strcmp_tj(&argv[i][1], param[j].p)) {
					no_of_param = j;
					break;
				}
			}
			if (no_of_param != -1) {
				if (i != argc - 2) {
					if (match_requirement(&param[no_of_param], argv[i + 1])) {
						check_result = 1;
						if (param[no_of_param].num_of_p)
							i++;
					}
					else {
						check_result = 0;
						cout << "参数" << argv[i] << "没有后续参数" << endl;
						break;
					}
				}
				else {
					if (match_requirement(&param[no_of_param], "-")) {
						check_result = 1;
						if (param[no_of_param].num_of_p)
							i++;
					}
					else {
						check_result = 0;
						cout << "参数" << argv[i] << "没有后续参数" << endl;
						break;
					}
				}
			}
			else {
				check_result = 0;
				cout << "参数" << argv[i] << "不存在" << endl;
				break;
			}
		}
	}

	return check_result;
}

void print_result(parameter param[], const char *string_IP)
{
	cout << "参数检查通过" << endl;

	cout << setiosflags(ios::left);
	for (int i = 0; param[i].p[0] != '\0'; i++) {
		cout << "-" << setw(2) << param[i].p << "参数：" << param[i].value << endl;
	}
	cout << setiosflags(ios::right);

	cout << "IP地址：" << string_IP << endl;
}

int main(int argc, char* argv[])
{
	parameter param[] = { {"l", "大小", 1, 32, 64000, 64},
						  {"n", "数量", 1, 1, 1024, 4},
						  {"t", "", 0, 0, 1, 0},
						  {"\0", "", 0, 0, 0, 0} };

	if (argc == 1) {
		usage(argv[0], param);
	}
	else if (!check_IP(argv[argc - 1])) {
		cout << "IP地址错误" << endl;
	}
	else if (argc - 1 == 1) {
		print_result(param, argv[argc - 1]);
	}
	else if (check_param(param, argc, argv)) {
		print_result(param, argv[argc - 1]);
	}

	return 0;
}