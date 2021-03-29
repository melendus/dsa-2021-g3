#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define B 10

typedef struct node{ //bucket table
    char key[60];
    struct node *next;
}NodeT;

void empty(NodeT *node[]){
    for (int i = 0; i < B; i++)
        node[i] = NULL;
}

int hash(char *key){
    int sum,len;
    sum = 0;
    len = strlen(key);
    for (int i = 0; i < len; i++)
        sum += key[i];
    return (sum % B);
}

NodeT *find(char *key,NodeT *BucketTable[]){
    int hashValue = hash(key);
    NodeT *p;
    //p = (NodeT*)malloc(sizeof(NodeT));
    p = BucketTable[hashValue];
    while (p != NULL){
        if (strcmp(key,p->key) == 0) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

void insert(char *key,NodeT *BucketTable[],char *fileName){
    NodeT *p,*found;
    int h;
    FILE *out = fopen(fileName,"a");
    p = (NodeT*)malloc(sizeof(NodeT));
    if (p){
        strcpy(p->key,key);
        //p->next = NULL;
        h = hash(key);
        if (BucketTable[h] == NULL){
            BucketTable[h] = p;
            p->next = NULL;
        }
        else{
            found = find(key,BucketTable);
            if (found != NULL){
                fprintf(out,"Already exists\n");
                fclose(out);
                return;
            }
            else{
                p->next = BucketTable[h];
                BucketTable[h] = p;
            }
        }
    }
    else{
        fprintf(out,"ERROR!\n");
        fclose(out);
        exit(1);
    }
    fclose(out);
}

void list(NodeT **BucketTable,char *fileName){
    NodeT *p;
    FILE *out = fopen(fileName,"a");
    for(int i = 0;i < B;i++){
        if (BucketTable[i] != NULL){
            fprintf(out,"Bucket for hash value %d\n",i);
            p = BucketTable[i];
            while (p != NULL){
                fprintf(out,"%s ",p->key);
                p = p->next;
            }
            fprintf(out,"\n");
        }
    }
    fclose(out);
}

void delete(char *key,NodeT **BucketTable){
    NodeT *current,*prev;
    int h;
    h = hash(key);
    current = BucketTable[h];
    prev = NULL;
    while(current != NULL){
        if (strcmp(key,current->key) == 0){
            break;
        }
        prev = current;
        current = current->next;
    }
    if (current == BucketTable[h]){
        prev = current;
        current = current->next;
        BucketTable[h] = current;
        free(prev);
    }
    else if (current->next == NULL){
        prev->next = NULL;
        free(current);
    }
    else{
        prev->next = current->next;
        free(current);
    }
}
int main() {
    FILE *in = fopen("in.txt","r");
    FILE *out = fopen("out.txt","w");
    if (in == NULL){
        printf("ERROR, CAN'T OPEN FILE");
        exit(1);
    }
    if (out == NULL){
        printf("ERROR, CAN'T OPEN FILE");
        exit(1);
    }
    fclose(out); //to clear the content in the file
    NodeT **BucketTable;
    BucketTable = (NodeT**)malloc(B*sizeof(NodeT*));
    empty(BucketTable);
    NodeT *found;
    char key[61],name[60];
    while(fscanf(in,"%s",key) == 1){
        strcpy(name,key+1);
        switch(key[0]){
            case 'i':
                insert(name,BucketTable,"out.txt");
                break;
            case 'd':
                delete(name,BucketTable);
                break;
            case 'f':
                found = find(name,BucketTable);
                if (found != NULL){
                    out = fopen("out.txt","a");
                    fprintf(out,"YES!\n");
                    fclose(out);
                }
                else{
                    out = fopen("out.txt","a");
                    fprintf(out,"NO!\n");
                    fclose(out);
                }
                break;
            case 'l':
                list(BucketTable,"out.txt");
                break;
            default:
                out = fopen("out.txt","a");
                fprintf(out,"INVALID OPERATION!\n");
                fclose(out);
        }
    }
    fclose(in);
    return 0;
}
