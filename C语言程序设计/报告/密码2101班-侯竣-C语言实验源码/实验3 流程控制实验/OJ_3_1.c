#include<stdio.h>
int main(){
    char c = getchar();
    int flag = 0;
    while (c!=EOF){
        if (c==' '){
            if (flag==0){
                putchar(c);
                flag=1;
            }
        }else{
            putchar(c);
            flag=0;
        }
        c=getchar();
    }
    
}