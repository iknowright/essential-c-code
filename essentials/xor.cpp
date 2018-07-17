#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
 
typedef struct Node
{
    int data;
    struct Node* linker;
}Node;
 
Node* XOR (Node *a,Node *b)
{
    return (Node*) ((intptr_t) (a) ^ (intptr_t) (b));
}
 
void insertion(Node **head, int data)
{
    Node *newNode  = (Node *) malloc (sizeof (Node));
    newNode->data = data;
    newNode->linker = XOR(*head, NULL);
    if (*head!= NULL)
    {
        Node* next = XOR((*head)->linker,  NULL);
        (*head)->linker = XOR(newNode, next);
    }
    *head= newNode;
}
 
// prints contents of doubly linked list in forward direction
void print(Node *headOrTail)
{
    bool firstnodot=true;
    Node *curr = headOrTail;
    Node *prev = NULL;
    Node *next;
    while (curr != NULL)
    {
        if (firstnodot)
        {
            printf ("%d", curr->data);
            firstnodot=false;
        }
        else printf (", %d", curr->data);
        next = XOR (prev, curr->linker);
        prev = curr;
        curr = next;
    }
}
int main ()
{
    Node *head = NULL;
    Node *tail = NULL;
    bool tailflag=true;
    int i;
    for(i=20;i>=0;i--)
    {
        insertion(&head,i);
        if (tailflag)
        {
            tail=head;
            tailflag=false;        
        }

    }
    printf("The data from left to right:\n");
    print(head);
    printf("\n");
    printf("The data from right to left:\n");
    print(tail);
    return (0);
}