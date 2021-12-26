#include <iostream>
#include <memory>

#include <cstring>
#include <cstdio>

struct A
{
	A(const int n = 96) : ptr_(new int(n)) {}
	A(const A& p) : ptr_(new int(*p.ptr_)) {}
	~A() { delete ptr_; }

	A& operator=(const A& p)
	{
		if (this != &p) {
			delete ptr_;
			ptr_ = new int(*p.ptr_);
		}
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& os, const A& p)
	{
		return os << *p.ptr_;
	}

	int* ptr_;
};

typedef std::allocator<A> alloc;

void print(const A* p, const int size)
{
	for (int i = 0; i < size; ++i)
		std::cout << p[i] << ' ';
	std::cout << '\n';
}

A* construct(const int size, const A& value, alloc a)
{
	A* ptr = a.allocate(size);
	for (int i = 0; i < size; ++i)
		a.construct(ptr + i, value);
	return ptr;
}

void destruct(A* ptr, const int size, alloc a)
{
	for (int i = 0; i < size; ++i)
		a.destroy(ptr + i);
	a.deallocate(ptr, size);
}

A* realloc(A* ptr, const int size, const int new_size, alloc a)
{
	A* tmp = a.allocate(new_size);
	std::memcpy(tmp, ptr, size * sizeof(A));
/*	for (int i = 0; i < size; ++i) {
		a.construct(tmp + i, ptr[i]);
		a.destroy(ptr + i);
	}*/
	a.deallocate(ptr, size);
	return tmp;
}

int main()
{
	alloc a;
	int size = 5;
	A* p = construct(size, A(), a);
	print(p, size);

	p = realloc(p, size, size << 1, a);
	a.construct(p + size++, A(5));
	print(p, size);

	destruct(p, size, a);
	std::getchar();
	return 0;
}
