#include <stdio.h>
#include <math.h>
int NQueen(int n);
int main(void)
{
    int n;
    scanf("%d", &n);
    if (n < 1 || n > 10){
        printf("无解");
        return 0;
    }
    int count = NQueen(n);
    if (count == 0)
        printf("无解");
    else
        printf("%d", count);
    return 0;
}
int NQueen(int n){
    int count = 0;
    int a[10] = {0};
    int i = 0, j = 0;
    while (i >= 0){
        if (i == n){
            count++;
            i--;
            j = a[i] + 1;
            continue;
        }
        // 从上一次的j开始
        for (; j < n; j++){
            int k = 0;
            // 判断是否冲突
            for (; k < i; k++){
                if (a[k] == j || abs(a[k] - j) == abs(k - i))
                    break;
            }
            // 如果没有冲突
            if (k == i){
                a[i] = j;
                i++;
                j = 0;
                break;
            }
        }
        // 如果没有找到合适的j
        if (j == n){
            i--;
            if (i >= 0)
                j = a[i] + 1;
        }
    }
    return count;
}