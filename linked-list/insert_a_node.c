#include <stddef.h>

typedef struct node
{
      int data;
      struct node *next, *prev;
} node;

node *insert_a_node(node *head, node *p)
{
      node *t = head;

      if (p == NULL)
            return head;
      if (head == NULL)
            return p;

      if (p->data <= head->data)
      {
            p->next = head;
            return p;
      }
      while (t->next != NULL && t->next->data < p->data)
            t = t->next;
      p->next = t->next;
      t->next = p;
      return head;
}
// calling:
// head = insert_a_node(head, p);
