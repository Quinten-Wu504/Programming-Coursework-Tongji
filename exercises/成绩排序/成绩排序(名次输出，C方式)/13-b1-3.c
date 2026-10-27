/* 2154146 吴金轩 计科1班 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

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
	FILE* infile;
	int num_of_stu = 0, i = 0;

	infile = fopen("student.txt", "r");
	if (infile == NULL) {
		printf("打开文件失败\n");
		return -1;
	}
	
	fscanf(infile, "%d", &num_of_stu);
	p = (struct student*)calloc(num_of_stu, sizeof(struct student));
	if (p == NULL) {
		printf("申请空间失败\n");
		return -1;
	}
	
	for (i = 0; i < num_of_stu; i++) {
		fscanf(infile, "%d %s %d", &(p[i].no), p[i].name, &(p[i].score));
	}
	
	bubble_sort_grade(p, num_of_stu);
	
	for (i = 0; i < num_of_stu; i++) {
		printf("%d %s %d %d\n", p[i].no, p[i].name, p[i].score, p[i].rank);
	}
	
	free(p);
	fclose(infile);
	
	return 0;
}
