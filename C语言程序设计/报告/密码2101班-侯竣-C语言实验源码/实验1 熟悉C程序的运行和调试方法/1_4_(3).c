#include <stdio.h>
int main()
{
    int count,max,x,t;
    printf("请输入一个正整数：");
    scanf("%d",&x);
    count=max=0;
    while(x)
    {
        t=x%10;
        if(t==0) //t=0改为t==0
            count++;
        if(t>max)
            max=t; //max=t改为max=t
        x=x/10;
    }
    printf("该数有%d个零，最大数字是%d\n",count,max);
    return 0;
}