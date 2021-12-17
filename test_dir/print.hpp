#ifndef PRINT_H_
#define PRINT_H_

#include <iostream>
#include <cstddef>

template <typename Vector>
void print(const Vector& v)
{
//	std::cerr << "PRINT TEST" << std::endl;
	std::cout << "s[" << v.size()
		<< "] c[" << v.capacity()
		<< "] f[" << v[0]
		<< "] l[" << v[v.size() - 1]
		<< "]\n";
}

template <typename Vector>
void printAll(const Vector& v)
{
	const size_t size = v.size();
	std::cout << "[ ";
	for (size_t i = 0; i < size; ++i)
		std::cout << v[i] << ' ';
	std::cout << "]\n";
}

#endif	// PRINT_H_
