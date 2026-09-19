//将ex16.c程序改为不用指针和malloc的版本

#include <stdio.h>
//引用该库调用assert函数
#include <assert.h>
//引用该库调用malloc（）和free（）
#include <stdlib.h>
//调用strdup（）
#include <string.h>

//定义一个名称为person的结构体，成员有......
typedef struct {
    char *name; int age;
    int height;
    int weight;
}Person;

Person Person_create(char *name, int age, int height, int weight)
{
    Person who;
//assert（）判断表达式是否为0，为0则输出错误标志并终止程序，非0则正常运行
    assert(&who != NULL);
//使用->来引用结构体的成员
    who.name = name;
    who.age = age;
    who.height = height;
    who.weight = weight;

    return who;
}

void Person_print(Person who)
{
    printf("Name: %s\n", who.name);
    printf("\tAge: %d\n", who.age);
    printf("\tHeight: %d\n", who.height);
    printf("\tWeight: %d\n", who.weight);
}

int main(int argc, char *argv[])
{
    // make two people structures
    Person joe = Person_create(
            "Joe Alex", 32, 64, 140);

    Person frank = Person_create(
            "Frank Blank", 20, 72, 180);

    // print them out and where they are in memory
    printf("Joe is at memory location %p:\n", &joe);
    Person_print(joe);

    printf("Frank is at memory location %p:\n", &frank);
    Person_print(frank);

    // make everyone age 20 years and print them again
    joe.age += 20;
    joe.height -= 2;
    joe.weight += 40;
    Person_print(joe);

    frank.age += 20;
    frank.weight += 20;
    Person_print(frank);

    return 0;
}
