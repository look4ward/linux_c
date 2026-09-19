#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person{
    char name;
    int age;
};

int main(void) {
    printf("%zu\n",sizeof(struct person));
    return 0;
}
