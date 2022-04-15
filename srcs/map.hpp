/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:42:23 by allanganoun       #+#    #+#             */
/*   Updated: 2022/03/22 18:24:14 by tglory           ###   ########lyon.fr   */

/*                                                                            */
/* ************************************************************************** */

#pragma once
# include "./utils/pair.hpp"
# include <memory>
# include <algorithm>
# include <cstddef>
# include "./utils/utils.hpp"
# include "./utils/reverse_iterator.hpp"
# include "./utils/tree_iterator.hpp"
# include "./utils/tree.hpp"
namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<pair<const Key, T> > >
	class map
	{
	public :

		typedef Key 																		key_type;
		typedef T 																			mapped_type;
		typedef ft::pair<const Key, T> 														value_type;
		typedef Compare 																	key_compare;
		typedef Allocator																	allocator_type;
		typedef typename allocator_type::size_type											size_type;
		typedef typename allocator_type::difference_type									difference_type;
		typedef	typename allocator_type::reference											reference;
		typedef	typename allocator_type::const_reference									const_reference;
		typedef typename allocator_type::pointer											pointer;
		typedef typename allocator_type::const_pointer										const_pointer;

		typedef typename ft::tree<value_type, Key, Compare, Allocator>::iterator			iterator;
		typedef typename ft::tree<value_type, Key, Compare, Allocator>::const_iterator		const_iterator;
		typedef typename ft::reverse_iterator<iterator>										reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>								const_reverse_iterator;

		class value_compare : std::binary_function<value_type, value_type, bool>
		{
		friend class map;
		protected:
			Compare comp;
			value_compare (Compare c) : comp(c) {}
		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
		  	bool operator() (const value_type& x, const value_type& y) const
		  	{
				return comp(x.first, y.first);
			}
		};

		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		:	_alloc(alloc),
			_tree(),
			_compare(comp)
		{}

		template <class InputIterator>
  		map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
	 	:	_alloc(alloc),
			_tree(),
			_compare(comp)
		{
			insert(first, last);
		}

		map(const map& x)
		:	_alloc(x._alloc),
			_tree(),
			_compare(x._compare)
		{
			insert(x.begin(), x.end());
		}

		~map() {}

		map& operator=(const map& x)
		{
			if (&x == this)
				return *this;
			clear();
			insert(x.begin(), x.end());
			return *this;
		}

		pair<iterator,bool> insert(const value_type& val)
		{
			iterator founded = this->find(val.first);
			if (founded == end())
				return ft::make_pair(_tree.insert(val), true);
			return (ft::make_pair(founded, false));
		}

		iterator insert(iterator position, const value_type& val) { return _tree.insert(position, val); }

		template <class InputIterator>
  		void insert(InputIterator first, InputIterator last) { _tree.insert(first, last); }

		iterator find(const key_type& k) { return _tree.find(k); }

		const_iterator find(const key_type& k) const { return _tree.find(k); }

		iterator lower_bound(const key_type& k) { return iterator(_tree.lower_bound(k)); }



		const_iterator lower_bound (const key_type& k) const { return const_iterator(_tree.lower_bound(k)); } // iulk faut retourner un const_iterator

		iterator upper_bound (const key_type& k) { return iterator(_tree.upper_bound(k)); }

		const_iterator upper_bound (const key_type& k) const { return const_iterator(_tree.upper_bound(k)); }

		pair<const_iterator, const_iterator> equal_range(const key_type& k) const { return make_pair(lower_bound(k), upper_bound(k)); }

		pair<iterator, iterator> equal_range(const key_type& k) { return make_pair(lower_bound(k), upper_bound(k)); }

		void erase(iterator position) { _tree.erase(position); }

		size_type erase(const key_type& k)
		{
			if (find(k) != end())
			{
				_tree.erase(k);
				return 1;
			}
			return 0;
		}

		void erase(iterator first, iterator last)  { return _tree.erase(first, last); }

		void clear() { _tree.clear(); }

		bool empty() const { return _tree.empty(); }

		size_type size() const { return _tree.size(); }

		size_type max_size() const { return _tree.max_size(); }

		iterator begin() { return _tree.begin(); }

		const_iterator begin() const { return _tree.begin(); }

		iterator end() { return _tree.end(); }

		const_iterator end() const { return _tree.end(); }

		reverse_iterator rbegin() { return reverse_iterator(end()); }

		const_reverse_iterator rbegin() const {  return const_reverse_iterator(end()); }

		reverse_iterator rend() { return reverse_iterator(begin()); }

		const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

		size_type count(const key_type& k) const { return _tree.count(k); }

		key_compare key_comp() const {return _tree.key_comp(); }

		value_compare value_comp() const { return value_compare(key_comp()); }

		allocator_type get_allocator() const { return _alloc; }

		mapped_type& operator[](const key_type &key)
 		{
 			iterator value = find(key);
 			if (value == end())
 				insert(ft::make_pair(key, mapped_type()));
 			value = find(key);
 			return ((*value).second);
 		}

		void swap(map &map) {
			std::swap(_alloc, map._alloc);
			_tree.swap(map._tree);
			std::swap(_compare, map._compare);
		}

	//protected :
		tree<value_type, key_type, key_compare, allocator_type>* get_tree()
		{
			return &_tree;
		}

	private :
		allocator_type 												_alloc;
		tree<value_type, key_type, key_compare, allocator_type>		_tree;
		key_compare 												_compare;
	};

	template <class Key, class T, class Alloc>
	bool operator==(const map<Key, T, Alloc>& lhs, const map<Key, T, Alloc>& rhs)
	{
		if (ft::equal(lhs.begin(), lhs.end(), rhs.begin()) != false)
			return lhs.size() == rhs.size();
		return false;
	}

	template <class Key, class T, class Alloc>
	bool operator!=(const map<Key, T, Alloc>& lhs, const map<Key, T, Alloc>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class Key, class T, class Alloc>
	bool operator<(const map<Key, T, Alloc> &lhs, const map<Key, T, Alloc> &rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class Key, class T, class Alloc>
	bool operator<=(const map<Key, T, Alloc>& lhs, const map<Key, T, Alloc>& rhs)
	{
		return !(lhs > rhs);
	}

	template <class Key, class T, class Alloc>
	bool operator>(const map<Key, T, Alloc> &lhs, const map<Key, T, Alloc> &rhs)
	{
		return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
	}

	template <class Key, class T, class Alloc>
	bool operator>=(const map<Key, T, Alloc>& lhs, const map<Key, T, Alloc>& rhs)
	{
		return !(lhs < rhs);
	}

	template <class Key, class T, class Alloc>
 		void swap (map<Key, T,Alloc>& x, map<Key, T,Alloc>& y)
	{
		x.swap(y);
	}
}
