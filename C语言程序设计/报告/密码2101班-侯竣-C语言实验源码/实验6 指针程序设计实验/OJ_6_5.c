#include<stdio.h>
#include<stdlib.h>
//z字形扫描矩阵, 指针操作数组
int main(){
    int m,n;
    scanf("%d%d",&m,&n);
    int *a = (int *)malloc(sizeof(int)*m*n);
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            scanf("%d",a+i*n+j);
        }
    }
    int i=0,j=0;
    int flag=0;
    while(i<m&&j<n){
        printf("%d ",*(a+i*n+j));
        if(flag==0){
            if(j==n-1){
                i++;
                flag=1;
            }else if(i==0){
                j++;
                flag=1;
            }else{
                i--;
                j++;
            }
        }else{
            if(i==m-1){
                j++;
                flag=0;
            }else if(j==0){
                i++;
                flag=0;
            }else{
                i++;
                j--;
            }
        }
    }
    return 0;

}