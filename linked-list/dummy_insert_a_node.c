#include <stddef.h>

typedef struct node
{
    int data;
    struct node *prev, *next;
} node;

dummy_insert_a_node(node *dh, node *p)
{
    node *t = dh;

    if (p == NULL)
        return;

    while (t->next != NULL && t->next->data < p->data)
        t = t->next;
    p->next = t->next;
    t->next = p;
    return;
}

// calling:
// head = insert_a_node(head, p);
