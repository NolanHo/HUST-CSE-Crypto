#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
本关任务：
输入n行文本，
每行不超过80个字符，用字符指针数组指向键盘输入的n行文本，且n行文本的存储无冗余。
然后执行如下操作：
删除每一行中的前置空格（' '）和水平制表符（'\t'），
并将文本中多个空格合并为一个空格，如果有。
该操作要求定义成函数。在main函数中输出执行了以上操作的各行。
*/
char* DeleteSpace(char *p){
	int i=0,j=0;
	char str[80];
	//删除前置空格
	while(p[i]==' '||p[i]=='\t'){
		i++;
	}
	//删除多余空格
	while(p[i]!='\0'){
		if(p[i]==' '&&p[i+1]==' '){
			i++;
		}else{
			str[j]=p[i];
			i++;
			j++;
		}
	}
	str[j]='\0';
	strcpy(p,str);
	return p;
}
int main(){
	int n;
	scanf("%d",&n);
	getchar();
	char *p[n];
	char str[80];
	for(int i=0;i<n;i++){
		gets(str);
		char *tmp = (char *)malloc(sizeof(char)*strlen(str));
		strcpy(tmp,str);
		p[i]=tmp;
	}

	for(int i=0;i<n;i++){
		printf("%s",DeleteSpace(p[i]));
		if(i!=n-1){
			printf("\n");
		}
	}
	return 0;
}
