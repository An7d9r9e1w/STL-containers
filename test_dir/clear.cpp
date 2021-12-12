#include <iostream>
#include <vector>

template <typename T>
void print(const std::vector<T>& v)
{
	std::cout << "s[" << v.size()
		<< "] c[" << v.capacity()
		<< "] f[" << *v.begin()
		<< "] l[" << v.end()[-1]
		<< "]\n";
}

int main()
{
	const int size = 20;
	int arr[size] = { 0 };
	for (int i = 0; i < size; ++i)
		arr[i] = i + 1;
	std::vector<int> v(arr, arr + size);
	print(v);
	v.clear();
	print(v);
	std::cout << "end[" << *v.end() << "]\n";
	return 0;
}
