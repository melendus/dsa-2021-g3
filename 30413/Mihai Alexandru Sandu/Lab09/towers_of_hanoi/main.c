#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int value;
    struct node *next;
}NodeT;

typedef struct stack{
    int nr;
    NodeT *top;
    NodeT *bottom;
}StackT;

NodeT *createNode(int value){
    NodeT *node = (NodeT*)malloc(sizeof(NodeT));
    if (node == NULL){
        printf("ERROR: NODE WAS NOT ALLOCATED");
        exit(1);
    }
    node->next = NULL;
    node->value = value;
    return node;
}

StackT *createEmptyStack(){
    StackT *stack = (StackT*)malloc(sizeof(StackT));
    if (stack == NULL){
        printf("ERROR: STACK WASN'T ALLOCATED");
        exit(1);
    }
    stack->bottom = stack->top = NULL;
    stack->nr = 0;
    return stack;
}

void push(StackT *stack,int value){
    NodeT *node = createNode(value);
    if (stack->nr == 0){
        stack->top = stack->bottom = node;
    }
    else{
        node->next = stack->top;
        stack->top = node;
    }
    stack->nr++;
}

int pop(StackT *stack){   // functie care returneaza ultima valoare de pe stack
    NodeT *top;
    top = stack->top;
    int value;
    if (top == NULL)
        return NULL;
    if (stack->nr == 1){
        value = stack->top->value;
        free(stack->top);
        free(stack->bottom);
    }
    else{
        value = stack->top->value;
        stack->top = stack->top->next;
        free(top);
    }
    stack->nr--;
    return value;
}

void printStack(StackT *stack,char tower){
    NodeT *p;
    p = stack->top;
    printf("%c : ");
    if ( stack->nr == 0){
        printf("TOWER EMPTY\n");
        return;
    }
    while (p != NULL){
        printf("%d ",p->value);
        p = p->next;
    }
    printf("\n");
}

void moveDisc(StackT *from,StackT *to){
    push(to,pop(from));  // aici, mut pe turnul to, care inseamna turnul pe care vreau sa mut, pe de turnul from. pop returneaza un int, iar acel int este dat ca parametrul functiei push
}

void hanoi(int n, StackT *from, StackT *to, StackT *aux,char fromT,char toT, char auxT){
    if (n == 1){
        //printf("move disk 1 from %c to %c\n",from,to);    // move 1 disc from a to c
        moveDisc(from,to);
        printStack(from,fromT);
        printStack(to,toT);
        printStack(aux,auxT);
        return;
    }
    hanoi(n - 1,from,aux,to,fromT,auxT,toT); // move n - 1 disks from a to b
    moveDisc(from,to);
    printStack(from,fromT);
    printStack(to,toT);
    printStack(aux,auxT);
    //printf("move disk %d from %c to %c\n",n,from,to);
    hanoi(n - 1,aux,to,from,auxT,toT,fromT);  // move n - 1 disks from b to c
}
//partea mai dificila acum, de afisat ce se afla pe tower-uri


int main() {
    StackT *a = createEmptyStack();
    for (int i = 3; i >= 1; i--){
        push(a,i);
    }
    StackT *b = createEmptyStack();
    StackT *c = createEmptyStack();
    hanoi(3,a,b,c,'A','C','B');
    return 0;
}
