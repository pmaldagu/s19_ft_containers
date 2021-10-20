/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 13:51:48 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/10/20 16:09:43 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft
{
	/*Lexicographical compare*/
	template<class InputIt1, class InputIt2>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                             InputIt2 first2, InputIt2 last2)
	{
    	for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 )
		{
        	if (*first1 < *first2) return true;
        	if (*first2 < *first1) return false;
    	}
    	return (first1 == last1) && (first2 != last2);
	};
	template<class InputIt1, class InputIt2, class Compare>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                             InputIt2 first2, InputIt2 last2,
                             Compare comp)
	{
    	for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) 
		{
        	if (comp(*first1, *first2)) return true;
        	if (comp(*first2, *first1)) return false;
    	}
    	return (first1 == last1) && (first2 != last2);
	}

	/*Enable if*/
	template<bool B, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> { typedef T type; };
}
