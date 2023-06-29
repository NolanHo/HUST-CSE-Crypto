#include<stdio.h> 
int main() {
    int a=100;
    while((100<=a)&&(a<=999)){
        if(a == ((a*a)%1000))
            printf("%d\n",a),a+=1;
        else 
            a+=1;
    }
    return 0;
}