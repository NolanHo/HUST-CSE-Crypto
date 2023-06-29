#include <stdio.h>
#define mask 0x00000001
int main() {
    int num;
    scanf("%d",&num);
    char a[33]={0};
    for(int i=31;i>=0;i--){
        a[i]=(num&mask)+'0';
        num=num>>1;
    }
    printf("%s",a);  
    return 0;
}