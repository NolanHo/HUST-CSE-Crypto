#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
    char str[2000];
    gets(str);
    int len = strlen(str);
    int max=0;
    char res[100]; //存放最长的子串
    for(int i=0;i<len;i++){
        //去除前面的空格
        while(str[i]==' '){
            i++;
        }
        //查找最长的单词
        int j=i;
        while(str[j]!=' '&&j<len){
            j++;
        }
        int max_len = j-i;
        if(max_len>max){
            max = max_len;
            strncpy(res,str+i,max);
            res[max]='\0';
        }
        i=j;

    }
    printf("%s",res);
    //长度
    printf(" %d",max);
    return 0;
}