#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct node
{
    int value;
    struct node *next;
}NodeT;

typedef struct
{
    int count;
    NodeT *first;
    NodeT *last;
}ListT;

ListT *createSLL()
{
    ListT *listPtr = (ListT*)malloc(sizeof(ListT));
    {
        if (listPtr)
        {
            listPtr->count = 0;
            listPtr->first = listPtr->last = NULL;
        }
    }
    return listPtr;
}

NodeT *createSLLNode(int value)
{
    NodeT *p = (NodeT*)malloc(sizeof(NodeT));
    if(p)
    {
        p->value = value;
        p->next = NULL;
    }
    return p;
}

int isEmpty(ListT *listPtr)
{
    if (listPtr->first==NULL && listPtr->last==NULL)
        return 1;
    else return 0;
}

void AF(ListT *listPtr,NodeT *p)
{
    //NodeT *p;
    //p = createSLLNode(value);
    if(listPtr)
    {
        p->next = listPtr->first;
        if (isEmpty(listPtr))
        {
            listPtr->last = p;
        }
        listPtr->first = p;
        listPtr->count++;
    }
}

void AL(ListT *listPtr,NodeT *p)
{
    //NodeT *p;
   // p = createSLLNode(value);
    if(listPtr)
    {
        if(isEmpty(listPtr))
        {
            listPtr->first = p;
        }
        else listPtr->last->next = p;

        listPtr->last = p; //p va fi ultimul nod, asa ca listPtr->last trebuie sa indice la noul nod
        listPtr->count++;
    }
}

void DF(ListT *listPtr)
{
    NodeT *p;
    if(listPtr)
    {
        if(listPtr->first != NULL)
        {
            p = listPtr->first;
            listPtr->first = listPtr->first->next;
            free(p);
            listPtr->count--;
            if(listPtr->first == NULL)
                listPtr->last = NULL;
        }
    }
}

void DL(ListT *listPtr)
{
    NodeT *q, *q1;
    q1 = NULL;
    q = listPtr->first;
    if(listPtr)
    {
        if(q != NULL)
        {
            while (q != listPtr->last)
            {
                q1 = q;
                q = q->next;
            }
            if (q == listPtr->first)
                listPtr->first = listPtr->last = NULL;
            else
            {
                q1->next = NULL;
                listPtr->last = q1;
            }
            listPtr->count--;
            free(q);
        }
    }
}

void DOOM_THE_LIST(ListT *listPtr)
{
    NodeT *p,*q;
    p = listPtr->first;
    while (p != listPtr->last)
    {
        q = p;
        p = p->next;
        free(q);
    }
    free(p);
    listPtr->first = listPtr->last =NULL;
    listPtr->count = 0;
}

void DE(ListT *listPtr, int value)
{
    NodeT *q,*q1;
    q1 = NULL;
    q = listPtr->first;
    while (q != NULL)
    {
        if( q->value == value ) break;
        q1 = q;
        q = q->next;
    }
    if ( q != NULL )
    {
        if( q == listPtr->first )
        {
            listPtr->first = listPtr->first->next;
            free(q);
        }
        else
        {
            q1->next = q->next;
            if ( q == listPtr->last ) listPtr->last = q1;
            free(q);
        }
        listPtr->count--;
    }
}

void PRINT_ALL(ListT *listPtr,char *file_name)
{
    NodeT *p;
    FILE *file = fopen(file_name,"a");
    p = listPtr->first;
    while ( p != NULL)
    {
        fprintf(file,"%d ",p->value);
        printf("%d ",p->value);
        p = p->next;
    }
    fprintf(file,"\n");
    fclose(file);
}

void PRINT_F(ListT *listPtr,char *file_name,int nr)
{
    NodeT *p;
    int count=0;
    p = listPtr->first;
    FILE *file = fopen(file_name,"a");
    while ( p !=NULL && count < nr )
    {
        fprintf(file,"%d ",p->value);
        count++;
        p = p->next;
    }
    fprintf(file,"\n");
    fclose(file);
}
/* *****

This one can be tricky because we work on a singly linked list, not a doubly linked list,
we can't start from the end, only from the front and we can only go one way(forward) in the
list, not backwards

******** */

void PRINT_L(ListT *listPtr,char *file_name, int nr)  //merge
{
    NodeT *p;
    ///FILE *file=fopen(file_name,"a");
    p = listPtr->first;
    int x,count = 0;
    x = listPtr->count - nr; //we find on how many characters we have to skip
    if (x > 0)
    {
        while( count < x )
        {
            p = p->next;
            count++;
        }
    }
    else
    {
        PRINT_ALL(listPtr,file_name);
        return;
    }
    FILE *file=fopen(file_name,"a");
    while ( p != NULL )
    {
        fprintf(file,"%d ",p->value);
        p = p->next;
    }
    fprintf(file,"\n");
    fclose(file);
}


int main()
{
    ListT *list;
    list = createSLL();
    FILE *pt = fopen("input.txt","r");
    FILE *pt1 = fopen("output.txt","w"); //to delete all the previous contents of the file
    fclose(pt1);
    char s[50], file[15];
    int value;
    NodeT *p;
    strcpy(file,"output.txt");
    while( fgets(s,49,pt) != NULL )
    {
        if ( strncmp(s,"AF",2) == 0)
        {
            value = atoi(s+3);
            p = createSLLNode(value);
            AF(list,p);
            //fgetc(pt);
        }
        else if ( strncmp(s,"AL",2) == 0)
        {
            value = atoi(s+3);
            p = createSLLNode(value);
            AL(list,p);
        }
        else if ( strncmp(s,"DF",2) == 0)
        {
            DF(list);
        }
        else if ( strncmp(s,"DL",2) == 0)
        {
            DL(list);
        }
        else if ( strncmp(s,"DOOM_THE_LIST",13) == 0)
        {
            DOOM_THE_LIST(list);
        }
        else if ( strncmp(s,"DE",2) == 0)
        {
            value = atoi(s+3);
            DE(list,value);
        }
        else if ( strncmp(s,"PRINT_ALL",9) == 0)
        {
            PRINT_ALL(list,file);
        }
        else if ( strncmp(s,"PRINT_F",7) == 0)
        {
            value = atoi(s+8);
            PRINT_F(list,file,value);
        }
        else if ( strncmp(s,"PRINT_L",7) == 0)
        {
            value = atoi(s+8);
            PRINT_L(list,file,value);
        }
    }
    printf("%d ",list->last->value);

    fclose(pt);
    DOOM_THE_LIST(list);
    free(list);

    return 0;
}
