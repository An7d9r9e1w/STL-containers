#include <iostream>
#include <vector>

#include <memory>

#include "../vector.hpp"

#include <cstdio>
#include <ctime>
#include <cstring>
#include <cstddef>

#define SIZE 10000000

template <class T, class Vector>
void testDefault()
{
    clock_t start, stop;

    start = std::clock();
    Vector v(SIZE);
    stop = std::clock();

    std::cout << v.size() << ' ' << v.capacity() << '\n';
    std::printf("time = %g s\n", static_cast<double>(stop - start) / CLOCKS_PER_SEC);
}

template <class T, class Vector>
void testFill(T value)
{
    clock_t start, stop;

    start = std::clock();
    Vector v(SIZE, value);
    stop = std::clock();

    std::cout << v[0] << ' ' << v[SIZE - 1] << ' ' << v.size() << ' ' << v.capacity() << '\n';
    std::printf("time = %g s\n", static_cast<double>(stop - start) / CLOCKS_PER_SEC);
}

template <class T, class Vector>
void testRange(T value)
{
    clock_t start, stop;
    T* arr = new T[SIZE];
    for (size_t i = 0; i < SIZE; ++i)
        arr[i] = value;
//    std::memset(arr, 0, SIZE * sizeof(T));

    start = std::clock();
    Vector v(arr, arr + SIZE);
    stop = std::clock();

    std::cout << v[0] << ' ' << v[SIZE - 1] << ' ' << v.size() << ' ' << v.capacity() << '\n';
    std::printf("time = %g s\n", static_cast<double>(stop - start) / CLOCKS_PER_SEC);

    delete[] arr;
}

template <class T, class Vector>
void testCopy(T value)
{
    clock_t start, stop;

    Vector orig(SIZE, value);
    start = std::clock();
    Vector v(orig);
    stop = std::clock();

    std::cout << v[0] << ' ' << v[SIZE - 1] << ' ' << v.size() << ' ' << v.capacity() << '\n';
    std::printf("time = %g s\n", static_cast<double>(stop - start) / CLOCKS_PER_SEC);
}

template <class T>
void test(T value)
{
    std::cout << "\n[Default]\n";
    std::cout << "[STD]\n";
    testDefault<T, std::vector<T> >();
    std::cout << "[FT]\n";
    testDefault<T, ft::vector<T> >();

    std::cout << "\n[Fill]\n";
    std::cout << "[STD]\n";
    testFill<T, std::vector<T> >(value);
    std::cout << "[FT]\n";
    testFill<T, ft::vector<T> >(value);

    std::cout << "\n[Range]\n";
    std::cout << "[STD]\n";
    testRange<T, std::vector<T> >(value);
    std::cout << "[FT]\n";
    testRange<T, ft::vector<T> >(value);

    std::cout << "\n[Copy]\n";
    std::cout << "[STD]\n";
    testCopy<T, std::vector<T> >(value);
    std::cout << "[FT]\n";
    testCopy<T, ft::vector<T> >(value);
}

int main()
{
    std::cout << "********[INT]*********\n";
    test(69);
    std::cout << "\n\n********[STRING]*********\n";
    test("Hello, world!");

    return 0;
}
