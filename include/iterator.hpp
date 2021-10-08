/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 12:26:02 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/10/08 16:54:00 by pmaldagu         ###   ########.fr       */
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
	struct iterator 
	{
		/*Member types*/
    	typedef T value_type;
    	typedef Distance difference_type;
    	typedef Pointer pointer;
    	typedef Reference reference;
    	typedef Category iterator_category;
  	};

	/*Define properties of iterators*/
	template <class Iterator> 
	struct iterator_traits
	{
		/*Member types*/
		typedef Iterator::value_type value_type;
    	typedef Iterator::difference_type difference_type;
    	typedef Iterator::pointer pointer;
    	typedef Iterator::reference reference;
    	typedef Iterator::iterator_category  iterator_category;
	};
	/*T* specialization*/ 
	template <class T> 
	struct iterator_traits<T*>
	{
		/*Member types*/
		typedef T value_type;
    	typedef ptrdiff_t difference_type;
    	typedef T* pointer;
    	typedef T& reference;
    	typedef ft::random_access_iterator_tag iterator_category;
	};
	/*const T* specialization*/
	template <class T> 
	struct iterator_traits<const T*>
	{
		/*Member types*/
		typedef T value_type;
    	typedef ptrdiff_t difference_type;
    	typedef const T* pointer;
    	typedef const T& reference;
    	typedef ft::random_access_iterator_tag iterator_category;
	};

	class vec_iter :

	/*Reverse iterator*/
	template <class Iterator> 
	class reverse_iterator
	{
		public:
			/*Constructor and destructor*/
			reverse_iterator() : current( Iterator() ) {}
			explicit reverse_iterator (iterator_type it) : current( it ) {}
			template <class Iter>
  			reverse_iterator (const reverse_iterator<Iter>& rev_it) : current( rev_it.current ) {}

			/*Member types*/
			typedef Iterator iterator_type;
    		typedef iterator_traits<Iterator>::iterator_category iterator_category;
    		typedef iterator_traits<Iterator>::value_type value_type;
    		typedef iterator_traits<Iterator>::difference_type difference_type;
    		typedef iterator_traits<Iterator>::pointer pointer;
    		typedef iterator_traits<Iterator>::reference reference;

			/*Member functions*/
			template< class U >
			reverse_iterator& operator=( const reverse_iterator<U>& other ) { this->current = other.current; }
			iterator_type base() const { return this->current; }
			reference operator*() const { Iterator tmp = this->current; return *--tmp; }
			reverse_iterator operator+(difference_type n) const { return reverse_iterator(base()-n); }
			reverse_iterator& operator++() { current--; return *this } 
			reverse_iterator operator++(int) { reverse_iterator tmp(*this); this->current--; return tmp; }
			reverse_iterator& operator+= (difference_type n) { current -= n; return *this }
			reverse_iterator operator-(difference_type n) const { return reverse_iterator(base()+n); }
			reverse_iterator& operator--() { current++; return *this }
			reverse_iterator  operator--(int) { reverse_iterator tmp(*this); this->current++; return tmp; }
			reverse_iterator& operator-=(difference_type n) { current += n; return *this }
			pointer operator->() const { return this->current - 1; }
			reference operator[](difference_type n) const { return this->current[-n]; }

		protected:
			iterator_type current;
	};
	template< class T >
	class vec_iterator
	{
		public:
		/*TODO*/
	};

	/*Non_member reverse_iterator functions*/
	template <class Iterator>
  	bool operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);
	{
		return lhs.base() == rhs.base();
	}
	template <class Iterator>
  	bool operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);
	{
		return lhs.base() != rhs.base();
	}
	template <class Iterator>
  	bool operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);
	{
		return lhs.base() > rhs.base();
	}
	template <class Iterator>
	bool operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);
	{
		return lhs.base() >= rhs.base();
	}
	template <class Iterator>
	bool operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);
	{
		return lhs.base() < rhs.base();
	}
	template <class Iterator>
	bool operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);
	{
		return lhs.base() <= rhs.base();
	}
	template <class Iterator>
  	reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n,
             const reverse_iterator<Iterator>& rev_it);
	{
		return reverse_iterator<Iterator>(it.base() - n);
	}
	template <class Iterator>
  	typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs);
	{
		return rhs.base() - lhs.base();
	}

}
