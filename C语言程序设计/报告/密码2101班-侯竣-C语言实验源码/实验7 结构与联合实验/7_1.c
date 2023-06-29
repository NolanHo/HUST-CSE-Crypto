#include <stdio.h>
char u[] = "UVWXYZ";
char v[] = "xyz";
struct T
{
    int x;
    char c;
    char *t;
} a[] = {{11, 'A', u}, {100, 'B', v}}, *p = a;
int main()
{
    /*求值验证s*/
    //(1)
    printf("(++p)->x: %d\n", (++p)->x);
    p=a;
    //(2)
    p++;
    printf("p++,p->c: %c\n", p->c);
    p = a;
    //(3)
    *p++->t;
    printf("*p++->t,*p->t: %c\n", *p->t);
    p = a;
    //(4)
    printf("*(++p)->t: %c\n", *(++p)->t);
    p = a;
    //(5)
    printf("*++p->t: %c\n", *++p->t);
    *--p->t;
    //(6)
    printf("++*p->t: %c\n", ++*p->t);
    return 0;
}