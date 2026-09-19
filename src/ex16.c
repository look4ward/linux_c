#include <stdio.h>
//引用该库调用assert函数
#include <assert.h>
//引用该库调用malloc（）和free（）
#include <stdlib.h>
//调用strdup（）
#include <string.h>

//定义一个名称为person的结构体，成员有......
struct Person {
    char *name; int age;
    int height;
    int weight;
};

//定义一个函数，返回值是结构体指针，参数是......
struct Person *Person_create(char *name, int age, int height, int weight)
{
//使用malloc函数在内存里开辟一块大小和结构体相等的空间，who指针指向这片内存
    struct Person *who = malloc(sizeof(struct Person));
//assert（）判断表达式是否为0，为0则输出错误标志并终止程序，非0则正常运行
    assert(who != NULL);
//使用->来引用结构体的成员
    who->name = strdup(name);
    who->age = age;
    who->height = height;
    who->weight = weight;

    return who;
}

void Person_destroy(struct Person *who)
{
    assert(who != NULL);
//释放who->name指针指向的空间
    free(who->name);
//释放who指针指向的空间
    free(who);
}

void Person_print(struct Person *who)
{
    printf("Name: %s\n", who->name);
    printf("\tAge: %d\n", who->age);
    printf("\tHeight: %d\n", who->height);
    printf("\tWeight: %d\n", who->weight);
}

int main(int argc, char *argv[])
{
    // make two people structures
    struct Person *joe = Person_create(
            "Joe Alex", 32, 64, 140);

    struct Person *frank = Person_create(
            "Frank Blank", 20, 72, 180);

    // print them out and where they are in memory
    printf("Joe is at memory location %p:\n", joe);
    Person_print(joe);

    printf("Frank is at memory location %p:\n", frank);
    Person_print(frank);

    // make everyone age 20 years and print them again
    joe->age += 20;
    joe->height -= 2;
    joe->weight += 40;
    Person_print(joe);

    frank->age += 20;
    frank->weight += 20;
    Person_print(frank);

    // destroy them both so we clean up
    Person_destroy(joe);
    Person_destroy(frank);

    return 0;
}
