#include <stddef.h>

typedef struct node
{
    int data;
    struct node *next, *prev;
} node;

insert_a_node_no_return(node **head, node *p)
{
    node *t = *head;

    if (p == NULL)
        return;
    if (*head == NULL)
    {
        *head = p;
        return;
    }

    if (p->data <= (*head)->data)
    {
        p->next = *head;
        *head = p;
        return;
    }
    while (t->next != NULL && t->next->data < p->data)
        t = t->next;
    p->next = t->next;
    t->next = p;
    return;
}
// calling:
// insert_a_node(&head, p);
