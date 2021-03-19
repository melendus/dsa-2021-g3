#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    char key;
    struct node *left;
    struct node *right;
}BSTNodeT;

BSTNodeT *createNode(char key)         //create a node with a given key
{
    BSTNodeT *node = (BSTNodeT*)malloc(sizeof(BSTNodeT));
    if (node)
    {
        node->key = key;
        node->left = node->right = NULL;
    }
    return node;
}

BSTNodeT *findNode(BSTNodeT *root,char key)
{
    if (root == NULL) return NULL;
    if (key < root->key)
        root = findNode(root->left,key);
    else if (key > root->key)
        root = findNode(root->right,key);
    else return root;
}

BSTNodeT *insertNode(BSTNodeT *root,char key)
{
    if (root == NULL)
        return createNode(key);
    else
    {
        if ( key < root->key )
            root->left = insertNode(root->left,key);
        else if ( key > root->key)
            root->right = insertNode(root->right,key);
        else printf("\n Node with key = %c already exists\n",key);
    }
    return root;
}

BSTNodeT *findMin(BSTNodeT *node)
{
    if ( node == NULL )
        return NULL;

    if ( node->left )
    {
        node = findMin(node->left);
    }
    return node;
}

BSTNodeT *findMax(BSTNodeT *node)
{
    if (node == NULL)
        return NULL;
    if (node->right)
        node = findMax(node->right);
    return node;
}

BSTNodeT *deleteNode(BSTNodeT *node, char key,char *argv)
{
    FILE *out;
    if ( node == NULL)
    {
        out = fopen(argv,"a");
        fprintf(out,"Node doesn't exist\n");
        fclose(out);
    }
    else if (key < node->key)
    {
        node->left = deleteNode(node->left,key,argv);
    }
    else if ( key > node->key)
    {
        node->right = deleteNode(node->right,key,argv);
    }
    else  //daca am gasit nodul
    {
        if ( node->left == NULL && node->right == NULL)  // e frunza
        {
            BSTNodeT *temp = node;
            node = NULL;
            free(temp);
        }
        else if ( node->left != NULL && node->right == NULL)
        {
            BSTNodeT *temp = node;
            node = node->left;
            free(temp);
        }
        else if ( node->left == NULL && node->right != NULL )
        {
            BSTNodeT *temp = node;
            node = node->right;
            free(temp);
        }
        else
        {
            BSTNodeT *temp = findMin(node->right);
            node->key = temp->key;
            node->right = deleteNode(node->right,temp->key,argv);
        }
    }
    return node;
}

void preorder(BSTNodeT *root,char *argv)
{
    FILE *out;
    if (root)
    {
        out = fopen(argv,"a");
        fprintf(out,"%c ",root->key);
        fclose(out);
        preorder(root->left,argv);
        preorder(root->right,argv);
    }
}

void postorder(BSTNodeT *root,char *argv)
{
    FILE *out;
    if (root)
    {
        postorder(root->left,argv);
        postorder(root->right,argv);
        out = fopen(argv,"a");
        fprintf(out,"%c ",root->key);
        fclose(out);
    }
}

void inorder(BSTNodeT*root,char *argv)
{
    FILE *out;
    if(root)
    {
        preorder(root->left,argv);
        out = fopen(argv,"a");
        fprintf(out,"%c ",root->key);
        fclose(out);
        preorder(root->right,argv);
    }
}

void preorder1(BSTNodeT *root)
{
    if (root)
    {
        printf("%c ",root->key);
        preorder1(root->left);
        preorder1(root->right);
    }
}
int main(int argc ,char *argv[])
{
   BSTNodeT *root = NULL;
  BSTNodeT *NodeToBeFound;
   FILE *in = fopen(argv[1],"r");
   FILE *out = fopen(argv[2],"w");
   fclose(out);
   char code[2];
   while (fscanf(in,"%s",code) == 1)
   {
       switch(code[0])
       {
           case 'i':
               root = insertNode(root,code[1]);
               break;

           case 'd':
               root = deleteNode(root,code[1],argv[2]);
               break;

           case 'f':
            NodeToBeFound = findNode(root,code[1]);
            if (NodeToBeFound != NULL)
            {
                out = fopen(argv[2],"a");
                fprintf(out,"The node was found\n");
                fclose(out);
            }
            break;

           case 't':
            switch(code[1])
            {
                case 'p':
                    preorder(root,argv[2]);
                    out = fopen(argv[2],"a");
                    fprintf(out,"\n");
                    fclose(out);
                    break;

                case 'P':
                    postorder(root,argv[2]);
                    out = fopen(argv[2],"a");
                    fprintf(out,"\n");
                    fclose(out);
                    break;

                case 'i':
                    inorder(root,argv[2]);
                    out = fopen(argv[2],"a");
                    fprintf(out,"\n");
                    fclose(out);
                    break;
            }
                case 'g':
                    switch (code[1])
                    {
                    case 'm':
                         NodeToBeFound = findMin(root);
                         out = fopen(argv[2],"a");
                         fprintf(out,"The min node is :%c\n",NodeToBeFound->key);
                         fclose(out);
                         break;

                    case 'M':
                        NodeToBeFound = findMax(root);
                        out = fopen(argv[2],"a");
                        fprintf(out,"The max node is: %c\n",NodeToBeFound->key);
                        fclose(out);
                        break;
                    }
       }
   }
    return 0;
}
