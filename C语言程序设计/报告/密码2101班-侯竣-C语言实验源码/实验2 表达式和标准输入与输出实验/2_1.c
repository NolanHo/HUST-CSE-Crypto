#include <stdio.h>
#define PI 3.14159 //多了个分号
int main(void){
    int f;
    short p, k;
    double c, r, s;

    /* 任务1 */
    printf("Input Fahrenheit: ");
    scanf("%d", &f);
    c = 5 / 9.0 * (f - 32);
    printf( " \n %d(F) = %.2f(C)\n\n ", f, c);

    /* 任务2 */
    printf("input the radius r:");
    scanf("%lf", &r);
    s = r * r * PI;
    printf("\nThe acreage is %.2f\n\n", s);

    /* 任务3 */
    k = 0xa1b2, p = 0x8432;
    short newint = (short)(p&0xff00) + (short)((k>>8)&0x00ff);
    printf("new int = %#hx\n\n", newint);
    return 0;
}