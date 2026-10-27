#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char p[10] = "123456789";
    p[11] = 'a';    //此句越界
    p[14] = 'A';    //此句越界
    p[15] = 'B';    //此句越界
    //p[11] = '\xcc'; //此句越界
    printf("addr:%p\n", p);
    for (int i = -4; i < 16; i++)
        //只有0-9是合理范围，其余都是越界读
        printf("%p:%02x\n", (p + i), p[i]);

    return 0;
}
