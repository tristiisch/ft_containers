/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alganoun <alganoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 22:32:21 by tglory            #+#    #+#             */
/*   Updated: 2022/03/15 15:25:39 by alganoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdexcept>
#include "./utils/tree.hpp"
#include "./utils/utils.hpp"

namespace ft
{
template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<pair<const Key, T> > >
class map
{
	public:
		typedef Key key_type;
		typedef T _type;
		typedef pair<const Key, T> value_type;
		typedef Compare key_compare;
		typedef Allocator allocator_type;

	private:
		typedef _tree<value_type, key_compare, allocator_type> tree_type;

	public:
		typedef typename tree_type::size_type size_type;
		typedef typename tree_type::difference_type difference_type;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;

		typedef typename tree_type::iterator iterator;
		typedef typename tree_type::const_iterator const_iterator;
		typedef typename tree_type::reverse_iterator reverse_iterator;
		typedef typename tree_type::const_reverse_iterator const_reverse_iterator;

		class value_compare: public std::binary_function<value_type, value_type, bool> {
			protected:
				friend class map;

				key_compare comp;

				value_compare(key_compare comp) : comp(comp) { }

			public:
				bool operator()(const value_type &lhs, const value_type &rhs) const {
					return comp(lhs.first, rhs.first);
				}
		};

	public:
		// Because all arguments have default value this also acts as a default constructor.
		explicit map(const key_compare &comp = key_compare(), const allocator_type &allocator = allocator_type()) : _tree(comp, allocator) {}

		template<class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &allocator = allocator_type()) : _tree(comp, allocator) {
			_tree.insert(first, last);
		}

		map(const map &other) : _tree(other._tree) {}

		~map() {}

		map& operator=(const map &other) {
			_tree = other._tree;
			return *this;
		}

		allocator_type get_allocator() const {
			return _tree.get_allocator();
		}

		// cppreference.com states that these method weren't introduced in CPP11 (which is what cplusplus.com says).
		// On cppreference we learn that it was retroactively applied to CPP98.
		//
		// tl;dr these methods weren't available at the beginning but are now in CPP98 so we decided to implement them.
		_type& at(const key_type &key) {
			iterator it = find(key);

			if (it == end()) {
				throw std::out_of_range("map::at");
			}

			return it->second;
		}

		const _type& at(const key_type &key) const {
			const_iterator it = find(key);

			if (it == end()) {
				throw std::out_of_range("map::at");
			}

			return it->second;
		}

		_type& operator[](const key_type &key) {
			return insert(ft::make_pair(key, T())).first->second;
		}

		iterator begin() {
			return _tree.begin();
		}

		const_iterator begin() const {
			return _tree.begin();
		}

		iterator end() {
			return _tree.end();
		}

		const_iterator end() const {
			return _tree.end();
		}

		reverse_iterator rbegin() {
			return _tree.rbegin();
		}

		const_reverse_iterator rbegin() const {
			return _tree.rbegin();
		}

		reverse_iterator rend() {
			return _tree.rend();
		}

		const_reverse_iterator rend() const {
			return _tree.rend();
		}

		bool empty() const {
			return _tree.empty();
		}

		size_type size() const {
			return _tree.size();
		}

		size_type max_size() const {
			return _tree.max_size();
		}

		void clear() {
			_tree.clear();
		}

		pair<iterator, bool> insert(const value_type& value) {
			return _tree.insert(value);
		}

		iterator insert(iterator hint, const value_type &value) {
			return _tree.insert(hint, value);
		}

		template<class InputIterator>
		void insert(InputIterator first, InputIterator last) {
			return _tree.insert(first, last);
		}

		void erase(iterator pos) {
			_tree.erase(pos);
		}

		size_type erase(const key_type &key) {
			iterator pos = find(key);

			if (pos == end()) {
				return 0;
			}

			_tree.erase(pos);
			return 1;
		}

		void erase(iterator first, iterator last) {
			_tree.erase(first, last);
		}

		void swap(map &other) {
			_tree.swap(other._tree);
		}

		size_type count(const key_type &key) const {
			return _tree.find(key) != end();
		}

		iterator find(const key_type &key) {
			return _tree.find(key);
		}

		const_iterator find(const key_type &key) const {
			return _tree.find(key);
		}

		pair<iterator, iterator> equal_range(const key_type &key) {
			return _tree.equal_range(key);
		}

		pair<const_iterator, const_iterator> equal_range(const key_type &key) const {
			return _tree.equal_range(key);
		}

		iterator lower_bound(const key_type &key) {
			return _tree.lower_bound(key);
		}

		const_iterator lower_bound(const key_type &key) const {
			return _tree.lower_bound(key);
		}

		iterator upper_bound(const key_type &key) {
			return _tree.upper_bound(key);
		}

		const_iterator upper_bound(const key_type &key) const {
			return _tree.upper_bound(key);
		}

		key_compare key_comp() const {
			return _tree.key_comp();
		}

		value_compare value_comp() const {
			return value_compare(key_comp());
		}

	private:
		 tree_type _tree;
};

template <class Key, class T, class Compare, class Alloc>
bool operator==(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {
	return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class Key, class T, class Compare, class Alloc>
bool operator!=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {
	return !(lhs == rhs);
}

template <class Key, class T, class Compare, class Alloc>
bool operator<(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class Key, class T, class Compare, class Alloc>
bool operator<=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {
	return !(rhs < lhs);
}

template <class Key, class T, class Compare, class Alloc>
bool operator>(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {
	return rhs < lhs;
}

template <class Key, class T, class Compare, class Alloc>
bool operator>=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {
	return !(lhs < rhs);
}
}

// Outside namespace `ft` because the non-member function specialization is on
// std::swap and we do not need to reimplement our own version of it, so a specialization is fine and makes sense.
namespace std {
template <class Key, class T, class Compare, class Alloc>
void swap(ft::map<Key, T, Compare, Alloc> &one, ft::map<Key, T, Compare, Alloc> &two) {
	one.swap(two);
}
}
