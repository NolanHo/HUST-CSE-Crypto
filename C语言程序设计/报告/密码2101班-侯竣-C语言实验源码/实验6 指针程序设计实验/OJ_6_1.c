#include <stdio.h>
int main()
{
    long x;
    scanf("%ld",&x);
    char *p = (char*)&x; // p指向x的第一个字节
    p += 3; // p指向x的第四个字节
    char high,low;
    for(int k=0;k<4;k++)
    {
        
        high = (*p>>4)&0x0f;
        printf("%X",high);
        low = (*p)&0x0f;
        printf("%X",low);
        p--;
    }
    return 0;
}