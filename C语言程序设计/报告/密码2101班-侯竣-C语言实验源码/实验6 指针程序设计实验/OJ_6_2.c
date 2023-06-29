#include <stdio.h>
//逆时针旋转90度
void Rotate(int *p,int n,int m){
    for(int j=m-1;j>=0;j--){
        for(int i=0;i<n;i++){
            if(i==n-1) printf("%d",*(p+i*m+j));
            else printf("%d ",*(p+i*m+j));
        }
        printf("\n");
    }
}
int main() {
    int n,m;
    scanf("%d %d",&n,&m);
    int a[n][m];
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%d",&a[i][j]);
        }
    }
    int *p=a;
    Rotate(p,n,m);
    return 0;
}
