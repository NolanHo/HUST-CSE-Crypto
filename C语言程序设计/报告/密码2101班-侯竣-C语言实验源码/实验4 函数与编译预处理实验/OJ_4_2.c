#include <stdio.h>
int find(int p)
{
    int sum = 0;
    for(int i=1;i<p;i++){
        if (p % i == 0) {
            sum += i;
        }
    }
    if(sum==p){ 
        return 1;
    }else{
        return 0;
    }
}
int main() {
    int p,term=0;
    for(p=3;p<=10000;p++)
    {
        if(find(p)){
            //打印完美数
            printf("%d=1+",p);
            for(int i=2;i<p;i++) {
                if(p%i==0){
                    term+=i;
                    if(term==p-1){
                        printf("%d\p",i);
                    }else{
                        printf("%d+",i);
                    }
                }
            }
            term = 0;
        }
    }
    return 0;
}