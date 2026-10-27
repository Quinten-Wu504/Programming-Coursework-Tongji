#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    FILE* fp;
    fp = fopen("out.txt", "w");

    fprintf(fp, "ABC\0\x61\x62\x63\n");

    fclose(fp);

    return 0;
}

