#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    char id;
    struct node *left;
    struct node *right;
}NodeT;

NodeT *createbinaryTree()
{
    char id;
    scanf("%c",&id);
    if (id == '*') return NULL;
    NodeT *p;
    p = (NodeT*)malloc(sizeof(NodeT));
    if (p == NULL)
        exit(1);
    p->id = id;
    p->left = createbinaryTree();
    p->right = createbinaryTree();
    return p;
}
void preorder(NodeT *node)
{
    if (node)
    {
        printf("%c ",node->id);
        preorder(node->left);
        preorder(node->right);
    }
}

void inorder(NodeT *node)
{
    if (node)
    {
        inorder(node->left);
        printf("%c ",node->id);
        inorder(node->right);
    }
}

void postorder(NodeT *node)
{
    if(node)
    {
        postorder(node->left);
        postorder(node->right);
        printf("%c ",node->id);
    }
}
static int nr1 = 0;

int numberOfNodes(NodeT *node)
{
    if(node)
    {
        nr1++;
        numberOfNodes(node->left);
        numberOfNodes(node->right);
    }
    return nr1;
}

NodeT *postorderFind(NodeT *node,char c)
{
    if(node == NULL)
        return NULL;

    if(node->id == c)
        return node;

    postorderFind(node->left,c);
    postorderFind(node->right,c);
}

void interchange(char id,NodeT *root,int nr1)  //face bine
{
    NodeT *node;
    NodeT *aux;
    node = postorderFind(root,id);
    if (node != NULL)
    {
        aux = node->left;
        node->left = node->right;
        node->right = aux;
        return;
    }
    else
    {
        printf("such a node doesn't exist\n");
        return;
    }
}
int max(int a, int b)
{
    if (a>b)
        return a;
    else return b;
}
int FindHeight(NodeT *node)
{
    if (node == NULL)
        return -1;
    int max1 = FindHeight(node->left);
    int max2 = FindHeight(node->right);
    return max(max1,max2)+1;
}
int FindLeaves(NodeT *node)
{
    if (node == NULL) return 0;
    if (node->left == NULL && node->right == NULL) return 1;
    return FindLeaves(node->left)+FindLeaves(node->right);
}

int main()
{
    NodeT *root;
    int height,leaves;
    root = createbinaryTree();
    height = FindHeight(root);
    leaves = FindLeaves(root);
    preorder(root);
    printf("\n");
    printf("%d\n",numberOfNodes(root));
    interchange('K',root,nr1);
    preorder(root);
    printf("\n");
    inorder(root);
    printf("\n");
    postorder(root);
    printf("\n");
    printf("height = %d and leaves = %d",height,leaves);
    return 0;
}
