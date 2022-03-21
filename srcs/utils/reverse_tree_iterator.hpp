/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_tree_iterator.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:34:39 by alganoun          #+#    #+#             */
/*   Updated: 2022/03/21 15:49:02 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>
#include "pair.hpp"
#include "./tree_iterator.hpp"
#include <memory>
#include <algorithm>
#include <cstddef>

namespace ft
{
template <typename T>
class	reverse_tree_iterator
{
public:

	typedef T							data_type;
	typedef typename T::value_type    	pair;
	typedef pair&						reference;
	typedef const pair&					const_reference;
	typedef pair*						pointer;
	typedef const pair*					const_pointer;
	typedef typename std::ptrdiff_t 	difference_type;


	reverse_tree_iterator(void) {}
	reverse_tree_iterator(T* other) : _node(other) {}
	//tree_iterator(Node* other) { _node = other->_node; };
	reverse_tree_iterator(const reverse_tree_iterator &src) { *this = src; }

	virtual ~reverse_tree_iterator() {}

	reverse_tree_iterator &operator=(reverse_tree_iterator const &src) { _node = src._node; return (*this); }

	// BOOLEANS : pas besoin dans ce cas
	bool operator ==(reverse_tree_iterator const& b) const { return (_node == b._node); }
	bool operator !=(reverse_tree_iterator const& b) const { return (!(_node == b._node)); }


	// INCREMENTERS
	reverse_tree_iterator& operator --() { _node = _node_next(_node); return ((*this)); }			// ++a
	reverse_tree_iterator operator --(int) 															// a++
	{
		T* tmp = _node;
		_node = _node_next(_node);
		return reverse_tree_iterator(tmp);
	}
	reverse_tree_iterator& operator ++() { _node = _node_prev(_node); return ((*this)); }			// --a
	reverse_tree_iterator operator ++(int)															// a--
	{
		T* tmp = _node;
		_node = _node_prev(_node);
		return reverse_tree_iterator(tmp);
	}

	//COMPOUND ASSIGNMENTS
	//tree_iterator& operator +=(difference_type b) {_node += b; return *this; };	// a += b
	//tree_iterator& operator -=(difference_type b) {_node -= b; return *this; };	// a -= b
//
	//DEREFERENCING & ADDRESS STUFF
	reference operator *() { return (_node->data); }											// *a
	const_reference operator *() const { return (_node->data); }								// *a
	pointer operator ->() { return &(_node->data); }											// a->b
	pointer operator ->() const { return &(_node->data); }											// a->b


	private:
		T* _node;
};

}

