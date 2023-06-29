#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
	char ch;
	FILE *fp;
	if (argc != 2)
	{
		printf("Arguments error!\n");
		exit(-1);
	}
	// 用freopen()函数代替fopen()函数
	if (freopen(argv[1], "r", stdin) == NULL)
	{
		printf("Can't open %s file!\n", argv[1]);
		exit(-1);
	}
	while ((ch = getchar()) != EOF)
		putchar(ch);

	return 0;
}