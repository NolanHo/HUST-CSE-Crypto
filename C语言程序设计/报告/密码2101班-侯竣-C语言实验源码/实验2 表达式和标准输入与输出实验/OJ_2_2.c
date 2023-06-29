#include<stdio.h>
int main(){
    unsigned short x,m,n;
    scanf("%hx %hx %hx",&x,&m,&n);
    if(m>=0&&m<=15&&n>=1&&n<=16-m){
        x=x>>m<<m;
        x=x<<(16-n-m);
        printf("%hx",x);
    }else{
        printf("error");
    }
    return 0;
}
