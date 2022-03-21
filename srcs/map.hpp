/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:42:23 by allanganoun       #+#    #+#             */
/*   Updated: 2022/03/21 15:21:44 by tglory           ###   ########lyon.fr   */
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

		typedef typename ft::tree<value_type, Key>::iterator	iterator;


	
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

		iterator insert (iterator position, const value_type& val)
		{
			return _tree.insert(position, val);
		}

		template <class InputIterator>
  		void insert (InputIterator first, InputIterator last)
		{
			_tree.insert(first, last);
		}

		// iterator insert (iterator position, const value_type& val) {}
		// 
		// template <class InputIterator>
  		// void insert (InputIterator first, InputIterator last) {}

		iterator find(const key_type& k) { return _tree.find(k); }

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

		void clear() { _tree.clear(); }

		bool empty() const { return this->size() == 0; }

		size_type size() const { return _tree.size(); }

		// A check
		size_type max_size() const { return allocator_type().max_size() / 5; }
		
		iterator begin() { return _tree.begin(); }

		// const_iterator begin() const { return _start; }

		iterator end() { return _tree.end(); }

		// const_iterator end() const { return _end; }

		// reverse_iterator rbegin() { return _start; }

		// const_reverse_iterator rbegin() const { return _start; }

		// reverse_iterator rend() { return _end; }

		// const_reverse_iterator rend() const { return _end; }

		size_type count(const key_type& k) const { return _tree.count(k); }

		allocator_type get_allocator() const { return _alloc; }

		// _type& operator[](const key_type& k) {}

		// temp function
		tree<value_type, key_type> get_tree() const { return _tree; }

	private :
		allocator_type 					_alloc;
		tree<value_type, key_type>		_tree;
		key_compare 					_compare;
	};
}
