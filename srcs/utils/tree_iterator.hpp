/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alganoun <alganoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:34:39 by alganoun          #+#    #+#             */
/*   Updated: 2022/03/18 17:25:20 by alganoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// ICI IL FAUT ENCORE FAIRE LES AUTRES ITERATEURS
#pragma once

#include <cstddef>
#include "pair.hpp"
#include "iterator.hpp"
#include <memory>
#include <algorithm>
#include <cstddef>

//fonction pour calculer les incrementations

# define LEFT	true
# define RIGHT	false

template <class Node>
bool _is_right_node(Node node)
{
	if (node->parent && node->parent->right == node)
		return true;
	return false;
}

template <class Node>
bool _is_left_node(Node node)
{
	if (node->parent && node->parent->left == node)
		return true;
	return false;
}

template <class Node>
Node _node_min(Node node) {
	while (node->right != NULL) {
		node = node->right;
	}
	return node;
}

template <class Node>
Node _node_max(Node node) {
	while (node->left != NULL) {
		node = node->left;
	}
	return node;
}

template <class Node>
bool _node_has_leaf(Node node)
{
	if (node->right== NULL && node->left == NULL)
		return true;
	return false;
}

template <class Node>
bool _node_exists_alone(Node node)
{
	if (node && _node_has_a_leaf(node))
		return true;
	return false;
}

template <class Node>
bool _node_exists_with(Node node)
{
	if (node && !_node_has_a_leaf(node))
		return true;
	return false;
}

template <class Node>
Node _node_next(Node node)
{
	while (_is_right_node(node))
		node = node->parent;
	if (_is_left_node(node) && node->right == NULL)
		return node->parent;
	else if (_is_left_node(node) && _node_exists_alone(node->right))
		return node->right;
	else if (_is_left_node(node) && _node_exists_with(node->right))
		return _node_min(node->right);
}

template <class Node>
Node _node_prev(Node node)
{
	while (_is_left_node(node))
		node = node->parent;
	if (_is_right_node(node) && node->left == NULL)
		return node->parent;
	else if (_is_right_node(node) && _node_exists_alone(node->left))
		return node->left;
	else if (_is_right_node(node) && _node_exists_with(node->left))
		return _node_max(node->left);
}

template <class Node>
Node _node_insert(Node to_insert, Node node, bool direction)
{
	if (direction == LEFT)
	{	
		return (Node(to_insert.data, node.left, NULL, NULL))
	}
	else if (direction == RIGHT)
	{	
		return (Node(to_insert.data, node.right, NULL, NULL))
	}
}

namespace ft
{

template <class Value>
struct	_node
{		
		Value							data;
		_node 							*parent;
		_node							*right;
		_node							*left;
		
		_node(Value const &v)
		: value(v), parent(NULL), right(NULL), left(NULL)
		{
		};

		_node(Value const & v, const _node *parent, _node *right, _node *left)
		: value(v), parent(parent), right(right), left(left)
		{

		}


};

template <typename T>
class	tree_iterator
{
public:

	typedef T							data_type;
	typedef ft::_node<data_type>		node;
	typedef node&						reference;
	typedef const node&					const_reference;
	typedef node*						pointer;
	typedef const node*					const_pointer;
	typedef typename std::ptrdiff_t 	difference_type;	

	
	
	tree_iterator(void) {};
	tree_iterator(pointer ptr) { _ptr = ptr; };
	tree_iterator(const tree_iterator &src) { *this = src; } ;


	virtual ~tree_iterator() {};

	tree_iterator &operator=(tree_iterator const &src) { _ptr = src.operator->(); return (*this); };

	// BOOLEANS : pas besoin dans ce cas
	bool operator ==(tree_iterator const& b) const { return (_ptr == b._ptr); };
	bool operator !=(tree_iterator const& b) const { return (!(_ptr == b.ptr)); };
	//bool operator >(tree_iterator const& b) const { return (_ptr > b._ptr); };
	//bool operator <(tree_iterator const& b) const { return (key_compare(_ptr, b._ptr)); };
	//bool operator >=(tree_iterator const& b) const { return (_ptr >= b._ptr); };
	//bool operator <=(tree_iterator const& b) const { return (_ptr <= b._ptr); };


	// INCREMENTERS
	tree_iterator& operator ++() { _ptr = _node_next(_ptr); return (*this); };			// ++a
	tree_iterator operator ++(int) { return (tree_iterator(_node_next(_ptr))); };	// a++
	tree_iterator& operator --() { _ptr = _node_prev(_ptr); return (*this); };			// --a
	tree_iterator operator --(int) { return (tree_iterator(_node_prev(_ptr))); };	// a--

	//COMPOUND ASSIGNMENTS
	//tree_iterator& operator +=(difference_type b) {_ptr += b; return *this; };	// a += b
	//tree_iterator& operator -=(difference_type b) {_ptr -= b; return *this; };	// a -= b
//
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
}
