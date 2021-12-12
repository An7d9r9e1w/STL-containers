#include <iostream>
#include <vector>

#include "../vector.hpp"

template <class Vector>
void test()
{
	Vector v(10);
	int i = 0;
	for ( ; i < 10; ++i)
		v[i] = i + 1;
	for (auto i : v)
		std::cout << i << ' ';
	std::cout << '\n';
	i = 0;
	for (auto iter = v.rbegin(); iter != v.rend(); ++iter)
		*iter = ++i;
	for (auto i : v)
		std::cout << i << ' ';
	std::cout << "\n\n";
}

int main()
{
	test<std::vector<int> >();
	test<ft::vector<int> >();
	return 0;
}
