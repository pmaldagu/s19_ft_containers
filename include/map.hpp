/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 13:43:00 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/11/02 14:44:17 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MAP_HPP
# define MAP_HPP

#include <iostream>
#include <limits>

namespace ft
{
	/*map*/
    template < class Key, class T, class Compare = std::less<Key>, class Alloc = allocator<pair<const Key,T>>
    class map
    {
		/*Attributes*/
        private:
            Alloc   _base;
            T*      _ptr;
            size_t  _size;
            size_t  _capacity;

        public:
			/*Member types*/
            typedef Key									key_type;
            typedef T									mapped_type;
            typedef typename ft::pair<const Key, T>		value_type;
            typedef size_t								size_type;
            typedef ptrdiff_t							difference_type;
            typedef Compare								key_compare;
            typedef Allocator							allocator_type;
            typedef value_type&							reference;
            typedef const value_type&					const_reference;
            typedef Allocator::pointer					pointer;
            typedef Allocator::const_pointer			const_pointer;
            // typedef iterator	LegacyBidirectionalIterator to value_type;
            // typedef const_iterator	LegacyBidirectionalIterator to const value_type;
            // typedef ft::reverse_iterator<iterator> reverse_iterator;
            // typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
			
			/*Constructor and destructor*/
            // explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
            // template <class InputIterator>
            // map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), 
			//		const allocator_type& alloc = allocator_type());
            // map (const map& x);
            // ~map() 
			
           	/*Nested class*/
			class value_compare : 
			{
				protected:
  					Compare comp;
  					value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object

				public:
					/*Member typed*/
  					typedef bool result_type;
  					typedef value_type first_argument_type;
  					typedef value_type second_argument_type;

					/*Member function*/
  					bool operator() (const value_type& x, const value_type& y) const
  					{
    					return comp(x.first, y.first);
  					}
			}

			/*Member functions*/
            // map& operator= (const map& x);
            allocator_type get_allocator() const { return (this->_base); }

            /*Iterator*/
            // iterator begin();
            // const_iterator begin() const;           
            // iterator end();
            // const_iterator end() const;
            // reverse_iterator rbegin();
            // const_reverse_iterator rbegin() const;
            // reverse_iterator rend();
            // const_reverse_iterator rend() const;

            /*Capacity*/
            bool empty() const 
            {
                if (this->_size == 0)
					return (true);
				return (false);
            }
            size_type size() const { return (this->_size); }
            size_type max_size() const { return (this->_capacity); }
            
            /*Modifiers*/
            //void clear()
			// std::pair<iterator, bool> insert( const value_type& value );
            // iterator insert( iterator hint, const value_type& value );
            // void erase( iterator pos );
            // void erase( iterator first, iterator last );
            void swap( map& other )
            {
                pointer tmp;
                size_t  tmp2;
                size_t  tmp3;

                tmp = this->_ptr;
                tmp2 = this->_size;
                tmp3 = this->capacity;
                this->_ptr = other._ptr;
                this->_size = other._size;
                this->capacity = other.capacity;
                other._ptr = tmp;
                other._size = tmp2;
                other._capacity = tmp3;
            }

            /*Lookup*/
            // size_type count( const Key& key ) const
            // {
            //     for (size_t i = 0; i < this->_size; i++)
            // }
            // iterator find( const Key& key );
            // const_iterator find( const Key& key ) const;
            // std::pair<iterator,iterator> equal_range( const Key& key );
            // std::pair<const_iterator,const_iterator> equal_range( const Key& key ) const;
            // iterator lower_bound( const Key& key );
            // const_iterator lower_bound( const Key& key ) const;
            // iterator upper_bound( const Key& key );
            // const_iterator upper_bound( const Key& key ) const;

            /*Observers*/
            // key_compare key_comp() const;
            // std::map::value_compare value_comp() const;

    };

    /*Non-member function*/
    // template< class Key, class T, class Compare, class Alloc >
    // bool operator==( const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs );
    // template< class Key, class T, class Compare, class Alloc >
    // bool operator!=( const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs );
    // template< class Key, class T, class Compare, class Alloc >
    // bool operator<( const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs );
    // template< class Key, class T, class Compare, class Alloc >
    // bool operator<=( const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs );
    // template< class Key, class T, class Compare, class Alloc >
    // bool operator>( const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs );
    // template< class Key, class T, class Compare, class Alloc >
    // bool operator>=( const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs );

}

