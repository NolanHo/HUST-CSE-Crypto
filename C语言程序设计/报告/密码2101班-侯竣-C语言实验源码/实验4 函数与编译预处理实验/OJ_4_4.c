#include <stdio.h>
#include <math.h>
#define s(a,b,c) ((a+b+c)/2)
#define GetArea(a,b,c,s) (sqrt((s)*(s-a)*(s-b)*(s-c)))
int main() {
    float a,b,c,s;
    scanf("%f %f %f",&a,&b,&c);
    s = s(a,b,c);
    printf("s=%.2f\n",s);
    printf("area=%.2f",GetArea(a,b,c,s));
    return 0;
}