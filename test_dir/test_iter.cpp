#include <iostream>
#include <algorithm>

#include "iterator.hpp"
#include <iterator>
 
template<typename T, size_t SIZE>
class Stack
{
    T arr[SIZE];
    size_t pos = 0;
public:
	typedef ft::reverse_iterator<T*> it;

    T pop() {
        return arr[--pos];
    }
    Stack& push(const T& t) {
        arr[pos++] = t;
        return *this;
    }
    // we wish that looping on Stack would be in LIFO order
    // thus we use std::reverse_iterator as an adaptor to existing iterators
    // (which are in this case the simple pointers: [arr, arr+pos)
	it begin() {
        return it(arr + pos);
    }
	it end() {
        return it(arr);
    }
};

struct point
{
	float x;
	float y;
};

void test_ref()
{
    Stack<int, 8> s;
    s.push(5).push(15).push(25).push(35);
    for(int val: s) {
        std::cout << val << ' ';
    }
	typedef typename Stack<int, 8>::it ref_it;

	ref_it it(s.begin());
	std::cout << '\n' << (it == ref_it(s.begin().base())) << " | 1\n";
	std::cout << it[2] << " | 15\n";

	point p = { 0.5, 0.6 };
	ft::reverse_iterator<point*> pit(&p);
	std::reverse_iterator<point*> spit(&p);
	std::cout << (pit - 1)->x << " | 0.5\n";
	std::cout << (-1 + pit)->x << " | 0.5\n";
	std::cout << (spit - 1)->x << " | 0.5\n";
	std::cout << (-1 + spit)->x << " | 0.5\n";

	std::cout << (s.end() - s.begin()) << " | 4\n";
	std::cout << s.begin() - s.end() << " | -4\n";
}

template<typename T, size_t SIZE>
class Stack2
{
    T arr[SIZE];
    size_t pos = 0;
public:
	typedef ft::RAIterator<T> it;

    T pop() {
        return arr[--pos];
    }
    Stack2& push(const T& t) {
        arr[pos++] = t;
        return *this;
    }
    // we wish that looping on Stack would be in LIFO order
    // thus we use std::reverse_iterator as an adaptor to existing iterators
    // (which are in this case the simple pointers: [arr, arr+pos)
	it begin() {
        return it(arr);
    }
	it end() {
        return it(arr + pos);
    }
};

void test_it()
{
    Stack2<int, 8> s;
    s.push(5).push(15).push(25).push(35);
    for(int val: s) {
        std::cout << val << ' ';
    }
	typedef typename Stack2<int, 8>::it ref_it;

	ref_it it(s.begin());
	std::cout << it[2] << " | 15\n";

	point p = { 0.5, 0.6 };
	ft::RAIterator<point> pit(&p);
	std::cout << (pit)->x << " | 0.5\n";

	std::cout << (s.end() - s.begin()) << " | 4\n";
	std::cout << s.begin() - s.end() << " | -4\n";
}
/*
void test_rai()
{
	RAIterator(pointer ptr);
	RAIterator(const RAIterator& rai);
	~RAIterator();

public:
	RAIterator&		operator=(const RAIterator& rai);

	reference		operator*();
	const reference	operator*() const;
	pointer			operator->();
	const pointer	operator->() const;
	reference		operator[](difference_type n);
	const reference	operator[](difference_type n) const;

	RAIterator&		operator++();
	RAIterator		operator++(int);
	RAIterator&		operator--();
	RAIterator		operator--(int);
	RAIterator&		operator+=(difference_type n);
	RAIterator&		operator-=(difference_type n);
	RAIterator		operator+(difference_type n) const;
	RAIterator		operator-(difference_type n) const;

	template <class U>
	friend RAIterator<U> operator+(typename RAIterator<U>::difference_type n,
		const RAIterator<U>& it);

	template <class U>
	friend typename RAIterator<U>::difference_type operator-(
		const RAIterator<U>& lhs,
		const RAIterator<U>& rhs);

	template <class U>
	friend bool		operator==(const RAIterator<U>& a, const RAIterator<U>& b);
	template <class U>
	friend bool		operator!=(const RAIterator<U>& a, const RAIterator<U>& b);
	template <class U>
	friend bool		operator<(const RAIterator<U>& a, const RAIterator<U>& b);
	template <class U>
	friend bool		operator>(const RAIterator<U>& a, const RAIterator<U>& b);
	template <class U>
	friend bool		operator<=(const RAIterator<U>& a, const RAIterator<U>& b);
	template <class U>
	friend bool		operator>=(const RAIterator<U>& a, const RAIterator<U>& b);
}*/

int main()
{
//	test_ref();
	test_it();
	return 0;
}
