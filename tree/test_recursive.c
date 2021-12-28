#include <stdio.h>
#include <stdlib.h>

int g_memo[101] = {0, 1, 1,};


int fib(int num)
{

    printf("num : %d\n", num);
    printf("before g_memo[num] : %d\n", g_memo[num]);
    if (num <= 0)
        return (0);
    if (g_memo[num] > 1)
        return (g_memo[num]);
    g_memo[num] = fib(num-1) + fib(fib(num-2));
    // printf("g_memo[num] : %d\n", g_memo[num]);

    return (g_memo[num]);
}

int main()
{
    
    printf("%d\n", fib(5));
    return (0);
}
