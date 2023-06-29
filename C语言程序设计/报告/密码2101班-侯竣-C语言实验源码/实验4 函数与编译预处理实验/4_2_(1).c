#include <stdio.h>
long long sum_fac(int n);
int main(void)
{
    int k;
    for (k = 1; k <= 20; k++)
        printf("k=%d\tthe sum is %lld\n", k, sum_fac(k));
    return 0;
}
long long sum_fac(int n)
{
    //修改为递归
    long long frc = 1;
    if(n==1)
        return 1;
    else
        for(int i=1;i<=n;i++)
            frc *= i;
    return frc + sum_fac(n-1);
}