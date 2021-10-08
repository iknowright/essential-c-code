#include <stddef.h>

typedef struct node
{
    int data;
    struct node *prev, *next;
} node;

node *delete_a_nodeA(node **head, int d)
{
    node **t = head, *p;

    while (*t != NULL && (*t)->data != d)
    {
        t = &((*t)->next);
    }
    if (*t == NULL)
    {
        return NULL;
    }
    if (t == head)
    {
        *head = (*t)->next;
        (*t)->next = NULL;
        return *t;
    }
    p = *t;
    *t = (*t)->next;
    return p;
}
// calling:
// p = delete_a_nodeA(&head, data);
