/* 2154146 吴金轩 计科1班 */
#include <iostream>
#include <cstdlib>
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

int strlen_tj(const char* s1)
{
	const char* p = NULL;
	for (p = s1; *p != '\0'; p++);
	return (p - s1);
}

bool judge_examined_stu_no(const char* const examined_stu_info)
{
	bool right_or_wrong = 1;

	if (strcmp_tj(examined_stu_info, "all")) {
		right_or_wrong = 1;
	}
	else if (strlen_tj(examined_stu_info) != 7) {
		cout << "要检查的学号不是7位" << endl;
		right_or_wrong = 0;
	}
	else {
		for (int i = 0; i < 7; i++) {
			if (examined_stu_info[i] < '0' || examined_stu_info[i] > '9') {
				cout << "要检查的学号不是7位数字" << endl;
				right_or_wrong = 0;
				break;
			}
		}
	}

	return right_or_wrong;
}

bool judge_matched_stu_no(const char* const examined_stu_info, const char* const matched_stu_info)
{
	bool right_or_wrong = 1;

	if (strcmp_tj(examined_stu_info, "all") && !strcmp_tj(matched_stu_info, "all")) {
		cout << "检查学号是all，匹配学号必须是all" << endl;
		right_or_wrong = 0;
	}
	else if (strcmp_tj(matched_stu_info, "all")) {
		right_or_wrong = 1;
	}
	else if (strlen_tj(matched_stu_info) != 7) {
		cout << "要匹配的学号不是7位" << endl;
		right_or_wrong = 0;
	}
	else {
		for (int i = 0; i < 7; i++) {
			if (matched_stu_info[i] < '0' || matched_stu_info[i] > '9') {
				cout << "要匹配的学号不是7位数字" << endl;
				right_or_wrong = 0;
				break;
			}
		}
	}

	return right_or_wrong;
}

bool judge_file_name(const char* const file_name)
{
	bool right_or_wrong = 1;

	if (strlen_tj(file_name) > 32) {
		cout << "源程序文件名超过了32字节" << endl;
		right_or_wrong = 0;
	}

	return right_or_wrong;
}

int judge_similarity(const char* const similarity)
{
	int simi_num = 0;

	simi_num = atoi(similarity);
	if (simi_num < 60 || simi_num>100) {
		simi_num = 80;
	}

	return simi_num;
}

bool judge_output_file(const char* const output_file_name)
{
	bool right_or_wrong = 1;

	if (strlen_tj(output_file_name) > 32) {
		cout << "输出结果文件名超过了32字节" << endl;
		right_or_wrong = 0;
	}

	return right_or_wrong;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int usage(const char* const procname)
{
	cout << "Usage: " << procname << " 要检查的学号/all 匹配学号/all 源程序名/all 相似度阀值(60-100) 输出(filename/screen)" << endl << endl;
	cout << "e.g. : " << procname << " 2159999 2159998 all       80 screen" << endl;
	cout << "       " << procname << " 2159999 all     14-b1.cpp 75 result.txt" << endl;
	cout << "       " << procname << " all     all     14-b2.cpp 80 check.dat" << endl;
	cout << "       " << procname << " all     all     all       85 screen" << endl;

	return 0;
}

int main(int argc, char *argv[])
{
	if (argc != 6) {
		usage(argv[0]);
	}
	else if (judge_examined_stu_no(argv[1]) && judge_matched_stu_no(argv[1], argv[2]) && judge_file_name(argv[3]) && judge_output_file(argv[5])) {
		cout << "参数检查通过" << endl;
		cout << "检查学号：" << argv[1] << endl;
		cout << "匹配学号：" << argv[2] << endl;
		cout << "源文件名：" << argv[3] << endl;
		cout << "匹配阈值：" << judge_similarity(argv[4]) << endl;
		cout << "输出目标：" << argv[5] << endl;
	}

	return 0;
}