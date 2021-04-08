#include <stdio.h>
#include <math.h>

int gcd(int x,int y){
    while (x != y){
        if ( x > y)
            x = x - y;
        else
            y = y-x;
    }
    return x;
}
int lcm(int x, int y){
    int temp,rez;
    temp = gcd(x,y);
    rez = (x * y)/temp;
    return rez;

}

void egyptianFraction(int *x,int *y){
    float nr;
    int temp;
    if (*x == 0)
        return;
    else{
        nr = (float)(*y)/(float)(*x);
        nr = ceil(nr);
        temp = lcm(nr,*y);
        if (temp == *y) {
            *x = *x - temp / nr;
        }
        else {
            *x = (*x) * (temp / (*y)) - temp/nr;
            *y = temp;
        }
        if (*x != 0)
            printf("1/%.0f + ",nr);
        else
            printf("1/%.0f",nr);
        egyptianFraction(x,y);
    }
}

int main() {
    int x = 5,y = 8;
    egyptianFraction(&x,&y);
    return 0;
}