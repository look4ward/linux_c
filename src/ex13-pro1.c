#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("You should input only one arguement\n");
        return 1;
    }
    int i = 0;
    size_t size_argv = strlen(argv[1]);
    printf("size_argv = %zu\n",size_argv);
    for(i = 0; argv[1][i] != '\0'; i++){
        if(65 <= argv[1][i] && argv[1][i] <= 90){
            argv[1][i] = argv[1][i] + 32;
        }
    }
    for(i = 0;i < size_argv; i++){
        printf("%c",argv[1][i]);
    }    
    printf("\n");
    return 0;
}
