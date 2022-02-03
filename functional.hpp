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

template <class T>
struct less
{
    bool operator()(const T& lhs, const T& rhs)
    {
        return lhs < rhs;
    }
};

}

#endif /*FUNCTIONAL_H_*/
