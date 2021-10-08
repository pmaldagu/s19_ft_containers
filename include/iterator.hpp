/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 12:26:02 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/09/30 13:44:09 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_HPP
#define ITER_HPP

//https://www.cplusplus.com/reference/iterator/iterator_traits/

namespace ft
{
	/*Category*/
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag {};
	struct bidirectional_iterator_tag {};
	struct random_access_iterator_tag {};

	/*Base class*/
	template <class Category, class T, class Distance = ptrdiff_t,
          class Pointer = T*, class Reference = T&>
	class iterator 
	{
		public:
			/*Member types*/
    		typedef T value_type;
    		typedef Distance difference_type;
    		typedef Pointer pointer;
    		typedef Reference reference;
    		typedef Category iterator_category;
  	};

	/*Define properties of iterators*/
	template <class Iterator> 
	class iterator_traits
	{
		public:
			/*Member types*/
			typedef Iterator::value_type value_type;
    		typedef Iterator::difference_type difference_type;
    		typedef Iterator::pointer pointer;
    		typedef Iterator::reference reference;
    		typedef Iterator::iterator_category  iterator_category;
	};
	/*T* specialization*/ 
	template <class T> 
	class iterator_traits<T*>
	{
		public:
			/*Member types*/
			typedef T value_type;
    		typedef ptrdiff_t difference_type;
    		typedef T* pointer;
    		typedef T& reference;
    		typedef ft::random_access_iterator_tag iterator_category;
	};
	/*const T* specialization*/
	template <class T> 
	class iterator_traits<const T*>
	{
		public:
			/*Member types*/
			typedef T value_type;
    		typedef ptrdiff_t difference_type;
    		typedef const T* pointer;
    		typedef const T& reference;
    		typedef ft::random_access_iterator_tag iterator_category;
	};

	/*Reverse iterator*/
	template <class Iterator> 
	class reverse_iterator
	{
		public:
			/*Constructor and destructor*/
			reverse_iterator();
			explicit reverse_iterator (iterator_type it) : current( it );
			template <class Iter>
  			reverse_iterator (const reverse_iterator<Iter>& rev_it) : current( rev_it.current );

			/*Member types*/
			typedef Iterator iterator_type;
    		typedef iterator_traits<Iterator>::iterator_category iterator_category;
    		typedef iterator_traits<Iterator>::value_type value_type;
    		typedef iterator_traits<Iterator>::difference_type difference_type;
    		typedef iterator_traits<Iterator>::pointer pointer;
    		typedef iterator_traits<Iterator>::reference reference;

			/*Member functions*/
			iterator_type base() const;
			{
				return this->current;
			}
			reference operator*() const;
			{
				return &this->current;
			}
			reverse_iterator operator+(difference_type n) const;
			reverse_iterator& operator++();
			reverse_iterator operator++(int);
			reverse_iterator& operator+= (difference_type n);
			reverse_iterator operator-(difference_type n) const;
			reverse_iterator& operator--();
			reverse_iterator  operator--(int);
			reverse_iterator& operator-=(difference_type n);
			pointer operator->() const;
			reference operator[](difference_type n) const;

		protected:
			iterator_type current;
	};

	/*Non_member overloads*/
	//[...]

}
