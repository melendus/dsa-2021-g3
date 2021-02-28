#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int id;
    struct node *next;
}NodeT;

typedef struct
{
    int count;
    NodeT *first;
    NodeT *last;
}ListT;

ListT *createEmptySLL() //the road is a SSL(singly linked list)
{
    ListT *listPtr=(ListT*)malloc(sizeof(ListT));
    if(listPtr)
    {
        listPtr->count=0;
        listPtr->first=listPtr->last=NULL;
    }
    return listPtr;
}

NodeT *createSLLNode(int id)
{
    NodeT *truck=(NodeT*)malloc(sizeof(NodeT));
    if(truck)
    {
        truck->id=id;
        truck->next=NULL;
    }
    return truck;
}

int isEmpty(ListT *listPtr)
{
    if (listPtr->first==NULL && listPtr->last==NULL)
        return 1;
    else return 0;
}

void insertAtFront(ListT *listPtr, NodeT *truck)
{
   if (listPtr)
   {
       truck->next=listPtr->first;
        if (isEmpty(listPtr))
        {
            listPtr->last=truck;
        }
        listPtr->first=truck;
        listPtr->count++;
    }
}

NodeT *deleteById(ListT *listPtr, int givenid)
{
    NodeT *q, *q1;
    q1=NULL;
    q=listPtr->first;
    while(q!=NULL)
    {
        if(q->id==givenid) break;
        q1=q;
        q=q->next;
    }
    if(q!=NULL)
    {
        if(q==listPtr->first)
        {
            listPtr->first=listPtr->first->next;
            if(listPtr->first==NULL) listPtr->last=NULL;
        }
        else
        {
            q1->next=q->next;
            if(q==listPtr->last) listPtr->last=q1;
        }
    }
    return q;
}

NodeT *deleteFirst(ListT *listPtr)
{
    NodeT *p;
    if(listPtr->first!=NULL)
    {
        p=listPtr->first;
        listPtr->first=listPtr->first->next;
        listPtr->count--;
        if(listPtr->first==NULL)
            listPtr->last=NULL;
        return p;
    }
    return NULL;
}

void show(ListT *listPtr,char *pt1,char mode)
{
    //FILE *argv=fopen(pt1,"a");
    //fprintf(argv,"%c: ",mode);
    NodeT *p;
    if(listPtr->first!=NULL)
    {
        p=listPtr->first;
    }
    else
    {
        FILE *argv=fopen(pt1,"a");
        fprintf(argv,"%c: ",mode);
        fprintf(argv,"none\n");
        fclose(argv);
        return;
    }
    FILE *argv=fopen(pt1,"a");
    fprintf(argv,"%c: ",mode);
    if(mode=='R')
    {
    do
    {
        fprintf(argv," %d",p->id);
        p=p->next;
    }while(p!=listPtr->first);
    }
    else if (mode=='G')
    {
        while(p!=NULL)
        {
            fprintf(argv," %d",p->id);
            p=p->next;
        }
    }                                         // nu inteleg dc daca fac cu un singur do while si pun la while conditia while(p!=listPtr || p!=NULL) imi intra intr-un loop
    fprintf(argv,"\n");
    fclose(argv);
}

void R(int id,ListT *road)  //R este de creare a unui nod/truck si plasarea lui intr-o lista, doar ca acum, dupa ce introduce un nod, ultimul va indica spre primul, devenind circulara
{
    NodeT *truck;
    truck=createSLLNode(id);
    insertAtFront(road,truck);
    road->last->next=road->first;
}

void E(int id, ListT *garage,ListT *road,char *pt1) //mutarea unui truck de pe road in garaj, adica din queue in stack
{
    //FILE *argv=fopen(pt1,"a");
    NodeT *truck;
    //truck=deleteById(road,id);
    if(road->last->id==id)
    {
        truck=deleteById(road,id);
        insertAtFront(garage,truck);
        road->last->next=road->first;
    }
    else
    {
        FILE *argv=fopen(pt1,"a");
        fprintf(argv,"error: %d not on road or at the front of queue\n",id);
        fclose(argv);
        return;
    }
}

void X(int id, ListT *road, ListT *garage,char *pt1)  //scoate din garaj, din stack si introduce la inceputul queue
{
    //FILE *argv=fopen(pt1,"a");
    NodeT *truck;
    if (garage->first->id!=id)
    {
        FILE *argv=fopen(pt1,"a");
        fprintf(argv,"error: %d not at exit!\n",id);
        fclose(argv);
        return;
    }
    else
    {
        truck=deleteFirst(garage);
        insertAtFront(road,truck);
        road->last->next=road->first;
    }
}

void S(char mode,ListT *road, ListT *garage,char *pt1)
{
    //FILE *argv=fopen(pt1,"a");
    switch(mode)
    {
    case 'R':
        //fprintf(argv,"%c:",mode);
        show(road,pt1,mode);
        //fprintf(argv,"\n");
        break;
    case 'G':
        //fprintf(argv,"%c:",mode);
        show(garage,pt1,mode);
        //fprintf(argv,"\n");
        break;
    }
}
void purge1(ListT *listPtr)
{
NodeT *p;
while ( listPtr->first != NULL )
{
p = listPtr->first;
listPtr->first = listPtr->first->next;
free( p );
}
listPtr->last = NULL;
listPtr->count = 0;
}
void purge2(ListT *listPtr)
{
NodeT *p;
listPtr->last->next = NULL;
while ( listPtr->first != NULL )
{
p = listPtr->first;
listPtr->first = listPtr->first->next;
free( p );
}
listPtr->last = NULL;
listPtr->count = 0;
}

int main(int argc, char *argv[])
{
    ListT *road, *garage;
    road=createEmptySLL();
    garage=createEmptySLL();
    FILE *pt=fopen(argv[1],"r");
    FILE *pt1=fopen(argv[2],"w");
    //fclose(pt1);
    char mode,mode1;
    int id;
    while (fscanf(pt,"%c)",&mode)!=EOF)
    {
        switch(mode)
        {
        case 'R':
            fscanf(pt,"(%d)",&id);
            R(id,road);
            fgetc(pt);

            break;
        case 'E':
            fscanf(pt,"(%d)",&id);
            E(id,garage,road,argv[2]);
            fgetc(pt);
            break;
        case 'X':
            fscanf(pt,"(%d)",&id);
            X(id,road,garage,argv[2]);
            fgetc(pt);
            break;
        case 'S':
            fscanf(pt,"(%c)",&mode1);
            S(mode1,road,garage,argv[2]);
            fgetc(pt);
        }
    }
    fclose(pt);
    fclose(pt1);
    purge1(garage);
    purge2(road);
    free(garage);
    free(road);
    return 0;
}
