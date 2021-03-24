#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// prima data imi fac structuri pt tree

typedef struct node{
    char key[20];
    struct node *right,*left;
}NodeT;

//creez structura pentru stiva

typedef struct nodeStack{
    char key[10];
    struct nodeStack *next;
    NodeT *nodeToTree;   // imi trebuie ca sa inlantui nodurile intre ele, sa nu pierd informatie cand bag in stiva, am facut fara si imi dadea gresit, am facut bkt si am realizat
}NodeS;

//creare header stiva

typedef struct {
    int nr;
    NodeS *top,*bottom;
}stack;

//imi trebuie functie de creare a nodurilor din tree

NodeT *createNodeTree(char *word){
    NodeT *node;
    node = (NodeT*)malloc(sizeof(NodeT));
    if ( node == NULL ){
        printf("ERROR\n");
        exit(1);
    }
    strcpy(node->key,word);
    node->right = node->left = NULL;
    return node;
}

// imi trebuie functie de creare a nodurilor din stiva

NodeS *createNodeStack(NodeT *node){      // creare node stack
    NodeS *p;
    p = (NodeS*)malloc(sizeof(NodeS));
    if ( p == NULL) {
        printf("ERROR\n");
        exit(1);
    }
    strcpy(p->key,node->key);
    p->next = NULL;
    p->nodeToTree = node; // vezi mai sus, treuie pt a nu pierde informatie
   return p;
}

stack *createEmptyStack(){   //creare empty stack care va fi folosit pt stocarea nodurilor
    stack *s = (stack*)malloc(sizeof(stack));
    if ( s == NULL){
        printf("ERROR\n");
        exit(1);
    }
    s->nr = 0;
    s->bottom = s->top = NULL;
    return s;
}

void push(stack *s,NodeT *node){  //introduce un node in stack
    NodeS * stackNode = createNodeStack(node);
    if ( s->top == NULL && s->bottom == NULL){
        s->top = s->bottom = stackNode;
    }
    else{
        stackNode->next = s->top;
        s->top = stackNode;
    }
    s->nr++;
}

NodeS *pop(stack *s){  //scoate un node din stack, acesta fiind de tip NodeS
    NodeS *temp = s->top;
    if ( s->top == NULL && s->bottom == NULL ){
        printf("stack empty\n");
        return NULL;
    }
    else if ( s->nr == 1){
        s->top = s->bottom = NULL;
    }
    else{
        s->top = s->top->next;
    }
    s->nr--;
    return temp;
}

void *reverse(char *string)  //idee, mai intai fac o copie la sir, o sparg cu strtok si numar cate cuvine am
{
    int len = strlen(string);
    char v[100]="";
    char *p = strtok(string," ");
    char aux;
    while ( p != NULL )
    {
        for (int i = 0; i < strlen(p)/2; i++)
        {
            aux = p[i];
            p[i] = p[strlen(p)-i-1];
            p[strlen(p)-i-1] = aux;
        }
        strcat(v,p);
        strcat(v," ");
        p = strtok(NULL," ");
    }
    v[len] = '\0';
    for (int i = 0; i < strlen(v)/2; i++)
    {
        aux = v[i];
        v[i] = v[strlen(v)-i-1];
        v[strlen(v)-i-1] = aux;
    }
    strcpy(string,v);
    printf("%s\n",string);
}

int isOp(char *c){
    if (( c[0] == '+' || c[0] == '-' || c[0] == '*' || c[0] == '/' )  &&  isdigit(c[1]) == 0 )
        return 1;
    else return 0;
}

NodeT *builtTree(char *string){
    NodeT *root;  //crearea root-ului tree-ului
    NodeT *myTreeNode;
    stack *myStack = createEmptyStack();  // crearea stack-ului pe care il voi folosi pt a forma tree-ul
    NodeS *a,*b; // cele doua noduri carora le voi da pop pentru a fi introdu-se in tree
    reverse(string); // inversez string-ul pentru ca acesta este dat in prefix form, iar eu voi lucra in postfix, fiind mai usor asa
    char *p = strtok(string," "); //sparg string-ul in cuvinte
    while ( p != NULL ){
        //myTreeNode = createNodeTree(p);
        if ( isOp(p) == 0 ){
            myTreeNode = createNodeTree(p);
            push(myStack,myTreeNode);
        }
        else{
            a = pop(myStack);
            b = pop(myStack);

            myTreeNode = createNodeTree(p);
            myTreeNode->left = a->nodeToTree;
            myTreeNode->right = b->nodeToTree;

            push(myStack,myTreeNode);
            free(a);
            free(b);
        }
        p = strtok(NULL," ");
    }
    root = myTreeNode;
    free(myStack);
    return root;
}

void preorder(NodeT *root){
    if ( root != NULL ){
        printf("%s ",root->key);
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(NodeT *root){
    if ( root != NULL ){
        inorder(root->left);
        printf("%s ",root->key);
        inorder(root->right);
    }
}

void postorder(NodeT *root) {
    if ( root != NULL ) {
        postorder(root->left);
        postorder(root->right);
        printf("%s ", root->key);
    }
}

int main() {
    char string[100];
    NodeT *root;
    scanf("%[^\n]",string);  //nu asta cu fgets era problema
    root = builtTree(string);
    preorder(root);
    printf("\n");
    inorder(root);
    printf("\n");
    postorder(root);
    printf("\n");

    return 0;
}
