#include <stdio.h>
int main()
{
    double salary,tax,x;
    printf("请输入工资：\n");
    printf("应交税：");
    scanf("%lf",&salary);
    x=salary / 1000;
    if(x>1) {
        switch ((int)x) {
            case 1:
                printf("应交税：%lf", tax = (salary - 1000) * (0.05));
                break;
            case 2:
                printf("应交税：%lf", tax = (salary - 2000) * (0.1) + 50);
                break;
            case 3:
                printf("应交税：%lf", tax = (salary - 3000) * (0.15) + 150);
                break;
            case 4:
                printf("应交税：%lf", tax = (salary - 4000) * (0.2) + 300);
                break;
            default:
                printf("应交税：%lf", tax = (salary - 5000) * (0.25) + 500);
                break;
        }
    }else{
        printf("应交税：0");    
    } 
    return 0;
}