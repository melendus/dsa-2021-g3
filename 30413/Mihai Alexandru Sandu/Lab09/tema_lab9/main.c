#include <stdio.h>
#include <stdlib.h>


int *readArray(char *file,int *number){
    FILE *pt = fopen(file,"r");
    int nr;
    fscanf(pt,"%d",&nr);
    int *array = (int*)calloc(nr,sizeof(int));
    if (array == NULL){
        printf("ERROR: READING");
        exit(1);
    }
    else{
        for( int i = 0; i < nr; i++)
            fscanf(pt,"%d",&array[i]);
    }
    for (int i = 0; i < nr; i++)
        printf("%d ",array[i]);
    *number = nr;
    fclose(pt);
    return array;
}

int max(int a,int b){
    if (a > b)
        return a;
    else return b;
}

int max3(int a, int b, int c){
    return max(max(a,b),c);
}

int midSUM(int *array,int middle, int right){
    int sum = 0;
    int leftSum = INT_MIN;
    for (int i = middle; i >= 0; i--){
        sum = sum + array[i];
        if (sum > leftSum)
            leftSum = sum;
    }
    sum = 0;
    int rightSum = INT_MIN;
    for (int i = middle + 1; i <= right; i++){
        sum = sum + array[i];
        if (sum > rightSum)
            rightSum = sum;
    }
    sum = leftSum + rightSum;
    return max3(leftSum,sum,rightSum);  // imi returneaza suma maxima dintre cele 3 sume
}

int maxSubArray(int left, int right, int * array){
    if (left == right)
        return array[left];     // conditia de finish pt recursivitate, cand ajung la array-uri de 1 element
    int middle = (left + right)/2;
    return max3(maxSubArray(0,middle,array), maxSubArray(middle + 1, right,array),midSUM(array,middle,right));
}
int main(int argc, char *argv[]) {
    int nr;
    //FILE *file1 = fopen(argv[1],"r");
    //scanf("%d",&nr);
    int *array = readArray(argv[1],&nr);
    int suma = maxSubArray(0,nr - 1,array);
    printf("\n%d",suma);
    return 0;
}
