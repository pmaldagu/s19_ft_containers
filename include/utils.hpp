/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 13:51:48 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/10/29 16:11:46 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

//https://www.it-swarm-fr.com/fr/c%2B%2B/c-11-specialisation-de-fonction-de-modele-pour-les-types-entiers/1067771861/
//https://stackoverflow.com/questions/43571962/how-is-stdis-integral-implemented
//https://stackoverflow.com/questions/58694521/what-is-stdfalse-type-or-stdtrue-type

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

	/*Is_integral*/
	struct integral_constant
    {
        static const T value = v;   // true or false vu qu'on passe un bool
        typedef T value_type;
        typedef integral_constant<T, v> type;
        operator T() { return v; }
    };

    template <class T>
    struct is_integral : public ft::integral_constant<bool, false> {};
    template<> struct is_integral<bool> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<char> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<char16_t> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<char32_t> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<wchar_t> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<signed char> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<short int> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<int> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<long int> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<long long int> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<unsigned char> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<unsigned short int> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<unsigned int> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<unsigned long int> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<unsigned long long int> : public ft::integral_constant<bool, true> {};
    // const
    template<> struct is_integral<const bool> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<const char> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<const char16_t> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<const char32_t> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<const wchar_t> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<const signed char> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<const short int> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<const int> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<const long int> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<const long long int> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<const unsigned char> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<const unsigned short int> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<const unsigned int> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<const unsigned long int> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<const unsigned long long int> : public ft::integral_constant<bool, true> {};

	/*pair*/
    template <class T1, class T2>
    struct pair
    {
        typedef T1 first_type;
        typedef T2 second_type;

        T1 first;
        T2 second;
    };

	/*less*/
	template< class T >
	struct less
	{
		typedef bool	result_type;
		typedef T		first_argument_type;
		typedef T 		second_argument_type;

		bool operator()(const T &lhs, const T &rhs) const
		{
    		return lhs < rhs; // assumes that the implementation uses a flat address space
		}
	};	
}

#endif
