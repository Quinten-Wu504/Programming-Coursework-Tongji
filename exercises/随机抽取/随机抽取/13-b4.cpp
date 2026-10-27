/* 2154146 吴金轩 计科1班 */
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

struct student {
	int no;
	char name[12];
	char school[15];
	struct student* next;
};

void delete_node(student* p_front, student* head) {
	student* temp = NULL;
	if (p_front->next != NULL) {
		temp = p_front->next;
		p_front->next = temp->next;
	}
	else if (p_front->next == NULL) {
		temp = head;
		head = temp->next;
	}
	delete temp;
}

int main()
{
	srand((unsigned int)(time(0)));

	struct student* p = NULL, * head = NULL;
	int num_of_enroll = 0, num_of_apply = 0, i = 0, j = 0;
	ifstream infile;
	ofstream outfile;

	infile.open("stulist.txt", ios::in);
	outfile.open("result.txt", ios::out);
	if (!infile.is_open()) {
		cout << "打开输入文件失败" << endl;
		return -1;
	}
	if (!outfile.is_open()) {
		cout << "打开输出文件失败" << endl;
		infile.close();
		return -1;
	}

	infile >> num_of_enroll >> num_of_apply;

	for (i = 0; i < num_of_apply; i++) {
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

		infile >> p->no >> p->name >> p->school;
	}

	p->next = NULL;
	p = head;

	for (j = 0; j < rand() % 1000; j++) {
		p = p->next;
	}
	outfile << p->next->no << " " << p->next->name << " " << p->next->school << endl;
	delete_node(p, head);

	for (i = 1; i < num_of_enroll; i++) {
		for (j = 0; j < rand() % 1000; j++) {
			if (p->next != NULL)
				p = p->next;
			else
				p = head;
		}
		outfile << p->next->no << " " << p->next->name << " " << p->next->school << endl;
		delete_node(p, head);
	}

	p = head;

	while (p) {
		head = p->next;
		delete p;
		p = head;
	}
	infile.close();
	outfile.close();

	return 0;
}