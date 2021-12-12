#include <iostream>
#include <vector>

#include <algorithm>
#include "algorithm.hpp"

#include <cstdlib>
#include <ctime>

#define SIZE 1000000

void fillv(std::vector<int>& v)
{
	for (size_t i = 0; i < SIZE; ++i)
		v[i] = i + 1;
}

bool pred(int i1, int i2)
{
	return i1 == i2;
}

void test1()
{
	std::vector<int> v(SIZE);
	fillv(v);
	std::cout << std::equal(v.begin(), v.end(), v.begin()) << '\n';
	std::cout << std::equal(v.begin(), v.end(), v.begin(), pred) << '\n';
	std::cout << ft::equal(v.begin(), v.end(), v.begin()) << '\n';
	std::cout << ft::equal(v.begin(), v.end(), v.begin(), pred) << '\n';

	std::vector<int> v1(SIZE);
	fillv(v1);
	v1[SIZE - 1] = -1;
	std::cout << std::equal(v.begin(), v.end(), v1.begin()) << '\n';
	std::cout << std::equal(v.begin(), v.end(), v1.begin(), pred) << '\n';
	std::cout << ft::equal(v.begin(), v.end(), v1.begin()) << '\n';
	std::cout << ft::equal(v.begin(), v.end(), v1.begin(), pred) << '\n';
}

template <class Equal>
void time_test(Equal equal)
{
	std::vector<int> v(SIZE);
	fillv(v);
	clock_t start = std::clock();
	for (int i = 0; i < 10; ++i) {
		equal(v.begin(), v.end(), v.begin());
	}
	clock_t end = std::clock();
	std::cout << "time: " <<
		static_cast<double>(end - start) / CLOCKS_PER_SEC << '\n';
}

int main()
{
//	test1();
	typedef typename std::vector<int>::iterator iter;
	time_test(std::equal<iter, iter>);
	time_test(ft::equal<iter, iter>);
	return 0;
}
