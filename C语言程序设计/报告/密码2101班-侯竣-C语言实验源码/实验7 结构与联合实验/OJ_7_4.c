#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
    int num;
    struct Node *next;
}Node;
Node *head = NULL;
int NumOfPeople = 0;
void AddNode(int n);
void Josephus(int m);
int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    NumOfPeople = n;
    AddNode(n);
    Josephus(m);
    return 0;
}
void AddNode(int n){
    // 虚构头结点, 单向循环链表
    head = (Node*)malloc(sizeof(Node));
    head->num = 0;
    head->next = NULL;
    Node *p = head;
    for (int i = 1; i <= n; i++) {
        Node *s = (Node*)malloc(sizeof(Node));
        s->num = i;
        s->next = NULL;
        p->next = s;
        p = s;
    }
    p->next = head->next;
}

void Josephus(int m){
    //快慢指针
    Node *p = head;
    Node *q = head->next;
    while(q->next != q){
        for (int i = 1; i < m; i++) {
            p = p->next;
            q = q->next;
        }
        printf("%d", q->num);
        if(NumOfPeople > 2){
            printf(" ");
        }
        p->next = q->next;
        free(q);
        q = p->next;
        NumOfPeople--;
    }
    printf("\n%d", p->num);
}
