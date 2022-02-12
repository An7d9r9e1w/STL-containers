/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functional.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 18:46:21 by nnamor            #+#    #+#             */
/*   Updated: 2022/01/31 19:07:15 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONAL_H_
#define FUNCTIONAL_H_

namespace ft
{

template <typename _Arg, typename _Result>
struct unary_function
{
    typedef _Arg    argument_type;
    typedef _Result result_type;
};

template <typename _Arg1, typename _Arg2, typename _Result>
struct binary_function
{
    typedef _Arg1   first_argument_type;
    typedef _Arg2   second_argument_type;
    typedef _Result result_type;
};

template <typename _Tp>
struct _Identity : public unary_function<_Tp, _Tp>
{
    _Tp&
    operator()(_Tp& x)
    {
        return x;
    }

    const _Tp&
    operator()(const _Tp& x) const
    {
        return x;
    }
};

template <typename _Tp>
struct _Identity<const _Tp> : _Identity<_Tp> { };

template <typename _Pair>
struct _Select1st : public unary_function<_Pair, typename _Pair::first_type>
{
    typename _Pair::first_type&
    operator()(_Pair& x)
    {
        return x.first;
    }

    const typename _Pair::first_type&
    operator()(const _Pair& x) const
    {
        return x.first;
    }
};

template <class _Tp>
struct less : public binary_function<_Tp, _Tp, bool>
{
    bool
    operator()(const _Tp& lhs,
               const _Tp& rhs) const
    {
        return lhs < rhs;
    }
};

}

#endif /*FUNCTIONAL_H_*/
