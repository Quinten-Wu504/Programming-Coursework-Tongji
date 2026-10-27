/* 2154146 吴金轩 计科 */
/* 1950617 罗楠 2152768 袁锐声 2250951 陈麒安 2251928 项文涛 2251265 苏传州 */
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
	printf("Usage : %s --infile hex格式文件 --outfile bin格式文件", procname);
#ifdef __linux__
	printf("\r");
#else
	printf("\r\n");
#endif
	printf("        ");
	printf("%s 15-b4-demo.exe --infile a.hex --outfile a.bin", procname);
#ifdef __linux__
	printf("\r");
#else
	printf("\r\n");
#endif
	return 0;
}

int hex_to_num(char hex_num)
{
	int num = 0;
	switch (hex_num) {
	case '0':
		num = 0;
		break;
	case '1':
		num = 1;
		break;
	case '2':
		num = 2;
		break;
	case '3':
		num = 3;
		break;
	case '4':
		num = 4;
		break;
	case '5':
		num = 5;
		break;
	case '6':
		num = 6;
		break;
	case '7':
		num = 7;
		break;
	case '8':
		num = 8;
		break;
	case '9':
		num = 9;
		break;
	case 'a':
		num = 10;
		break;
	case 'b':
		num = 11;
		break;
	case 'c':
		num = 12;
		break;
	case 'd':
		num = 13;
		break;
	case 'e':
		num = 14;
		break;
	case 'f':
		num = 15;
		break;
	default:
		num = 99;
		break;
	}
	return num;
}

char hex_to_dec_num(char hex_num[])
{
	char dec_num = 0;
	for (int i = 0; hex_num[i] != '\0'; i++) {
		dec_num = dec_num * 16 + hex_to_num(hex_num[i]);
	}
	return dec_num;
}

int check_parameter(char* argv[])
{
	int mark_check = 0;
	
	if (strcmp_tj(argv[1], parameter[0]) && strcmp_tj(argv[3], parameter[1]))
		mark_check = 1;
	else if (strcmp_tj(argv[1], parameter[1]) && strcmp_tj(argv[3], parameter[0]))
		mark_check = 1;

	return mark_check;
}

int get_file_name(char* argv[], FILE** p_infile, FILE** p_outfile)
{
	int mark_check = 1;
	
	if (strcmp_tj(argv[1], parameter[0]) && strcmp_tj(argv[3], parameter[1])) {
		*p_infile = fopen(argv[2], "rb");
		*p_outfile = freopen(argv[4], "wb", stdout);
		if (*p_infile == NULL) {
			fprintf(stderr, "输入文件%s打开失败!", argv[2]);
			if (*p_outfile != NULL) {
				fclose(*p_outfile);
			}
			mark_check = 0;
		}
		else {
			if (*p_outfile == NULL) {
				fprintf(stderr, "输出文件%s打开失败!", argv[4]);
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
			if (*p_outfile != NULL) {
				fclose(*p_outfile);
			}
			mark_check = 0;
		}
		else {
			if (*p_outfile == NULL) {
				fprintf(stderr, "输出文件%s打开失败!", argv[4]);
				fclose(*p_infile);
				mark_check = 0;
			}
		}
	}

	return mark_check;
}

int main(int argc, char* argv[])
{
	char hex_char16[16][3] = { 0 }, temp_char = 0;
	int count = -1;

	if (argc != 5 || !check_parameter(argv)) {
		usage(argv[0]);
	}
	else {
		FILE* infile;
		FILE* outfile;

		if (get_file_name(argv, &infile, &outfile)) {
			while (1) {
				fseek(infile, 10, SEEK_CUR);
				count = -1;
				for (int i = 0; i < 16; i++) {
					if (i == 8) {
						fseek(infile, 2, SEEK_CUR);
					}
					fread(hex_char16[i], 3, 1, infile);
					hex_char16[i][2] = '\0';
					if (!((hex_char16[i][0] >= 48 && hex_char16[i][0] <= 57) || (hex_char16[i][0] >= 'a' && hex_char16[i][0] <= 'f'))) {
						count = i;
						break;
					}
					temp_char = hex_to_dec_num(hex_char16[i]);
					printf("%c", temp_char);
				}

				if (count == -1) {
					fseek(infile, 4, SEEK_CUR);
					fseek(infile, 16, SEEK_CUR);
					fread(&temp_char, 1, 1, infile);
					while (temp_char == 13 || temp_char == 10) {
						fread(&temp_char, 1, 1, infile);
					}
					fseek(infile, -1, SEEK_CUR);
				}
				else {
					break;
				}
			}

			fclose(infile);
			fclose(outfile);
		}
	}

	

	return 0;
}