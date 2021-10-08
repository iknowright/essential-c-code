#include <stddef.h>

typedef struct node
{
    int data;
    struct node *next, *prev;
} node;

node *search_a_list(node *head, int d)
{
    node *t=head;

    while (t != NULL && t->data != d){
         t = t -> next;
    }
    return t;
}

// calling:
// int data = 10;
// p = search_a_list(head, data);
