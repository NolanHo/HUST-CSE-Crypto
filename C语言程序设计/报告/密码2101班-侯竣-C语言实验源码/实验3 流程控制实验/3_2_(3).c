#include <stdio.h>
int main()
{
    //改成纯粹合数求解器
    for (int p = 100; p < 1000; p++)
    {
        int x = p;
        int flag = 0;
        int i, k;
        while (x>0){
            for (i = 2, k = x >> 1; i <= k; i++){
                if (!(x % i)){
                    flag += 1;
                    break;
                }
            }
            x /= 10;
        }
        if (flag == 3)
            printf("%d\t", p);
    }
    
    return 0;
}