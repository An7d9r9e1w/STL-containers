#include <iostream>
#include <string>
#include <memory>

struct A
{
	A(const int n) : n(new int(n))
	{
		std::cout << "A::ctor[" << n << ']' << std::endl;
	}
	A(const A& a)
	{
		std::cout << "A::copy ctor[" << n << ']' << std::endl;
		delete n;
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

	int* n;
};

template <class T>
void testAlloc(const T& value)
{
	std::allocator<T> alloc;

	T* ptr = alloc.allocate(1);
	alloc.construct(ptr, value);
	std::cout << "ptr = " << *ptr << '\n';

	T* cp = alloc.allocate(1);
	alloc.construct(cp, *ptr);
//	*cp = *ptr;
	std::cout << " cp = " << *cp << '\n';

	std::cout << "Rector\n";
//	alloc.construct(ptr, *cp);
	*ptr = *cp;
	std::cout << "Rector end\n";

	alloc.destroy(cp);
	alloc.deallocate(cp, 1);
	alloc.destroy(ptr);
	alloc.deallocate(ptr, 1);
}

int main()
{
//	testAlloc(5);
//	testAlloc<std::string>("Hello, world");
	A a(5);
	std::cout << "TEST\n";
	testAlloc(a);
	std::cout << "TEST end\n";
	return 0;
}
