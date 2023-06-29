#include<stdio.h> 
int main()
{
	int a=1;
	int i=0,j,N,h; //i为行, j为列, N为行数, h为空格数
	scanf("%d",&N);
	while(i <= N){
		for(h=1;h<=N+2*(N-i);h++){
            //根据高度右移空格
            printf(" ");
        }
		printf("%d",a);
		printf("   ");
        j = 1;
		while(j<=i){
			int b = a*(i-j+1)/j; //递推公式
			printf("%d",b);
			int c = b/10;
			if (c!=0){
                //行末两个空格
                printf("  ");
            }else{
                //数字间三个空格
                printf("   ");
            }
			a = b;
            j++;
		}
		printf("\n");i++;
	}
	return 0;
}