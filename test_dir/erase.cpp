#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

#include <cstdio>
#include <ctime>

#include "../vector.hpp"
#include "print.hpp"

#define SIZE 1000000

enum testType
{
	ERROR = -1,
	SINGLE,
	SINGLE_TIME,
	SINGLE_ALL,
	RANGE,
	RANGE_TIME,
	RANGE_ALL,
	ALL_TIME
};

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

template <class T>
void printPtr(T* ptr)
{
	std::cout << "ptr [" << *ptr << "][" << ptr << "]\n";
}

/// single insert
template <class Vector>
void singleEraseTest(const std::string& prompt, size_t size, size_t cap, ssize_t pos)
{
	try {
		printTestLabel("SINGLE", prompt, size, cap, pos);

		if (size > cap) throw std::runtime_error("size > capacity");
		if (pos < 0 || pos >= size) throw std::runtime_error("invalid position");

		int* arr = new int[size];
		for (size_t i = 0; i < size; ++i)
			arr[i] = i + 1;

		Vector v;
		v.reserve(cap);
		v.assign(arr, arr + size);
		delete[] arr;

		checkprint(v);

		printPtr(&*v.end() - 1);
		printPtr(&*v.erase(v.begin() + pos));

		checkprint(v);
	}
	catch (const std::exception& e) {
		std::cerr << "SINGLE: " << prompt << ": " << e.what() << '\n';
	}
}

void singleEraseTests(const std::string& stdv, const std::string& ftv)
{
	singleEraseTest<std::vector<int> >(stdv, 5, 10, 0);
	singleEraseTest<ft::vector<int> >(ftv, 5, 10, 0);
	singleEraseTest<std::vector<int> >(stdv, 5, 10, 3);
	singleEraseTest<ft::vector<int> >(ftv, 5, 10, 3);
	singleEraseTest<std::vector<int> >(stdv, 5, 10, 4);
	singleEraseTest<ft::vector<int> >(ftv, 5, 10, 4);
//	singleEraseTest<std::vector<int> >(stdv, 5, 10, 5);	segfault

	singleEraseTest<std::vector<int> >(stdv, 5, 5, 0);
	singleEraseTest<ft::vector<int> >(ftv, 5, 5, 0);
	singleEraseTest<std::vector<int> >(stdv, 5, 5, 3);
	singleEraseTest<ft::vector<int> >(ftv, 5, 5, 3);
	singleEraseTest<std::vector<int> >(stdv, 5, 5, 4);
	singleEraseTest<ft::vector<int> >(ftv, 5, 5, 4);

//	singleEraseTest<std::vector<int> >(stdv, 0, 0, 0);
//	singleEraseTest<ft::vector<int> >(ftv, 0, 0, 0);
}

template <class T, class Vector>
void singleEraseTestTime(const std::string& prompt, size_t size, const T& value)
{
	std::cout << "[ SINGLE TIME, size = " << size
		<< ", value = " << value
		<< "] [" << prompt
		<< "]\n";
	Vector v(size, value);
	clock_t start, stop;
	print(v);
	start = std::clock();
	v.erase(v.begin());
	stop = std::clock();
	print(v);
	std::cout << "time = " << static_cast<double>(stop - start) / CLOCKS_PER_SEC << " s\n";
}

void singleEraseTestsTime(const std::string& stdv, const std::string& ftv)
{
	singleEraseTestTime<int, std::vector<int> >(stdv, SIZE, 69);
	singleEraseTestTime<int, ft::vector<int> >(ftv, SIZE, 69);
	singleEraseTestTime<std::string, std::vector<std::string> >(stdv, SIZE, "Hello, world!");
	singleEraseTestTime<std::string, ft::vector<std::string> >(ftv, SIZE, "Hello, world!");
	singleEraseTestTime<IntPtr, std::vector<IntPtr> >(stdv, SIZE, IntPtr());
	singleEraseTestTime<IntPtr, ft::vector<IntPtr> >(ftv, SIZE, IntPtr());
}


/// range insert
template <class Vector>
void rangeEraseTest(const std::string& prompt,
					size_t size,
					size_t cap,
					ssize_t pos,
					size_t count)
{
	try {
		printTestLabel2("RANGE", prompt, size, cap, pos, count);

		if (size > cap) throw std::runtime_error("size > capacity");
		if (pos < 0 || pos + count > size) throw std::runtime_error("invalid position");

		int* arr = new int[size];
		for (size_t i = 0; i < size; ++i)
			arr[i] = i + 1;

		Vector v;
		v.reserve(cap);
		v.assign(arr, arr + size);
		delete[] arr;

		checkprint(v);

		if (!size) {
			std::cerr << &*v.erase(v.begin() + pos, v.begin() + pos + count) << '\n';
		} else {
			printPtr(&*v.end() - 1);
			printPtr(&*v.erase(v.begin() + pos, v.begin() + pos + count));
		}

		checkprint(v);
	}
	catch (const std::exception& e) {
		std::cerr << "RANGE: " << prompt << ": " << e.what() << '\n';
	}
}

void rangeEraseTests(const std::string& stdv, const std::string& ftv)
{
	rangeEraseTest<std::vector<int> >(stdv, 5, 10, 0, 3);
	rangeEraseTest<ft::vector<int> >(ftv, 5, 10, 0, 3);
	rangeEraseTest<std::vector<int> >(stdv, 5, 10, 3, 2);
	rangeEraseTest<ft::vector<int> >(ftv, 5, 10, 3, 2);
	rangeEraseTest<std::vector<int> >(stdv, 5, 10, 4, 1);
	rangeEraseTest<ft::vector<int> >(ftv, 5, 10, 4, 1);
	rangeEraseTest<std::vector<int> >(stdv, 5, 10, 5, 0);
	rangeEraseTest<ft::vector<int> >(ftv, 5, 10, 5, 0);
	rangeEraseTest<std::vector<int> >(stdv, 5, 10, 0, 5);
	rangeEraseTest<ft::vector<int> >(ftv, 5, 10, 0, 5);

	rangeEraseTest<std::vector<int> >(stdv, 5, 5, 0, 3);
	rangeEraseTest<ft::vector<int> >(ftv, 5, 5, 0, 3);
	rangeEraseTest<std::vector<int> >(stdv, 5, 5, 3, 2);
	rangeEraseTest<ft::vector<int> >(ftv, 5, 5, 3, 2);
	rangeEraseTest<std::vector<int> >(stdv, 5, 5, 5, 0);
	rangeEraseTest<ft::vector<int> >(ftv, 5, 5, 5, 0);
	rangeEraseTest<std::vector<int> >(stdv, 5, 10, 0, 5);
	rangeEraseTest<ft::vector<int> >(ftv, 5, 10, 0, 5);

	rangeEraseTest<std::vector<int> >(stdv, 0, 0, 0, 0);
	rangeEraseTest<ft::vector<int> >(ftv, 0, 0, 0, 0);
}

template <class T, class Vector>
void rangeEraseTestTime(const std::string& prompt, size_t size, const T& value)
{
	std::cout << "[ RANGE TIME, size = " << size
		<< ", value = " << value
		<< "] [" << prompt
		<< "]\n";
	Vector v(size, value);
	clock_t start, stop;
	print(v);
	start = std::clock();
	v.erase(v.begin(), v.begin() + (size >> 1));
	stop = std::clock();
	print(v);
	std::cout << "time = " << static_cast<double>(stop - start) / CLOCKS_PER_SEC << " s\n";
}

void rangeEraseTestsTime(const std::string& stdv, const std::string& ftv)
{
	rangeEraseTestTime<int, std::vector<int> >(stdv, SIZE, 69);
	rangeEraseTestTime<int, ft::vector<int> >(ftv, SIZE, 69);
	rangeEraseTestTime<std::string, std::vector<std::string> >(stdv, SIZE, "Hello, world!");
	rangeEraseTestTime<std::string, ft::vector<std::string> >(ftv, SIZE, "Hello, world!");
	rangeEraseTestTime<IntPtr, std::vector<IntPtr> >(stdv, SIZE, IntPtr());
	rangeEraseTestTime<IntPtr, ft::vector<IntPtr> >(ftv, SIZE, IntPtr());
}

/// main

testType getTestType(const char* arg)
{
	const std::string flags[] = {
		"-s",
		"-st",
		"-sa",
		"-r",
		"-rt",
		"-ra",
		"-t"
	};
	const size_t size = sizeof(flags) / sizeof(std::string);

	if (!arg) return ALL_TIME;

	const std::string str(arg);
	for (int i = 0; i < size; ++i) {
		if (flags[i] == str) return static_cast<testType>(i);
	}
	return ERROR;
}

int main(int argc, char** argv)
{
	const std::string stdv("std::vector");
	const std::string ftv("ft::vector");

	switch (getTestType(argv[1]))
	{
	case SINGLE:
		singleEraseTests(stdv, ftv);
		break;
	case SINGLE_TIME:
		singleEraseTestsTime(stdv, ftv);
		break;
	case SINGLE_ALL:
		singleEraseTests(stdv, ftv);
		singleEraseTestsTime(stdv, ftv);
		break;
	case RANGE:
		rangeEraseTests(stdv, ftv);
		break;
	case RANGE_TIME:
		rangeEraseTestsTime(stdv, ftv);
		break;
	case RANGE_ALL:
		rangeEraseTests(stdv, ftv);
		rangeEraseTestsTime(stdv, ftv);
		break;
	case ALL_TIME:
		singleEraseTestsTime(stdv, ftv);
		rangeEraseTestsTime(stdv, ftv);
		break;
	default:
		std::cout << "flags: -s | -st | -sa | -r | -rt | -ra | -t\n";
		return 1;
	}
	std::cout << "Press enter...";
	std::getchar();
	return 0;
}
