/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 14:36:30 by nnamor            #+#    #+#             */
/*   Updated: 2022/01/31 19:28:59 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_H_
#define UTILITY_H_

namespace ft
{

/// pair
template <class T1, class T2>
struct pair
{
    typedef T1 first_type;
    typedef T2 second_type;

    first_type  first;
    second_type second;

    pair();
    pair(const first_type& x, const second_type& y);
    pair(const pair<T1, T2>& p);

    pair& operator=(const pair& other);

    template<class U1, class U2>
    friend bool operator==(const std::pair<U1,U2>& lhs, const std::pair<U1,U2>& rhs);
    template<class U1, class U2>
    friend bool operator!=(const std::pair<U1,U2>& lhs, const std::pair<U1,U2>& rhs);
    template<class U1, class U2>
    friend bool operator< (const std::pair<U1,U2>& lhs, const std::pair<U1,U2>& rhs);
    template<class U1, class U2>
    friend bool operator<=(const std::pair<U1,U2>& lhs, const std::pair<U1,U2>& rhs);
    template<class U1, class U2>
    friend bool operator> (const std::pair<U1,U2>& lhs, const std::pair<U1,U2>& rhs);
    template<class U1, class U2>
    friend bool operator>=(const std::pair<U1,U2>& lhs, const std::pair<U1,U2>& rhs);

};

/// make_pair
template <class T1,class T2>
pair<T1,T2> make_pair(T1 x, T2 y)
{
    return pair<T1, T2>(x, y);
}

///--------------------------Implementation--------------------------------------

/// pair
template <class T1, class T2>
pair<T1, T2>::pair()
    :
    first(),
    second()
{
}

template <class T1, class T2>
pair<T1, T2>::pair(const first_type& x, const second_type& y)
    :
    first(x),
    second(y)
{
}

template <class T1, class T2>
pair<T1, T2>::pair(const pair<T1, T2>& p)
    :
    first(p.first),
    second(p.second)
{
}

template<class T1, class T2>
inline pair<T1, T2>& pair<T1, T2>::operator=(const pair& other)
{
    if (this != &other) {
        first = other.first;
        second = other.second;
    }
    return *this;
}

template<class T1, class T2>
inline bool operator==(const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs)
{
    return lhs.first == rhs.first
        && lhs.second == rhs.second;
}

template<class T1, class T2>
inline bool operator!=(const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs)
{
    return !(lhs == rhs);
}

template<class T1, class T2>
inline bool operator<(const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs)
{
    if (lhs.first < rhs.first) return true;
    if (rhs.first < lhs.first) return false;
    if (lhs.second < rhs.second) return true;
    return false;
}

template<class T1, class T2>
inline bool operator<=(const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs)
{
    return !(rhs < lhs);
}

template<class T1, class T2>
inline bool operator>(const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs)
{
    return rhs < lhs;
}

template<class T1, class T2>
inline bool operator>=(const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs)
{
    return !(lhs < rhs);
}

}

#endif /*UTILITY_H_*/
