#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *rand_set(const size_t size);
void test(const int*, const size_t);
void test2(const int*, const size_t);

#define SIZE 1000000

int main(void)
{
    int *set = rand_set(SIZE);
    clock_t start, stop;
    start = clock();
    test(set, SIZE);
    stop = clock();
    printf("test1 = %g\n", (double)(stop - start) / CLOCKS_PER_SEC);

    start = clock();
    test2(set, SIZE);
    stop = clock();
    printf("test2 = %g\n", (double)(stop - start) / CLOCKS_PER_SEC);

    free(set);
    return 0;
}
