#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>


/* to get the address o the current node:   address of previous node XOR address of the next node
   pt parcurgere ->  address of current ( care este address of previous node XOR address of the next node) XOR address of previous node
*/

typedef struct node
    {
        int value;
        struct node *npx;
    }NodeT;

typedef struct SLL
{
    int count;
    NodeT *first;
    NodeT *last;
}SLListT;

SLListT *createEmptySLList()
{
    SLListT *list = (SLListT*)malloc(sizeof(SLListT));
    if (list)
    {
        list->count = 0;
        list->first = list->last = NULL;
    }
    return list;
}

NodeT *createNode(int value)
{
    NodeT *p = (NodeT*)malloc(sizeof(NodeT));
    if (p)
    {
        p->npx = NULL;
        p->value = value;
    }
    return p;
}
NodeT *XOR(NodeT *a,NodeT *b)
{
    return (NodeT*)((uintptr_t)(a) ^ (uintptr_t)(b));
}

void AddFirst(SLListT *list, NodeT *p)
{
    if (list)
    {
        if (list->count == 0)
        {
            list->first = list->last = p;
        }
        else if (list->count == 1)
        {
            p->npx = XOR(NULL,list->first);
            list->first->npx = XOR(p,NULL);
            list->first = p;
        }
        else
        {
            p->npx = XOR(NULL,list->first);
            list->first->npx = XOR(p,list->first->npx);
            list->first = p;
        }
        list->count++;
    }
}

void AddLast(SLListT *list, NodeT *p)
{
    if(list)
    {
        if (list->count == 0)
        {
            list->first = list->last = p;
        }
        else if (list->count == 1)
        {
            p->npx = XOR(list->last,NULL);
            list->first->npx =XOR(NULL,p);
            list->last = p;
        }
        else
        {
            p->npx = XOR(list->last,NULL);
            list->last->npx = XOR(list->last,p);
            list->last = p;
        }
        list->count++;
    }
}

void InsertBeforeKey(int key, SLListT *list, NodeT *node)
{
    NodeT *current;
    NodeT *previous;
    NodeT *next;
    previous = NULL;
    current = list->first;
    while (current != NULL)
    {
        if (current->value == key) break;
        next = XOR(previous,current->npx);
        previous = current;
        current = next;
    }
    if (current != NULL)
    {
        if (current == list->first)
            AddFirst(list,node);
        else
        {
            node->npx = XOR(previous,current);  // previous is behind node, current after
            previous->npx = XOR(node,XOR(current,previous->npx));
            current->npx = XOR(node,XOR(previous,current->npx));
        }
        list->count++;
    }
}

void InsertAfterKey(int key,SLListT *list,NodeT *node)
{
    NodeT *current;
    NodeT *previous;
    NodeT *next;
    previous = NULL;
    current = list->first;
    while (current != NULL)
    {
        if (current->value == key) break;
        next = XOR(previous,current->npx);
        previous = current;
        current = next;
    }
    if (current != NULL)
    {
        if (current == list->last)
            AddLast(list,node);
        else
        {
            next = XOR(previous,current->npx);
            node->npx = XOR(current,next);
            current->npx = XOR(previous,node);
            next->npx = XOR(node,XOR(node,next->npx));
        }
        list->count++;
    }
}

void DeleteFirst(SLListT *list)  //merge
{
    NodeT *p;
    if (list->count == 0) return;
    else if (list->count == 1)
    {
        p = list->first;
        list->first = list->last = NULL;
        free(p);
        list->count--;
    }
    else
    {
        p = list->first;
        list->first = XOR(NULL,list->first->npx);
        list->first->npx = XOR(NULL,XOR(p,list->first->npx));
        list->count--;
    }
}

void DeleteLast(SLListT *list) //merge si asta
{
   NodeT *p;
   if (list->count == 0) return;
   else if (list->count == 1)
   {
       p = list->last;
       list->first = list->last = NULL;
       free(p);
       list->count--;
   }
   else
   {
       p = list->last;
       list->last = XOR(NULL,list->last->npx);
       list->last->npx = XOR(NULL,XOR(p,list->last->npx));
       list->count--;
   }
}

void DeleteByKey(SLListT *list, int key) //merge
{
    NodeT *previous;
    NodeT *current;
    NodeT *next;
    NodeT *p;
    previous = NULL;
    current = list->first;
    while (current != NULL)
    {
        if (current->value == key) break;
        next = XOR(previous,current->npx);
        previous = current;
        current = next;
    }
    if (current != NULL)
    {
        if (list->count == 1)
        {
            p = list->first;
            list->first = list->last = NULL;
            list->count--;
            free(p);
        }
        else if (current == list->first)
        {
            DeleteFirst(list);
            list->count--;
        }
        else if (current == list->last)
        {
            DeleteLast(list);
            list->count--;
        }
        else
        {
            next = XOR(previous,current->npx);
            previous->npx = XOR(next,XOR(current,previous->npx));
            next->npx = XOR (previous,XOR(current,next->npx));
            free(current);
            list->count--;
        }
    }
}

void printForward(SLListT *list) //merge
{
    NodeT *previous;
    NodeT *current;
    NodeT *next;
    previous = NULL;
    current = list->first;
    while (current != NULL)
    {
        printf("%d ",current->value);
        next = XOR(previous,current->npx);
        previous = current;
        current = next;
    }
    printf("\n");
}

void printBackwards(SLListT *list) //merge
{
    NodeT *previous;
    NodeT *current;
    NodeT *next;
    previous = NULL;
    current = list->last;
    while (current != NULL)
    {
        printf("%d ",current->value);
        next = XOR(previous,current->npx);
        previous = current;
        current = next;
    }
    printf("\n");
}

int main()
{
    SLListT *listPtr;
    listPtr = createEmptySLList();
    AddFirst(listPtr,createNode(5));
    AddFirst(listPtr,createNode(3));
    AddFirst(listPtr,createNode(2));
    AddFirst(listPtr,createNode(1));
    AddFirst(listPtr,createNode(50));
    //InsertBeforeKey(3,listPtr,createNode(66));
    //InsertAfterKey(50,listPtr,createNode(69));
    printForward(listPtr);
    DeleteFirst(listPtr);
     printForward(listPtr);
     DeleteLast(listPtr);
      printForward(listPtr);
      DeleteByKey(listPtr,2);
       printForward(listPtr);
//    DeleteFirst(listPtr);
//    printForward(listPtr);
//    DeleteLast(listPtr);
//    printForward(listPtr);
    //printf("%d %d\n",listPtr->first->data, listPtr->last->data);
    InsertAfterKey(1,listPtr,createNode(100));
    InsertBeforeKey(100,listPtr,createNode(200));
    //deleteByKey(listPtr,5);
    //deleteByKey(listPtr,50);
    //deleteByKey(listPtr,50);
    //printf("%d %d\n",listPtr->first->data, listPtr->last->data);
    //printf("%d ",listPtr->count);
    printForward(listPtr);
    return 0;
}
