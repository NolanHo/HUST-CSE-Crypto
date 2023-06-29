#include <stdio.h>
/*判断x是否完数，是则返回1，否则返回0*/
int isPerfect(int x)
{
    int y, s;
    for (s = 0, y = 1; y <= x / 2; y++) //y<x/2, 改为y<=x/2
    {
        if (!(x % y))
            s += y;
    }
    if (s == x)
        return 1;
    return 0;
}

int main()
{
    int a;
    printf("1000内的完数有：");
    for (a = 1; a <= 1000; a++) /*遍历所有数*/
        if (isPerfect(a))
            printf("%8d", a);
    return 0;
}
