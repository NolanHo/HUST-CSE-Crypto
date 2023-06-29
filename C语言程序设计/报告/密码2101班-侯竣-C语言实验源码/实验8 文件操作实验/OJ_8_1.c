#include <stdio.h>
#include "string.h"
#define PATH "EXP/exp801/source.txt"
#define PATH2 "test.txt"
/*
编写一个程序，用给定的单词替换文件source.txt中的目标单词，并显示输出替换的个数。
注意：读取的文件路径请使用
EXP/exp801/source.txt
*/
int main() {
    FILE* f = fopen(PATH, "r");
    char word[100];
    char target[1000];
    char replace[1000];
    char result[1000] = {0};
    scanf("%s", target);
    scanf("%s", replace);
    int cnt = 0;
    int pos = 0;
    while (fscanf(f, "%s", word) != EOF) {
        // 处理逗号和句号
        char last = 0;
        if (word[strlen(word) - 1] == ',' || word[strlen(word) - 1] == '.') {
            last = word[strlen(word) - 1];
            word[strlen(word) - 1] = 0;
        }
        if (strcmp(word, target) == 0) {
            cnt++;
            strcat(result, replace);
        } else {
            strcat(result, word);
        }
        if (last) {
            result[strlen(result)] = last;
        }
        result[strlen(result)] = ' ';
    }
    printf("%d\n", cnt);
    printf("%s", result);
    fclose(f);
    return 0;
}
