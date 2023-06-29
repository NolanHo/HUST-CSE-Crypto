#include<stdio.h>
#define SUM (a+b) //加上括号
#define DIF (a-b)
#define SWAP(a,b)  {int t; t=a; a=b; b=t;} //这样定义交换函数
int main() 
{
    int a,b;
    printf("Input two integers a, b:");
    scanf("%d%d", &a,&b);
    printf("\nSUM=%d\n the difference between square of a and square of b is:%d",SUM, SUM*DIF);
    SWAP(a,b);
    printf("\nNow a=%d,b=%d\n",a,b);
    return 0;
}