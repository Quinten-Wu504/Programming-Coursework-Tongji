/* 2154146 吴金轩 计科1班 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct student {
	int no;			//学号，不考虑0开头
	char name[9];	//姓名，最长4个汉字（无生僻字，均为双字节汉字）
	int score;		//成绩，不考虑小数点
	struct student* next;
};

int main()
{
	struct student* p = NULL, * head = NULL;
	FILE* infile;
	int temp_no = 0;

	infile = fopen("list.txt", "r");
	if (infile == NULL) {
		printf("打开文件失败\n");
		return -1;
	}

	fscanf(infile, "%d", &temp_no);
	while (temp_no != 9999999) {
		if (p == NULL) {
			p = (struct student*)calloc(1, sizeof(struct student));
			head = p;
		}
		else if (p != NULL) {
			p->next = (struct student*)calloc(1, sizeof(struct student));
			p = p->next;
		}
		if (p == NULL) {
			printf("申请空间失败\n");
			return -1;
		}
		p->no = temp_no;
		fscanf(infile, "%s %d", p->name, &(p->score));
		fscanf(infile, "%d", &temp_no);
	}

	p->next = NULL;

	for (p = head; p != NULL; p = p->next) {
		printf("%d %s %d\n", p->no, p->name, p->score);
	}

	p = head;

	while (p) {
		head = p->next;
		free(p);
		p = head;
	}
	fclose(infile);

	return 0;
}
