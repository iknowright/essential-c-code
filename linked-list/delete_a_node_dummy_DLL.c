#include <stddef.h>

typedef struct node
{
    int data;
    struct node *prev, *next;
} node;

node *delete_a_node_dummy_DLL(node *head, int d)
{
    node *t = head, *p;

    while (t->next != NULL && t->next->data != d)
    {
        if (t->next->data > d)
            return NULL;
        t = t->next;
    }
    if (t->next == NULL)
        return NULL;
    p = t->next;
    t->next = t->next->next;
    if (t->next != NULL)
        t->next->prev = t;
    p->next = p->prev = NULL;
    return p;
}
// calling:
// p = delete_a_node_dummy_DLL(head, data);
