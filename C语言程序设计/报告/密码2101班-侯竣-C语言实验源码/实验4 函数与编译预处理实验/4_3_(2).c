#include <stdio.h>
#include<assert.h> //加上assert.h
#define R
int integer_fraction(float x); //定义函数
int main(void)
{
    float r, s;
    int s_integer = 0;
    printf("Input a number: ");
    scanf("%f", &r);
#ifdef R
    s = 3.14159 * r * r;
    printf("Area of round is: %f\n", s);
    s_integer = integer_fraction(s);
    if((s - s_integer) < 0.5){ //assert修改为if
        printf("The integer fraction of area is %d\n", s_integer);
    }else{
        printf("The integer fraction of area is %d\n", s_integer + 1);
    }
    
#endif
    return 0;
}

int integer_fraction(float x)
{
    int i = x;
    return i;
}