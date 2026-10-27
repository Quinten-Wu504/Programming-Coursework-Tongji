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
	struct student* p = NULL, * q = NULL, * head = NULL;
	FILE* infile;
	int temp_no = 0;

	infile = fopen("list.txt", "r");
	if (infile == NULL) {
		printf("打开文件失败\n");
		return -1;
	}

	fscanf(infile, "%d", &temp_no);
	while (temp_no != 9999999) {
		if (p != NULL)
			q = p;
		p = (struct student*)calloc(1, sizeof(struct student));
		if (p == NULL) {
			printf("申请空间失败\n");
			return -1;
		}
		p->no = temp_no;
		fscanf(infile, "%s %d", p->name, &(p->score));
		if (q != NULL)
			q->next = p;
		else
			head = p;
		fscanf(infile, "%d", &temp_no);
	}

	p->next = NULL;

	for (p = head; p != NULL; p = p->next) {
		printf("%d %s %d\n", p->no, p->name, p->score);
	}

	p = head;

	while (p) {
		q = p->next;
		free(p);
		p = q;
	}
	fclose(infile);

	return 0;
}