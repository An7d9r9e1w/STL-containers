#include <vector>
#include <iostream>

#include "../vector.hpp"

class CustomAlloc : public std::vector<int>::allocator_type
{};

int main()
{
	std::vector<int> v1(10);
	std::vector<int, CustomAlloc> v2(10);

//	v1 = v2;					// error
//	std::vector<int> v3(v2);	// error

	ft::vector<int> mv1(10);
	ft::vector<int, CustomAlloc> mv2(10);

//	mv1 = mv2;					// error
//	std::vector<int> v3(v2);	// error

	return 0;
}
