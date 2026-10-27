/* 2154146 吴金轩 计科1班 */
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

struct student {
	int no;			//学号，不考虑0开头
	char name[9];	//姓名，最长4个汉字（无生僻字，均为双字节汉字）
	int score;		//成绩，不考虑小数点
	int rank;		//名次
};

void bubble_sort_grade(struct student* p, int num_of_stu)
{
	int i = 0, j = 0;
	struct student temp_stu;
	for (i = 0; i < num_of_stu; i++) {
		for (j = num_of_stu - 1; j >= i + 1; j--) {
			if (p[j].score > p[j - 1].score) {
				temp_stu = p[j];
				p[j] = p[j - 1];
				p[j - 1] = temp_stu;
			}
		}

		for (j = i; p[j].score == p[j - 1].score && p[j].no < p[j - 1].no; j--) {
			temp_stu = p[j];
			p[j] = p[j - 1];
			p[j - 1] = temp_stu;
		}
	}

	p[0].rank = 1;
	for (i = 1; i < num_of_stu; i++) {
		if (p[i].score == p[i - 1].score)
			p[i].rank = p[i - 1].rank;
		else
			p[i].rank = i + 1;
	}
}

int main()
{
	struct student* p;
	int num_of_stu = 0, i = 0;
	ifstream infile;
	
	infile.open("student.txt", ios::in);
	if (!infile.is_open()) {
		cout << "打开文件失败" << endl;
		return -1;
	}
	
	infile >> num_of_stu;
	p = new(nothrow) student[num_of_stu];
	if (p == NULL) {
		cout << "申请空间失败" << endl;
		return -1;
	}
	
	for (i = 0; i < num_of_stu; i++) {
		infile >> p[i].no >> p[i].name >> p[i].score;
	}
	
	bubble_sort_grade(p, num_of_stu);
	for (i = 0; i < num_of_stu; i++) {
		cout << p[i].no << " " << p[i].name << " " << p[i].score << " " << p[i].rank << endl;
	}

	delete[]p;
	infile.close();
	return 0;
}
