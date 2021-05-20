#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    struct node *north;
    struct node *east;
    struct node *north_east;
}Node;

Node *createNode(/*int x,int y,int z*/) {
    Node *node = (Node*)malloc(sizeof(Node));

    node->east = NULL;
    node->north = NULL;
    node->north_east = NULL;

    return node;
}

void addNode(Node *node) {
    Node *node = createNode();

}

typedef struct {
    Node *root;
    int leaf;
}Tree;

Tree *createEmptyTree() {
    Tree *tree = (Tree*)malloc(sizeof(Tree));
    if (tree == NULL) {
        exit(1);
    }
    return tree;
}

int checkToInsert(int matrice[2][3],int i, int j) {
    if (i == 0)
        return -1;
    if (j == 2)
        return (-1);
}



int main() {
    int N = 2;
    int M = 3;
    int matrice[2][3];
    Tree tree = createEmptyTree();
    tree.root = createNode();

    for(int i = 0;i < 2;i++){
        for (int j = 0;j < 3;j++) {
            if (checkToInsert(matrice,i,j))
                tree.root->east = createNode();
        }
    }



    return 0;
}


