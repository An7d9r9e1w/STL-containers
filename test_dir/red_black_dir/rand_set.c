#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*
#define SIZE 100
*/
int *rand_set(const size_t size)
{
    if (!size) return NULL;
    srand(clock() * time(NULL));
    int *arr = malloc(sizeof(int) * size);
    if (!arr) return NULL;
    arr[0] = 1;
    arr[1] = 2;
    for (size_t i = 2; i < size; ++i) {
        int index = rand() % i;
        arr[i] = arr[index];
        arr[index] = i + 1;
    }
    return arr;
}

void print_arr(const int *arr, const size_t size)
{
    if (!size) {
        printf("{ empty }\n");
        return;
    }
    printf("{ ");
    for (size_t i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }
    printf("}\n");
}
/*
#define SIZE 15

int main(void)
{
    int *set = rand_set(SIZE);
    print_arr(set, SIZE);
    free(set);
    return 0;
}*/
