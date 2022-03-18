/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alganoun <alganoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:36:17 by allanganoun       #+#    #+#             */
/*   Updated: 2022/03/18 17:28:56 by alganoun         ###   ########.fr       */
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
		typedef node_type *						node_pointer;
		typedef ft::tree_iterator<data_type>	iterator;

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

			new_node = _node_alloc.allocate(1);
			if (_root == NULL)
			{
				_node_alloc.construct(new_node, Node(val));
				_root = new_node;
				_start = new_node;
				return (make_pair(iterator(_root), true));
			}
			iterator ite = this->begin();
			while (_comp((*ite).data.first, val.first))
				ite++;
			// ici il faut inserer le cas d'égalité.
			if (this->_comp((*(--ite)).data.first, val.first))
			{
				_node_alloc.construct(new_node, _node_insert<Node>(*new_node, &ite, LEFT)); // il faut revoir les pointeurs wet tout parce que rien ne va
				
			}
			else
			{
				new_node = _node_insert<Node>(new_node, &ite, RIGHT);
			}
		}

		iterator begin() { return iterator(_node_min(_root)); }
	private :
		node_pointer _end;
		node_pointer _start;
		node_pointer _root;
		node_alloc	_node_alloc;
		Compare		_comp;
	};
}
