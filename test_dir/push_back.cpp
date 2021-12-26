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
	PUSHBACK,
	PUSHBACK_TIME,
	PUSHBACK_ALL
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

void printTestLabel(const std::string& test_name, const std::string& prompt, size_t size, size_t cap)
{
	std::cout << "\n--- [" << test_name
		<< ", size = " << size
		<< ", cap = " << cap
		<< "] [" << prompt
		<< "] ---\n";
}


/// push_back
template <class Vector>
void pushBackTest(const std::string& prompt, size_t size, size_t cap, const int value)
{
	try {
		printTestLabel("PUSHBACK", prompt, size, cap);

		if (size > cap) throw std::runtime_error("size > capacity");

		int* arr = new int[size];
		for (size_t i = 0; i < size; ++i)
			arr[i] = i + 1;

		Vector v;
		v.reserve(cap);
		v.assign(arr, arr + size);
		delete[] arr;

		checkprint(v);

		v.push_back(value);

		checkprint(v);
	}
	catch (const std::exception& e) {
		std::cerr << "PUSHBACK: " << prompt << ": " << e.what() << '\n';
	}
}

void pushBackTests(const std::string& stdv, const std::string& ftv)
{
	pushBackTest<std::vector<int> >(stdv, 5, 10, 69);
	pushBackTest<ft::vector<int> >(ftv, 5, 10, 69);

	pushBackTest<std::vector<int> >(stdv, 5, 5, 69);
	pushBackTest<ft::vector<int> >(ftv, 5, 5, 69);

	pushBackTest<std::vector<int> >(stdv, 0, 0, 69);
	pushBackTest<ft::vector<int> >(ftv, 0, 0, 69);
}

template <class T, class Vector>
void pushBackTestTime(const std::string& prompt, size_t size, const T& value)
{
	std::cout << "[ PUSHBACK TIME, size = " << size
		<< ", value = " << value
		<< "] [" << prompt
		<< "]\n";
	Vector v(size, value);
	clock_t start, stop;
	print(v);
	start = std::clock();
	v.push_back(value);
	stop = std::clock();
	print(v);
	std::cout << "time = " << static_cast<double>(stop - start) / CLOCKS_PER_SEC << " s\n";
}

void pushBackTestsTime(const std::string& stdv, const std::string& ftv)
{
	pushBackTestTime<int, std::vector<int> >(stdv, SIZE, 69);
	pushBackTestTime<int, ft::vector<int> >(ftv, SIZE, 69);
	pushBackTestTime<std::string, std::vector<std::string> >(stdv, SIZE, "Hello, world!");
	pushBackTestTime<std::string, ft::vector<std::string> >(ftv, SIZE, "Hello, world!");
	pushBackTestTime<IntPtr, std::vector<IntPtr> >(stdv, SIZE, IntPtr());
	pushBackTestTime<IntPtr, ft::vector<IntPtr> >(ftv, SIZE, IntPtr());
}

/// main
testType getTestType(const char* arg)
{
	const std::string flags[] = {
		"-p",
		"-pt",
		"-pa"
	};
	const size_t size = sizeof(flags) / sizeof(std::string);

	if (!arg) return PUSHBACK_TIME;

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
	case PUSHBACK:
		pushBackTests(stdv, ftv);
		break;
	case PUSHBACK_TIME:
		pushBackTestsTime(stdv, ftv);
		break;
	case PUSHBACK_ALL:
		pushBackTests(stdv, ftv);
		pushBackTestsTime(stdv, ftv);
		break;
	default:
		std::cout << "flags: -p | -pt | -pa | -t\n";
		return 1;
	}
	std::cout << "Press enter...";
	std::getchar();
	return 0;
}
