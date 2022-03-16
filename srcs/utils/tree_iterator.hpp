/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:34:39 by alganoun          #+#    #+#             */
/*   Updated: 2022/03/16 01:06:21 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <cstddef>
# include "pair.hpp"
# include <memory>
# include <algorithm>
# include <cstddef>

namespace ft
{


template <typename T, class Key, class Compare = std::less<Key> >
class	tree_iterator
{
public:

	typedef T						value_type;
	typedef value_type&				reference;
	typedef Compare					key_compare;
	typedef const value_type&		const_reference;
	typedef value_type*				pointer;
	typedef const value_type*		const_pointer;
	typedef typename std::ptrdiff_t difference_type;

	struct	_node
	{		
			tree_iterator	p;
			_node 		*parent;
			_node		*right;
			_node		*left;
	};
	
	tree_iterator(void) {};
	tree_iterator(pointer ptr) { _ptr = ptr; };
	tree_iterator(const tree_iterator &src) { *this = src; } ;


	virtual ~tree_iterator() {};

	tree_iterator &operator=(tree_iterator const &src) { _ptr = src.operator->(); return (*this); };

	// BOOLEANS
	bool operator ==(tree_iterator const& b) const { return (_ptr == b._ptr); };
	bool operator !=(tree_iterator const& b) const { return (_ptr != b._ptr); };
	bool operator >(tree_iterator const& b) const { return (_ptr > b._ptr); };
	bool operator <(tree_iterator const& b) const { return (); };
	bool operator >=(tree_iterator const& b) const { return (_ptr >= b._ptr); };
	bool operator <=(tree_iterator const& b) const { return (_ptr <= b._ptr); };

	// ARITHMETICS
	tree_iterator operator +(difference_type b) const { return (tree_iterator(_ptr + b)); }; // a + n
	tree_iterator operator -(difference_type b) const { return (tree_iterator(_ptr - b)); }; // a - n

	difference_type operator +(tree_iterator b) { return (_ptr + b._ptr); }; // a + b
	difference_type operator -(tree_iterator b) { return (_ptr - b._ptr); }; // a - b

	// INCREMENTERS
	tree_iterator& operator ++() { _ptr++; return (*this); };			// ++a
	tree_iterator operator ++(int) { return (tree_iterator( _ptr++)); };	// a++
	tree_iterator& operator --() { _ptr--; return (*this); };			// --a
	tree_iterator operator --(int) { return (tree_iterator(_ptr--)); };	// a--

	//COMPOUND ASSIGNMENTS
	tree_iterator& operator +=(difference_type b) {_ptr += b; return *this; };	// a += b
	tree_iterator& operator -=(difference_type b) {_ptr -= b; return *this; };	// a -= b

	//DEREFERENCING & ADDRESS STUFF
	reference operator *() { return (*_ptr); };											// *a
	const_reference operator *() const { return (*_ptr); };								// *a
	reference operator [](difference_type b) { return (*(_ptr + b)); };					// a[]
	const_reference operator [](difference_type b) const { return (*(_ptr + b)); };		// a[]
	pointer operator ->() { return (_ptr); };											// a->b
	pointer operator ->() const { return (_ptr); };											// a->b

	tree_iterator base() const {return _ptr;};

	static const bool input_iter = true;


	private:
		pointer _ptr;
};

	template < class One, class Two>
	bool operator==(const One &lhs, const Two &rhs) {
		return lhs.base() == rhs.base();
	}

	template < class One, class Two>
	bool operator!=(const One &lhs, const Two &rhs) {
		return lhs.base() != rhs.base();
	}

/*********** USLESS : les comparaisons ne vont pas dedans ***********/
	// template <class One, class Two>
	// bool operator<(const tree_iterator<One> &lhs, const tree_iterator<Two> &rhs) {
	// 	return lhs.base() < rhs.base();
	// }

	// template <class One, class Two>
	// bool operator<=(const tree_iterator<One> &lhs, const tree_iterator<Two> &rhs) {
	// 	return !(rhs < lhs);
	// }

	// template <class One, class Two>
	// bool operator>(const tree_iterator<One> &lhs, const tree_iterator<Two> &rhs) {
	// 	return (rhs < lhs);
	// }

	// template <class One, class Two>
	// bool operator>=(const tree_iterator<One> &lhs, const tree_iterator<Two> &rhs) {
	// 	return !(lhs < rhs);
	// }

	template < class One, class Two>
	bool operator<(const One &lhs, const Two &rhs) {
		return lhs.base() < rhs.base();
	}

	template < class One, class Two>
	bool operator<=(const One &lhs, const Two &rhs) {
		return lhs.base() <= rhs.base();
	}

	template < class One, class Two>
	bool operator>(const One &lhs, const Two &rhs) {
		return (lhs.base() > rhs.base());
	}

	template < class One, class Two>
	bool operator>=(const One &lhs, const Two &rhs) {
		return lhs.base() >= rhs.base();
	}

/********************************************************************/

	template <class Inputtree_iterator>
	typename Inputtree_iterator::difference_type operator-(const Inputtree_iterator &lhs, const Inputtree_iterator&rhs) {
		return lhs.base() - rhs.base();
	}

	template <class Inputtree_iterator>
	Inputtree_iterator operator+(const typename Inputtree_iterator::difference_type &lhs, const Inputtree_iterator&rhs) {
		return rhs + lhs;
	}
}