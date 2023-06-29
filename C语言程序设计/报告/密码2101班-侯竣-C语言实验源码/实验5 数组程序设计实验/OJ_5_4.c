#include<stdio.h>
int main(){
    int seats[20] = {0};
    char SeatName[] = {'A','B','C','D','F'};
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int t = 0;
        scanf("%d", &t);
        int flag = 0; //是否找到了相邻座位
        for(int p=0;p<20;p++){
            if(seats[p]+t<=5){
                seats[p]+=t;
                flag = 1;
                for(int j=0;j<t;j++){
                    printf("%d%c", p+1, SeatName[j+seats[p]-t]);
                    if(j!=t-1)
                        printf(" ");
                }
                printf("\n");
                break;
            }
        }
        if(flag==0){
            for(int p=0;p<20;p++){
                if(seats[p]<5){
                    while(seats[p]<5){
                        seats[p]++;
                        printf("%d%c ", p+1, SeatName[seats[p]-1]);
                        t--;
                        if(t==0)
                            return 0;
                    }
                }
            }
        }
    }
    return 0;
}