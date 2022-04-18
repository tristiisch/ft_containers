/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:34:39 by alganoun          #+#    #+#             */
/*   Updated: 2022/04/18 22:49:00 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>
#include "pair.hpp"
#include "iterator.hpp"
#include "reverse_iterator.hpp"
#include <iostream>
#include <memory>
#include <algorithm>
#include <cstddef>

# define LEFT	true
# define RIGHT	false

inline int _comp_max(int a, int b)
{
	return (a > b) ? a : b;
}

template <class Node>
bool _is_right_node(Node node)
{
	if (node && node->parent && node->parent->right == node)
		return true;
	return false;
}

template <class Node>
bool  _is_left_node(Node node)
{
	if (node && node->parent && node->parent->left == node)
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
	return node->parent;
}

template <class Node>
Node _node_true_max(Node node) {
	while (node->right != NULL) {
		node = node->right;
	}
	return node;
}


template <class Node>
bool _node_has_leaf(Node node)
{
	if (node->right == NULL && node->left == NULL)
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
		return _node_true_max(node->left);
	}
	while (_is_left_node(node)) {
		node = node->parent;
	}
	return node->parent;
}

template <class Node>
int _node_height(Node node)
{
	if (node == NULL)
		return 0;
	return node->height;
}



template <class Node>
int		_node_balance(Node node)
{
	if (node == NULL)
		return (0);
	return _node_height(node->left) - _node_height(node->right);
}

template <class Node>
bool _check_node(Node node)
{
	Node parent;
	parent = node->parent;
	if (parent && (parent->right == NULL || parent->left == NULL) && !_node_has_leaf(node))
		return (false);
	return (true);
}

namespace ft
{

template <class Value>
struct	_node
{
		typedef Value					value_type;

		value_type						data;
		_node 							*parent;
		_node							*right;
		_node							*left;
		int								height;

		_node()
		:	data(),
			parent(NULL),
			right(NULL),
			left(NULL),
			height(1)
		{

		}
		_node(Value const &v)
		:	data(v),
			parent(NULL),
			right(NULL),
			left(NULL),
			height(1)

		{
		};

		_node(Value const & v, _node *parent, _node *right, _node *left, int height)
		:	data(v),
			parent(parent),
			right(right),
			left(left),
			height(height)
		{

		}

		~_node()
		{}



		int max_depth() const {
			const int left_depth = left ? left->max_depth() : 0;
			const int right_depth = right ? right->max_depth() : 0;
			return (left_depth > right_depth ? left_depth : right_depth) + 1;
		}


};

template <typename T>
class	tree_iterator
{
public:

	typedef T							value_type;
	typedef typename T::value_type    	pair;
	typedef pair&						reference;
	typedef const pair&					const_reference;
	typedef pair*						pointer;
	typedef const pair*					const_pointer;
	typedef typename std::ptrdiff_t 	difference_type;

	tree_iterator(void) : _node(NULL) {}
	tree_iterator(T* other) : _node(other) {}
	tree_iterator(const tree_iterator &src) { *this = src; }

	virtual ~tree_iterator() {}

	tree_iterator &operator=(tree_iterator const &src) { _node = src._node; return (*this); }

	bool operator ==(T* const base) const { return (_node == base); }
	bool operator ==(tree_iterator const& b) const { return (_node == b._node); }
	bool operator !=(tree_iterator const& b) const { return (!(_node == b._node)); }

	tree_iterator& operator ++() { _node = _node_next(_node); return ((*this)); }
	tree_iterator operator ++(int)
	{
		T* tmp = _node;
		_node = _node_next(_node);
		return tree_iterator(tmp);
	}
	tree_iterator& operator --() { _node = _node_prev(_node); return ((*this)); }
	tree_iterator operator --(int)
	{
		T* tmp = _node;
		_node = _node_prev(_node);
		return tree_iterator(tmp);
	}

	reference operator *() { return (_node->data); }
	const_reference operator *() const { return (_node->data); }
	pointer operator ->() { return &(_node->data); }
	const_pointer operator ->() const { return &(_node->data); }

	T* base() const {return _node;};

	private:
		T* _node;
};

template <typename T>
class	const_tree_iterator
{
public:

	typedef T							value_type;
	typedef typename T::value_type    	pair;
	typedef const pair&					reference;
	typedef const pair*					pointer;
	typedef typename std::ptrdiff_t 	difference_type;

	const_tree_iterator(void) : _node(NULL) {}
	const_tree_iterator(T* other) : _node(other) {}
	const_tree_iterator(const const_tree_iterator &src) { *this = src; }
	const_tree_iterator(const tree_iterator<value_type> &src) { _node = src.base(); }

	virtual ~const_tree_iterator() {}

	const_tree_iterator &operator=(const_tree_iterator const &src) { _node = src._node; return (*this); }

	bool operator ==(T* const base) const { return (_node == base); }
	bool operator ==(const_tree_iterator const& b) const { return (_node == b._node); }
	bool operator !=(const_tree_iterator const& b) const { return (!(_node == b._node)); }

	const_tree_iterator& operator ++() { _node = _node_next(_node); return ((*this)); }
	const_tree_iterator operator ++(int)
	{
		T* tmp = _node;
		_node = _node_next(_node);
		return const_tree_iterator(tmp);
	}
	const_tree_iterator& operator --() { _node = _node_prev(_node); return ((*this)); }
	const_tree_iterator operator --(int)
	{
		T* tmp = _node;
		_node = _node_prev(_node);
		return const_tree_iterator(tmp);
	}

	reference operator *() const { return (_node->data); }
 	pointer operator ->() const { return &(_node->data); }

 	T* base() const {return _node;}

 	private:
 		T* _node;

};

	template <class Iterator>
    class tree_reverse_iterator
    {
        public:
            typedef Iterator							iterator_type;
            typedef typename Iterator::value_type		value_type;
            typedef typename Iterator::difference_type	difference_type;
            typedef typename Iterator::pointer			pointer;
            typedef typename Iterator::reference		reference;

            tree_reverse_iterator(): _elem() {}

            explicit tree_reverse_iterator (iterator_type it): _elem(it) {}

            template <class Iter>
            tree_reverse_iterator (const tree_reverse_iterator<Iter>& rev_it): _elem(rev_it.base()) {}

            virtual ~tree_reverse_iterator() {}

            iterator_type base() const { return (_elem); }
            reference operator*() const { iterator_type tmp = _elem; return (*(--tmp)); }
            tree_reverse_iterator operator+ (difference_type n) const { return (tree_reverse_iterator(_elem - n)); }
            tree_reverse_iterator& operator++() { --_elem; return (*this); }
            tree_reverse_iterator operator++(int)
            {
                tree_reverse_iterator tmp = *this;
                ++(*this);
                return (tmp);
            }
            tree_reverse_iterator& operator+= (difference_type n) { _elem -= n; return (*this); }
            tree_reverse_iterator operator- (difference_type n) const { return (tree_reverse_iterator(_elem + n)); }
            tree_reverse_iterator& operator--() { ++_elem; return (*this); }
            tree_reverse_iterator operator--(int)
            {
                tree_reverse_iterator tmp = *this;
                --(*this);
                return (tmp);
            }

            tree_reverse_iterator& operator-= (difference_type n) { _elem += n; return (*this); }
            pointer operator->() const { return &(operator*()); }
            reference operator[] (difference_type n) const { return (this->base()[-n - 1]); }

        private:
            iterator_type     _elem;
    };

	template <typename T>
    bool operator==(const ft::tree_iterator<T> lhs, const ft::tree_iterator<T> rhs)
    {
        return (lhs.operator*() == rhs.operator*());
    }

    template<typename T_L, typename T_R>
    bool operator==(const ft::tree_iterator<T_L> lhs, const ft::tree_iterator<T_R> rhs)
    {
        return (lhs.operator*() == rhs.operator*());
    }

    template <typename T>
    bool operator!=(const ft::tree_iterator<T> lhs, const ft::tree_iterator<T> rhs)
    {
        return (lhs.operator*() != rhs.operator*());
    }

    template<typename T_L, typename T_R>
    bool operator!=(const ft::tree_iterator<T_L> lhs, const ft::tree_iterator<T_R> rhs)
    {
        return (lhs.operator*() != rhs.operator*());
    }
}
