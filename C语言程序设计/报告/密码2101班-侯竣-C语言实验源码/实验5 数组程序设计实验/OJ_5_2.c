#include <stdio.h>
#include "string.h"
// 成绩输入
void InputScore(int n,char b[][100],int a[])
{
    int i;
    for(i=0;i<n;i++)
        scanf("%s%d",b[i],&a[i]);
    printf("%d records were input!\n",i);
}
// 成绩排序
void SortScore(int n,char b[][100],int a[]){
    int i,t;
    char c[100];
    for(i=0;i<n-1;i++)
    {
        for(int j=0;j<n-1;j++)
        {
            if (a[j]>=a[j + 1])
            {
                t = a[j], a[j] = a[j + 1], a[j + 1] = t;
                strcpy(c, b[j]);
                strcpy(b[j], b[j + 1]);
                strcpy(b[j + 1], c);
            }
        }
    }
    printf("Reorder finished!\n");
}
// 成绩输出
void PrintScore(int n,char b[][100],int a[]){
    for(int i=n-1;i>=0;i--){
        printf("%s %d\n",b[i],a[i]);
    }
}
// 寻找成绩
void FindScore(int x,int n,char b[][100],int a[])
{
    int l=0, r=n-1, mid;
    while(l<=r){
        mid=(l+r)/2;
        if(x<a[mid]) r=mid-1;
        else if(x>a[mid]) {
            l=mid+1;
        }
        else{
            printf("%s %d\n", b[mid],a[mid]);
            break;
        }
    }
    if(x != a[mid]) printf("not found!\n");
}
int main(){
    int i,n,k;
    while ((scanf("%d",&i))!=0)
    {
        static int t;
        if(i==1){
            scanf("%d",&n);
        }
        t=n;
        int a[20];
        char b[20][100];
        switch (i) 
        {
            case 0:
                return 0;
            case 1:
                InputScore(t,b,a);
                break;
            case 2:
                SortScore(t,b,a);
                break;
            case 3:
                PrintScore(t,b,a);
                break;
            case 4:
                
                scanf("%d",&k);
                FindScore(k,t,b,a);
                break;
        }
    }
    return 0;
}