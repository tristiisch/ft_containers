/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:34:39 by alganoun          #+#    #+#             */
/*   Updated: 2022/03/20 23:44:06 by allanganoun      ###   ########lyon.fr   */
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
	if (!node)
		return (NULL);
	while (node->left != NULL) {
		node = node->left;
	}
	return node;
}

template <class Node>
Node _node_max(Node node) {
	while (node->right != NULL) {
		node = node->right;
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
	if (node && _node_has_leaf(node))
		return true;
	return false;
}

template <class Node>
bool _node_exists_with(Node node)
{
	if (node && !_node_has_leaf(node))
		return true;
	return false;
}

template <class Node>
bool _node_is_root(Node node)
{
	if (node->parent == NULL)
		return true;
	return false;
}

template <class Node>
Node _node_next(Node node)
{
	if (node->right != NULL) {
		return _node_min(node->right);
	}
	while (_is_right_node(node)) {
		node = node->parent;
	}
	return node->parent;
}

template <class Node>
Node _node_prev(Node node)
{
	if (node->left != NULL) {
		return _node_max(node->left);
	}
	while (_is_left_node(node)) {
		node = node->parent;
	}
	return node->parent;
}


namespace ft
{

template <class Value>
struct	_node
{
		typedef Value						value_type;
		Value							data;
		_node 							*parent;
		_node							*right;
		_node							*left;

		_node(Value const &v)
		: data(v), parent(NULL), right(NULL), left(NULL)
		{
		};

		_node(Value const & v, _node *parent, _node *right, _node *left)
		: data(v), parent(parent), right(right), left(left)
		{

		}


};

template <class Value>
ft::_node<Value> _node_insert(ft::_node<Value> *to_insert, ft::_node<Value> *node, bool direction)
{

	return (ft::_node<Value>(to_insert->data, node, NULL, NULL));
}

template <typename T>
class	tree_iterator
{
public:

	typedef T							data_type;
	typedef typename T::value_type    	pair;
	typedef pair&						reference;
	typedef const pair&					const_reference;
	typedef pair*						pointer;
	typedef const pair*					const_pointer;
	typedef typename std::ptrdiff_t 	difference_type;



	tree_iterator(void) {}
	tree_iterator(T* other) : _node(other) {}
	//tree_iterator(Node* other) { _node = other->_node; };
	tree_iterator(const tree_iterator &src) { *this = src; }


	virtual ~tree_iterator() {}

	tree_iterator &operator=(tree_iterator const &src) { _node = src._node; return (*this); }

	// BOOLEANS : pas besoin dans ce cas
	bool operator ==(tree_iterator const& b) const { return (_node == b._node); }
	bool operator !=(tree_iterator const& b) const { return (!(_node == b._node)); }
	//bool operator >(tree_iterator const& b) const { return (_node > b._node); };
	//bool operator <(tree_iterator const& b) const { return (key_compare(_node, b._node)); };
	//bool operator >=(tree_iterator const& b) const { return (_node >= b._node); };
	//bool operator <=(tree_iterator const& b) const { return (_node <= b._node); };


	// INCREMENTERS
	tree_iterator& operator ++() { _node = _node_next(_node); return ((*this)); }			// ++a
	tree_iterator operator ++(int) 															// a++
	{
		T* tmp = _node;
		_node = _node_next(_node);
		return tree_iterator(tmp);
	}
	tree_iterator& operator --() { _node = _node_prev(_node); return ((*this)); }			// --a
	tree_iterator operator --(int)															// a--
	{
		T* tmp = _node;
		_node = _node_prev(_node);
		return tree_iterator(tmp);
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

