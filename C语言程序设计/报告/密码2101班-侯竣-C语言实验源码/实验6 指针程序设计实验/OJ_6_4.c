#include <stdio.h>
void execute(void (*p[])(), int n);
void task0()
{
    printf("task0 is called!\n");
}
void task1()
{
    printf("task1 is called!\n");
}
void task2()
{
    printf("task2 is called!\n");
}
void task3()
{
    printf("task3 is called!\n");
}
void task4()
{
    printf("task4 is called!\n");
}
void task5()
{
    printf("task5 is called!\n");
}
void task6()
{
    printf("task6 is called!\n");
}
void task7()
{
    printf("task7 is called!\n");
}
void scheduler()
{
    int cnt = 0;
    char b[10];
    scanf("%s", b);
    for (int i = 0; b[i] != '\0'; cnt++)
        i++;
    int *tasks[cnt];
    for (int j = 0; j < cnt; j++)
    {
        int choice = b[j] - '0';
        switch (choice)
        {
        case 0:
            tasks[j] = (int *)task0;
            break;
        case 1:
            tasks[j] = (int *)task1;
            break;
        case 2:
            tasks[j] = (int *)task2;
            break;
        case 3:
            tasks[j] = (int *)task3;
            break;
        case 4:
            tasks[j] = (int *)task4;
            break;
        case 5:
            tasks[j] = (int *)task5;
            break;
        case 6:
            tasks[j] = (int *)task6;
            break;
        case 7:
            tasks[j] = (int *)task7;
            break;
        }
    }
    execute(tasks, cnt);
}
void execute(void (*tasks[])(), int n)
{
    for (int i = 0; i < n; i++)
    {
        tasks[i]();
    }
}
int main()
{
    scheduler();
    return 0;
}
