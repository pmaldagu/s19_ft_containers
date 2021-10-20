/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 12:26:02 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/10/20 16:46:32 by pmaldagu         ###   ########.fr       */
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
	struct forward_iterator_tag {} : public input_iterator_tag { };
	struct bidirectional_iterator_tag {} : public forward_iterator_tag { };
	struct random_access_iterator_tag {} public bidirectional_iterator_tag { };

	/*Base class*/
	template <class Category, class T, class Distance = ptrdiff_t,
          class Pointer = T*, class Reference = T&>
	struct iterator 
	{
		/*Member types*/
    	typedef T								value_type;
    	typedef Distance						difference_type;
    	typedef Pointer							pointer;
    	typedef Reference						reference;
    	typedef Category						iterator_category;
  	};

	/*Define properties of iterators*/
	template <class Iterator> 
	struct iterator_traits
	{
		/*Member types*/
		typedef Iterator::value_type			value_type;
    	typedef Iterator::difference_type		difference_type;
    	typedef Iterator::pointer				pointer;
    	typedef Iterator::reference				reference;
    	typedef Iterator::iterator_category		iterator_category;
	};
	/*T* specialization*/ 
	template <class T> 
	struct iterator_traits<T*>
	{
		/*Member types*/
		typedef T								value_type;
    	typedef ptrdiff_t						difference_type;
    	typedef T*								pointer;
    	typedef T&								reference;
    	typedef ft::random_access_iterator_tag	iterator_category;
	};
	/*const T* specialization*/
	template <class T> 
	struct iterator_traits<const T*>
	{
		/*Member types*/
		typedef T								value_type;
    	typedef ptrdiff_t						difference_type;
    	typedef const T*						pointer;
    	typedef const T&						reference;
    	typedef ft::random_access_iterator_tag	iterator_category;
	};

	/*Reverse iterator*/
	template <class Iterator> 
	class reverse_iterator
	{
		public:			
			/*Member types*/
			typedef Iterator iterator_type;
    		typedef iterator_traits<Iterator>::iterator_category	iterator_category;
    		typedef iterator_traits<Iterator>::value_type			value_type;
    		typedef iterator_traits<Iterator>::difference_type		difference_type;
    		typedef iterator_traits<Iterator>::pointer				pointer;
    		typedef iterator_traits<Iterator>::reference			reference;

			/*Constructor and destructor*/
			reverse_iterator() : current( Iterator() ) {}
			explicit reverse_iterator (iterator_type it) : current( it ) {}
			template <class Iter>
  			reverse_iterator (const reverse_iterator<Iter>& rev_it) : current( rev_it.current ) {}

			/*Member functions*/
			template< class U >
			reverse_iterator& operator=( const reverse_iterator<U>& other ) { this->current = other.current; return *this }
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
			pointer operator->() const { return &(operator*()); }
			reference operator[](difference_type n) const { return this->current[-n]; }

		protected:
			iterator_type current;
	};
	template< class T >
	class vec_it
	{
		public:
			/*Member types*/
			typedef vec_it									iterator_type;
    		typedef iterator_traits<T*>::iterator_category	iterator_category;
    		typedef iterator_traits<T*>::value_type			value_type;
    		typedef iterator_traits<T*>::difference_type	difference_type;
    		typedef iterator_traits<T*>::pointer			pointer;
    		typedef iterator_traits<T*>::reference			reference;

			/*Constructor and destructor*/
			vec_it(pointer ptr = nullptr) : _ptr( ptr ) {}
			vec_it( const vec_it<T>& other) : _ptr( other._ptr ) {}
			~vec_it() {}

			/*Member functions*/
			vec_it& operator=( const vec_it<T>& other ) { this->_ptr = other._ptr; return *this }
			reference operator*() const { return (*this->_ptr); }
            pointer operator->() const { return (this->_ptr);
            vec_it& operator++() { this->_ptr++; return (*this); }
            vec_it operator++(int) { It tmp = *this; ++(*this); return (tmp); }
            vec_it& operator+=(difference_type n) { this->_ptr += n; return (*this); }
            vec_it operator+(difference_type n) const { It tmp = *this; return (tmp += n); }
            vec_it& operator-=(difference_type n) { this->_ptr -= n; return (*this); }
            vec_it operator-(difference_type n) const { It tmp = *this; return (tmp -= n); }
            vec_it& operator--() { this->_ptr--; return (*this); }
            vec_it  operator--(int) { It tmp = *this; --(*this); return (tmp); }
            reference operator[](difference_type n) const { return *(this->_ptr + n); }
			
			/*Getter*/
			pointer getPtr() const { return (this->_ptr); } ///pourri mais ca passe

		private:
			pointer _ptr;

	};
	/*Non_member vector_iterator functions*/
	template < class T >
    bool operator==(const ft::vec_it<T>& lhs, const ft::vec_it<T> rhs) { return (lhs.getPtr() == rhs.getPtr()); }
    template < class T >
    bool operator!=(const ft::vec_it<T>& lhs, const ft::vec_it<T> rhs) { return (lhs.getPtr() != rhs.getPtr()); }
    template < class T >
    bool operator<(const ft::vec_itt<T>& lhs, const ft::vec_itt<T> rhs) { return (lhs.getPtr() < rhs.getPtr()); }
    template < class T >
    bool operator<=(const ft::vec_it<T>& lhs, const ft::vec_it<T> rhs) { return (lhs.getPtr() <= rhs.getPtr()); }
    template < class T >
    bool operator>(const ft::vec_it<T>& lhs, const ft::vec_it<T> rhs) { return (lhs.getPtr() > rhs.getPtr()); }
    template < class T >
    bool operator>=(const ft::vec_it<T>& lhs, const ft::vec_it<T> rhs) { return (lhs.getPtr() >= rhs.getPtr()); }

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
