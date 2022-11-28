/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 10:29:24 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/12/04 16:24:30 by pmaldagu         ###   ########.fr       */
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
#include "utils/iterator.hpp"
#include "utils/utils.hpp"

namespace ft
{
	template < typename T, typename Allocator = std::allocator<T> >
	class vector
	{
		public:
			/*Member types*/
			typedef T											value_type;
			typedef Allocator									allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef ft::It<value_type>							iterator;
			typedef ft::It<const value_type>					const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<iterator>				const_reverse_iterator;
			typedef ptrdiff_t									difference_type;
			typedef size_t										size_type;

			/* Constructors & Destructor */
            explicit vector(const allocator_type& alloc = allocator_type()): _size(0), _cap(0), _base(alloc)
            {
                this->_ptr = this->_base.allocate(0);
            }
            explicit vector(size_type n, const value_type& val = value_type(), 
				const allocator_type& alloc = allocator_type()): _size(n), _cap(n), _base(alloc)
            {
                this->_ptr = this->_base.allocate(n);
                for (size_t i = 0; i < n; i++)
                    this->_base.construct(this->_ptr + i, val);
            }
            template <class InputIterator>
            vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), 
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr): 
				_size(0), _cap(0), _base(alloc)
            {
                for (; first < last; first++)
                    this->_size++;
                this->_cap = this->_size;
                first -= _size;
                this->_ptr = this->_base.allocate(this->_size);
                for (size_t a = 0; a < this->_size; a++)
                    this->_base.construct(_ptr + a, *(first + a));
            }

            vector(const vector& x): _size(x._size), _cap(x._cap), _base(x._base)
            {
                this->_ptr = this->_base.allocate(0);
                *this = x;
            }

			/* Member function */
            vector& operator=(const vector& x)
            {
                if (this != &x)
                {
                    this->clear();
                    this->_base.deallocate(this->_ptr, this->_cap);
                    this->_ptr = this->_base.allocate(x._cap);
                    for (size_t i = 0; i < x._size; i++)
                        this->_base.construct(this->_ptr + i, *(x._ptr + i));
                    this->_size = x._size;
                    this->_cap = x._cap;
                }
                return (*this);
            }
            virtual ~vector()
            {
                this->clear();
                this->_base.deallocate(this->_ptr, this->_cap);
            }

            /* Iterators */
            iterator begin() { return (iterator(this->_ptr)); }
            const_iterator begin() const { return (const_iterator(this->_ptr)); }
            iterator end() { return (iterator(this->_ptr + this->_size)); }
            const_iterator end() const { return (const_iterator(this->_ptr + this->_size)); }
            reverse_iterator rbegin() { return (reverse_iterator(this->_ptr + this->_size)); }
            const_reverse_iterator rbegin() const { return (const_reverse_iterator(this->_ptr + this->_size)); }
            reverse_iterator rend() { return (reverse_iterator(this->_ptr)); }
            const_reverse_iterator rend() const { return (const_reverse_iterator(this->_ptr)); }

			/* Capacity */
            size_type size() const { return (this->_size); } 
            size_type max_size() const { return (this->_base.max_size()); }
            void resize(size_type n, value_type val = value_type())
            {
                if (n < this->_size)
                {
                    for (size_t i = n; i < this->_size; i++)
                        this->_base.destroy(this->_ptr + i);
                }
                else if (n > this->_size && n <= this->_cap)
                {
                    for (size_t i = this->_size; i < n; i++)
                        this->_base.construct(this->_ptr + i, val);
                }
                else if (n > this->_size && n > this->_cap)
                {
                    if (n < this->_cap * 2)
                        reserve(this->_cap * 2);
                    else
                        reserve(n);
                    for (size_t i = this->_size; i < n; i++)
                        this->_base.construct(this->_ptr + i, val);
                }
                this->_size = n;
            }
            size_type capacity() const { return (this->_cap); }
            bool empty() const
            {
                if (this->_size == 0)
                    return (true);
                return (false);
            }
            void reserve(size_type n)
            {
                if (n > this->_cap)
                {
                    vector copy;

                    copy = *this;
                    this->clear();
                    this->_base.deallocate(this->_ptr, this->_cap);
                    this->_ptr = this->_base.allocate(n);
                    for (size_t i = 0; i < copy._size; i++)
                        this->_base.construct(this->_ptr + i, *(copy._ptr + i));
                    this->_size = copy._size;
                    this->_cap = n;
                }
            }

            /* Element access */
            reference operator[](size_type n) { return (at(n)); }
            const_reference operator[](size_type n) const { return (at(n)); } 
            reference at(size_type n)
            {
                if (n >= this->_size)
                    throw std::out_of_range("Vector"); 
                return (*(this->_ptr + n));
            }
            const_reference at(size_type n) const
            {
                if (n >= this->_size)
                    throw std::out_of_range("Vector"); 
                return *(this->_ptr + n);
            }
            reference front() { return (*this->_ptr); }
            const_reference front() const { return (*this->_ptr); }
            reference back() { return *(this->_ptr + this->_size - 1); }
            const_reference back() const { return *(this->_ptr + this->_size - 1); }

            /* Modifiers */
            template <class InputIterator>
            void assign(InputIterator first, InputIterator last, 
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr)
            {
                clear();
                insert(begin(), first, last);
                this->_cap = _size;
            }
            void assign(size_type n, const value_type& val)
            {
                clear();
                for (size_t a = 0; a < n; a++)
                    push_back(val);
            }
            void push_back(const value_type& val) { resize(this->_size + 1, val); }
            void pop_back() { resize(this->_size - 1, value_type()); }
            iterator insert(iterator position, const value_type& val)
            {
                iterator it;
                size_t a = 0;
                size_t i = 0;

                for (it = this->begin(); it < position; it++)
                    a++;
                this->reserve(this->_size + 1);
                this->_size += 1;
                i = this->_size - 1;
                while (i > a)
                {
                    this->_ptr[i] = this->_ptr[i - 1];
                    i--;
                }
                this->_ptr[a] = val;
                return (begin() + a);
            }
            void insert(iterator position, size_type n, const value_type& val)
            {
                iterator it = position;
                for (size_t a = 0; a < n; a++)
                {
                    it = insert(it, val);
                    it++;
                }
            }
            template <class InputIterator>
            void insert(iterator position, InputIterator first, InputIterator last, 
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr)
            {
                iterator    it = position;
                vector      tmp(first, last);
                iterator    begin = tmp.begin();
                iterator    end = tmp.end();
                
                for (; begin < end; begin++)
                {

                    it = insert(it, *begin);
                    it++;
                }
            }
            iterator erase(iterator position)
            {
                iterator it;
                size_t i = 0;

                this->_size--;
                for (it = this->begin(); it < position; it++)
                    i++;
                for (; i < this->_size; i++)
                    this->_ptr[i] = this->_ptr[i + 1];
                if (position == this->end() + 1)
                    return (this->end());
                return (position);
            }
            iterator erase(iterator first, iterator last)
            {
                iterator it;
                size_t i = 0;
                size_t j = 0;

				i = first - begin();
                j = last - first;
                this->_size -= j;
                for (; i < this->_size; i++)
                    this->_ptr[i] = this->_ptr[i + j];
                return (last - j);
            }
            void swap(vector& x)
            {
                pointer tmp;
                size_t  tmp2;
                size_t  tmp3;

                tmp = this->_ptr;
                tmp2 = this->_size;
                tmp3 = this->_cap;
                this->_ptr = x._ptr;
                this->_size = x._size;
                this->_cap = x._cap;
                x._ptr = tmp;
                x._size = tmp2;
                x._cap = tmp3;
            }
            void clear()
            {
                for (size_t i = 0; i < this->_size; i++)
                    this->_base.destroy(&this->_ptr[i]);
                this->_size = 0;
            }

            /* Allocator */
            allocator_type get_allocator() const { return (this->_base); }

        private:
            size_type		_size;
            size_type		_cap;
            allocator_type	_base;
            pointer			_ptr;
    };/* End of Class */

    /* Non-member functions */
    template <class T, class Alloc>
    bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) 
	{ 
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin())); 
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
