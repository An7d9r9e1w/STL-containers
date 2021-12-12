#include <iostream>
#include <vector>

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
	ft::vector<int> v1(10);
	print(v);
	print(v1);
	std::cout << '\n';

	v.assign(15, 5);
	v1.assign(15, 5);
	print(v);
	print(v1);
	std::cout << '\n';

	v.assign(5, 7);
	v1.assign(5, 7);
	print(v);
	print(v1);
	std::cout << '\n';

	const int size = 20;
	int arr[size] = { 0 };
	for (int i = 0; i < size; ++i)
		arr[i] = i + 1;
	v.assign(arr, arr + size);
	v1.assign(arr, arr + size);
	print(v);
	print(v1);
	std::cout << '\n';

	v.assign(0, 1);
	v1.assign(0, 1);
	print(v);
	print(v1);
	std::cout << '\n';

	v.assign(5, 7);
	v.assign(arr, arr);
	v1.assign(5, 7);
	v1.assign(arr, arr);
	print(v);
	print(v1);
	std::cout << '\n';
	return 0;
}
