# Lab 10

> In this lab we learned about dynamic programing and also about heuristics.
> We did some examples for dynamic programing and we also had to implement a problem
> Solved the mandatory problem with my brother

>how did we solve it.

First, we had to find a way to know if it's possible to obtain A from B with the given numbers,
and we came across Bezout's property which gives you the Bezout coefficients when calculating the gcd of two numbers.
Then we checked if that number can be divided by gcd, which means we can indeed obtain the number B from A.
> Then we had to came up with an algorythm to solve the problem.
> It goes like this:
first, we create a vector in which we store the values that we are going to use. The vector must be of size max,
can be either the max nr in the vector given or (a - b) + 1.
Then we initialise all the elements at the positions dp[vector[i]] where vector[i] iterates over the given vector.
The other elements in the vector are INT_MAX.
Then, for every element, we have to find the minimum of steps to get to it, which is done by comparing
the different position in the vector. If one of the positions is not calculated, we will try to find it
(it's hard to write it, I have a drawing which ilustrates this part better).
If we make a certain number of steps to find that number, we will just initialise it with the number of steps
Bezout's algo returns( which is ax + by = gcd and that would be a + b)
By doing this we will complete the whole vector for the minimum number of steps.
At the end, we return dp[abs(a - b)] and the problem is done.

First, we solved the exercise recursively, then we had to implement it using dp.
We used the dynamic programming memoization tehnique because, like in coin problem, there are a lot of values
that will be recalculated. So we will store them for later use. We can't go linearly, like in the coin problem,
where we can relate to only values that we calculated before,so to find some values, will use recursion,
and if such a value is not found, will initialise it as the min number of steps from bezout's coefficients.
These values will be later calculated and the appropriate result will pe stored in the vector dp.


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

gives us the bezout's coefficients


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

this gives of the number of steps to get to gcd, using bezout's property, and if it is not possible to obtain C = A - B from that, it returns -1


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

this function will fill the rremaining elements in the dp vector that weren't initiated at the beginning


