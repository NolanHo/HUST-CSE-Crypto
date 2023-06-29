#include <math.h>       /*数学函数库的头文件*/
#include <stdio.h>
int main()
{
    long x,y;
    for(int i=1;i<100000;i++) //i未定义, 改为int i
    {
        x=sqrt(i+100);  /*sqrt是求平方根的函数*/
        y=sqrt(i+268);
        if((x*x==i+100)&&(y*y==i+268)) //=改为==
            printf("\n%d",i);
    }
    return 0;
}