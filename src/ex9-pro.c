#include <stdio.h>

char *name = "aaaa";

int main(void)
{
    // 把 name 当作一个 int 使用
    int *name_int = (int *)name;

    // 读：4 个 'a' 拼成的整数
    printf("as int (read):  %d  0x%08x\n", *name_int, (unsigned)*name_int);

    // 写：赋一个整数，会覆盖这 4 个字节
    *name_int = 0x44434241;   // 小端机器上 → 内存变成 'A' 'B' 'C' 'D'
    printf("name now: %s\n", name);   // 注意：没有 '\0'，可能打印乱码！

    // 也可以直接写一个整数，让字节正好拼出 "Zed\0"
    // 'Z'=0x5A, 'e'=0x65, 'd'=0x64, '\0'=0x00
    // 小端：低字节在前 → 0x0064655A
    *name_int = 0x0064655A;
    printf("name now: %s\n", name);   // "Zed"
    return 0;
}
