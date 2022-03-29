/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:36:17 by allanganoun       #+#    #+#             */
/*   Updated: 2022/03/29 23:37:08 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>
#include <memory>
#include <algorithm>
#include <iostream>
#include <limits>
//#include "reverse_iterator.hpp"
#include "tree_iterator.hpp"
#include "../vector.hpp"
#include "utils.hpp"

namespace ft
{
	template <class Value, class Key, class Compare, class Value_alloc = std::allocator<Value>
				, class Node = ft::_node<Value>, class Node_alloc = std::allocator<Node> >
	class tree
	{
	public :
		typedef Value											data_type;
		typedef Node_alloc										node_alloc;
		typedef Node											node_type;
		typedef Node *											node_pointer;
		typedef typename node_alloc::size_type					size_type;
		typedef ft::tree_iterator<node_type>					iterator;
		typedef ft::const_tree_iterator<node_type>				const_iterator;
		typedef ft::reverse_tree_iterator<node_type>			reverse_iterator;
		typedef ft::const_reverse_tree_iterator<node_type>		const_reverse_iterator;
		typedef typename Value_alloc::difference_type 			difference_type;

		tree(const node_alloc &alloc = node_alloc(), const Compare &comp = Compare() )
		: _end(NULL), _end_node(NULL), _root(NULL), _node_alloc(alloc), _comp(comp), _size(0)
		{

		}

		~tree()
		{
			if (_root != NULL)
				clear();
			_root = NULL;
			_end_node = NULL;
			_end = NULL;
			_size = 0;

		}

		node_pointer pre_organize_tree(node_pointer node)
		{
			if (_is_right_node(node) && node->left)
			{
				node->left->parent = node->parent;
				node->parent->right = node->left;
				node->left->right = node;
				node->parent = node->left;
				node->left = NULL;
				return (node->parent);
			}
			else if (_is_left_node(node) && node->right)
			{
				node->right->parent = node->parent;
				node->parent->left = node->right;
				node->right->left = node;
				node->parent = node->right;
				node->right = NULL;
				return (node->parent);
			}
			return node;
		}

		void organise_tree(node_pointer node)
		{
			node = pre_organize_tree(node);
			if (_is_right_node(node))
			{
				//std::cout << "ENTER = "<< node->data.first << std::endl;
				if (node->parent != _root)
				{
					if (_is_right_node(node->parent))	
						node->parent->parent->right = node;
					else if (_is_left_node(node->parent))	
						node->parent->parent->left = node;
				}
				node->left = node->parent;
				node->parent->right = NULL;
				node->parent = node->left->parent;
				node->left->parent = node;
			}
			else if (_is_left_node(node))
			{
				if (node->parent != _root)
				{
					if (_is_right_node(node->parent))	
						node->parent->parent->right = node;
					else if (_is_left_node(node->parent))	
						node->parent->parent->left = node;
				}
				node->right = node->parent;
				node->parent->left = NULL;
				node->parent = node->right->parent;
				node->right->parent = node;
			}
			if (node->parent == NULL)
				_root = node;
		}

		void check_tree()
		{
			node_pointer current = _node_min(_root);
			//int i = 0;
			while (current != NULL )
			{
				//std::cout << current->data.first << std::endl;
				if (!_check_node(current))
				{	
					//std::cout << "CHECK = " << current->data.first << std::endl;
					organise_tree(current);
					current = _node_min(_root);
					/*std::cout << "MIN = " << current->data.first << std::endl;
					std::cout << "MIN PARENT= " << current->parent->data.first << std::endl;
					std::cout << "ROOT = " << _root->data.first << std::endl;
					std::cout << "ROOT LEFT = " << _root->left->data.first << std::endl;
					if (_root->left->left != NULL)
						std::cout << "ROOT LEFT LEFT = " << _root->left->left->data.first << std::endl;
					if (_root->left->right != NULL)
						std::cout << "ROOT LEFT RIGHT = " << _root->left->right->data.first << std::endl;
					std::cout << "NEXT = " << _node_next(current)->data.first << std::endl;
					std::cout << "NEXT = " << _node_next(current)->data.first << std::endl;
					
					std::cout << "PARENT = " << current->parent->data.first << std::endl;
					if (current->parent->left != NULL)
						std::cout << "CHILD L = " << current->parent->left->data << std::endl;
					if (current->parent->right != NULL)
						std::cout << "CHILD R = " << current->parent->right->data << std::endl;*/
					//std::cout << "SURPRISE = " << current->right->data.first << std::endl;
				}
				else
					current = _node_next(current);
				//i++;
			}
		}

		pair<iterator,bool> insert(const data_type& val) // iterateur sur la valeur insérée + True pour dire valeur ajoutée ou false pour déjà éxistante
		{
			node_pointer new_node;
			node_pointer current;


			if (_root == NULL)
			{
				_end_node =_node_alloc.allocate(1);
				new_node = _node_alloc.allocate(1);
				_node_alloc.construct(new_node, Node(val));
				_node_alloc.construct(_end_node, Node());
				_root = new_node;
				_root->right = _end_node;
				_end_node->parent = _root;
				++_size;
				return (ft::make_pair(iterator(_root), true));
			}
			_end_node->parent->right = NULL;
			//_end_node->parent = NULL;
			current = _root;
			while (current != NULL)
			{

				if (_comp(val.first, current->data.first) && current->left != NULL)
					current = current->left;
				else if (current->data.first == val.first)
					return ft::make_pair(iterator(current), false);
				else if (_comp(current->data.first, val.first) && current->right != NULL)
					current = current->right;
				else
					break;
			}

			new_node = _node_alloc.allocate(1);
			if (this->_comp(current->data.first, val.first))
			{
				_node_alloc.construct(new_node, Node(val));
				current->right = new_node;
				new_node->parent = current;
			}
			else
			{
				_node_alloc.construct(new_node, Node(val));
				current->left = new_node;
				new_node->parent = current;
			}
			//if (val.first != '5')
				check_tree();
			/*else
			{
				std::cout << "verif " << new_node->data << std::endl;
				std::cout << "verif " << new_node->parent->data.first << std::endl;
				// std::cout << "verif " << new_node->parent->right << std::endl;
				std::cout << "verif " << new_node->parent->left->data.first << std::endl;
				std::cout << "verif " << new_node->parent->data << std::endl;
				//_verify_node(current);
			}*/
			_end_node->parent = _node_true_max(_root);
			(_node_true_max(_root))->right = _end_node;
			++_size;
			return ft::make_pair(iterator(new_node), true);
		}

		iterator insert (iterator position, const data_type& val)
		{
			(void)position;
			return(insert(val).first);
		}

		template <class InputIterator>
  		void insert (InputIterator first, InputIterator last)
		{
			for(InputIterator ite = first ; ite != last ; ite++)
				insert((*ite));
		}

		iterator begin()
		{
			if (_root)
				return iterator(_node_min(_root));
			return NULL;
		}

		const_iterator begin() const
		{
			if (_root)
				return const_iterator(_node_min(_root));
			return NULL;
		}

		iterator end()
		{
			if (_root)
				return iterator(_node_max(_root)->right);
			return NULL;
		}

		const_iterator end() const
		{
			if (_root)
				return const_iterator(_node_max(_root)->right);
			return NULL;
		}

		reverse_iterator rbegin()
		{
			if (_root)
				return reverse_iterator(_node_max(_root));
			return NULL;
		}

		reverse_iterator rend()
		{
			return reverse_iterator(_end);
		}

		const_reverse_iterator rbegin() const
		{
			if (_root)
				return const_reverse_iterator(_node_max(_root));
			return NULL;
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(_end);
		}

		size_type size() const
		{
			return _size;
		}

		bool empty() const
		{
			return size() == 0;
		}

		void clear()
		{
			erase(this->begin(), this->end());
		}

		iterator find(const Key& k)
		{
			node_pointer node = _node_min(_root);
			while (node != _end_node)
			{
				data_type &pair = node->data;
				if (pair.first == k)
					return iterator(node);
				node = _node_next(node);
			}
			return end();
		}

		const_iterator find(const Key& k) const
		{
			node_pointer node = _node_min(_root);
			while (node != _end_node)
			{
				data_type &pair = node->data;
				if (pair.first == k)
					return const_iterator(node);
				node = _node_next(node);
			}
			return end();
		}

		size_type count(const Key& k) const
		{
			if (this->find(k) != end())
				return 1;
			else
				return 0;
		}

		size_type erase(const Key& k)
		{
			node_pointer current = _node_min(_root);
			node_pointer next;

			while (current != _end_node && current->data.first != k)
			{
				current = _node_next(current);
				if (current == _end_node)
					return (0);
			}
			_end_node->parent->right = NULL;
			if (_node_is_root(current) && current->right)
			{
				//std::cout << "ROOT IS " << current->data.first << std::endl;
				//std::cout << "CHILD IS " << current->right->data.first << std::endl;
				//std::cout << "NEXT IS " << (_node_next(current))->data.first << std::endl;
				//std::cout << "MIN IS " << (_node_min(current->right))->data.first << std::endl;
				next = _node_next(current);
				if (_is_left_node(next))
				{
					next->right = current->right;
					current->right->parent = next;
					next->parent->left = NULL;
				}
				if (current->left)
				{
					next->left = current->left;
					current->left->parent = next;
				}
				next->parent = NULL;
				_root = next;
			}
			else if (_node_is_root(current) && _node_has_leaf(current))
			{
				//std::cout << "Delete " << current->data << std::endl;
				_node_alloc.destroy(current);
				_node_alloc.deallocate(current, 1);
				_node_alloc.destroy(_end_node);
				_node_alloc.deallocate(_end_node, 1);
				_size = 0;
				_root = NULL;
				_end_node = NULL;
				return (1);
			}
			else if (!_node_has_leaf(current)) // il faut reprendre ici
			{
				next = _node_next(current);
				if (_is_right_node(next))
					next->parent->right = NULL;
				else
					next->parent->left = NULL;
				if (_is_right_node(current))
					current->parent->right = next;
				else
					current->parent->left = next;
				next->parent = current->parent;
				if (current->right)
				{
					next->right = current->right;
					current->right->parent = next;
				}
				if (current->left)
				{
					next->left = current->left;
					current->left->parent = next;
				}
			}
			else
			{
				if (_is_left_node(current))
					current->parent->left = NULL;
				else if (_is_right_node(current))
					current->parent->right = NULL;
			}
			//std::cout << "Erase " << current->data << std::endl;
			_node_alloc.destroy(current);
			_node_alloc.deallocate(current, 1);
			_end_node->parent = _node_true_max(_root);
			(_node_true_max(_root))->right = _end_node;
			_size--;
			return (1);
		}

		void erase(iterator position) {
			erase(position->first);
		}

		void erase(iterator first, iterator last)
		{
			iterator one = first;
			iterator two = last;
			while (one != two)
			{	
				//std::cout << "ERASING = " << one->first << std::endl;
				erase((one++)->first);
			}
		}

		iterator lower_bound(const Key& k) // je ne suis pas sûr d'avoir bein compris ce que cette fonction fait
		{
			iterator ite = this->begin();
			while (ite != this->end() && _comp(ite->first, k))
				ite++;
			return (ite);
		}

		const_iterator lower_bound(const Key& k) const// je ne suis pas sûr d'avoir bein compris ce que cette fonction fait
		{
			const_iterator ite = this->begin();
			while (ite != this->end() && _comp(ite->first, k))
				ite++;
			return (ite);
		}

		iterator upper_bound(const Key& k) // je ne suis pas sûr d'avoir bein compris ce que cette fonction fait
		{
			iterator ite = this->begin();
			while (ite != this->end() && !(_comp(k, ite->first)))
				ite++;
			return (ite++); // pourquoi est ce que ++ite ne marche pas ?
		}

		const_iterator upper_bound(const Key& k) const// je ne suis pas sûr d'avoir bein compris ce que cette fonction fait
		{
			const_iterator ite = this->begin();
			while (ite != this->end() && !(_comp(k, ite->first)))
				ite++;
			return (ite++);
		}

		// TODO Verify
		size_type max_size() const {
			return Node_alloc().max_size();
		}

		Compare key_comp() const { return _comp ; }

		void swap(tree &tree) {
			std::swap(_start, tree._start);
			std::swap(_end, tree._end);
			std::swap(_root, tree._root);
			std::swap(_end_node, tree._end_node);
			std::swap(_node_alloc, tree._node_alloc);
			std::swap(_comp, tree._comp);
			std::swap(_size, tree._size);
		}
	
		node_pointer get_root() const { return _root ; }

	private :

		size_type _erase(const node_pointer current)
		{
			node_pointer next;

			if (!_node_has_leaf(current))
			{
				next = _node_next(current);
				if (next && current->parent)
				{
					if (_is_left_node(next))
						next->parent->left = NULL;
					else if (_is_right_node(next))
						next->parent->right = NULL;
					next->parent = current->parent;
				}
				else
					next->parent = NULL;

				if (current->left)
				{
					current->left->parent = next;
					next->left = current->left;
				}
				if (_is_left_node(current))
					current->parent->left = next;
				else if (current->parent)
					current->parent->right = next;
				if (_node_is_root(next))
					_root = next;
			}
			else if (_node_is_root(current) && _node_has_leaf(current))
			{
				//std::cout << "Clear1" << std::endl;
				_node_alloc.destroy(static_cast<node_type*>(current));
				_node_alloc.deallocate(static_cast<node_type*>(current), 1);
				_size = 0;
				_root = NULL;
				return (1);
			}
			else
			{
				if (_is_left_node(current))
					current->parent->left = NULL;
				else if (_is_right_node(current))
					current->parent->right = NULL;
			}
			//std::cout << "Clear2" << std::endl;
			_node_alloc.destroy(current);
			_node_alloc.deallocate(current, 1);
			_size--;
			return (1);
		}

		/**
		 * Based on https://stephane.glondu.net/projets/tipe/transparents.pdf#page=4
		 */
		void _rotateRight(node_pointer node)
		{
			node_pointer a = node->left;
			node_pointer b = node;
			node_pointer c = node->right;
			node_pointer d = node->parent;
			node_pointer e = node->parent->left;

			b->parent = d->parent;
			b->right = d;
			d->parent = b;
			d->left = c;
			c->parent = d;
		}

		void _rotateLeft(node_pointer node)
		{
			node_pointer a = node->parent->right;
			node_pointer b = node->parent;
			node_pointer c = node->left;
			node_pointer d = node;
			node_pointer e = node->right;

			d->parent = b->parent;
			d->left = b;
			b->parent = d;
			b->right = c;
			c->parent = b;
		}

		unsigned int _treeHeigh(node_pointer node)
		{
			unsigned int i = 0;
			node_pointer tempNode;
			do {
				tempNode = node;
				++i;
			} while (tempNode->parent);
			return i;
		}

	private :
		node_pointer _start;
		node_pointer _end;
		node_pointer _end_node;
		node_pointer _root;

		node_alloc	_node_alloc;
		Compare		_comp;
		size_type	_size;
	};
}
