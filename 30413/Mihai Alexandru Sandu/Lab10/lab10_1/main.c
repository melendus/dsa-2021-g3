#include <stdio.h>
#include <stdlib.h>

int **tabel(int row,int col){
    int **table = (int**)calloc(row,sizeof(int*));
    for (int i = 0; i < row; i++)
        table[i] = (int*)calloc(col,sizeof(int));
    return table;
}

void fillTheTable(int **table,int row, int col){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++) {
            scanf("%d", &table[i][j]);
        }
    }
}

int min(int a, int b){
    if (a > b)
        return b;
    else return a;
}

void print(int **table,int row,int col){
    for(int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%d ", table[i][j]);
        }
        printf("\n");
    }
}

void minPath(int **table,int **newTable, int row, int col){  // umplerea tabelului
    int i;
    int j;
    //int a,b,c;
    newTable[0][0] = table[0][0];
    for (i = 1; i < col; i++){                                // umplerea primului rand respectiv primei coloane din tabel
        newTable[0][i] = newTable[0][i - 1] + table[0][i];
    }

    for ( i = 1; i < row; i++){
            newTable[i][0] = newTable[i - 1][0] + table[i][0];
    }

    for (i = 1; i < row; i++){
        for (j = 1; j < col; j++){
            newTable[i][j] = table[i][j] + min(min(newTable[i][j - 1],newTable[i - 1][j]),newTable[i - 1][j - 1]);
        }
    }
}

int problem(int **table,int row, int col,int x,int y){
    int i;
    int j;
    int **newTable = tabel(row,col); //creez tabelul de ajutor
    minPath(table,newTable,row,col); // umplerea tabelului de ajutor
    printf("\n");
    print(newTable,row,col);
    printf("\n");
    return newTable[x][y];
}


int main() {
    int **primulTabel = tabel(4,7);
    //print(primulTabel,4,7);
    fillTheTable(primulTabel,4,7);
    printf("\n");
    print(primulTabel,4,7);
    printf("%d",problem(primulTabel,4,7,3,6));
    return 0;
}
