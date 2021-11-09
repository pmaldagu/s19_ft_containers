/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 13:16:56 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/11/05 17:43:39 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BTREE_HPP
# define BTREE_HPP

# include "utils.hpp"
# include <memory>

namespace ft
{
    template < class T >
    struct Node
    {
        typedef T   value_type;

        value_type  data;
        Node*       parent;
        Node*       left;
        Node*       right;
        int         color;
    };

    template < class Key, class Value, class T = ft::pair< Key, Value >, class Compare = ft::less<T>, class Node = ft::Node<T>, class Node_Alloc = std::allocator<Node> >
    class BTree
    {
        public:
			typedef Key								key_type;
            typedef T                               value_type;
            typedef Node                            node_type;
            typedef Node*                           node_pointer;
            typedef Compare                         key_compare;
            typedef Node_Alloc                      node_alloc;
            typedef typename node_alloc::pointer    pointer;

            node_pointer insert(const value_type& val)
            {
				/*Insert*/
                node_pointer tmp = this->root;
                node_pointer parent = nullptr;

                while (tmp)
                {
                    parent = tmp;
                    if (val.first < tmp->data.first)
                        tmp = tmp->left;
                    else
                        tmp = tmp->right;
                }
                if (parent && (val.first == parent->data.first))
                    return (nullptr);
                pointer toInsert = node_alloc.allocate(1);
                toInsert->data.first = val.first;
                toInsert->data.second = val.second;
                toInsert->parent = parent;
                toInsert->left = nullptr;
                toInsert->right = nullptr;
                toInsert->color = 1;
                if (!this->root)
                {
					toInsert->color = 0;
                    this->root = toInsert;
                    return (toInsert);
                }
                else if (toInsert->data.first < parent->data.first)
                    parent->left = toInsert;
                else
                    parent->right = toInsert;
				
				/*Rebalance*/
				if (toInsert->parent->parent == nullptr)
					return (toInsert);
				while (toInsert->parent->color == 1)
				{
					if (toInsert->parent == toInsert->parent->parent->right)
					{
						tmp = toInsert->parent->parent->left;
						if (tmp->color == 1)
						{
							tmp->color = 0;
							toInsert->parent->color = 0;
							toInsert->parent->parent->color = 1;
							toInsert = toInsert->parent->parent;
						}
						else
						{

					}
					else
					{
					}
					if (toInsert == this->root)
						break;
				}


                return (toInsert);			

            }

            delete(const value_type& val)
            {
				/*Garreth est un gros con
                pointer tmp = this->root;
                pointer a = tmp;
                pointer b, c;
                while (tmp)
                {
                    if (tmp->data.first = val.first)
                        a = tmp;
                    if (tmp->data.first <= val.first)
                        tmp = tmp->right;
                    else
                        tmp = tmp->left;
                }
                if (a = tmp) //// pas trouve de key correspondante
                    return (nullptr);
				*/

            }

            node_pointer search(const key_type& key)
            {
                pointer tmp = this->root;

                while (tmp)
                {
                    if (tmp->data.first == key)
                        return (tmp);
                    else if (key < tmp->data.first)
                    {
                        tmp = tmp->left;
                    }
                    else
                    {
                        tmp = tmp->right;
                    }   
                }
                return (nullptr);
            }

//          fix()
//          {

//          }

        private:
            node_pointer root;
    };
}

#endif
