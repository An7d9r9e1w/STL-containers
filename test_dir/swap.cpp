#include <iostream>
#include <vector>

#include <cstdio>

#include "../vector.hpp"

template<class Os, class Co> Os& operator<<(Os& os, const Co& co) {
    os << "{";
    for (size_t i = 0; i < co.size(); ++i) { os << ' ' << co[i]; }
    return os << " } ";
}
 
template <class Vector>
void test()
{
	int arr1[] = { 1, 2, 3 };
	int arr2[] = { 4, 5 };
    Vector a1(arr1, arr1 + 3), a2(arr2, arr2 + 2);
 
    typedef typename Vector::iterator iter;

    
	iter it1 = a1.begin();
    iter it2 = a2.begin();
 
    int& ref1 = a1.front();
    int& ref2 = a2.front();
 
    std::cout << a1 << a2 << *it1 << ' ' << *it2 << ' ' << ref1 << ' ' << ref2 << '\n';
    a1.swap(a2);
    std::cout << a1 << a2 << *it1 << ' ' << *it2 << ' ' << ref1 << ' ' << ref2 << '\n';
 
    // Note that after swap the iterators and references stay associated with their
    // original elements, e.g. it1 that pointed to an element in 'a1' with value 2
    // still points to the same element, though this element was moved into 'a2'.
}

int main()
{
	test<std::vector<int> >();
	test<ft::vector<int> >();
	std::getchar();
	return 0;
}
