#include <iostream>
#include <vector>

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
	std::vector<int> v1(15);
	std::vector<int> v2(10);

	print(v1);
	v1 = v2;
	print(v1);

	std::vector<int> v3(10);
	print(v3);
	v3 = v1;
	print(v3);

	return 0;
}
