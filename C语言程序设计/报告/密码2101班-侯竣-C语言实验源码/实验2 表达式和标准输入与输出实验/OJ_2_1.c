#include <stdio.h>
int main(void)
{
    char c;
    while ((c = getchar()) != EOF)
    {
        putchar((c >= 'A' && c <= 'Z') ? c - 'A' + 'a' : c);
    }
}