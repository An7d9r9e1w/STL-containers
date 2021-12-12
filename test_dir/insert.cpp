#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

#include <cstdio>
#include <ctime>

#include "../vector.hpp"
#include "print.hpp"

#define SIZE 1000000

struct IntPtr
{
	IntPtr(const int n = 96) : ptr_(new int(n)) {}
	IntPtr(const IntPtr& p) : ptr_(new int(*p.ptr_)) { }
	~IntPtr() { delete ptr_; }

	IntPtr& operator=(const IntPtr& p)
	{
		if (this != &p) {
			delete ptr_;
			ptr_ = new int(*p.ptr_);
		}
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& os, const IntPtr& p)
	{
		return os << *p.ptr_;
	}

	int* ptr_;
};

template <class Vector>
void checkprint(const Vector& v)
{
	if (!v.empty()) {
		print(v);
		printAll(v);
	}
	else {
		std::cout << "[ EMPTY ]\n";
	}
}

void printTestLabel(const std::string& test_name, const std::string& prompt, size_t size, size_t cap, ssize_t pos)
{
	std::cout << "\n--- [" << test_name
		<< ", size = " << size
		<< ", cap = " << cap
		<< ", pos = " << pos
		<< "] [" << prompt
		<< "] ---\n";
}

void printTestLabel2(const std::string& test_name, const std::string& prompt, size_t size, size_t cap, ssize_t pos, size_t count)
{
	std::cout << "\n--- [" << test_name
		<< ", size = " << size
		<< ", cap = " << cap
		<< ", pos = " << pos
		<< ", count = " << count
		<< "] [" << prompt
		<< "] ---\n";
}


/// single insert
template <class T, class Vector>
void singleInsertTest(const std::string& prompt, size_t size, size_t cap, ssize_t pos, const T& value)
{
	try {
		printTestLabel("SINGLE", prompt, size, cap, pos);

		if (size > cap) throw std::runtime_error("size > capacity");
		if (pos < 0 || pos > size) throw std::runtime_error("invalid position");

		T* arr = new T[size];
		T tmp = T();
		for (size_t i = 0; i < size; ++i)
			arr[i] = ++tmp;
		delete[] arr;

		Vector v;
		v.reserve(cap);
		v.assign(arr, arr + size);

		checkprint(v);

		v.insert(v.begin() + pos, value);

		checkprint(v);
	}
	catch (const std::exception& e) {
		std::cerr << "SINGLE: " << prompt << ": " << e.what() << '\n';
	}
}

void singleInsertTests(const std::string& stdv, const std::string& ftv)
{
	singleInsertTest<int, std::vector<int> >(stdv, 5, 10, 0, 69);
	singleInsertTest<int, ft::vector<int> >(ftv, 5, 10, 0, 69);
	singleInsertTest<int, std::vector<int> >(stdv, 5, 10, 3, 69);
	singleInsertTest<int, ft::vector<int> >(ftv, 5, 10, 3, 69);
	singleInsertTest<int, std::vector<int> >(stdv, 5, 10, 5, 69);
	singleInsertTest<int, ft::vector<int> >(ftv, 5, 10, 5, 69);
//	singleInsertTest<int, std::vector<int> >(stdv, 5, 10, 6, 69);	segfault

	singleInsertTest<int, std::vector<int> >(stdv, 5, 5, 0, 69);
	singleInsertTest<int, ft::vector<int> >(ftv, 5, 5, 0, 69);
	singleInsertTest<int, std::vector<int> >(stdv, 5, 5, 3, 69);
	singleInsertTest<int, ft::vector<int> >(ftv, 5, 5, 3, 69);
	singleInsertTest<int, std::vector<int> >(stdv, 5, 5, 5, 69);
	singleInsertTest<int, ft::vector<int> >(ftv, 5, 5, 5, 69);

	singleInsertTest<int, std::vector<int> >(stdv, 0, 0, 0, 69);
	singleInsertTest<int, ft::vector<int> >(ftv, 0, 0, 0, 69);
}

template <class T, class Vector>
void singleInsertTestTime(const std::string& prompt, size_t size, const T& value)
{
	std::cout << "[ SINGLE TIME, size = " << size
		<< ", value = " << value
		<< "] [" << prompt
		<< "]\n";
	Vector v(size, value);
	clock_t start, stop;
	print(v);
	start = std::clock();
	v.insert(v.begin(), value);
	stop = std::clock();
	print(v);
	std::cout << "time = " << static_cast<double>(stop - start) / CLOCKS_PER_SEC << " s\n";
}

void singleInsertTestsTime(const std::string& stdv, const std::string& ftv)
{
	singleInsertTestTime<int, std::vector<int> >(stdv, SIZE, 69);
	singleInsertTestTime<int, ft::vector<int> >(ftv, SIZE, 69);
	singleInsertTestTime<std::string, std::vector<std::string> >(stdv, SIZE, "Hello, world!");
	singleInsertTestTime<std::string, ft::vector<std::string> >(ftv, SIZE, "Hello, world!");
	singleInsertTestTime<IntPtr, std::vector<IntPtr> >(stdv, SIZE, IntPtr());
	singleInsertTestTime<IntPtr, ft::vector<IntPtr> >(ftv, SIZE, IntPtr());
}


/// fill insert
template <class T, class Vector>
void fillInsertTest(const std::string& prompt,
					size_t size,
					size_t cap,
					ssize_t pos,
					size_t count,
					const T& value)
{
	try {
		printTestLabel2("FILL", prompt, size, cap, pos, count);

		if (size > cap) throw std::runtime_error("size > capacity");
		if (pos < 0 || pos > size) throw std::runtime_error("invalid position");

		T* arr = new T[size];
		T tmp = T();
		for (size_t i = 0; i < size; ++i)
			arr[i] = ++tmp;
		delete[] arr;

		Vector v;
		v.reserve(cap);
		v.assign(arr, arr + size);

		checkprint(v);

		v.insert(v.begin() + pos, count, value);

		checkprint(v);
	}
	catch (const std::exception& e) {
		std::cerr << "FILL: " << prompt << ": " << e.what() << '\n';
	}
}

void fillInsertTests(const std::string& stdv, const std::string& ftv)
{
	fillInsertTest<int, std::vector<int> >(stdv, 5, 10, 0, 3, 69);
	fillInsertTest<int, ft::vector<int> >(ftv, 5, 10, 0, 3, 69);
	fillInsertTest<int, std::vector<int> >(stdv, 5, 10, 3, 5, 69);
	fillInsertTest<int, ft::vector<int> >(ftv, 5, 10, 3, 5, 69);
	fillInsertTest<int, std::vector<int> >(stdv, 5, 10, 5, 10, 69);
	fillInsertTest<int, ft::vector<int> >(ftv, 5, 10, 5, 10, 69);
	fillInsertTest<int, std::vector<int> >(stdv, 5, 10, 5, 15, 69);
	fillInsertTest<int, ft::vector<int> >(ftv, 5, 10, 5, 15, 69);
	fillInsertTest<int, std::vector<int> >(stdv, 5, 10, 5, 20, 69);
	fillInsertTest<int, ft::vector<int> >(ftv, 5, 10, 5, 20, 69);

	fillInsertTest<int, std::vector<int> >(stdv, 5, 5, 0, 3, 69);
	fillInsertTest<int, ft::vector<int> >(ftv, 5, 5, 0, 3, 69);
	fillInsertTest<int, std::vector<int> >(stdv, 5, 5, 3, 5, 69);
	fillInsertTest<int, ft::vector<int> >(ftv, 5, 5, 3, 5, 69);
	fillInsertTest<int, std::vector<int> >(stdv, 5, 5, 5, 10, 69);
	fillInsertTest<int, ft::vector<int> >(ftv, 5, 5, 5, 10, 69);

	fillInsertTest<int, std::vector<int> >(stdv, 0, 0, 0, 1, 69);
	fillInsertTest<int, ft::vector<int> >(ftv, 0, 0, 0, 1, 69);
	fillInsertTest<int, std::vector<int> >(stdv, 0, 0, 0, 3, 69);
	fillInsertTest<int, ft::vector<int> >(ftv, 0, 0, 0, 3, 69);
}

template <class T, class Vector>
void fillInsertTestTime(const std::string& prompt, size_t size, const T& value)
{
	std::cout << "[ FILL TIME, size = " << size
		<< ", value = " << value
		<< "] [" << prompt
		<< "]\n";
	Vector v(size, value);
	clock_t start, stop;
	print(v);
	start = std::clock();
	v.insert(v.begin(), size, value);
	stop = std::clock();
	print(v);
	std::cout << "time = " << static_cast<double>(stop - start) / CLOCKS_PER_SEC << " s\n";
}

void fillInsertTestsTime(const std::string& stdv, const std::string& ftv)
{
	fillInsertTestTime<int, std::vector<int> >(stdv, SIZE, 69);
	fillInsertTestTime<int, ft::vector<int> >(ftv, SIZE, 69);
	fillInsertTestTime<std::string, std::vector<std::string> >(stdv, SIZE, "Hello, world!");
	fillInsertTestTime<std::string, ft::vector<std::string> >(ftv, SIZE, "Hello, world!");
	fillInsertTestTime<IntPtr, std::vector<IntPtr> >(stdv, SIZE, IntPtr());
	fillInsertTestTime<IntPtr, ft::vector<IntPtr> >(ftv, SIZE, IntPtr());
}


/// main
int main()
{
	const std::string stdv("std::vector");
	const std::string ftv("ft::vector");

//	singleInsertTests(stdv, ftv);
//	singleInsertTestsTime(stdv, ftv);

//	fillInsertTests(stdv, ftv);
	fillInsertTestsTime(stdv, ftv);

	std::cout << "Press enter...";
	std::getchar();
	return 0;
}
