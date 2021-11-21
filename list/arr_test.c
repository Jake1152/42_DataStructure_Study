//test_arr

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int arr[10];
    int *arr_alloc;
    int idx;

    printf("sizeof arr %lu \n", sizeof(arr));    
    idx = 0;
    arr[0] = 1;

    arr_alloc = malloc();
    while (arr[idx])
        printf("arr[idx] %d\n", arr[idx++]);
    return (0);
}
