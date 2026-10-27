/* 2154146 吴金轩 计科 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

const char* const parameter[2] = { "--infile", "--outfile" };

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
	printf("Usage: %s --infile 原始文件[--outfile hex格式文件]", procname);
#ifdef __linux__
	printf("\n");
#else
	printf("\r\n");
#endif
	printf("        ");
	printf("%s --infile a.docx", procname);
#ifdef __linux__
	printf("\n");
#else
	printf("\r\n");
#endif
	printf("        ");
	printf("%s --infile a.docx --outfile a.hex", procname);
#ifdef __linux__
	printf("\n");
#else
	printf("\r\n");
#endif
	return 0;
}

void print_hex_number(unsigned int dec_num, int num_of_digit)
{
	unsigned int base = 1;
	unsigned int temp = dec_num;
	for (int i = 0; i < num_of_digit - 1; i++) {
		base *= 16;
	}
	
	for (int i = 0; i < num_of_digit; i++) {
		printf("%x", (temp / base) % 16);
		temp = temp % base;
		base = base / 16;
	}
}

int check_parameter(int argc, char* argv[])
{
	int mark_check = 0;
	if (argc == 3) {
		if (strcmp_tj(argv[1], parameter[0]))
			mark_check = 1;
	}
	else if (argc == 5) {
		if (strcmp_tj(argv[1], parameter[0]) && strcmp_tj(argv[3], parameter[1]))
			mark_check = 1;
		else if (strcmp_tj(argv[1], parameter[1]) && strcmp_tj(argv[3], parameter[0]))
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
			printf("输入文件%s打开失败!", argv[2]);
#ifdef __linux__
			printf("\n");
#else
			printf("\r\n");
#endif
			mark_check = 0;
		}
	}
	else if (argc == 5) {
		if (strcmp_tj(argv[1], parameter[0]) && strcmp_tj(argv[3], parameter[1])) {
			*p_infile = fopen(argv[2], "rb");
			*p_outfile = freopen(argv[4], "wb", stdout);
			if (*p_infile == NULL) {
				fprintf(stderr, "输入文件%s打开失败!", argv[2]);
#ifdef __linux__
				fprintf(stderr, "\n");
#else
				fprintf(stderr, "\r\n");
#endif
				if (*p_outfile != NULL) {
					fclose(*p_outfile);
				}
				mark_check = 0;
			}
			else {
				if (*p_outfile == NULL) {
					fprintf(stderr, "输出文件%s打开失败!", argv[4]);
#ifdef __linux__
					fprintf(stderr, "\n");
#else
					fprintf(stderr, "\r\n");
#endif
					fclose(*p_infile);
					mark_check = 0;
				}
			}
		}
		else if (strcmp_tj(argv[1], parameter[1]) && strcmp_tj(argv[3], parameter[0])) {
			*p_infile = fopen(argv[4], "rb");
			*p_outfile = freopen(argv[2], "wb", stdout);
			if (*p_infile == NULL) {
				fprintf(stderr, "输入文件%s打开失败!", argv[2]);
#ifdef __linux__
				fprintf(stderr, "\n");
#else
				fprintf(stderr, "\r\n");
#endif
				if (*p_outfile != NULL) {
					fclose(*p_outfile);
				}
				mark_check = 0;
			}
			else {
				if (*p_outfile == NULL) {
					fprintf(stderr, "输出文件%s打开失败!", argv[4]);
#ifdef __linux__
					fprintf(stderr, "\n");
#else
					fprintf(stderr, "\r\n");
#endif
					fclose(*p_infile);
					mark_check = 0;
				}
			}
		}
	}

	return mark_check;
}

int main(int argc, char* argv[])
{
	char char_col[16] = { 0 };
	int count = 0;
	if ((argc != 5 && argc != 3) || !check_parameter(argc, argv)) {
		usage(argv[0]);
	}
	else {
		FILE* infile;
		FILE* outfile;
		if (get_file_name(argc, argv, &infile, &outfile)) {
			char temp_char = 0;
			fread(&temp_char, 1, 1, infile);
			while (!feof(infile)) {
				if (count % 16 == 0) {
					print_hex_number(count, 8);
					printf("  ");
				}

				if (count % 16 == 8) {
					printf("- ");
				}

				char_col[count % 16] = temp_char;
				print_hex_number(temp_char, 2);
				printf(" ");

				count++;

				if (count % 16 == 0) {
					printf("    ");
					for (int i = 0; i < 16; i++) {
						if (char_col[i] >= 33 && char_col[i] <= 126)
							printf("%c", char_col[i]);
						else
							printf(".");
					}
#ifdef __linux__
					printf("\n");
#else
					printf("\r\n");
#endif
				}

				fread(&temp_char, 1, 1, infile);
			}

			if (count % 16 != 0) {
				for (int i = 0; i < 16 - count % 16; i++) {
					printf("   ");
				}
				if (count % 16 != 0 && count % 16 <= 8) {
					printf("  ");
				}
				printf("    ");
				for (int i = 0; i < count % 16; i++) {
					if (char_col[i] >= 33 && char_col[i] <= 126)
						printf("%c", char_col[i]);
					else
						printf(".");
				}

#ifdef __linux__
				printf("\n");
#else
				printf("\r\n");
#endif
			}

			fclose(infile);
			if (argc == 5) {
				fclose(outfile);
			}
		}
	}

	return 0;
}