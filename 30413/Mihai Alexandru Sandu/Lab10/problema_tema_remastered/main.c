#include <stdio.h>
#include <stdlib.h>
#define MAXI 100000


int gcdSpecial(int a, int b, int *x, int *y)
{
    if (a == 0)
    {
        *x = 0;
        *y = 1;
        return b;
    }

    int _x, _y;
    int gcd = gcdSpecial(b % a, a, &_x, &_y);

    *x = _y - (b/a) * _x;
    *y = _x;

    return gcd;
}

int gcd(int n1, int n2){
    while(n1 != n2){
        if(n1 > n2)
            n1 -= n2;
        else
            n2 -= n1;
    }
    return n1;
}

int bezut(int *vector, int length, int C) {  // za most important function
    for (int i = 0; i < length - 1; i++)
        for (int j = i + 1; j < length; j++)
            if (C % gcd(vector[i], vector[j]) == 0)
                return 1;
    return 0;
}

int maxPasi(int A, int B, int *vector,int length){
    int C;
    int x,y;
    int nr;
    C = abs(A-B);
    for (int i = 0; i < length - 1; i++) {
        for (int j = i + 1; j < length; j++) {
            if (C % gcd(vector[i], vector[j]) == 0) {
                nr = gcdSpecial(vector[i], vector[j], &x, &y);
                return (C / nr) * (abs(x) + abs(y));
            }
        }
    }
    return -1;//not possible;
}

/*void minOp(int C,int *vector,int length,int nrMin,int *pasiBezut){
    if(nrMin >= *pasiBezut) return;
    if (C == 0) {
        if(nrMin < *pasiBezut)
            *pasiBezut = nrMin;
        return;
    }
    nrMin++;
    for(int i =0; i < length; i++) {
        minOp(abs(C - vector[i]), vector, length, nrMin, pasiBezut);
    }
}*/

int nrMaxVector(int *vector,int length) {
    int max = vector[0];
    for (int i = 1; i < length; i++) {
        if (vector[i] > max)
            max = vector[i];
    }
    return max;
}

int min(int a, int b){
    if (a < b)
        return a;
    else
        return b;
}

void function(int *dp,int *vector, int length, int *bezutP, int nrPasi, int poz){
    if(nrPasi > *bezutP) {
        dp[poz] = *bezutP;
        return;
    }
    else {
        int minimum = dp[abs(poz - vector[0])];
        for (int i = 0; i < length; i++) {
            if (dp[abs(poz - vector[i])] == INT_MAX) {
                function(dp, vector, length, bezutP, ++nrPasi, abs(poz - vector[i]));
            } else
                minimum = min(minimum, dp[abs(poz - vector[i])]);
        }
        dp[poz] = minimum + 1;
    }
}

void minOpDP(int A, int B,int *vector,int length){
    int max;
    int bezutP = maxPasi(A,B,vector,length);
    max = nrMaxVector(vector,length);
    if (abs(A - B) > max)
        max = abs(A - B) + 1;
    int dp[max];
    for(int i = 0; i < max; i++)
        dp[i] = INT_MAX;
    dp[0] = 0;
    for( int i = 1; i < length; i++)
        dp[vector[i]] = 1;
    for( int i = 1; i < max; i++){
        if(dp[i] == 1) continue;
        function(dp,vector,length,&bezutP,0,i);
    }
    //for(int i = 0; i < max; i++)
        //printf("%d ",dp[i]);
    printf("%d \n",dp[abs(A - B)]);
}


int main()
{
    int A = 45, B = 97;//52
    int v[] = {5,10};
    int n = 2;
    minOpDP(A,B,v,n);
    return 0;
}

