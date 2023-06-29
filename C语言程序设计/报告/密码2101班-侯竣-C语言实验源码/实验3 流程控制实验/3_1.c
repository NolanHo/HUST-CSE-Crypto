/* 实验3-1改错题程序：合数判断器*/
#include <stdio.h>
int main()
{
    int i, x, k, flag = 0;
    printf("本程序判断合数，请输入大于1的整数，以Ctrl+Z结束\n");
    while (scanf("%d", &x) != EOF){
        flag = 0; //加上flag=0
        for (i = 2, k = x >> 1; i <= k; i++)
            if (!(x % i)){ //加上括号
                flag = 1;
                break;
            }
        if (flag == 1)
            printf("%d是合数", x);
        else
            printf("%d不是合数", x);
    }
    return 0;
}