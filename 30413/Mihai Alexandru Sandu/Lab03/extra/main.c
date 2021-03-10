#include <stdio.h>
#include <stdlib.h>


/*  *******************************************************

    I wrote those functions and structures just to exercise

    ******************************************************** */


 typedef struct node
    {
        int value;
        struct node *next;
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
        p->next = NULL;
        p->value = value;
    }
    return p;
}

void AddFirst(SLListT *list, NodeT *p)
{
    if ( list )
    {
        if (list->first == NULL && list->last == NULL)
        {
            list->first = list->last = p;
        }
        else
        {
            p->next = list->first;
            list->first = p;
        }
        list->count++;
    }
}

// Function to find the intersection of two lists
// input : 2 SLLists
// output: the first node of the intersection

NodeT *FindIntersection( SLListT *list1, SLListT *list2)
{
    NodeT *p1,*p2;
    if ( list1 && list2 )
    {
        for ( p1 = list1->first; p1 != NULL; p1 = p1->next )
            {
                for ( p2 = list2->first; p2 != NULL; p2 = p2->next )
                {
                    if ( p1->value == p2->value )
                        return p2;
                }
            }
                if ( p1 == NULL && p2 == NULL) return NULL;
    }
    else return NULL;
}
void SortSLList(SLListT *list)
{
    NodeT *p1;
    NodeT *p2;
    NodeT *aux;

    for(p1 = list->first; p1 != NULL; p1 = p1->next)
    {
        for(p2 = p1->next; p2 != NULL; p2 = p2->next)
        {
            if (p1->value == p2->value)
            {
                aux = p1;
                p1 = p2;
                p2 = aux;
            }
        }
    }
}

int IntersectionFct(int d, SLListT *list1, SLListT *list2)
{
    NodeT *p1 = list1->first;
    NodeT *p2 = list2->first;
    for(int i = 0; i < d; i++)
        p1 = p1->next;
    while ( p1 != NULL && p2 != NULL)
    {
        if (p1 == p2)
            return p1->value;
        p1 = p1->next;
        p2 = p2->next;
    }
    return -1;
}

// it return the value of the node of the intersection, otherwise it return -1

int Intersection(SLListT *list1, SLListT *list2)
{
    int d;
    int data;
    NodeT *p1 = list1->first;
    NodeT *p2 = list2->first;
    if (list1->count > list2->count)
    {
        d = list1->count - list2->count;
        data = IntersectionFct(d,list1,list2);
    }
    else
    {
        d= list2->count - list1->count;
        data = IntersectionFct(d,list2,list1);
    }
    return data;
}


void DeleteDuplicates(SLListT *list)
{
    SortSLList(list);
    NodeT *p1 = list->first;
    NodeT *p2;
    while (p1 != NULL)
    {
        p2 = p1->next;
        if (p2 != NULL)
        {
            if (p1->value == p2->value)
            {
                if (p2->next == NULL)
                {
                    p1->next = NULL;
                    free(p2);
                }
                else
                {
                    p1->next = p2->next;
                    free(p2);
                }
            }
        }
        p1 = p1->next;
    }
}
void show(SLListT *list)
{
    NodeT *p = list->first;
    while (p != NULL)
    {
        printf("%d ",p->value);
        p = p->next;
    }
}

int main()
{
    SLListT *list1, *list2;
    list1 = createEmptySLList();
    list2 = createEmptySLList();
    NodeT *p1,*p2,*p3,*p4,*p5,*p6,*nodeIntersection;   // I was lazy so I did this
    p1 = createNode(5);
    p2 = createNode(2);
    p3 = createNode(9);
    p4 = createNode(4);
    p5 = createNode(11);
    p6 = createNode(9);
    AddFirst(list1,p1);
    AddFirst(list1,p2);
    AddFirst(list1,p3);
    AddFirst(list2,p4);
    AddFirst(list2,p5);
    AddFirst(list2,p6);
    //nodeIntersection = FindIntersection(list1,list2);
    DeleteDuplicates(list1);
    show(list1);

    //printf("%d",nodeIntersection->value);

    return 0;
}
