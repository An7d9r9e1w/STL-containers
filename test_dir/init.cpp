#include <iostream>
#include <vector>

template <typename T>
void print(const std::vector<T>& v)
{
	std::cout << "s[" << v.size()
		<< "] c[" << v.capacity()
		<< "] d[" << v.data()
		<< "] f[" << &v.begin()
		<< "]\n";
}

int main()
{
	std::vector<int> v;
	print(v);
	return 0;
}
