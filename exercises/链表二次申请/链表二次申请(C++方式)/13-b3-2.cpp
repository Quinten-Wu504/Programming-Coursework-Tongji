/* 2154146 吴金轩 计科1班 */
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

struct student {
	int no;			//学号，不考虑0开头
	char name[9];	//姓名，最长4个汉字（无生僻字，均为双字节汉字）
	int score;		//成绩，不考虑小数点
	struct student* next;
};

int main()
{
	struct student* p = NULL, * head = NULL;
	int temp_no = 0;
	ifstream infile;

	infile.open("list.txt", ios::in);
	if (!infile.is_open()) {
		cout << "打开文件失败" << endl;
		return -1;
	}

	infile >> temp_no;

	while (temp_no != 9999999) {
		if (p == NULL) {
			p = new(nothrow) student;
			head = p;
		}
		else if (p != NULL) {
			p->next = new(nothrow) student;
			p = p->next;
		}

		if (p == NULL) {
			cout << "申请空间失败" << endl;
			return -1;
		}
		
		p->no = temp_no;
		infile >> p->name >> p->score;
		infile >> temp_no;
	}

	p->next = NULL;

	for (p = head; p != NULL; p = p->next) {
		cout << p->no << " " << p->name << " " << p->score << endl;
	}

	p = head;

	while (p) {
		head = p->next;
		delete p;
		p = head;
	}
	infile.close();

	return 0;
}
