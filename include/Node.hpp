/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 10:39:06 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/09/21 11:09:13 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//https://towardsdatascience.com/data-structures-in-c-part-1-b64613b0138d
//https://www.geeksforgeeks.org/namespace-in-c/

#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>

namespace ft
{
	template < typename T >
	class Node
	{
		public:
			Node();
			Node( T value );
			Node ( Node const & src );
			virtual~Node();

			Node & operator=( Node const & rhs );

			void setNext( Node & src );
			void setPrevious( Node & src );

			Node & getNext( void ) const;
			Node & getPrevious( void ) const;

		private:
			T _value;
			Node *_next;
			Node *_previous;
	};

	template < typename T >
	Node::Node( void ) : 
	_value(),
	_next( nullptr ),
	_previous( nullptr ),
	{
		std::cout << "Node default constructor called" << std::endl;
	}

	template < typename T >
	Node::Node( T value ) : 
	_value( value ),
	_next( nullptr ),
	_previous( nullptr),
	{
		std::cout << "Node parametric constructor called" << std::endl;
	}
	
	template < typename T >
	Node::Node( Node const & rhs ) : 
	_value( rhs._value ),
	_next( rhs._next ),
	_previous( rhs._previous ),
	{
		std::cout << "Node copy  constructor called" << std::endl;
	}

	template< typename T >
	Node & Node::operator=( Node const & rhs )
	{
		std::cout << "Node assignation operator called" << std::endl;

		this->_value = rhs._value;
		this->_next = rhs._next;
		this->_previous = rhs._previous;

		return *this;
	}

	template< typename T >
	Node & Node::getNext( void ) const
	{
		return *this->_next;
	}
	
	template< typename T >
	Node & Node::getPrevious( void ) const
	{
		return *this->_previous;
	}

	template< typename T >
	void Node::setNext( Node & src )
	{
		this->_next = src;
	}

	template< typename T >
	void Node::setNext( Node & src )
	{
		this->_next = src;
	}
}

#endif
