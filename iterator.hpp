/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 12:21:13 by nnamor            #+#    #+#             */
/*   Updated: 2022/01/31 22:11:52 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_H_
#define ITERATOR_H_

#include <cstddef>
#include <iterator>

namespace ft
{

/// iterator
using std::input_iterator_tag;
using std::output_iterator_tag;
using std::forward_iterator_tag;
using std::bidirectional_iterator_tag;
using std::random_access_iterator_tag;
//struct input_iterator_tag {};
//struct output_iterator_tag {};
//struct forward_iterator_tag : public input_iterator_tag {};
//struct bidirectional_iterator_tag : public forward_iterator_tag {};
//struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <
    class Category,
    class T,
    class Distance  = std::ptrdiff_t,
    class Pointer   = T*,
    class Reference = T&>
struct iterator
{
    typedef Category  iterator_category;
    typedef T         value_type;
    typedef Distance  difference_type;
    typedef Pointer   pointer;
    typedef Reference reference;
};

/// iterator_traits
template <class Iter>
struct iterator_traits
{
    typedef typename Iter::difference_type   difference_type;
    typedef typename Iter::value_type        value_type;
    typedef typename Iter::pointer           pointer;
    typedef typename Iter::reference         reference;
    typedef typename Iter::iterator_category iterator_category;
};

template <class T>
struct iterator_traits<T*>
{
    typedef std::ptrdiff_t             difference_type;
    typedef T                          value_type;
    typedef T*                         pointer;
    typedef T&                         reference;
    typedef random_access_iterator_tag iterator_category;
};

template <class T>
struct iterator_traits<const T*>
{
    typedef std::ptrdiff_t             difference_type;
    typedef T                          value_type;
    typedef const T*                   pointer;
    typedef const T&                   reference;
    typedef random_access_iterator_tag iterator_category;
};

/// Random-access iterator
template <class T>
class wrap_iter : public iterator<random_access_iterator_tag, T>
{
public:
    typedef typename iterator<random_access_iterator_tag, T>::iterator_category iterator_category;
    typedef typename iterator<random_access_iterator_tag, T>::value_type        value_type;
    typedef typename iterator<random_access_iterator_tag, T>::difference_type   difference_type;
    typedef typename iterator<random_access_iterator_tag, T>::pointer           pointer;
    typedef typename iterator<random_access_iterator_tag, T>::reference         reference;

public:
    wrap_iter(pointer ptr);
    wrap_iter(const wrap_iter& rai);
    ~wrap_iter();

public:
    wrap_iter&      operator=(const wrap_iter& rai);

    reference       operator*();
    const reference operator*() const;
    pointer         operator->();
    const pointer   operator->() const;
    reference       operator[](difference_type n);
    const reference operator[](difference_type n) const;

    wrap_iter&      operator++();
    wrap_iter       operator++(int);
    wrap_iter&      operator--();
    wrap_iter       operator--(int);
    wrap_iter&      operator+=(difference_type n);
    wrap_iter&      operator-=(difference_type n);
    wrap_iter       operator+(difference_type n) const;
    wrap_iter       operator-(difference_type n) const;

    template <class U>
    friend wrap_iter<U> operator+(typename wrap_iter<U>::difference_type n,
        const wrap_iter<U>& it);

    template <class U>
    friend typename wrap_iter<U>::difference_type operator-(
        const wrap_iter<U>& lhs,
        const wrap_iter<U>& rhs);

    template <class U>
    friend bool operator==(const wrap_iter<U>& a, const wrap_iter<U>& b);
    template <class U>
    friend bool operator!=(const wrap_iter<U>& a, const wrap_iter<U>& b);
    template <class U>
    friend bool operator< (const wrap_iter<U>& a, const wrap_iter<U>& b);
    template <class U>
    friend bool operator> (const wrap_iter<U>& a, const wrap_iter<U>& b);
    template <class U>
    friend bool operator<=(const wrap_iter<U>& a, const wrap_iter<U>& b);
    template <class U>
    friend bool operator>=(const wrap_iter<U>& a, const wrap_iter<U>& b);


private:
    pointer ptr_;
};


/// Reverse iterator
template <class Iter>
class reverse_iterator
{
public:
    typedef Iter                                                iterator_type;
    typedef typename iterator_traits<Iter>::iterator_category   iterator_category;
    typedef typename iterator_traits<Iter>::value_type          value_type;
    typedef typename iterator_traits<Iter>::difference_type     difference_type;
    typedef typename iterator_traits<Iter>::pointer             pointer;
    typedef typename iterator_traits<Iter>::reference           reference;

public:
    reverse_iterator();
    reverse_iterator(iterator_type x);
    reverse_iterator(const reverse_iterator<Iter>& other);

public:
    reverse_iterator& operator=(const reverse_iterator<Iter>& other);

    iterator_type     base() const;
    reference         operator*() const;
    pointer           operator->() const;
    reference         operator[](difference_type n) const;

    reverse_iterator& operator++();
    reverse_iterator& operator--();
    reverse_iterator  operator++(int);
    reverse_iterator  operator--(int);
    reverse_iterator  operator+(difference_type n) const;
    reverse_iterator  operator-(difference_type n) const;
    reverse_iterator& operator+=(difference_type n);
    reverse_iterator& operator-=(difference_type n);

    template<class Iterator>
    friend bool operator==(const reverse_iterator<Iterator>& lhs,
                           const reverse_iterator<Iterator>& rhs);
    template<class Iterator>
    friend bool operator!=(const reverse_iterator<Iterator>& lhs,
                           const reverse_iterator<Iterator>& rhs);
    template<class Iterator>
    friend bool operator< (const reverse_iterator<Iterator>& lhs,
                           const reverse_iterator<Iterator>& rhs);
    template<class Iterator>
    friend bool operator<=(const reverse_iterator<Iterator>& lhs,
                           const reverse_iterator<Iterator>& rhs);
    template<class Iterator>
    friend bool operator> (const reverse_iterator<Iterator>& lhs,
                           const reverse_iterator<Iterator>& rhs);
    template<class Iterator>
    friend bool operator>=(const reverse_iterator<Iterator>& lhs,
                           const reverse_iterator<Iterator>& rhs);
    template <class Iterator>
    friend reverse_iterator<Iterator> operator+(
        typename reverse_iterator<Iterator>::difference_type n,
        const reverse_iterator<Iterator>& rev_it);

    template <class Iterator>
    friend typename reverse_iterator<Iterator>::difference_type operator-(
        const reverse_iterator<Iterator>& lhs,
        const reverse_iterator<Iterator>& rhs);

protected:
    Iter current_;
};

///--------------------------Implementation--------------------------------------

/// Random-access iterator
template <class T>
wrap_iter<T>::wrap_iter(pointer ptr)
    : ptr_(ptr) {}

template <class T>
wrap_iter<T>::wrap_iter(const wrap_iter& rai)
    : ptr_(rai.ptr_) {}

template <class T>
wrap_iter<T>::~wrap_iter() {}

template <class T>
inline wrap_iter<T>& wrap_iter<T>::operator=(const wrap_iter& rai)
{
    if (this != &rai) {
        ptr_ = rai.ptr_;
    }
    return *this;
}

template <class T>
inline bool operator==(const wrap_iter<T>& a, const wrap_iter<T>& b)
{
    return a.ptr_ == b.ptr_;
}

template <class T>
inline bool operator!=(const wrap_iter<T>& a, const wrap_iter<T>& b)
{
    return a.ptr_ != b.ptr_;
}

template <class T>
inline bool operator<(const wrap_iter<T>& a, const wrap_iter<T>& b)
{
    return a.ptr_ < b.ptr_;
}

template <class T>
inline bool operator>(const wrap_iter<T>& a, const wrap_iter<T>& b)
{
    return a.ptr_ > b.ptr_;
}

template <class T>
inline bool operator<=(const wrap_iter<T>& a, const wrap_iter<T>& b)
{
    return a.ptr_ <= b.ptr_;
}

template <class T>
inline bool operator>=(const wrap_iter<T>& a, const wrap_iter<T>& b)
{
    return a.ptr_ >= b.ptr_;
}

template <class T>
inline typename wrap_iter<T>::reference
wrap_iter<T>::operator*()
{
    return *ptr_;
}

template <class T>
inline const typename wrap_iter<T>::reference
wrap_iter<T>::operator*() const
{
    return *ptr_;
}

template <class T>
inline typename wrap_iter<T>::pointer
wrap_iter<T>::operator->()
{
    return ptr_;
}

template <class T>
inline const typename wrap_iter<T>::pointer
wrap_iter<T>::operator->() const
{
    return ptr_;
}

template <class T>
inline typename wrap_iter<T>::reference
wrap_iter<T>::operator[](difference_type n)
{
    return ptr_[n];
}

template <class T>
inline const typename wrap_iter<T>::reference
wrap_iter<T>::operator[](difference_type n) const
{
    return ptr_[n];
}

template <class T>
inline wrap_iter<T>& wrap_iter<T>::operator++()
{
    ++ptr_;
    return *this;
}

template <class T>
inline wrap_iter<T> wrap_iter<T>::operator++(int)
{
    wrap_iter<T> tmp = *this;
    ++ptr_;
    return tmp;
}

template <class T>
inline wrap_iter<T>& wrap_iter<T>::operator--()
{
    --ptr_;
    return *this;
}

template <class T>
inline wrap_iter<T> wrap_iter<T>::operator--(int)
{
    wrap_iter<T> tmp = *this;
    ++ptr_;
    return tmp;
}

template <class T>
inline wrap_iter<T>& wrap_iter<T>::operator+=(difference_type n)
{
    ptr_ += n;
    return *this;
}

template <class T>
inline wrap_iter<T>& wrap_iter<T>::operator-=(difference_type n)
{
    ptr_ -= n;
    return *this;
}

template <class T>
inline wrap_iter<T> wrap_iter<T>::operator+(difference_type n) const
{
    wrap_iter<T> result(*this);
    result.ptr_ += n;
    return result;
}

template <class T>
inline wrap_iter<T> wrap_iter<T>::operator-(difference_type n) const
{
    wrap_iter<T> result(*this);
    result.ptr_ -= n;
    return result;
}

template <class T>
inline wrap_iter<T> operator+(typename wrap_iter<T>::difference_type n,
                              const wrap_iter<T>& it)
{
    wrap_iter<T> result(it);
    result.ptr_ += n;
    return result;
}

template <class T>
inline typename wrap_iter<T>::difference_type
operator-(const wrap_iter<T>& lhs,
          const wrap_iter<T>& rhs)
{
    return lhs.ptr_ - rhs.ptr_;
}


/// Reverse iterator
template <class Iter>
reverse_iterator<Iter>::reverse_iterator()
    : current_() {}

template <class Iter>
reverse_iterator<Iter>::reverse_iterator(iterator_type x)
    : current_(x) {}

template <class Iter>
reverse_iterator<Iter>::reverse_iterator(const reverse_iterator<Iter>& other)
    : current_(other.current_) {}

template <class Iter>
inline reverse_iterator<Iter>& reverse_iterator<Iter>::operator=(const reverse_iterator<Iter>& other)
{
    if (this != &other) {
        current_ = other.current_;
    }
    return *this;
}

template <class Iter>
inline typename reverse_iterator<Iter>::iterator_type
reverse_iterator<Iter>::base() const
{
    return current_;
}

template <class Iter>
inline typename reverse_iterator<Iter>::reference
reverse_iterator<Iter>::operator*() const
{
    Iter tmp(base());
    return *--tmp;
}

template <class Iter>
inline typename reverse_iterator<Iter>::pointer
reverse_iterator<Iter>::operator->() const
{
    return &(operator*());
}

template <class Iter>
inline typename reverse_iterator<Iter>::reference
reverse_iterator<Iter>::operator[](difference_type n) const
{
    return base()[-n - 1];
}

template <class Iter>
inline reverse_iterator<Iter>& reverse_iterator<Iter>::operator++()
{
    --current_;
    return *this;
}

template <class Iter>
inline reverse_iterator<Iter>& reverse_iterator<Iter>::operator--()
{
    ++current_;
    return *this;
}

template <class Iter>
inline reverse_iterator<Iter> reverse_iterator<Iter>::operator++(int)
{
    reverse_iterator<Iter> tmp(*this);
    --current_;
    return tmp;
}

template <class Iter>
inline reverse_iterator<Iter> reverse_iterator<Iter>::operator--(int)
{
    reverse_iterator<Iter> tmp(*this);
    ++current_;
    return tmp;
}

template <class Iter>
inline reverse_iterator<Iter>
reverse_iterator<Iter>::operator+(difference_type n) const
{
    return reverse_iterator<Iter>(base() - n);
}

template <class Iter>
inline reverse_iterator<Iter>
reverse_iterator<Iter>::operator-(difference_type n) const
{
    return reverse_iterator<Iter>(base() + n);
}

template <class Iter>
inline reverse_iterator<Iter>&
reverse_iterator<Iter>::operator+=(difference_type n)
{
    current_ -= n;
    return *this;
}

template <class Iter>
inline reverse_iterator<Iter>&
reverse_iterator<Iter>::operator-=(difference_type n)
{
    current_ += n;
    return *this;
}

template<class Iterator>
bool operator==(const reverse_iterator<Iterator>& lhs,
                const reverse_iterator<Iterator>& rhs)
{
    return lhs.base() == rhs.base();
}

template<class Iterator>
bool operator!=(const reverse_iterator<Iterator>& lhs,
                const reverse_iterator<Iterator>& rhs)
{
    return lhs.base() != rhs.base();
}

template<class Iterator>
bool operator<(const reverse_iterator<Iterator>& lhs,
               const reverse_iterator<Iterator>& rhs)
{
    return lhs.base() > rhs.base();
}

template<class Iterator>
bool operator<=(const reverse_iterator<Iterator>& lhs,
                const reverse_iterator<Iterator>& rhs)
{
    return lhs.base() >= rhs.base();
}

template<class Iterator>
bool operator>(const reverse_iterator<Iterator>& lhs,
               const reverse_iterator<Iterator>& rhs)
{
    return lhs.base() < rhs.base();
}

template<class Iterator>
bool operator>=(const reverse_iterator<Iterator>& lhs,
                const reverse_iterator<Iterator>& rhs)
{
    return lhs.base() <= rhs.base();
}

template <class Iterator>
reverse_iterator<Iterator> operator+(
    typename reverse_iterator<Iterator>::difference_type n,
    const reverse_iterator<Iterator>& rev_it)
{
    return reverse_iterator<Iterator>(rev_it.base() - n);
}

template <class Iterator>
typename reverse_iterator<Iterator>::difference_type operator-(
    const reverse_iterator<Iterator>& lhs,
    const reverse_iterator<Iterator>& rhs)
{
    return rhs.base() - lhs.base();
}

};

#endif    //ITERATOR_H_
