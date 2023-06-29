#include <stdio.h>
#include "math.h"
int find(int n); //自幂数
int find(int n){
	int z = n / 10, t = n;
	int i;
	for (i = 1; z > 0; i++){
		z = z / 10;
	}
	int x = n % 10;
	int term = 0; //n次幂
	for (int j = i; j >= 1; j--){
		term += pow(x, i);
		n = n / 10;
		x = n % 10;
	}
	if (term == t)return 1;
	else return 0;
}
int main(){
	int k;
	while (scanf("%d", &k) != EOF){
		int count = 0;
		if (k == 0)
			break;//输入0结束
		else{
			for (int i = pow(10, k - 1); i < pow(10, k); i++){
				if (find(i)){
					count++;
				}
			}	
			switch (k){
			case 3:
				printf("3位的水仙花数共有%d个", count);
				break;
			case 4:
				printf("4位的四叶玫瑰数共有%d个", count);
				break;
			case 5:
				printf("5位的五角星数共有%d个", count);
				break;
			case 6:
				printf("6位的六合数共有%d个", count);
				break;
			case 7:
				printf("7位的北斗星数共有%d个", count);
				break;
			case 8:
				printf("8位的八仙数共有%d个", count);
				break;
			}
			if (count == 1){
				for (int i = pow(10, k - 1); i < pow(10, k); i++)
					if (find(i))printf("%d\n", i);
			}
			else{
				int t = 0;
				int n = 1;
				for (int i = pow(10, k - 1); (i < pow(10, k)) && (n < count); i++){
					if (find(i)){
						printf("%d,", i);
						n++;
					}
					t = i;
				}
				for (int z = t + 1; z < pow(10, k); z++)
					if (find(z))
						printf("%d\n", z);
			}
		}
	}
	return 0;
}