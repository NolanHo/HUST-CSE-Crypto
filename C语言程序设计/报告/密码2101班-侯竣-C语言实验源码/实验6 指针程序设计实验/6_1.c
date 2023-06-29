#include<stdio.h>
#include<stdlib.h>
char *strcopy(char *, const char *);
int main(void)
{
	char *s1, *s2, *s3;
    s1 = malloc(sizeof(char) * 10); //修改: 用malloc分配内存
	s2 = malloc(sizeof(char) * 10); 
	printf("Input a string:\n");
	scanf("%s", s2);
	strcopy(s1, s2);
	printf("%s\n", s1);
	printf("Input a string again:\n");
	scanf("%s", s2);
	s3 = strcopy(s1, s2);
	printf("%s\n", s3);
	return 0;
}
/*将字符串s复制给字符串t，并且返回串t的首地址*/
char * strcopy(char *t, const char *s)
{
	char *p = t; //修改: 用p保存t的首地址
	while(*t++ = *s++);
	return p;
}