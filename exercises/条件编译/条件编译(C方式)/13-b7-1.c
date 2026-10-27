/* 2154146 吴金轩 计科1班 */
#include <stdio.h>

int main()
{
    /* 三个条件编译的相互位置可互换（例：目前#if满足是输出VS2022，允许先换为Linux）*/
#if _MSC_VER >= 1930
    printf("VS2022\n");
#elif __GNUC__ == 9 && __GNUC_MINOR__ == 2 && __GNUC_PATCHILEVEL__ == 0
    printf("Dev\n");
#elif __GNUC__ == 8 && __GNUC_MINOR__ == 5 && __GNUC_PATCHILEVEL__ == 0
    printf("Linux\n");
#endif

    return 0;
}
