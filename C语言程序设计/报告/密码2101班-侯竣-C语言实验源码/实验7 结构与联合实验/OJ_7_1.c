#include <stdio.h>
#include "stdlib.h"
typedef struct Student {
    int num;
    char name[20];
    int english, math, physics, c;
    struct Student *next;
}Student;
Student *head = NULL;
void AddStudent();
void PrintAllStudent();
void ModifyStudent();
void PrintAllAverage();
void PrintAllTotal();
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
