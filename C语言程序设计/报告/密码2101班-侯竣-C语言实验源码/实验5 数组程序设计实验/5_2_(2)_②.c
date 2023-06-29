#include<stdio.h>
#define M 10
#define N 3
int main(void)
{
    int a[M], b[M]; /* 数组a存放圈中人的编号，数组b存放出圈人的编号 */
    int i, j, k; 
    for (i = 0; i < M; i++) /* 对圈中人按顺序编号1—M */
        a[i] = i + 1;
    for (i = M, j = 0; i > 1; i--)
    {
        for (k = 1; k <= N; k++){
            if(a[j]==0) k--; //如果a[j]已经出圈，k--, 再往前走一步
            if (++j > M - 1) j = 0; /* 最后一个人报数后第一个人接着报，形成一个圈 */
        }
        b[M - i] = j ? a[j - 1] : a[M - 1]; //b[M-i]存放出圈人的编号 
        if(j) 
            a[j-1]=0; //a[j-1]出圈
        else
            a[M-1]=0; //a[M-1]出圈
    }
    for (i = 0; i < M - 1; i++) /* 按次序输出出圈人的编号 */
        printf("%6d", b[i]);
    for(i=0;i<M-1;i++)
        if(a[i]!=0) printf("%6d",a[i]); /* 输出圈中最后一个人的编号 */
    return 0;
}