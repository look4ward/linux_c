//使用指针来处理命令行参数，就像处理names那样

#include <stdio.h>

int main(int argc, char *argv[]){
    int i = 0;
    for(i = 0; i < argc; i++){
        printf("argv[%d] is %s\n", i, *(argv + i));
    }
    return 0;
}
