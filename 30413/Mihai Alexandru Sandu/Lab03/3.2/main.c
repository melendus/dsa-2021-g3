#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    char word[20];
    int count;
    struct node *next;
    struct node *prev;
}NodeT;

typedef struct
{
    int count;
    NodeT *first;
    NodeT *last;
}DLListT;

DLListT *createEmptyDLL()
{
    DLListT *listPtr = (DLListT*)malloc(sizeof(DLListT));
    if(listPtr)
    {
        listPtr->count = 0;
        listPtr->first = listPtr->last = NULL;
    }
    return listPtr;
}

NodeT *createDLLNode(char *word)
{
    NodeT *p = (NodeT*)malloc(sizeof(NodeT));
    if(p)
    {
        strcpy(p->word, word);
        p->next = p->prev = NULL;
        p->count = 1;
    }
    return p;
}

int CheckDuplicate(char *word, DLListT *list)
{
    NodeT *p;
    p = list->first;
    if(list)
    {
        while(p != NULL)
        {
            if(strcmp(p->word,word) == 0)
            {
                p->count++;
                return p->count;
            }
            else p = p->next;
        }
        return 0;
    }
}

void AddFirst(NodeT *node, DLListT *list)
{
    if (list)
    {
        if( list->first == NULL && list->last == NULL) //lista este goala
        {
            list->first = list->last = node;
            node->next = node->prev = NULL;
        }
        else
        {
            node->next = list->first;
            list->first->prev = node;
            list->first = node;
            node->prev = NULL;
        }
        list->count++;
    }
}

void AddLast(NodeT *node, DLListT *list)
{
    if (list)
    {
        if(list->first == NULL) //lista este goala
        {
            list->first = list->last = node;
            node->next = node->prev = NULL;
        }
        else
        {
            list->last->next = node;
            node->prev = list->last;
            list->last = node;
            node->next = NULL;
        }
        list->count++;
    }
}


void AddByOrder(DLListT *list, NodeT *node)
{
    NodeT *p1,*p2;
    p1 = list->first;
    p2 = list->first->next;
    if (list)
    {
        while (p2 != NULL)
        {
            if (stricmp(p1->word,node->word)<0 && stricmp(p2->word,node->word)>0)
            {
                p1->next = node;
                node->next = p2;
                node->prev = p1;
                p2->prev = node;
                list->count++;
                return;
            }
            else
            {
                p1 = p1->next;
                p2 = p2->next;
            }
        }
    }
}

void show(DLListT *list, char *argv)
{
    FILE *out = fopen(argv,"w");
    NodeT *p;
    p = list->first;
    while (p !=NULL)
    {
        fprintf(out,"%s: %d\n",p->word,p->count);
        p = p->next;
    }
    p = list->last;
    fprintf(out,"\n\n\n");
    while(p != NULL)
    {
        fprintf(out,"%s: %d\n",p->word,p->count);
        p = p->prev;
    }
    fclose(out);
}


int main(int argc, char *argv[])
{
    FILE *in = fopen(argv[1],"r");
    char word[20];
    DLListT *list;
    NodeT *node;
    list = createEmptyDLL();
    while (fscanf(in,"%s",word) != EOF)
    {
        node = createDLLNode(word);
        if (list->first == NULL && list->last == NULL)
        {
            //node = createDLLNode(word);
            AddFirst(node,list);
        }
        else if (CheckDuplicate(word,list) == 0)
        {
            //node = createDLLNode(word);
            if (stricmp(node->word,list->first->word) < 0)
            {
                AddFirst(node,list);
            }
            else if (stricmp(node->word,list->last->word) > 0)
            {
                AddLast(node,list);
            }
            else
            {
                AddByOrder(list,node);
            }
        }
    }
    show(list,argv[2]);
    return 0;
}
