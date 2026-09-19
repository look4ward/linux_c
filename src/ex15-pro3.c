//在其它程序中使用指针来代替数组访问
#include <stdio.h>

char name[4] = {'a','a','a','a'};

int main(int argc, char *argv[])
{
    int numbers[4] = {7};

    // first, print them out raw
    printf("numbers: %d %d %d %d\n",
            *numbers, *(numbers + 1),
            *(numbers + 2), *(numbers + 3));

    printf("name each: %c %c %c %c\n",
            *name, *(name + 1),
            *(name + 2), *(name + 3));

    printf("name: %s sizeof(name) is %lu\n", name, sizeof(name));

    // setup the numbers
    *numbers = 1;
    *(numbers + 1) = 2;
    *(numbers + 2) = 3;
    *(numbers + 3) = 4;

    // setup the name
    *name = 'Z';
    *(name + 1) = 'E';
    *(name + 2) = 'D';
    *(name + 3) = '\0';

    // then print them out initialized
    printf("numbers: %d %d %d %d\n",
            *numbers, *(numbers + 1),
            *(numbers + 2), *(numbers + 3));

    printf("name each: %c %c %c %c\n",
            *(name), *(name + 1),
            *(name + 2), *(name + 3));

    // print the name like a string
    printf("name: %s\n", name);

    // another way to use name
    char *another = "Zed";

    printf("another: %s\n", another);

    printf("another each: %c %c %c %c\n",
            *another, *(another + 1),
            *(another + 2), *(another + 3));

    return 0;
}
