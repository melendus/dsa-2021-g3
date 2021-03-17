#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    float key;
    struct node *left;
    struct node *right;
}NodeT;

NodeT *createBinaryTree()
{
    int key;
    scanf("%d",&key);
    if ( key == -1 ) return NULL;
    NodeT *p;
    p = (NodeT*)malloc(sizeof(NodeT));
    if ( p == NULL )
        exit(1);
    p->key = key;
    p->left = createBinaryTree();
    p->right = createBinaryTree();
    return p;

}

void inOrder(NodeT *node)
{
    if (node)
    {
        inOrder(node->left);
        printf("%f ",node->key);
        inOrder(node->right);
    }
}

void NrOfNodes(NodeT *node,int *nr) //calculeaza numarul de noduri ale unui tree cu radacina in node
{
    //static int nr = 0;
    if ( node )
    {
        *nr = *nr +1;
        NrOfNodes(node->left,nr);
        NrOfNodes(node->right,nr);
    }
    //return nr;
}
void NrOfMonths(NodeT *node,float *nr) //calculeaza numarul de months al unui tree cu radacina in node
{
//    static int nr = 0;
    if( node )
    {
        *nr = *nr +node->key;
        NrOfMonths(node->left,nr);
        NrOfMonths(node->right,nr);
    }
    //return nr;
}



void *OldestManager(NodeT *node,float *base,NodeT **manager)
{
    if (( node == NULL ) || ( node->left == NULL && node->right == NULL))
        return;
    float maximum = 0;
    int nr = 0;
    NrOfMonths(node,&maximum);
    NrOfNodes(node,&nr);
    maximum = maximum / nr;
    printf("%f\n",maximum); //printeaza bine
    if (maximum > *base)
    {
        *base = maximum;
        *manager = node;
    }
    OldestManager(node->left,base,manager);
    OldestManager(node->right,base,manager);
}

int main()
{
    NodeT *root;
    root = createBinaryTree();
    inOrder(root);
    int nr = 0;
    NrOfNodes(root,&nr);
    printf("\n%d",nr);
    float nr1 = 0;
    NrOfMonths(root,&nr1);
    printf("\n%f",nr1);
    float nr2;
    //float m = 0, n = 0;
    //nr2 = (float)NrOfMonths(root,&m)/(float)NrOfNodes(root,&n);
    //printf("\n%f",nr2);
    //NodeT *node;

    NodeT *manager = (NodeT*)malloc(sizeof(NodeT));
    manager->key = 0;
    float base = 0;

   OldestManager(root,&base,&manager);
    printf("\n%f",manager->key);
    return 0;
}
