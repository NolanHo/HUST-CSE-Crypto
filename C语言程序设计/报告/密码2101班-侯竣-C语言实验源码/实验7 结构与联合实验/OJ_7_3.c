#include <stdio.h>
#include "stdlib.h"
/*
将实验7-1的菜单选择项6修改为：
⑥增加按照平均成绩进行升序（0）及降序（1）排序的函数，
写出用交换结点指针域的方法排序的函数，排序可指定用选择法（0）或冒泡法（1）。
*/
typedef struct Student {
    int num;
    char name[20];
    int english, math, physics, c;
    struct Student *next;
}Student;
Student *head = NULL;
int StudentCount = 0;
void AddStudent();
void PrintAllStudent();
void ModifyStudent();
void PrintAllAverage();
void PrintAllTotal();
void SortStudent();
void BubbleSort(int op);
void SelectSort(int op);
int main(){
    int op; // 操作码
    while(1){
        scanf("%d", &op);
        switch(op){
            case 0: return 0;
            case 1: AddStudent(); break;
            case 2: PrintAllStudent(); break;
            case 3: ModifyStudent(); break;
            case 4: PrintAllAverage(); break;
            case 5: PrintAllTotal(); break;
            case 6: SortStudent(); break;
        }
    }
    //释放内存
    Student *p = head;
    while(p){
        Student *q = p;
        p = p->next;
        free(q);
    }
    return 0;
}

void AddStudent(){
    int n = 0;
    scanf("%d", &n);
    StudentCount += n;
    for (int i = 0; i < n; i++) {
        Student *s = (Student*)malloc(sizeof(Student));
        scanf("%d %s %d %d %d %d", &s->num, s->name, &s->english, &s->math, &s->physics, &s->c);
        // 插到尾部
        if (head == NULL) {
            head = s;
            s->next = NULL;
        } else {
            Student *p = head;
            while (p->next) {
                p = p->next;
            }
            p->next = s;
            s->next = NULL;
        }
    }
    printf("完成了%d位同学的成绩输入\n", n);
}

void PrintAllStudent(){
    Student *p = head;
    while(p){
        printf("%d %s %d %d %d %d", p->num, p->name, p->english, p->math, p->physics, p->c);
    }
}

void ModifyStudent(){
    int num = 0;
    scanf("%d", &num);
    int op = 0; // 0: name, 1: english, 2: math, 3: physics, 4: c
    scanf("%d", &op);
    Student *p = head;
    while(p){
        if (p->num == num) {
            switch(op){
                case 0: scanf("%s", p->name); break;
                case 1: scanf("%d", &p->english); break;
                case 2: scanf("%d", &p->math); break;
                case 3: scanf("%d", &p->physics); break;
                case 4: scanf("%d", &p->c); break;
            }
            break;
        }
        p = p->next;
    }
    //打印修改后的信息
    printf("%d %s %d %d %d %d", p->num, p->name, p->english, p->math, p->physics, p->c);
}

void PrintAllAverage(){
    Student *p = head;
    while(p){
        printf("%d %s %.2f\n", p->num, p->name, (p->english + p->math + p->physics + p->c) / 4.0);
        p = p->next;
    }
}

void PrintAllTotal(){
    Student *p = head;
    while(p){
        printf("%d %s %d %.2f\n", 
                p->num, p->name, 
                p->english + p->math + p->physics + p->c, 
                (p->english + p->math + p->physics + p->c) / 4.0);
        p = p->next;
    }
}

void SortStudent(){
    int op = 0; // 0: 升序, 1: 降序
    scanf("%d", &op);
    int method = 0; // 0: 选择法, 1: 冒泡法
    scanf("%d", &method);
    if(method == 0){
        SelectSort(op);
    } else {
        BubbleSort(op);
    }
    PrintAllAverage();
}

void BubbleSort(int op){
    Student *p[StudentCount]; // 临时数组
    Student *q = head;
    for (int i = 0; i < StudentCount; i++) {
        p[i] = q;
        q = q->next;
    }
    for (int i = 0; i < StudentCount - 1; i++) {
        for (int j = 0; j < StudentCount - 1 - i; j++) {
            if (op == 0) {
                if ((p[j]->english + p[j]->math + p[j]->physics + p[j]->c) > (p[j+1]->english + p[j+1]->math + p[j+1]->physics + p[j+1]->c)) {
                    Student *t = p[j];
                    p[j] = p[j+1];
                    p[j+1] = t;
                }
            } else {
                if ((p[j]->english + p[j]->math + p[j]->physics + p[j]->c) < (p[j+1]->english + p[j+1]->math + p[j+1]->physics + p[j+1]->c)) {
                    Student *t = p[j];
                    p[j] = p[j+1];
                    p[j+1] = t;
                }
            }
        }
    }
    // 重新连接
    for (int i = 0; i < StudentCount - 1; i++) {
        p[i]->next = p[i+1];
    }
    p[StudentCount-1]->next = NULL;
    head = p[0];
}

void SelectSort(int op){
    Student *p[StudentCount]; // 临时数组
    Student *q = head;
    for (int i = 0; i < StudentCount; i++) {
        p[i] = q;
        q = q->next;
    }
    for (int i = 0; i < StudentCount - 1; i++) {
        int min = i;
        for (int j = i + 1; j < StudentCount; j++) {
            if (op == 0) {
                if ((p[j]->english + p[j]->math + p[j]->physics + p[j]->c) < (p[min]->english + p[min]->math + p[min]->physics + p[min]->c)) {
                    min = j;
                }
            } else {
                if ((p[j]->english + p[j]->math + p[j]->physics + p[j]->c) > (p[min]->english + p[min]->math + p[min]->physics + p[min]->c)) {
                    min = j;
                }
            }
        }
        if (min != i) {
            Student *t = p[i];
            p[i] = p[min];
            p[min] = t;
        }
    }
    // 重新连接
    for (int i = 0; i < StudentCount - 1; i++) {
        p[i]->next = p[i+1];
    }
    p[StudentCount-1]->next = NULL;
    head = p[0];
}