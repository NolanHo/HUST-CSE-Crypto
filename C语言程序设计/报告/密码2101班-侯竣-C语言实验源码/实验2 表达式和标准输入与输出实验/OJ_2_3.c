#include<stdio.h>

int main(){
    unsigned int ip;
    while(scanf("%d", &ip) != EOF){
        printf("%d.%d.%d.%d\n", (ip>>24)&0x000000ff, (ip>>16)&0x000000ff, (ip>>8)&0x000000ff, ip&0x000000ff);
    }
}