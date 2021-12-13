#include <iostream>

template <class T>
struct test
{
	template <class U>
	static void foo(...) { std::cout << "test\n"; }
	template <class U>
	static void foo(typename U::type* = NULL) { std::cout << "test::type\n"; }
};

struct A
{
	typedef int type;
};

int main()
{
	test<int>::foo<int>(0);
	test<A>::foo<A>(0);
	return 0;
}
