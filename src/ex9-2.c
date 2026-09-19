/*验证打印字符串是在遇到第一个\0截止的*/
#include <stdio.h>
#include <string.h>

char name[4] = {'a','a','\0','a'};

int main(void)
{
    char buf[16];
    memset(buf, 'B', sizeof(buf));   // 全部填 'B'
    memcpy(buf, name, 4);            // 只拷 4 个字节，没带 '\0'

    // buf 现在是 "aaaaBBBBBBBBBBBB"，且 buf[15] 后也可能没 0
    // 但如果我们手动保证结尾有 0：
    buf[15] = '\0';
    printf("buf: %s\n", buf);        // "aaaaBBBBBBBBBBB"

    // 现在把 B 换成 0，看打印到哪里停
    memset(buf, 0, sizeof(buf));
    memcpy(buf, name, 4);
    printf("buf (后面全 0): %s\n", buf);   // 只打印 "aaaa"，因为 buf[4]=0
    return 0;
}
