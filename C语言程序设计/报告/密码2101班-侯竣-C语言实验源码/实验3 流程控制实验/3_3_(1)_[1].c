#include <stdio.h>
int main()
{
    //if-else
    double salary,tax=0;
    printf("请输入工资：\n");
    printf("应交税：");
    scanf("%lf",&salary);
    // scanf("应交税：%lf",&salary);
    if((salary>=1000)&&(salary<2000)){
        printf("应交税：%lf ",tax=(salary-1000)*(0.05));
    }else if((salary>=2000)&&(salary<3000)){
        printf("应交税：%lf ",tax=((salary-2000)*(0.1)+50));
    }else if((salary>=3000)&&(salary<4000)){
        printf("应交税：%lf ",tax=(salary-3000)*(0.15)+150);
    }else if((salary>=4000)&&(salary<5000)){
        printf("应交税：%lf ",tax=(salary-4000)*(0.2)+300);
    }else if(salary>=5000){
        printf("应交税：%lf", tax=(salary-5000)*(0.25)+500);
    }else{
        printf("应交税：0");
    }
    return 0;
}