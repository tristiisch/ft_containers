/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:42:23 by allanganoun       #+#    #+#             */
/*   Updated: 2022/03/16 16:22:34 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include "./utils/pair.hpp"
# include <memory>
# include <algorithm>
# include <cstddef>
# include "./utils/utils.hpp"
# include "./utils/iterator.hpp"
# include "./utils/const_iterator.hpp"
# include "./utils/reverse_iterator.hpp"
# include "./utils/const_reverse_iterator.hpp"
# include "./utils/tree_iterator.hpp"

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<pair<const Key, T> > >
	class map
	{
	public :
		typedef Key 											key_type;
		typedef T 												mapped_type;
		typedef pair<const Key, T> 								value_type;
		typedef Compare 										key_compare;
		typedef Allocator										allocator_type;
		typedef ft::_node										_node;
		typedef typename allocator_type::size_type				size_type;
		typedef typename allocator_type::difference_type		difference_type;
		typedef	typename allocator_type::reference				reference;
		typedef	typename allocator_type::const_reference		const_reference;
		typedef typename allocator_type::pointer				pointer;
		typedef typename allocator_type::const_pointer			const_pointer;

		typedef ft::iterator<value_type>						iterator;
		typedef ft::const_iterator<value_type>					const_iterator;
		typedef ft::reverse_iterator<iterator>					reverse_iterator;
		typedef	ft::const_reverse_iterator<iterator>			const_reverse_iterator;
		

		explicit map (const key_compare& comp = key_compare(),
             const allocator_type& alloc = allocator_type())
		:	_alloc(alloc),
			_start(NULL), 
			_end(NULL), 
			_node_count(0)
		{

		}

		template <class InputIterator>
  		map (InputIterator first, InputIterator last,
       			const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
	 	:	_alloc(alloc),
			_start(NULL),
			_end(NULL),
			_node_count(0)
		{
			
		}

		pair<iterator,bool> insert (const value_type& val) // iterateur sur la valeur insérée + True pour dire valeur ajoutée ou false pour déjà éxistante
		{
			_node new_node;
			_node *current;
			new_node.p = val;

			while (current->right != NULL || current->left != NULL)
			{
				if (key_compare(val, current->p))
					current = current->left;
				else if (iterator(val) == current->p)
					return (make_pair(current->p, false))
				else
					current = current->right;
			}
			new_node->parent = current;
			
		}

		iterator insert (iterator position, const value_type& val) {}
		
		template <class InputIterator>
  		void insert (InputIterator first, InputIterator last) {}
	
		iterator find(const key_type& k) {}
		
		const_iterator find(const key_type& k) const {}

		iterator lower_bound(const key_type& k) {}

		const_iterator lower_bound(const key_type& k) const {}

		iterator upper_bound(const key_type& k) {}

		const_iterator upper_bound(const key_type& k) const {}

		pair<const_iterator, const_iterator> equal_range(const key_type& k) const {}

		pair<iterator, iterator> equal_range(const key_type& k) {}

		void erase(iterator position) {}

		size_type erase(const key_type& k) {}

		void erase(iterator first, iterator last) {}

		void clear() {}

		bool empty() const { return this->size > 0; }

		size_type size() const { return _node_count; }

		size_type max_size() const { return allocator_type().max_size(); }
		
		iterator begin() { return _start; }

		const_iterator begin() const { return _start; }

		iterator end() { return _end; }

		const_iterator end() const { return _end; }

		reverse_iterator rbegin() { return _start; }

		const_reverse_iterator rbegin() const { return _start; }

		reverse_iterator rend() { return _end; }

		const_reverse_iterator rend() const { return _end; }
		
		size_type count(const key_type& k) const
		{
			if (this->find(k) != this->end())
				return 1;
			else
				return 0;
		}

		allocator_type get_allocator() const { return _alloc; }

		_type& operator[](const key_type& k) {}

	private :
		allocator_type _alloc;
		_node *_start;
		_node *_end;
		_node *root;
		size_type _node_count;
		
		void _rotateRight(_node node)
		{
			//std::swap(node->left, node->right);
		}

		unsigned int _nodeHeigh(_node &node)
		{
			unsigned int i = 0;
			_node tempNode;
			do {
				tempNode = node;
				++i;
			} while (tempNode->parent);
			return i;
		}
	};
}
