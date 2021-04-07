#include <stdio.h>
#include <stdlib.h>

// voi folosi o matrice de adiacenta, deoarece pozitiile imi sunt da-te
// o lista inlantuita, pentru printare
// va trebui sa declar o lista si functiile necesare
// pentru a citi elementele:
// 1) mai intai imi fac o matrice de n*2 ( pe fiecare linie din matrice voi avea doua nr, de ex 1 2 )
// caut maximul din matricea asta
// creez matrice de adiacenta
// apoi voi introduce in lista nodurile, conform matricei de adiacenta

typedef struct node{
    int value;
    struct node *next;
}NodeT;

typedef struct list{
    int count;
    NodeT *first;
    NodeT *last;
}ListHeader;

ListHeader *createEmptyList(){
    ListHeader *list = (ListHeader*)malloc(sizeof(ListHeader));
    if (list == NULL){
        printf("ERROR: LIST ALLOCATION");
        exit(1);
    }
    list->first = list->last = NULL;
    list->count = 0;
    return list;
}

NodeT *createNode(int value){
    NodeT *p = (NodeT*)malloc(sizeof(NodeT));
    if (p == NULL){
        printf("ERROR: NODE ALLOCATION");
        exit(1);
    }
    p->value = value;
    p->next = NULL;
    return p;
}

void addLast(ListHeader *list,int value){
    if(list == NULL){
        printf("ERROR: LIST ALLOCATION");
        exit(1);
    }
    NodeT *p = createNode(value);
    if(list->first == NULL && list->last == NULL){
        list->first = list->last = p;
    }
    else {
        list->last->next = p;
        list->last = p;
    }
    list->count++;
}

NodeT *findNode(ListHeader *list,int value){
    NodeT *q;
    q = list->first;
    while (q != NULL){
        if(q->value == value){
            return q;
        }
        q = q->next;
    }
    if (q == NULL)
        return NULL;
}

int **initialArray(int value){
    int **array = (int**)malloc(value*sizeof(int*));
    for(int i = 0;i < value;i++){
        array[i] = (int*)malloc(2*sizeof(int));
    }
    return array;
}
void switchNodes(ListHeader *list,int a,int b) {
    if (a == b) // daca sunt egale nu trb sa fac nimic
        return;
    NodeT *prevA = NULL;
    NodeT *currA = list->first;
    while (currA != NULL) {
        if (currA->value == a)
            break;
        prevA = currA;
        currA = currA->next;
    }
    NodeT *prevB = NULL;
    NodeT *currB = list->first;
    while (currB != NULL) {
        if (currB->value == b)
            break;
        prevB = currB;
        currB = currB->next;
    }
    if (currA == NULL || currB == NULL)
        return;

    if (prevA != NULL) //a nu este list->first
        prevA->next = currB;
    else
        list->first = currB;

    if (prevB != NULL) //b nu este list->first
        prevB->next = currA;
    else
        list->first = currA;

    NodeT *temp = currB->next;
    currB->next = currA->next;
    currA->next = temp;
}

int **getAdjMatrix(int *max){  //returneaza nodul cu numarul maxim pentru a putea crea o matrice max*max si in acelasi timp imi introduce intr-un array mai mic toate valorile citite
    int nr;
    int a,b;
    int i;
    int x,y;
    scanf("%d",&nr);
    int **array = (int**)malloc(nr*sizeof(int*));  // creez o matrice[nr][2] ca sa stochez input-urile
    for(i = 0;i < nr;i++){
        array[i] = (int*)malloc(2*sizeof(int));
    }
    for(i = 0;i < nr;i++){
        scanf("%d%d",&a,&b);
        array[i][0] = a;
        array[i][1] = b;
        if (a > *max) *max = a;
        else if (b > *max) *max = b;
    }

    int **adjMatrix = (int**)calloc(*max,sizeof(int*));
    for(i = 0;i < *max;i++){
        adjMatrix[i] =(int*)calloc(*max,sizeof(int));
    }
    for(i = 0;i < nr;i++){
        x = array[i][0]-1;
        y = array[i][1]-1;
        adjMatrix[x][y] = 1;
    }
    return adjMatrix;
}

void createAndSort(ListHeader *list,int max,int **adjMatrix){
    int i,j;
    int a,b;
    for(i = 1;i <= max; i++){  // creaza o lista neordonata cu toate nodurile, de ex 1-> 2-> 3-> 4
        addLast(list,i);
    }
    for(i = 0;i < max;i++){
        for(j = 0;j < max;j++){
            if ( i > j && adjMatrix[i][j] == 1){
                a = i+1;
                b = j+1;
                switchNodes(list,a,b);
            }
        }
    }
}

void printList(ListHeader *list){
    NodeT *q = list->first;
    while (q != NULL){
        printf("%d ",q->value);
        q = q->next;
    }
}

int main() {
    ListHeader *list;
    int max = 0;
    list = createEmptyList();
    int ** adjMatrix = getAdjMatrix(&max);
    createAndSort(list,max,adjMatrix);
    printList(list);
    return 0;
}
