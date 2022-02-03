/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:02:09 by nnamor            #+#    #+#             */
/*   Updated: 2022/01/30 21:16:27 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_H_
#define TYPE_TRAITS_H_

namespace ft
{

/// integral_constant
template < class T, T v >
struct integral_constant
{
    static const T value = v;
    typedef T value_type;
    typedef integral_constant<T,v> type;
    operator value_type() const { return value; }
};

typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

/// Constant-volatile specifiers
template <typename T>
struct remove_const
    { typedef T type; };

template <typename T>
struct remove_const<const T>
    { typedef T type; };

template <typename T>
struct remove_volatile
    { typedef T type; };

template <typename T>
struct remove_volatile<volatile T>
    { typedef T type; };

template <typename T>
struct remove_cv
{ typedef typename
    remove_const<typename remove_volatile<T>::type>::type type; };

/// is_integral
template <typename T_>
struct is_integral_helper_ : public false_type {};

template <> struct is_integral_helper_<bool> : public true_type {};
template <> struct is_integral_helper_<char> : public true_type {};
//template <> struct is_integral_helper_<char16_t> : public true_type {};   // C++11
//template <> struct is_integral_helper_<char32_t> : public true_type {};   // C++11
template <> struct is_integral_helper_<wchar_t> : public true_type {};
template <> struct is_integral_helper_<short> : public true_type {};
template <> struct is_integral_helper_<int> : public true_type {};
template <> struct is_integral_helper_<long> : public true_type {};
template <> struct is_integral_helper_<long long> : public true_type {};

template <> struct is_integral_helper_<unsigned char> : public true_type {};
template <> struct is_integral_helper_<unsigned short> : public true_type {};
template <> struct is_integral_helper_<unsigned int> : public true_type {};
template <> struct is_integral_helper_<unsigned long> : public true_type {};
template <> struct is_integral_helper_<unsigned long long> : public true_type {};

template <class T>
struct is_integral
    : public integral_constant<bool, is_integral_helper_<typename
        remove_cv<T>::type>::value>
{};

/// enable_if
template <bool B, class T = void>
struct enable_if {};

template <class T>
struct enable_if<true, T>
{
    typedef T type;
};

/// is_iterator
template <class T_>
struct has_iterator_category_
{
private:
    struct twoBytes_ { char b1_; char b2_; };
    template <class U_> static twoBytes_ test_(...);
    template <class U_> static char test_(typename U_::iterator_category* = NULL);
public:
    static const bool value = sizeof(test_<T_>(0)) == 1;
};

template <class T>
struct is_iterator
    : public integral_constant<bool, has_iterator_category_<T>::value> {};

template <class T>
struct is_iterator<T*> : public true_type {};

}

#endif /*TYPE_TRAITS_H_*/
