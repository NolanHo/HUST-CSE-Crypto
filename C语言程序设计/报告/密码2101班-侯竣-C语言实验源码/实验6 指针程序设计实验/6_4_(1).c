#include<stdio.h>

int main(int argc, char *argv[]){
    //arh[0] 是程序名
    for(int i = 1; i < argc; i++){
        printf("argv[%d] = %s\n", i, argv[i]);
    }
    return 0;
}