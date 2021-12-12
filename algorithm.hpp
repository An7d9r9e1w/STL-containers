/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 13:40:02 by nnamor            #+#    #+#             */
/*   Updated: 2021/12/11 15:12:41 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_H_
#define ALGORITHM_H_

namespace ft
{

/// equal compare
template <class InputIt1, class InputIt2>
inline bool equal(InputIt1 first1, InputIt1 last1,
				  InputIt2 first2)
{
	for ( ; first1 != last1; ++first1, ++first2) {
		if (*first1 != *first2) return false;
	}
	return true;
}

template <class InputIt1, class InputIt2, class BinaryPredicate>
inline bool equal(InputIt1 first1, InputIt1 last1,
				  InputIt2 first2, BinaryPredicate pred)
{
	for ( ; first1 != last1; ++first1, ++first2) {
		if (!pred(*first1, *first2)) return false;
	}
	return true;
}

/// lexicographical_compare
template<class InputIt1, class InputIt2>
inline bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
									InputIt2 first2, InputIt2 last2)
{
    for ( ; (first1 != last1) && (first2 != last2); ++first1, ++first2 ) {
        if (*first1 < *first2) return true;
        if (*first2 < *first1) return false;
    }
    return (first1 == last1) && (first2 != last2);
}

template<class InputIt1, class InputIt2, class Compare>
inline bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
									InputIt2 first2, InputIt2 last2, Compare comp)
{
    for ( ; (first1 != last1) && (first2 != last2); ++first1, ++first2 ) {
        if (comp(*first1, *first2)) return true;
        if (comp(*first2, *first1)) return false;
    }
    return (first1 == last1) && (first2 != last2);
}

/// swap
template <class T>
inline void swap(T& a, T& b)
{
	T tmp = a;
	a = b;
	b = tmp;
}


}

#endif	// ALGORITHM_H_
