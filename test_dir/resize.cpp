#include <iostream>
#include <vector>

#include "../vector.hpp"

template <typename Vector>
void print(const Vector& v)
{
	std::cout << "s[" << v.size()
		<< "] c[" << v.capacity()
//		<< "] f[" << v[0]
//		<< "] l[" << v[v.size() - 1]
//		<< "] d[" << v.data()
		<< "]\n";
}

template <class Vector>
void test()
{
	Vector v(10);
	for (int i = 0; i < 10; ++i)
		v[i] = i + 1;
	print(v);
	size_t size = (size_t)-1 >> 2;
	std::cout << size << '\n';
	try {
		v.assign(size, 10);
	}
	catch (std::bad_alloc& e) {
		std::cerr << "ba: " << e.what() << '\n';
	}
	catch (std::length_error& e) {
		std::cerr << "le: " << e.what() << '\n';
	}
	print(v);
}

int main()
{
	test<std::vector<int> >();
	test<ft::vector<int> >();
	return 0;
}
