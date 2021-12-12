#include <iostream>
#include <iterator>
#include <type_traits>
#include <vector>

template <class T_>
struct has_iterator_category_
{
private:
	struct twoBytes_ { char b1_; char b2_; };
	template <class U_> static twoBytes_ test_(...);
	template <class U_> static char test_(typename U_::iterator_category* = nullptr);
public:
	static const bool value = sizeof(test_<T_>(0)) == 1;
};

template <class T>
struct is_iterator
	: public std::integral_constant<bool, has_iterator_category_<T>::value> {};

template <class T>
struct is_iterator<T*> : public std::true_type {};

int main()
{
//	std::cout << has_iterator_category_<int>::value << '\n';
//	std::cout << has_iterator_category_<std::vector<int>::iterator>::value << '\n';
//	std::cout << has_iterator_category_<std::iterator_traits<int*> >::value << '\n';
	std::cout << is_iterator<int>::value << '\n';
	std::cout << is_iterator<std::vector<int>::iterator>::value << '\n';
	std::cout << is_iterator<int*>::value << '\n';

	return 0;
}
