#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 4
/*对指针数组s指向的size个字符串进行升序排序*/
void strsort(char *s[], int size)
{
	char *temp; //填空1
	int i, j;
    for(i=0; i<size-1; i++)
	    for (j=0; j<size-i-1; j++)
		    if (strcmp(s[j], s[j+1]) > 0)//填空2
            {
                temp = s[j];
                s[j] = s[j+1]; //填空3
                s[j+1] = temp;
            }
}

int main()
{
	int i;
	char *s[N], t[50];
	for (i=0; i<N; i++)
	{
		gets(t);
		s[i] = (char *)malloc(strlen(t)+1);
		strcpy(s[i], t); //填空4
	}
	strsort(s, N); //填空5
	for (i=0; i<N; i++)	{puts(s[i]); free(s[i]);}
	return 0;
}