#include "stdio.h"
#include "stdlib.h"
struct s_list
{
    int data;            /* 数据域 */
    struct s_list *next; /* 指针域 */
};
void create_list(struct s_list **headp, int *p);
int main(void)
{
    struct s_list *head = NULL, *p;
    int s[] = {1, 2, 3, 4, 5, 6, 7, 8, 0}; /* 0为结束标记 */
    create_list(&head, s);                 /* 创建新链表 */
    p = head;                              /*遍历指针p指向链头 */
    while (p)
    {
        printf("%d\t", p->data); /* 输出数据域的值 */
        p = p->next;             /*遍历指针p指向下一结点 */
    }
    p = head;
    printf("\n");
    return 0;
}
void create_list(struct s_list **headp, int *p)
{
    //修改后的代码
    struct s_list *loc_tail = NULL, *head;
    if (p[0] == 0); /* 相当于*p==0 */
    else
    { /* loc_tail指向动态分配的最后一个结点 */
        loc_tail = (struct s_list *)malloc(sizeof(struct s_list));
        loc_tail->data = *p++; /* 对数据域赋值 */
        head = loc_tail;              /* tail指向最后一个结点 */
        while (*p)
        { /* head2所指结点的指针域指向动态创建的结点 */
            struct s_list *tmp = (struct s_list *)malloc(sizeof(struct s_list));
            tmp->next = head;
            tmp->data = *p++;
            head = tmp;
        }
        loc_tail->next = NULL; /* 对指针域赋NULL值 */
    }
    *headp = head; /* 使头指针headp指向新创建的链表 */
}