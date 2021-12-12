#include <vector>
#include <iostream>

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
	for (int i = 0; i < 10; ++i)
		v[i] = i + 1;

	v.resize(0);
	print(v);
	std::cout << v.front() << ' ' << &v.front() << '\n';
	std::cout << *(&v.front() + 1) << ' ' << &v.front() + 1<< '\n';
	std::cout << *(&v.front() - 1) << ' ' << &v.front() - 1<< '\n';
	std::cout << v.back() << ' ' << &v.back() << '\n';
	return 0;
}
