#include <iostream>
#include <string>
#include <stdexcept>

#include <vector>
#include "../vector.hpp"

#include "print.hpp"

#define EQUAL_PROMPT "EQUAL"
#define NOTEQUAL_PROMPT "NOT EQUAL"
#define GREAT_PROMPT "GREAT"
#define GREATEQUAL_PROMPT "GREAT or EQUAL"
#define LESS_PROMPT "LESS"
#define LESSEQUAL_PROMPT "LESS or EQUAL"

enum testType
{
	EQUAL,
	NOTEQUAL,
	GREAT,
	GREATEQUAL,
	LESS,
	LESSEQUAL
};

void printLabel(const std::string& test, const std::string& prompt,
	size_t cap1, size_t size1, int direct1,
	size_t cap2, size_t size2, int direct2)
{
	std::cout << "---[" << test
		<< "]--- " << prompt
		<< "\ncap1 = " << cap1
		<< ", size1 = " << size1
		<< ", direct1 = " << direct1
		<< "\ncap2 = " << cap2
		<< ", size2 = " << size2
		<< ", direct2 = " << direct2 << '\n';
}

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

template <class Vector>
Vector createVector(size_t cap, size_t size, int direct)
{
	Vector v;
	v.reserve(cap);
	int value = (direct >= 0) ? 0 : -direct * size + direct;
	for (size_t i = 0; i < size; ++i) {
		v.push_back(value);
		value += direct;
	}
	return v;
}

template <class Vector>
void test(const std::string& prompt, const std::string& test, testType type,
	size_t cap1, size_t size1, int direct1,
	size_t cap2, size_t size2, int direct2)
{
	printLabel(test, prompt, cap1, size1, direct1, cap2, size2, direct2);
	try {
		if (size1 > cap1 || size2 > cap2) throw std::runtime_error("size > cap");
		Vector v1 = createVector<Vector>(cap1, size1, direct1);
		Vector v2 = createVector<Vector>(cap2, size2, direct2);
		checkprint(v1);
		checkprint(v2);
		bool res;
		switch (type) {
		case EQUAL:
			res = (v1 == v2); break;
		case NOTEQUAL:
			res = (v1 != v2); break;
		case GREAT:
			res = (v1 > v2); break;
		case GREATEQUAL:
			res = (v1 >= v2); break;
		case LESS:
			res = (v1 < v2); break;
		case LESSEQUAL:
			res = (v1 <= v2); break;
		default:
			throw std::runtime_error("invalid comparison type");
		}
		std::cout << res << '\n';
	}
	catch (const std::exception& e) {
		std::cerr << test << ": " << e.what() << '\n';
	}
}

void equalTests(const std::string& stdv, const std::string& ftv)
{
	test<std::vector<int> >(stdv, EQUAL_PROMPT, EQUAL,
							5, 5, 0,
							5, 5, 0);
	test<ft::vector<int> >(ftv, EQUAL_PROMPT, EQUAL,
							5, 5, 0,
							5, 5, 0);
	test<std::vector<int> >(stdv, EQUAL_PROMPT, EQUAL,
							5, 5, 1,
							5, 5, 0);
	test<ft::vector<int> >(ftv, EQUAL_PROMPT, EQUAL,
							5, 5, 1,
							5, 5, 0);
	test<std::vector<int> >(stdv, EQUAL_PROMPT, EQUAL,
							5, 5, 1,
							5, 5, -1);
	test<ft::vector<int> >(ftv, EQUAL_PROMPT, EQUAL,
							5, 5, 1,
							5, 5, -1);
	test<std::vector<int> >(stdv, EQUAL_PROMPT, EQUAL,
							5, 4, 0,
							5, 5, 0);
	test<ft::vector<int> >(ftv, EQUAL_PROMPT, EQUAL,
							5, 4, 0,
							5, 5, 0);
	test<std::vector<int> >(stdv, EQUAL_PROMPT, EQUAL,
							4, 4, 0,
							5, 4, 0);
	test<ft::vector<int> >(ftv, EQUAL_PROMPT, EQUAL,
							4, 4, 0,
							5, 4, 0);
}

void lessTests(const std::string& stdv, const std::string& ftv)
{
	test<std::vector<int> >(stdv, LESS_PROMPT, LESS,
							5, 4, 0,
							5, 4, 1);
	test<ft::vector<int> >(ftv, LESS_PROMPT, LESS,
							5, 4, 0,
							5, 4, 1);
}

void lessEqualTests(const std::string& stdv, const std::string& ftv)
{
	test<std::vector<int> >(stdv, LESSEQUAL_PROMPT, LESSEQUAL,
							5, 4, 0,
							5, 4, 0);
	test<ft::vector<int> >(ftv, LESSEQUAL_PROMPT, LESSEQUAL,
							5, 4, 0,
							5, 4, 0);
}

int main()
{
	const std::string stdv("std::vector");
	const std::string ftv("ft::vector");

	equalTests(stdv, ftv);
	lessTests(stdv, ftv);
	lessEqualTests(stdv, ftv);
	return 0;
}
