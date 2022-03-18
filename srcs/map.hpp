/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:42:23 by allanganoun       #+#    #+#             */
/*   Updated: 2022/03/18 18:25:52 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include "./utils/pair.hpp"
# include <memory>
# include <algorithm>
# include <cstddef>
# include "./utils/utils.hpp"
# include "./utils/iterator.hpp"
# include "./utils/tree_iterator.hpp"
# include "./utils/const_iterator.hpp"
# include "./utils/reverse_iterator.hpp"
# include "./utils/const_reverse_iterator.hpp"
# include "./utils/tree_iterator.hpp"
# include "./utils/tree.hpp"
namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<pair<const Key, T> > >
	class map
	{
	public :
		typedef Key 											key_type;
		typedef T 												mapped_type;
		typedef ft::pair<const Key, T> 							value_type;
		typedef Compare 										key_compare;
		typedef Allocator										allocator_type;
		typedef typename allocator_type::size_type				size_type;
		typedef typename allocator_type::difference_type		difference_type;
		typedef	typename allocator_type::reference				reference;
		typedef	typename allocator_type::const_reference		const_reference;
		typedef typename allocator_type::pointer				pointer;
		typedef typename allocator_type::const_pointer			const_pointer;

		typedef ft::tree_iterator<value_type>					iterator;
		// typedef ft::const_iterator<value_type>					const_iterator;
		// typedef ft::reverse_iterator<iterator>					reverse_iterator;
		// typedef	ft::const_reverse_iterator<iterator>			const_reverse_iterator;


		

		explicit map(const key_compare& comp = Compare(),
             const allocator_type& alloc = allocator_type())
		:	_alloc(alloc),
			_tree(),
			_compare(comp)
		{

		}

		template <class InputIterator>
  		map(InputIterator first, InputIterator last,
       			const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
	 	:	_alloc(alloc),
			_tree(),
			_compare(comp)
		{
			
		}

		pair<iterator,bool> insert(const value_type& val) // iterateur sur la valeur insérée + True pour dire valeur ajoutée ou false pour déjà éxistante
		{
			return (_tree.insert(val));
		}

		// iterator insert (iterator position, const value_type& val) {}
		// 
		// template <class InputIterator>
  		// void insert (InputIterator first, InputIterator last) {}

		// Not working
		/*iterator find(const key_type& k)
		{
			iterator it = _tree._start;
			while (it != _tree._end)
			{
				value_type pair = it->data;
				if (pair.getKey() == k)
					return it;
			}
			return _tree._end;
		}*/

		// const_iterator find(const key_type& k) const {}

		// iterator lower_bound(const key_type& k) {}

		// const_iterator lower_bound(const key_type& k) const {}

		// iterator upper_bound(const key_type& k) {}

		// const_iterator upper_bound(const key_type& k) const {}

		// pair<const_iterator, const_iterator> equal_range(const key_type& k) const {}

		// pair<iterator, iterator> equal_range(const key_type& k) {}

		// void erase(iterator position) {}

		// size_type erase(const key_type& k) {}

		// void erase(iterator first, iterator last) {}

		// void clear() {}

		bool empty() const { return this->size > 0; }

		size_type size() const { return _tree._node_count; }

		size_type max_size() const { return allocator_type().max_size(); }
		iterator begin() { return iterator(_tree.begin()); }

		// const_iterator begin() const { return _start; }

		iterator end() { return NULL; }

		// const_iterator end() const { return _end; }

		// reverse_iterator rbegin() { return _start; }

		// const_reverse_iterator rbegin() const { return _start; }

		// reverse_iterator rend() { return _end; }

		// const_reverse_iterator rend() const { return _end; }

		/*size_type count(const key_type& k) const
		{
			if (this->find(k) != this->end())
				return 1;
			else
				return 0;
		}*/

		allocator_type get_allocator() const { return _alloc; }

		// _type& operator[](const key_type& k) {}

	private :
		allocator_type 					_alloc;
		tree<value_type, key_type>		_tree;
		key_compare 					_compare;

		/**
		 * Based on https://stephane.glondu.net/projets/tipe/transparents.pdf#page=4
		 */
		void _rotateRight(value_type node)
		{
			value_type a = node->left;
			value_type b = node;
			value_type c = node->right;
			value_type d = node->parent;
			value_type e = node->parent->left;

			b->parent = d->parent;
			b->right = d;
			d->parent = b;
			d->left = c;
			c->parent = d;
		}

		void _rotateLeft(value_type node)
		{
			value_type a = node->parent->right;
			value_type b = node->parent;
			value_type c = node->left;
			value_type d = node;
			value_type e = node->right;

			d->parent = b->parent;
			d->left = b;
			b->parent = d;
			b->right = c;
			c->parent = b;
		}

		unsigned int _nodeHeigh(value_type &node)
		{
			unsigned int i = 0;
			value_type tempNode;
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

			if (!_printOne(_tree._root))
				return;
			std::cout << std::endl;
			_printNextNodes(_tree._root);
		}

		void _printNextNodes(value_type &node)
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

		bool _printOne(value_type &node)
		{
			if (!node)
			{
				std::cout << "Empty" << std::endl;
				return false;
			}
			std::cout << "        " << node.data << "\n      /    \\     ";
			return true;
		}
	};
}
