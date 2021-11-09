/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 10:29:24 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/11/05 16:14:03 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//https://towardsdatascience.com/data-structures-in-c-part-1-b64613b0138d
//https://docs.microsoft.com/en-us/cpp/standard-library/vector-class?view=msvc-160#:~:text=The%20C%2B%2B%20Standard%20Library%20vector,performance%20is%20at%20a%20premium.
//https://medium.com/@vgasparyan1995/what-is-an-allocator-c8df15a93ed
//https://stackoverflow.com/questions/57456285/c-use-typedef-with-legacyrandomaccessiterator
//https://en.cppreference.com/w/cpp/iterator/iterator

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <stdexcept>
#include <iostream>
#include "iterator.hpp"
#include "utils.hpp"

namespace ft
{
	template < typename T, typename Allocator = std::allocator<T> >
	class vector
	{
		/*Memspace*/
		private:
			Allocator _base;
			T* _ptr;
			size_t _size;
			size_t _cap; //capacity

		public:
			/*Member types*/
			typedef T											value_type;
			typedef Allocator									allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef ft::vec_it<value_type>						iterator;
			typedef ft::vec_it<const value_type>				const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<iterator>				const_reverse_iterator;
			typedef ptrdiff_t									difference_type;
			typedef size_t										size_type;
		
			/*Constructor and destructor*/
			explicit vector (const allocator_type& alloc = allocator_type()) : _base( alloc ), _size( 0), _cap ( 0 )
			{
				this->_ptr = this->_base.allocate(0);
			}
			explicit vector (size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type()) : _base( alloc ), _size( n ), _cap (n)
			{
				size_t i;

				i = 0;
				this->_ptr = this->_base.allocate(n);
				while( i < n )
				{
					this->_base.construct(this->_ptr + i, val);
					i++;
				}
			}
			template <class InputIterator>
            vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), 
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = nullptr) : 
						_base(alloc), _size(0), _maxSize(0) 
            {
                for (; first < last; first++)
                    this->_size++;
                this->_maxSize = this->_size;
                first -= _size;
                this->_ptr = this->_base.allocate(this->_size);
                for (size_t a = 0; a < this->_size; a++)
                    this->_base.construct(_ptr + a, *(first + a));
            }
			vector (const vector& x) : _base( x._base ), _size( x._size ), _cap( x ._cap ), _ptr( x._ptr ) {}
			virtual~vector( void )
			{
				this->clear();
				this->_base.deallocate(this->_ptr, this->_cap);
			}

			/*Member functions*/
			vector & operator=( const vector & x )
			{
				size_t i;

				i = 0;
				if (this != &x)
				{
					this->clear();
					this->_base.deallocate(this->_ptr, this->_cap);
					this->_ptr = this->_base.allocate(x._cap);
					while (i < x._size)
					{
						this->_base.construct(this->_ptr + i, *(x._ptr + i));
						i++;
					}
					this->_size = x._size;
					this->_cap = x._cap;
				}
				return *this;
			}

			/*Iterators*/
			iterator begin() { return (iterator(this->_ptr)); }
            const_iterator begin() const { return (const_iterator(this->_ptr)); }
            iterator end() { return (iterator(this->_ptr + this->_size)); }
            const_iterator end() const { return (const_iterator(this->_ptr + this->_size)); }
            reverse_iterator rbegin() { return (reverse_iterator(this->end())); }
            const_reverse_iterator rbegin() const { return (const_reverse_iterator(this->end())); }
            reverse_iterator rend() { return (reverse_iterator(this->begin())); }
            const_reverse_iterator rend() const { return (const_reverse_iterator(this->begin())); }
		
			/*Capacity*/
			size_t size( void ) const { return this->_size; }
			size_t max_size( void ) const { return this->_base.max_size(); }
			void resize( size_type n, value_type val = value_type() )
			{
				size_t i;

				if ( n > this->_size )
				{
					i = this->_size;
					this->reserve(n);
					while (i < n)
					{
						this->_base.construct(this->_ptr + i, val);
						i++;
					}
				}
				else
				{
					i = n;
					while ( i < this->_size)
					{
						this->_base.destroy(this->_ptr + i);
						i++;
					}
				}
				this->_size = n;
			}
			size_type capacity( void ) const
			{
				return this->_cap;
			}
			bool empty( void ) const
			{
				if (this->_size == 0)
					return true;
				return false;
			}
			void reserve( size_type n )
			{
				if ( n > this->_cap)
				{
					size_t i;
					vector cpy;

					i = 0;
				   	cpy = *this;
					this->clear();
					this->_base.deallocate(this->_ptr, this->_cap);
					this->_ptr = this->_base.allocate(n);
					while (i < cpy._size)
					{
						this->_base.construct(this->_ptr + i, *(cpy._ptr + i));
						i++;
					}
					this->_size = cpy._size;
					this->_cap = n;
				}
			}

			/*Element acces*/
			reference operator[]( size_type n ) { return this->at(n); }
			const_reference operator[](size_type n ) const { return this->at(n); }
			reference at( size_type n )
			{
				if ( n >= this->_size )
					throw std::out_of_range("vector");
				else
					return *(this->_ptr + n);
			}
			const_reference at( size_type n ) const
			{
				if ( n >= this->_size )
					throw std::out_of_range("vector");
				else
					return *(this->_ptr + n);
			}
			reference front( void ) { return *(this->_ptr); }
			const_reference front( void ) const { return *(this->_ptr); }
			reference back( void ) { return *(this->_ptr + this->_size - 1); }
			const_reference back( void ) const { return *(this->_ptr + this->_size - 1); }

			/*Modifiers*/
			template <class InputIterator>
            void assign(InputIterator first, InputIterator last, 
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = nullptr)
            {
                clear();
                insert(begin(), first, last);
                this->_maxSize = _size;
            }
			void assign( size_type n, const value_type & val )
			{
				size_t i;

				i = 0;
				this->clear()
				while (i < n)
				{
					this->_base.push_back(val)
					i++;
				}
			}
			void push_back( const value_type & val )
			{
				if (this->_size == this->_cap)
				{
					this->reserve(this->_size + 1);
				}
				this->_size++;
				this->_base.construct(this->_ptr + this->_size - 1, val);
			}
			void pop_back( void )
			{
				if (this->_size != 0)
				{
					this->_size--;
					this->_base.destroy(this->_ptr + this->_size);
				}
			}
			template <class InputIterator>
            void insert(iterator position, InputIterator first, InputIterator last, 
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = nullptr)
            {
                iterator it = position;

                for (; first < last; first++)
                {
                    it = insert(it, *first);
                    it++;
                }
            }
            iterator erase(iterator position)
            {
				/*
                iterator it;
                size_t a = 0;
                this->_size--;
                for (it = this->begin(); it < position; it++)
                    a++;
                for (; a < this->_size; a++)
                    this->_ptr[a] = this->_ptr[a + 1];
                if (position == this->end() + 1)
                    return (this->end());
                return (position);
				*/
                iterator it;
                vector tmp;
                size_t a = 0;
                size_t b = 0;

                if (position == this->end())
                    return (this->end());
                tmp = *this;
                tmp._size--;
                this->clear();
                for (it = tmp.begin(); it < position; it++)
                    a++;
                for (; b < tmp._size; b++)
                {
                    if (b != a)
                        this->_base.construct(this->_ptr + b, *(tmp._ptr + b));
                }
                this->_size = tmp._size;
                this->_maxSize = tmp._maxSize;
                return (position);
            }
			void swap(vector& x)
            {
                pointer tmp;
                size_t  tmp2;
                size_t  tmp3;

                tmp = this->_ptr;
                tmp2 = this->_size;
                tmp3 = this->_maxSize;
                this->_ptr = x._ptr;
                this->_size = x._size;
                this->_maxSize = x._maxSize;
                x._ptr = tmp;
                x._size = tmp2;
                x._maxSize = tmp3;
            }
			void clear( void )
			{				
				size_t i;
				
				i = 0;
				while (i < this->_size)
				{
					this->_base.destroy(this->_ptr + i);
					i++;
				}
				this->_size = 0;
			}

			/*Allocator*/
			allocator_type get_allocator( void ) const
			{
				return this->_base;
			}

	};
	/*Non-member functions*/
	template <class T, class Alloc>
    bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
		size_t i;
		size_t size;

		i = 0;
		size = lhs.size();
		if (size != rhs.size())
            return false;
		while (i < size)
		{
            if (lhs[i] != rhs[i])
                return false;
			i++;
        }
        return true;
    }
    template <class T, class Alloc>
    bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (!(lhs == rhs)); }
    template <class T, class Alloc>
    bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }
    template <class T, class Alloc>
    bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (!(rhs < lhs)); }
    template <class T, class Alloc>
    bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (rhs < lhs); }
    template <class T, class Alloc>
    bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (!(lhs < rhs)); }
    template <class T, class Alloc>
    void swap (vector<T, Alloc>& x, vector<T, Alloc>& y) { x.swap(y); }

}/*End of namespaces*/

#endif
