#include <iostream>
#include <vector>

#include "../vector.hpp"

template <class Vector>
void print_sizes()
{
	std::cout << "size[" << sizeof(Vector)
		<< "] value_type[" << sizeof(typename Vector::value_type)
		<< "] allocator_type[" << sizeof(typename Vector::allocator_type)
		<< "] reference[" << sizeof(typename Vector::reference)
		<< "] const_reference[" << sizeof(typename Vector::const_reference)
		<< "] pointer[" << sizeof(typename Vector::pointer)
		<< "] const_pointer[" << sizeof(typename Vector::const_pointer)
		<< "] iterator[" << sizeof(typename Vector::iterator)
		<< "] iterator[" << sizeof(typename Vector::iterator)
		<< "] const_iterator[" << sizeof(typename Vector::const_iterator)
		<< "] const_iterator[" << sizeof(typename Vector::const_iterator)
		<< "] reverse_iterator[" << sizeof(typename Vector::reverse_iterator)
		<< "] const_reverse_iterator[" << sizeof(typename Vector::const_reverse_iterator)
		<< "] difference_type[" << sizeof(typename Vector::difference_type)
		<< "] size_type[" << sizeof(typename Vector::size_type)
		<< "]\n";
}

int main()
{
	print_sizes<std::vector<int> >();
	print_sizes<ft::vector<int> >();
	return 0;
}
