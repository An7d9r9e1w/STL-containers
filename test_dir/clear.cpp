#include <iostream>
#include <vector>

#include <cstdio>

#include "../vector.hpp"
#include "ptr.h"

template <typename Vector>
void print(const Vector& v)
{
	std::cout << "s[" << v.size()
		<< "] c[" << v.capacity()
		<< "] f[" << *v.begin()
		<< "] l[" << v.end()[-1]
		<< "]\n";
}

int main()
{
/*	const int size = 20;
	int arr[size] = { 0 };
	for (int i = 0; i < size; ++i)
		arr[i] = i + 1;
	std::vector<int> v(arr, arr + size);
	print(v);
	v.clear();
	print(v);
	std::cout << "end[" << *v.end() << "]\n";*/
	
	Ptr<char> p1('A');
	Ptr<char> p2('8');

	std::cout << "TEST\n";
	ft::vector<Ptr<char> > v(3, p1);
	print(v);
	v.insert(v.begin(), p2);
	print(v);
	std::getchar();
	return 0;
}
