/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:36:17 by allanganoun       #+#    #+#             */
/*   Updated: 2022/03/19 00:19:40 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>
# include <memory>
# include <algorithm>
# include "tree_iterator.hpp"

namespace ft
{
	template <class Value, class Key, class Compare = std::less<Key>, class Value_alloc = std::allocator<Value>
				, class Node = ft::_node<Value>, class Node_alloc = std::allocator<Node> >
	class tree
	{
	public :
		typedef Value							data_type;
		typedef Node_alloc						node_alloc;
		typedef Node							node_type;
		typedef Node *							node_pointer;
		typedef ft::tree_iterator<node_type>	iterator;

		tree(const node_alloc &alloc = node_alloc(), const Compare &comp = Compare() )
		: _node_alloc(alloc), _end(NULL), _start(NULL), _root(NULL), _comp(comp)
		{

		}

		~tree()
		{

		}

		pair<iterator,bool> insert(const data_type& val) // iterateur sur la valeur insérée + True pour dire valeur ajoutée ou false pour déjà éxistante
		{
			node_pointer new_node;
			node_pointer current;
			node_pointer tmp;

			new_node = _node_alloc.allocate(1);
			if (_root == NULL)
			{
				_node_alloc.construct(new_node, Node(val));
				_root = new_node;
				_start = new_node;
				return (make_pair(iterator(_root), true));
				
			}
			current = _node_min(_root);
			std::cout << "OK1" << std::endl;
			while (_comp(current->data.first, val.first))
			{

				tmp = _node_next(current);
				if (tmp != NULL)
					current = tmp;
				else
					break;
			}

			while (!_node_has_leaf(current))
			{

				current = _node_prev(current);
			}
			//current = _node_prev(current);
			std::cout << current->data.first << std::endl;
			if (this->_comp(current->data.first, val.first))
			{
				_node_alloc.construct(new_node, Node(val));

				current->right = new_node;
				new_node->parent = current;
			}
			else
			{
				_node_alloc.construct(new_node, Node(val));

				current->left = new_node;
				new_node->parent = current;
			}
			current = current->right;
			std::cout << current->data.first << std::endl;
			return make_pair(iterator(new_node), true);
				
		}

		iterator begin() 
		{
			if (_root)
				// return iterator(_node_min(_root));
				return iterator(_start);
			return iterator(_end);
		}

		iterator end() 
		{
			return iterator(_end);
		}

		iterator find(const Key& k)
		{
			Node node = _start;
			while (node != NULL)
			{
				value_type pair = node->data;
				if (pair.getKey() == k)
					return it;
			}
			return _tree._end;
		}

	private :
		node_pointer _end;
		node_pointer _start;
		node_pointer _root;
		node_alloc	_node_alloc;
		Compare		_comp;
	};
}
