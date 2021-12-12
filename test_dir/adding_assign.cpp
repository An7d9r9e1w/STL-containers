#include <cstdio>
#include <ctime>
#include <cstring>

#include <vector>

#include "iterator.hpp"

#define SIZE 100000000


class Array
{
public:
//	typedef ft::RAIterator<int> iter;
	typedef ft::iterator_traits<int*>::pointer iter;

public:
	Array() : arr_(new int[SIZE])
	{
		std::memset(arr_, 0, SIZE * sizeof(int));
	}
	~Array() { delete[] arr_; }

public:
	iter begin() { return iter(arr_); }
	iter end() { return iter(arr_ + SIZE); }

	int& operator[](size_t index) { return arr_[index]; }

private:
	int* arr_;
};


void foov(int* arr, const int& i)
{
	*arr = i;
}

void test_v1()
{
	clock_t start, stop;

	std::vector<int> v(SIZE);
	int* arr = new int[SIZE];
	int* p = arr;

	start = std::clock();
	for (int i = 0; i < SIZE; ++i)
		foov(p + i, v[i]);
	stop = std::clock();

	delete[] arr;

	std::printf("adding time = %g s\n"
			"\t%zu ticks\n",
			(double)(stop - start) / CLOCKS_PER_SEC, stop - start);
}
void test_v2()
{
	clock_t start, stop;

	std::vector<int> v(SIZE);
	int* arr = new int[SIZE];
	int* p = arr;

	typedef std::vector<int>::iterator iter;
	iter end(v.end());
	start = std::clock();
	for (iter it(v.begin()); it != end; ++it)
		foov(p++, *it);
	p -= SIZE;
	stop = std::clock();

	delete[] arr;

	std::printf("assign time = %g s\n"
			"\t%zu ticks\n",
			(double)(stop - start) / CLOCKS_PER_SEC, stop - start);
}

void test_v3()
{
	clock_t start, stop;

	int* arr = new int[SIZE];
	int* p = arr;

	Array a;
	typedef Array::iter iter;
	iter end(a.end());
	start = std::clock();
	for (iter it(a.begin()); it != end; ++it)
		foov(p++, *it);
	p -= SIZE;
	stop = std::clock();

	delete[] arr;

	std::printf("marray time = %g s\n"
			"\t%zu ticks\n",
			(double)(stop - start) / CLOCKS_PER_SEC, stop - start);
}

int main(void)
{
	test_v1();
	test_v2();
	test_v3();
	return 0;
}
