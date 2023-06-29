#include <stdio.h>
long long sum_fac(int n); //改成long long
int main(void)
{
    int k;
    for (k = 1; k <= 20; k++)
        printf("k=%d\tthe sum is %lld\n", k, sum_fac(k)); //改成%lld
    return 0;
}
long long sum_fac(int n) //改成long long
{
    long long s = 0; //改成long long
    long long fac = 1;
    for (int i = 1; i <= n; i++){
        fac *= i;
        s += fac; //s+=fac
    }
    return s;
}