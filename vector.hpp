/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 15:51:52 by nnamor            #+#    #+#             */
/*   Updated: 2021/12/12 17:57:09 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H_
#define VECTOR_H_

#include <memory>
#include <stdexcept>
#include <new>
#include <limits>

#include <cstddef>
#include <cstring>

#include "iterator.hpp"
#include "type_traits.hpp"



namespace ft
{

template <class T, class Allocator = std::allocator<T> >
class vector
{
public:
	typedef 		 T													value_type;
	typedef 		 Allocator											allocator_type;
	typedef typename allocator_type::reference							reference;
	typedef typename allocator_type::const_reference					const_reference;
	typedef typename allocator_type::pointer							pointer;
	typedef typename allocator_type::const_pointer						const_pointer;
	typedef 		 ft::wrap_iter<value_type>							iterator;
//	typedef			 ft::iterator_traits<pointer>						iterator;
	typedef 		 ft::wrap_iter<const value_type>					const_iterator;
//	typedef			 ft::iterator_traits<const_pointer>					const_iterator;
	typedef 		 ft::reverse_iterator<iterator>						reverse_iterator;
	typedef 		 ft::reverse_iterator<const_iterator>				const_reverse_iterator;
	typedef typename ft::iterator_traits<iterator>::difference_type		difference_type;
	typedef 		 std::size_t										size_type;

public:
	/// default constructor
	explicit
	vector (const allocator_type& alloc = allocator_type());
	/// fill constructor
	explicit
	vector (size_type n,
			const value_type& val = value_type(),
			const allocator_type& alloc = allocator_type());
	/// range constructor
	template <class InputIterator>
	vector (InputIterator first, InputIterator last,
			const allocator_type& alloc = allocator_type(),
			typename enable_if<is_iterator<InputIterator>::value, bool>::type = 0);
	/// copy constructor
	vector (const vector& x);

	~vector();

public:
	vector&			operator=(const vector& other);
	template <class InputIterator>
	void			assign(InputIterator first, InputIterator last,
						typename enable_if<is_iterator<InputIterator>::value, bool>::type = 0);
	void			assign(size_type count, const value_type& val);
	allocator_type	get_allocator() const;

	/// element access
	reference		at(size_type pos);
	const_reference	at(size_type pos) const;

	reference		operator[](size_type pos);
	const_reference	operator[](size_type pos) const;

	reference		front();
	const_reference	front() const;
	reference		back();
	const_reference	back() const;

//	value_type*		data();		// officially since C++11


	/// iterators
	iterator		begin();
	const_iterator	begin() const;
	iterator		end();
	const_iterator	end() const;

	reverse_iterator		rbegin();
	const_reverse_iterator	rbegin() const;
	reverse_iterator		rend();
	const_reverse_iterator	rend() const;

	/// capacity
	bool			empty() const;
	size_type		size() const;
	size_type		max_size() const;
	void			reserve(size_type new_cap);
	size_type		capacity() const;

	/// modifiers
	void			clear();
	iterator		insert(iterator pos, const value_type& value);
	void			insert(iterator pos, size_type count, const T& value);
	iterator		erase(iterator pos);
	iterator		erase(iterator first, iterator last);

	void			resize(size_type count, value_type value = value_type());

private:
	void	realloc_(size_type count);
	void	destroy_();

private:
	allocator_type	alloc_;
	pointer			arr_;
	size_type		size_;
	size_type		capacity_;
};



/// vector
template <class T, class Allocator>
vector<T, Allocator>::vector (const allocator_type& alloc)
	: alloc_(alloc),
	arr_(NULL),
	size_(0),
	capacity_(0)
{
}

template <class T, class Allocator>
vector<T, Allocator>::vector (size_type n, const value_type& val, const allocator_type& alloc)
	: alloc_(alloc),
	arr_(NULL),
	size_(0),
	capacity_(0)
{
	resize(n, val);
}

template <class T, class Allocator>
	template <class InputIterator>
vector<T, Allocator>::vector (InputIterator first, InputIterator last, const allocator_type& alloc,
	typename enable_if<is_iterator<InputIterator>::value, bool>::type)
	: alloc_(alloc),
	arr_(NULL),
	size_(0),
	capacity_(0)
{
	assign(first, last);
}

template <class T, class Allocator>
vector<T, Allocator>::vector (const vector& x)
	: alloc_(x.alloc_),
	arr_(NULL),
	size_(0),
	capacity_(0)
{
	*this = x;
}

template <class T, class Allocator>
vector<T, Allocator>::~vector()
{
	destroy_();
}

template <class T, class Allocator>
vector<T, Allocator>& vector<T, Allocator>::operator=(const vector& other)
{
	if (this != &other) {
		clear();
		if (other.size_ > capacity_) realloc_(other.size_);
		while (size_ < other.size_) {
			alloc_.construct(arr_ + size_, other.arr_[size_]);
			++size_;
		}
	}
	return *this;
}

template <class T, class Allocator>
	template <class InputIterator>
void vector<T, Allocator>::assign(InputIterator first, InputIterator last,
	typename enable_if<is_iterator<InputIterator>::value, bool>::type)
{
	size_type n = 0;
	for (InputIterator it(first); it != last; ++it)
		++n;
	clear();
	if (n > capacity_) realloc_(n);
	for ( ; first != last; ++first)
		alloc_.construct(arr_++, *first);
	arr_ -= n;
	size_ = n;
}

template <class T, class Allocator>
inline void vector<T, Allocator>::assign(size_type count, const value_type& val)
{
	clear();
	resize(count, val);
}

template <class T, class Allocator>
inline typename vector<T, Allocator>::allocator_type
vector<T, Allocator>::get_allocator() const
{
	return alloc_;
}

template <class T, class Allocator>
inline typename vector<T, Allocator>::reference
vector<T, Allocator>::operator[](size_type pos)
{
	return arr_[pos];
}

template <class T, class Allocator>
inline typename vector<T, Allocator>::const_reference
vector<T, Allocator>::operator[](size_type pos) const
{
	return arr_[pos];
}

template <class T, class Allocator>
inline typename vector<T, Allocator>::reference
vector<T, Allocator>::at(size_type pos)
{
	if (pos >= size_) throw std::out_of_range("vector");
	return arr_[pos];
}

template <class T, class Allocator>
inline typename vector<T, Allocator>::const_reference
vector<T, Allocator>::at(size_type pos) const
{
	if (pos >= size_) throw std::out_of_range("vector");
	return arr_[pos];
}

template <class T, class Allocator>
inline typename vector<T, Allocator>::reference
vector<T, Allocator>::front()
{
	return *arr_;
}

template <class T, class Allocator>
inline typename vector<T, Allocator>::const_reference
vector<T, Allocator>::front() const
{
	return *arr_;
}

template <class T, class Allocator>
inline typename vector<T, Allocator>::reference
vector<T, Allocator>::back()
{
	return arr_[size_ - 1];
}

template <class T, class Allocator>
inline typename vector<T, Allocator>::const_reference
vector<T, Allocator>::back() const
{
	return arr_[size_ - 1];
}

template <class T, class Allocator>
inline typename vector<T, Allocator>::iterator
vector<T, Allocator>::begin()
{
	return iterator(arr_);
}

template <class T, class Allocator>
inline typename vector<T, Allocator>::const_iterator
vector<T, Allocator>::begin() const
{
	return iterator(arr_);
}

template <class T, class Allocator>
inline typename vector<T, Allocator>::iterator
vector<T, Allocator>::end()
{
	return iterator(arr_ + size_);
}

template <class T, class Allocator>
inline typename vector<T, Allocator>::const_iterator
vector<T, Allocator>::end() const
{
	return iterator(arr_ + size_);
}

template <class T, class Allocator>
inline typename vector<T, Allocator>::reverse_iterator
vector<T, Allocator>::rbegin()
{
	return reverse_iterator(end());
}

template <class T, class Allocator>
inline typename vector<T, Allocator>::const_reverse_iterator
vector<T, Allocator>::rbegin() const
{
	return reverse_iterator(end());
}

template <class T, class Allocator>
inline typename vector<T, Allocator>::reverse_iterator
vector<T, Allocator>::rend()
{
	return reverse_iterator(begin());
}

template <class T, class Allocator>
inline typename vector<T, Allocator>::const_reverse_iterator
vector<T, Allocator>::rend() const
{
	return reverse_iterator(begin());
}

template <class T, class Allocator>
inline bool vector<T, Allocator>::empty() const
{
	return !size_;
}

template <class T, class Allocator>
inline typename vector<T, Allocator>::size_type
vector<T, Allocator>::size() const
{
	return size_;
}

template <class T, class Allocator>
inline typename vector<T, Allocator>::size_type
vector<T, Allocator>::max_size() const
{
	size_t type_size = sizeof(value_type);
	if (type_size < 4)
		return std::numeric_limits<difference_type>::max();
	return std::numeric_limits<difference_type>::max() / (type_size >> 1);
}

template <class T, class Allocator>
inline void vector<T, Allocator>::reserve(size_type new_cap)
{
	if (new_cap > capacity_) realloc_(new_cap);
}

template <class T, class Allocator>
inline typename vector<T, Allocator>::size_type
vector<T, Allocator>::capacity() const
{
	return capacity_;
}

template <class T, class Allocator>
inline void vector<T, Allocator>::clear()
{
	for (size_type i = 0; i < size_; ++i)
		alloc_.destroy(arr_ + i);
	size_ = 0;
}

template <class T, class Allocator>
typename vector<T, Allocator>::iterator
vector<T, Allocator>::insert(iterator pos, const value_type& value)
{
	difference_type shift = &*pos - arr_;
	if (!capacity_) {
		realloc_(1);
	}
	else if (size_ + 1 > capacity_) {
		realloc_(capacity_ << 1);
	}
	pointer target = arr_ + shift;
	std::memmove(target + 1, target, sizeof(value_type) * (size_++ - shift));
	alloc_.construct(target, value);
	return iterator(target);
}

template <class T, class Allocator>
void vector<T, Allocator>::insert(iterator pos, size_type count, const T& value)
{
	difference_type shift = &*pos - arr_;
	if (!capacity_) {
		realloc_(count);
	}
	else if (size_ + count > capacity_) {
		if (size_ + count > (capacity_ << 1))
			realloc_(size_ + count);
		else
			realloc_(capacity_ << 1);
	}
	pointer target = arr_ + shift;
	std::memmove(target + count, target, sizeof(value_type) * (size_ - shift));
	for (size_type i = 0; i < count; ++i)
		alloc_.construct(target + i, value);
	size_ += count;
}
//TODO TEST
template <class T, class Allocator>
typename vector<T, Allocator>::iterator
vector<T, Allocator>::erase(iterator pos)
{
	difference_type shift = &*pos - arr_;
	//TODO check std::vector for	pos >= end()
	if (shift == size_) return pos;
	pointer target = &*pos;
	alloc_.destroy(target);
	std::memmove(target, target + 1, sizeof(value_type) * (--size_ - shift));
	return pos;
}
/*
	1 2 3 4 5
	pos = 2
	shift = 2
	size - shift - 1 = 2
	1 2 * 4 5
	size = 4

	-1	-> because pos is deleted
	but |	last is out of delete range, so there is no -1
		V
*/
//TODO TEST
template <class T, class Allocator>
typename vector<T, Allocator>::iterator
vector<T, Allocator>::erase(iterator first, iterator last)
{
	difference_type shift = &*last - arr_;
	//TODO
	//if
	pointer target = &*first;
	size_type len = last - first;
	for (size_type i = 0; i < len; ++i)
		alloc_.destroy(target + i);
	std::memmove(target, target + len, sizeof(value_type) * (size_ - shift));
	size_ -= len;
}
/*
	1 2 3 4 5 6 7
	f = 2
	l = 5
	shift = 5
	len = 3
	size - shift = 2
	1 2 * * * 5 7
	size = 7 - 3 = 4
*/
template <class T, class Allocator>
void vector<T, Allocator>::resize(size_type count, value_type value)
{
	if (count > capacity_) realloc_(count);
	while (size_ > count)
		alloc_.destroy(arr_ + --size_);
	while (size_ < count)
		alloc_.construct(arr_ + size_++, value);
}

template <class T, class Allocator>
inline void vector<T, Allocator>::realloc_(size_type count)
{
	if (count > max_size()) {
		destroy_();
		throw std::length_error("vector");
	}
	try {
		pointer tmp_arr = alloc_.allocate(count);
		std::memcpy(tmp_arr, arr_, sizeof(value_type) * size_);
		alloc_.deallocate(arr_, capacity_);
		arr_ = tmp_arr;
		capacity_ = count;
	}
	catch (const std::bad_alloc& e) {
		destroy_();
		throw;
	}
}

template <class T, class Allocator>
inline void vector<T, Allocator>::destroy_()
{
	clear();
	alloc_.deallocate(arr_, capacity_);
	arr_ = NULL;
	capacity_ = 0;
}


}

#endif	// VECTOR_H_
