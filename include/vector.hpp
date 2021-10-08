/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 10:29:24 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/10/08 16:57:52 by pmaldagu         ###   ########.fr       */
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
			typedef T value_type;
			typedef Allocator allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			//typedef It<value_type> iterator;
			//typedef It<const value_type> const_iterator;
			//typedef ft::reverse_iterator<iterator> reverse_iterator;
			//typedef ft::reverse_iterator<iterator> const_reverse_iterator;
			typedef ptrdiff_t difference_type;
			typedef size_t size_type;
		
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
			/*TODO
			template <class InputIterator>
         	vector (InputIterator first, InputIterator last,
                 const allocator_type& alloc = allocator_type());
			{
				first::pointer begin;
				last::pointer end;
			}
			*/
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
				//if (*this != &x)
				//{
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
				//}
				return *this;
			}

			/*Iterators*/
			/*
			iterator begin( void );
			const_iterator begin( void ) const;
			iterator end( void );
			const_iterator end( void ) const;
			reverse_iterator rbegin( void );
			const_reverse_iterator rbegin( void ) const;
			reverse_iterator rend( void );
			const_reverse_iterator rend( void ) const;
			*/

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
					throw std::out_of_range;
				else
					return *(this->_ptr + n);
			}
			reference front( void ) { return *(this->_ptr); }
			const_reference front( size_type n ) const { return *(this->_ptr); }
			reference back( void ) { return *(this->_ptr + this->_size - 1); }
			const_reference back( size_type n ) const { return *(this->_ptr + this->_size - 1); }

			/*Modifiers*/
			/*TODO*/
			//template <class InputIterator>
  			//void assign( InputIterator first, InputIterator last);
			//void assign( size_type n, const value_type & val );
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

			//iterator insert( iterator position, const value_type & val );
			//void insert( iterator position, size_type n, const value_type & val );
			//template <class InputIterator>
    		//void insert( iterator position, InputIterator first, InputIterator last );
			//iterator erase( iterator position );
			//iterator erase( iterator first, iterator last );
			//void swap( vector & x );
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

	};/*End of class*/

}/*End of namespaces*/

#endif
