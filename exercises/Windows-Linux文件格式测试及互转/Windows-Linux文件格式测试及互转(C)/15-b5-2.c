/* 2154146 吴金轩 计科 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

const char* const parameter[4] = { "--check", "--convert", "wtol", "ltow" };

int strcmp_tj(const char* s1, const char* s2)
{
	int same_or_not = 1;
	for (int i = 0; s1[i] != '\0' || s2[i] != '\0'; i++) {
		if (s1[i] != s2[i]) {
			same_or_not = 0;
			break;
		}
	}
	return same_or_not;
}

int usage(const char* const procname)
{
	printf("Usage : %s --check 文件名 | --convert { wtol|ltow } 源文件名 目标文件名", procname);
#ifdef __linux__
	printf("\r");
#else
	printf("\r\n");
#endif
	printf("        %s --check a.txt", procname);
#ifdef __linux__
	printf("\r");
#else
	printf("\r\n");
#endif
	printf("        %s --convert wtol a.win.txt a.linux.txt", procname);
#ifdef __linux__
	printf("\r");
#else
	printf("\r\n");
#endif
	printf("        %s --convert ltow a.linux.txt a.win.txt", procname);
#ifdef __linux__
	printf("\r");
#else
	printf("\r\n");
#endif
	return 0;
}

int check_parameter(int argc, char* argv[])
{
	int mark_check = 0;
	if (argc == 3) {
		if (strcmp_tj(argv[1], parameter[0]))
			mark_check = 1;
	}
	else if (argc == 5) {
		if (strcmp_tj(argv[1], parameter[1]) && (strcmp_tj(argv[2], parameter[2]) || strcmp_tj(argv[2], parameter[3])))
			mark_check = 1;
	}
	return mark_check;
}

int get_file_name(int argc, char* argv[], FILE** p_infile, FILE** p_outfile)
{
	int mark_check = 1;
	if (argc == 3) {
		*p_infile = fopen(argv[2], "rb");
		if (*p_infile == NULL) {
			printf("文件打开失败");
#ifdef __linux__
			printf("\r");
#else
			printf("\r\n");
#endif
			mark_check = 0;
		}
	}
	else if (argc == 5) {
		*p_infile = fopen(argv[3], "rb");
		*p_outfile = fopen(argv[4], "wb");
		if (*p_infile == NULL) {
			printf("文件打开失败");
#ifdef __linux__
			printf("\r");
#else
			printf("\r\n");
#endif
			if (*p_outfile != NULL) {
				fclose(*p_outfile);
			}
			mark_check = 0;
		}
		else {
			if (*p_outfile == NULL) {
				printf("文件打开失败");
#ifdef __linux__
				printf("\r");
#else
				printf("\r\n");
#endif
				fclose(*p_infile);
				mark_check = 0;
			}
		}
	}

	return mark_check;
}

void check_file_type(FILE** p_infile, int* p_mark_windows, int* p_mark_linux)
{
	char temp_char = 0;
	fread(&temp_char, 1, 1, *p_infile);
	while (!feof(*p_infile) && (*p_mark_linux != 1 || *p_mark_windows != 1)) {
		if (temp_char == '\n') {
			if (ftell(*p_infile) != 1) {
				fseek(*p_infile, -2, SEEK_CUR);
				fread(&temp_char, 1, 1, *p_infile);
				if (temp_char == '\r')
					*p_mark_windows = 1;
				else
					*p_mark_linux = 1;
				fread(&temp_char, 1, 1, *p_infile);
			}
			else
				*p_mark_linux = 1;

		}
		fread(&temp_char, 1, 1, *p_infile);
	}
}

void check_command(int mark_windows, int mark_linux)
{
	if (mark_windows == 1 && mark_linux == 0) {
		printf("Windows格式");
#ifdef __linux__
		printf("\r");
#else
		printf("\r\n");
#endif
	}
	else if (mark_windows == 0 && mark_linux == 1) {
		printf("Linux格式");
#ifdef __linux__
		printf("\r");
#else
		printf("\r\n");
#endif
	}
	else {
		printf("文件格式无法识别");
#ifdef __linux__
		printf("\r");
#else
		printf("\r\n");
#endif
	}
}

void convert_command(FILE** p_infile, FILE** p_outfile, char* argv[], int mark_windows, int mark_linux)
{
	char temp_char = 0;
	int num_0D = 0;

	if (strcmp_tj(argv[2], parameter[2])) {
		if (mark_windows == 1 && mark_linux == 0) {
			rewind(*p_infile);
			fseek(*p_infile, 0, SEEK_SET);
			fread(&temp_char, 1, 1, *p_infile);

			while (!feof(*p_infile)) {
				if (temp_char == '\r') {
					fread(&temp_char, 1, 1, *p_infile);
					if (temp_char == '\n') {
						fwrite(&temp_char, 1, 1, *p_outfile);
						num_0D++;
					}
					else if (!feof(*p_infile)) {
						fwrite("\r", 1, 1, *p_outfile);
						fwrite(&temp_char, 1, 1, *p_outfile);
					}
					else if (feof(*p_infile)) {
						fwrite("\r", 1, 1, *p_outfile);
						break;
					}
				}
				else {
					fwrite(&temp_char, 1, 1, *p_outfile);
				}

				fread(&temp_char, 1, 1, *p_infile);
			}

			printf("转换完成，去除%d个0x0D", num_0D);
#ifdef __linux__
			printf("\r");
#else
			printf("\r\n");
#endif
		}
		else {
			printf("文件格式无法识别");
#ifdef __linux__
			printf("\r");
#else
			printf("\r\n");
#endif
		}
	}
	else if (strcmp_tj(argv[2], parameter[3])) {
		if (mark_windows == 0 && mark_linux == 1) {
			rewind(*p_infile);
			fseek(*p_infile, 0, SEEK_SET);
			fread(&temp_char, 1, 1, *p_infile);
			while (!feof(*p_infile)) {
				if (temp_char == '\n') {
					fwrite("\r", 1, 1, *p_outfile);
					num_0D++;
				}

				fwrite(&temp_char, 1, 1, *p_outfile);
				fread(&temp_char, 1, 1, *p_infile);
			}

			printf("转换完成，加入%d个0x0D", num_0D);
#ifdef __linux__
			printf("\r");
#else
			printf("\r\n");
#endif
		}
		else {
			printf("文件格式无法识别");
#ifdef __linux__
			printf("\r");
#else
			printf("\r\n");
#endif
		}
	}
}

int main(int argc, char* argv[])
{
	if (((argc != 5 && argc != 3) || !check_parameter(argc, argv))) {
		usage(argv[0]);
	}
	else {
		FILE* infile;
		FILE* outfile;
		if (get_file_name(argc, argv, &infile, &outfile)) {
			int mark_windows = 0, mark_linux = 0;
			check_file_type(&infile, &mark_windows, &mark_linux);

			if (argc == 3)
				check_command(mark_windows, mark_linux);
			else if (argc == 5) {
				convert_command(&infile, &outfile, argv, mark_windows, mark_linux);
			}

			fclose(infile);
			if (argc == 5)
				fclose(outfile);
		}
	}
	return 0;
}
