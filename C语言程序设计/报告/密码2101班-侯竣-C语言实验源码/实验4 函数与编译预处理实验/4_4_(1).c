#include <stdio.h>
#define CHANGE 0
#if CHANGE
int main()
{
    char c;
    while ((c = getchar()) != '\n')
        if ((c <= 'Z') && (c >= 'A'))
        {
            putchar(c - 'A' + 'a');
        }
        else
        {
            putchar(c - 'a' + 'A');
        }
    return 0;
}
#else
int main()
{
    char c;
    while ((c = getchar()) != '\n')
    {
        putchar(c);
    }
    return 0;
}
#endif