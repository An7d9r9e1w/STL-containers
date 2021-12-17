#include <iostream>
#include <string>

#include <cstring>
#include <cstdio>
#include <memory>

//#include "../vector.hpp"

struct A
{
	A(const int n) : n(new int(n))
	{
		std::cout << "A::ctor[" << n << ']' << std::endl;
	}
	A(const A& a) : n(new int(*a.n))
	{
		std::cout << "A::copy ctor[" << n << ']' << std::endl;
	}
	~A()
	{
		std::cout << "A::dtor[" << n << ']' << std::endl;
		delete n;
	}

	friend std::ostream& operator<<(std::ostream& os, const A& a)
	{
		return os << *a.n;
	}

//	int*	ptr;
	int*		n;
};

template <class T>
void testMove(const T& value)
{
//	ft::vector<std::string> v(1, "Hello, world");
//	std::cout << v.front() << '\n';

	std::allocator<T> alloc;

	T* ptr = alloc.allocate(1);
	alloc.construct(ptr, value);
	std::cout << "ptr = " << *ptr << '\n';

	T* cp = alloc.allocate(1);
	std::memmove(cp, ptr, sizeof(T));
	std::memset(ptr, 0, sizeof(T));
	std::cout << " cp = " << *cp << '\n';

//	alloc.destroy(cp);
	alloc.deallocate(cp, 1);
	alloc.deallocate(ptr, 1);
}

int main()
{
//	testMove(5);
//	testMove<std::string>("Hello, world 01");
	test();
	return 0;
}
