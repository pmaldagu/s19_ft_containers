/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 10:39:06 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/10/01 11:47:24 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//https://towardsdatascience.com/data-structures-in-c-part-1-b64613b0138d
//https://www.geeksforgeeks.org/namespace-in-c/
//https://stackoverflow.com/questions/39844582/c-member-types
//https://www.cplusplus.com/reference/stack/stack/
//https://en.cppreference.com/w/cpp/container/stack

#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include <deque>

namespace ft
{
	template < typename T, typename Container = std::deque<T> >//////a changer pour ft::vector
	class stack
	{

		/*Friendzone (cause lexicographical_compare, non-local)*/
		friend bool operator==( const stack & lhs, const stack & rhs)
		{
			return (lhs.c == rhs.c);
		}
		friend bool operator!=( const stack & lhs, const stack & rhs)
		{
			return (lhs.c != rhs.c);
		}
		friend bool operator<( const stack & lhs, const stack & rhs)
		{
			return (lhs.c < rhs.c);
		}
		friend bool operator<=( const stack & lhs, const stack & rhs)
		{
			return (lhs.c <= rhs.c);
		}
		friend bool operator>( const stack & lhs, const stack & rhs)
		{
			return (lhs.c > rhs.c);
		}
		friend bool operator>=( const stack & lhs, const stack & rhs)
		{
			return (lhs.c >= rhs.c);
		}

		public:
			/*Constructor and Destructor*/
			explicit stack( const Container & cont = Container() );
			stack ( const stack & other );
			virtual~stack();

			/*Member types*/
			typedef typename Container::value_type value_type;
			typedef Container container_type;
			typedef typename Container::size_type size_type;

			/*Member functions*/
			stack & operator=( const stack & other )
			{
				if (*this != &other)
				{
					this->c = other.c;
				}
				return *this;
			}
			bool empty( void ) const
			{
				return this->c.empty();
			}
			size_type size( void ) const
			{
				return this->c.size();
			}
			void push( const value_type& val )
			{
				this->c.push_back(val);
			}
			void pop( void )
			{
				this->c.pop_back();
			}
			value_type & top( void )
			{
				return this->c.back();
			}
			const value_type & top( void ) const
			{
				return this->c.back();
			}

		protected:
			Container c;

	};/*end of Class*/

	/*Constructor and Destructor*/
	template < typename T, typename Container >
	stack<T, Container>::stack( const container_type& cont ) :
	c( cont )
	{
		std::cout << "stack parametric constructor called" << std::endl;
	}

	template < typename T, typename Container >
	stack<T, Container>::~stack( void )
	{
		std::cout << "stack destructor called" << std::endl;
	}

}/*end of the namespace*/

#endif
