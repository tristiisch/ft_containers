/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:36:17 by allanganoun       #+#    #+#             */
/*   Updated: 2022/03/20 23:44:01 by allanganoun      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>
#include <memory>
#include <algorithm>
#include <iostream>
#include "tree_iterator.hpp"

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
				return (make_pair(iterator(_root), true));
			}
			current = _node_min(_root);
			while (_comp(current->data.first, val.first))
			{
				tmp = _node_next(current);
				if (tmp != NULL)
					current = tmp;
				else
					break;
			}
			if (current->data.first == val.first)
				return make_pair(iterator(current), false);
			while (current !=_start && !_node_has_leaf(current))
				current = _node_prev(current);
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
			_start = _node_min(_root);
			return make_pair(iterator(new_node), true);
		}
		iterator insert (iterator position, const data_type& val)
		{}

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
				data_type pair = node->data;
				if (pair.getKey() == k)
					return iterator(node);
			}
			return iterator(_end);
		}

		/**
		 * Based on https://stephane.glondu.net/projets/tipe/transparents.pdf#page=4
		 */
		void _rotateRight(node_type node)
		{
			node_type a = node->left;
			node_type b = node;
			node_type c = node->right;
			node_type d = node->parent;
			node_type e = node->parent->left;

			b->parent = d->parent;
			b->right = d;
			d->parent = b;
			d->left = c;
			c->parent = d;
		}

		void _rotateLeft(node_type node)
		{
			node_type a = node->parent->right;
			node_type b = node->parent;
			node_type c = node->left;
			node_type d = node;
			node_type e = node->right;

			d->parent = b->parent;
			d->left = b;
			b->parent = d;
			b->right = c;
			c->parent = b;
		}

		unsigned int _nodeHeigh(node_type &node)
		{
			unsigned int i = 0;
			node_type tempNode;
			do {
				tempNode = node;
				++i;
			} while (tempNode->parent);
			return i;
		}

		/**
		 * Does not work as intended, need height and
		 * print all lvl as same time
		 */
		void _print()
		{
			bool hasLeft;
			bool hasRight;

			if (!_printOne(_root))
				return;
			std::cout << std::endl;
			_printNextNodes(_root);
		}

		void _printNextNodes(node_type &node)
		{
			bool hasLeft;
			bool hasRight;

			hasLeft = _printOne(node->left);
			hasRight = _printOne(node->right);
			std::cout << std::endl;
			if (hasLeft)
				_printNextNodes(node->left);
			if (hasRight)
				_printNextNodes(node->right);
		}

		bool _printOne(node_type &node)
		{
			if (!node)
			{
				std::cout << "Empty" << std::endl;
				return false;
			}
			std::cout << "        " << node.data << "\n      /    \\     ";
			return true;
		}

	private :
		node_pointer _end;
		node_pointer _start;
		node_pointer _root;
		node_alloc	_node_alloc;
		Compare		_comp;
	};
}
