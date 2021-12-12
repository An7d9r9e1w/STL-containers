#include <vector>
#include <iostream>

#include "../vector.hpp"

template <typename Vector>
void print(const Vector& v)
{
	std::cout << "s[" << v.size()
		<< "] c[" << v.capacity()
		<< "] f[" << v[0]
		<< "] l[" << v[v.size() - 1]
		<< "]\n";
}

int main()
{
	std::vector<int> v(10);
	try {
		v.at(10);
	}
	catch (std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	std::cout << v.size() << '\n';

	ft::vector<int> v1(10);
	try {
		v1.at(10);
	}
	catch (std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	std::cout << v1.size() << '\n';
	return 0;
}
