#include <stddef.h>

typedef struct node
{
    int data;
    struct node *prev, *next;
} node;

node *delete_a_node(node **head, int d)
{
    node *t = *head, *prev = NULL;

    while (t != NULL && t->data != d)
    {
        if (t->data > d)
            return NULL;
        prev = t;
        t = t->next;
    }
    if (t == NULL)
    {
        return NULL;
    }
    if (prev == NULL)
    {
        *head = t->next;
        t->next = NULL;
        return t;
    }
    prev->next = t->next;
    t->next = NULL;
    return t;
}
// calling:
// p = delete_a_node(&head, data);
