/* 实验3-1改错题程序：合数判断器*/
#include <stdio.h>
int main()
{
    int i, x, k;
    printf("本程序判断合数，请输入大于1的整数，以Ctrl+Z结束\n");
    while (scanf("%d", &x) != EOF){
        for (i = 2, k = x >> 1; i <= k && (x%i); i++); //去掉break, 加上&& (x%i)
        if (!(x%i) && x!=2)
            printf("%d是合数", x);
        else
            printf("%d不是合数", x);
    }
    return 0;
}