#include <stdio.h>
#define N 100
double mulx(double x, int n);
long fac(int n);
double XResult[N];
long long FResult[N]; //计算量最小, 使用数组存储
double sum(double x, int n)
{
    int i;
    double z = 1.0;
    for (i = 1; i <= n; i++)
    {
        z = z + mulx(x, i) / fac(i);
    }
    return z;
}
double mulx(double x, int n)
{
    if(n==1) 
        return XResult[n]=x;
    else 
        return XResult[n]=XResult[n-1]*x;
}
long fac(int n)
{
    if(n==1) return FResult[n]=1;
    else return FResult[n]=FResult[n-1]*n;
}
int main()
{
    double x;
    int n;
    printf("Input x and n:");
    scanf("%lf%d", &x, &n);
    printf("The result is %lf", sum(x, n));
    return 0;
}