#include <iostream>
#include <vector>

#include "../vector.hpp"
#include "print.hpp"

#ifndef SIZE
#define SIZE 1000000
#endif //SIZE

template <class Vector>
void test()
{
//	int* arr = new int[SIZE];
//	for (int i = 0; i < SIZE; ++i)
//		arr[i] = i + 1;
	Vector v(/*arr, arr + SIZE);/*/SIZE, 65);
//	delete [] arr;
	print/*All*/(v);
	v.insert(v.begin(), -1);
	print/*All*/(v);
}

int main()
{
	std::cout << "FT\n";
	test<ft::vector<int> >();
	std::cout << "STD\n";
	test<std::vector<int> >();
	return 0;
}

/*	p
 *	1	2	3
 *
 *	count = 6
 *	pos = 0
 *	shift = 1
 *
 */
