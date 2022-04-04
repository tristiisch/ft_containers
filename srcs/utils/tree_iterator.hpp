/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:34:39 by alganoun          #+#    #+#             */
/*   Updated: 2022/04/04 02:01:25 by allanganoun      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


// ICI IL FAUT ENCORE FAIRE LES AUTRES ITERATEURS
#pragma once

#include <cstddef>
#include "pair.hpp"
#include "iterator.hpp"
#include <iostream>
#include <memory>
#include <algorithm>
#include <cstddef>

//fonction pour calculer les incrementations

# define LEFT	true
# define RIGHT	false

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
		_node							*to_have_same_max_size;

		_node()
		:	data(),
			parent(NULL),
			right(NULL),
			left(NULL)
		{

		}
		_node(Value const &v)
		:	data(v),
			parent(NULL),
			right(NULL),
			left(NULL)
		{
		};

		_node(Value const & v, _node *parent, _node *right, _node *left)
		:	data(v),
			parent(parent),
			right(right),
			left(left)
		{

		}

		~_node()
		{

		}

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

	// BOOLEANS : pas besoin dans ce cas
	bool operator ==(T* const base) const { return (_node == base); }
	bool operator ==(tree_iterator const& b) const { return (_node == b._node); }
	bool operator !=(tree_iterator const& b) const { return (!(_node == b._node)); }
	//bool operator >(tree_iterator const& b) const { return (_node > b._node); };
	//bool operator <(tree_iterator const& b) const { return (key_compare(_node, b._node)); };
	//bool operator >=(tree_iterator const& b) const { return (_node >= b._node); };
	//bool operator <=(tree_iterator const& b) const { return (_node <= b._node); };


	// INCREMENTERS
	tree_iterator& operator ++() { _node = _node_next(_node); return ((*this)); }			// ++a //
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

	//DEREFERENCING & ADDRESS STUFF
	reference operator *() { return (_node->data); }											// *a
	const_reference operator *() const { return (_node->data); }								// *a
	pointer operator ->() { return &(_node->data); }											// a->b
	pointer operator ->() const { return &(_node->data); }											// a->b

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

	// BOOLEANS : pas besoin dans ce cas
	bool operator ==(T* const base) const { return (_node == base); }
	bool operator ==(const_tree_iterator const& b) const { return (_node == b._node); }
	bool operator !=(const_tree_iterator const& b) const { return (!(_node == b._node)); }

	// INCREMENTERS
	const_tree_iterator& operator ++() { _node = _node_next(_node); return ((*this)); }			// ++a
	const_tree_iterator operator ++(int) 														// a++
	{
		T* tmp = _node;
		_node = _node_next(_node);
		return const_tree_iterator(tmp);
	}
	const_tree_iterator& operator --() { _node = _node_prev(_node); return ((*this)); }			// --a
	const_tree_iterator operator --(int)														// a--
	{
		T* tmp = _node;
		_node = _node_prev(_node);
		return const_tree_iterator(tmp);
	}

	reference operator *() const { return (_node->data); }								// *a
 	pointer operator ->() const { return &(_node->data); }

 	T* base() const {return _node;};									// a->b

 	private:
 		T* _node;

};

	template <class Iterator>
    class tree_reverse_iterator
    {
        public:
            typedef Iterator    iterator_type;
            typedef typename Iterator::value_type      value_type;
            typedef typename Iterator::difference_type     difference_type;
            typedef typename Iterator::pointer				pointer;

            typedef typename Iterator::reference   reference;

            tree_reverse_iterator(): _elem() {}


            explicit tree_reverse_iterator (iterator_type it)
            :
                _elem(it)
            {}

            template <class Iter>
                tree_reverse_iterator (const tree_reverse_iterator<Iter>& rev_it)
                :
                    _elem(rev_it.base())
                {}

            virtual ~tree_reverse_iterator() {}

            iterator_type base() const
            { return (_elem); }

            reference operator*() const
            {
                iterator_type tmp = _elem;
                return (*(--tmp));
            }

            tree_reverse_iterator operator+ (difference_type n) const { return (tree_reverse_iterator(_elem - n)); }

            tree_reverse_iterator& operator++()
            {
                --_elem;
                return (*this);
            }

            tree_reverse_iterator operator++(int)
            {
                tree_reverse_iterator tmp = *this;
                ++(*this);
                return (tmp);
            }

            tree_reverse_iterator& operator+= (difference_type n)
            {
                _elem -= n;
                return (*this);
            }

            tree_reverse_iterator operator- (difference_type n) const { return (tree_reverse_iterator(_elem + n)); }

            tree_reverse_iterator& operator--()
            {
                ++_elem;
                return (*this);
            }

            tree_reverse_iterator operator--(int)
            {
                tree_reverse_iterator tmp = *this;
                --(*this);
                return (tmp);
            }

            tree_reverse_iterator& operator-= (difference_type n)
            {
                _elem += n;
                return (*this);
            }

            pointer operator->() const { return &(operator*()); }

            reference operator[] (difference_type n) const { return (this->base()[-n - 1]); }

        private:
            iterator_type     _elem;
    };
}

template <typename T>
std::ostream &operator<<(std::ostream &outputFile, ft::_node<T> &node)
{
	outputFile << node->first << "=" << node->second;
	return outputFile;
}

template <typename T, typename U>
std::ostream &operator<<(std::ostream &outputFile, ft::pair<T, U> &pair)
{
	outputFile << pair.first << "=" << pair.second;
	return outputFile;
}

template <class Node>
bool _verify_node(Node node)
{
	if (node && node->parent)
	{
		if (_is_right_node(node) && node->parent->right != node)
		{
			std::cerr << "\033[0;31mNode " << node->data << " error verify : parent not linked correctly\033[0m" << std::endl;
			std::cerr << "\033[0;31mNode parent " << node->parent->data << " has not this node in right (has " << node->parent->right->data << ")\033[0m" << std::endl;
			exit(1);
		}
		else if (_is_left_node(node) && node->parent->left != node)
		{
			std::cerr << "\033[0;31mNode " << node->data << " error verify : parent not linked correctly\033[0m" << std::endl;
			std::cerr << "\033[0;31mNode parent " << node->parent->data << " has not this node in left (has " << node->parent->left->data << ")\033[0m" << std::endl;
			exit(1);
			return false;
		}
	}
	if (node->right && node->right->parent != NULL && node->right->parent != node)
	{
		std::cerr << "\033[0;31mNode " << node->data << " error verify : right not linked correctly\033[0m" << std::endl;
		if (node->right->parent)
			std::cerr << "\033[0;31mNode child right " << node->right->data << " has not this node in right (has " << node->right->parent->data << ")\033[0m" << std::endl;
		exit(1);
		return false;
	}
	if (node->left && node->left->parent != NULL && node->left->parent != node)
	{
		std::cerr << "\033[0;31mNode " << node->data << " error verify : left not linked correctly\033[0m" << std::endl;
		exit(1);
		return false;
	}
	return true;
}
