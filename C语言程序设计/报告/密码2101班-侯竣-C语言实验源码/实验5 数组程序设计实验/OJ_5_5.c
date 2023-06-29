#include <stdio.h>
int main(){
    int a[100],n,m1,n1,m2,n2;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    scanf("%d%d%d%d",&m1,&n1,&m2,&n2);
    // 交换m1~n1和m2~n2的数据
    int temp;
    // 交换较短的一段
    if(n1-m1<n2-m2){
        for(int i=0;i<n1-m1+1;i++){
            temp=a[m1+i];
            a[m1+i]=a[m2+i];
            a[m2+i]=temp;
        }
    }else{
        for(int i=0;i<n2-m2+1;i++){
            temp=a[m1+i];
            a[m1+i]=a[m2+i];
            a[m2+i]=temp;
        }
    }
    // 移动剩下的数据
    if(n1-m1<n2-m2){
        for(int i=n1-m1+1;i<n2-m2+1;i++){
            temp=a[m2+i];
            for(int j=m2+i;j>m1+i;j--){
                a[j]=a[j-1];
            }
            a[m1+i]=temp;
        }
    }else{
        for(int i=n2-m2+1;i<n1-m1+1;i++){
            temp=a[m1+i];
            for(int j=m1+i;j<m2+i;j++){
                a[j]=a[j+1];
            }
            a[m2+i-1]=temp;
        }
    }
    for(int i=0;i<n;i++){
        printf("%d ",a[i]);
    }
    return 0;
}