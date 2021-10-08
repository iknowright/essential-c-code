#include <stddef.h>

typedef struct node
{
    int data;
    struct node *prev, *next;
} node;

node *delete_a_nodeDLL(node **head, int d)
{
    node *t = *head;

    while (t != NULL && t->data != d)
    {
        if (t->data > d)
            return NULL;
        t = t->next;
    }
    if (t == NULL)
    {
        return NULL;
    }
    if (t == *head)
        *head = t->next;
    if (t->prev != NULL)
    {
        t->prev->next;
        t->next;
    }
    if (t->next != NULL)
    {
        t->next->prev = t->prev;
    }
    t->next = t->prev = NULL;
    return t;
}
// calling:
// p = delete_a_node(&head, data);
