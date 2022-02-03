#include <stdio.h>

#define SIZE 10

/*
 *  X = [0, N - 1]
 *  P = [0; l) U (u; N - 1]
 *  Xj != T : j e P
 */

int binary_search(const int *arr, const int size, const int n)
{
    int low = 0;
    int high = size -1;
    while (low <= high) {
        int mid = low + ((high - low) >> 1);
        if (n == arr[mid]) return mid;
        if (n < arr[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }
    return -1;
}

int main(void)
{
    int arr[SIZE];
    for (int i = 0; i < SIZE; ++i)
        arr[i] = i;
    for (int i = -3; i < SIZE + 3; ++i) {
        printf("[%d: %d] ", i, binary_search(arr, SIZE, i));
    }
    printf("\n");
    return 0;
}
