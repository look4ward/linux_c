#include <stdio.h>

void print_arry_way_1(char **names, int *ages, int count){
    for(int i = 0; i < count; i++){
        printf("%s is %d years old.\n", *(names + i), *(ages + i));
    }
}

void printf_arry_way_2(char **cur_names,int *cur_ages,int count){
    for(int i = 0; i < count; i++){
        printf("%s is %d years old again.\n", *(cur_names + i), *(cur_ages + i));
    }
}
int main(int argc, char *argv[])
{
    // create two arrays we care about
    int ages[] = {23, 43, 12, 89, 2};
    char *names[] = {
        "Alan", "Frank",
        "Mary", "John", "Lisa"
    };

    // safely get the size of ages
    int count = sizeof(ages) / sizeof(int);
    int i = 0;

    // first way using indexing
    print_arry_way_1(names, ages, count);

    printf("---\n");

    // setup the pointers to the start of the arrays
    int *cur_age = ages;
    char **cur_name = names;

    // second way using pointers
    printf_arry_way_2(cur_name, cur_age, count);

    printf("---\n");

    // third way, pointers are just arrays

    for(cur_name = cur_name + count - 1, cur_age = cur_age + count - 1;
            cur_age >= ages;
            cur_name--, cur_age--)
    {
        printf("%s lived %d years so far.\n",
                *cur_name, *cur_age);
    }

    return 0;
}
