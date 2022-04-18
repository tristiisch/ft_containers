/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alganoun <alganoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:36:17 by allanganoun       #+#    #+#             */
/*   Updated: 2022/04/18 15:17:47 by alganoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>
#include <memory>
#include <algorithm>
#include <iostream>
#include <limits>
#include "iterator.hpp"
#include "tree_iterator.hpp"
#include "../vector.hpp"
#include "utils.hpp"

namespace ft
{
	template <class Value, class Key, class Compare, class Allocator, class Value_alloc = std::allocator<Value>
				, class Node = ft::_node<Value> >
	class tree
	{
	public :
		typedef Value													data_type;
		typedef typename Allocator::template rebind<Node>::other		node_alloc;
		typedef Node													node_type;
		typedef Node *													node_pointer;
		typedef typename node_alloc::size_type							size_type;
		typedef ft::tree_iterator<node_type>							iterator;
		typedef ft::const_tree_iterator<node_type>						const_iterator;
		typedef typename Value_alloc::difference_type 					difference_type;

		tree(const node_alloc &alloc = node_alloc(), const Compare &comp = Compare() )
		: _end(NULL), _end_node(NULL), _root(NULL), _node_alloc(alloc), _comp(comp), _size(0)
		{
			_end_node =_node_alloc.allocate(1);
			_node_alloc.construct(_end_node, Node());
			_root  = _end_node;
		}

		~tree()
		{
			if (_root != NULL)
				clear();
			_root = NULL;
			_end = NULL;
			_size = 0;
			_node_alloc.destroy(_end_node);
			_node_alloc.deallocate(_end_node, 1);

		}


		iterator insert (const data_type& val)
		{
			if (_root != _end_node)
				_end_node->parent->right = NULL;
			insert2(NULL, _root, val);
			_end_node->parent = _node_true_max(_root);
			(_node_true_max(_root))->right = _end_node;
			return this->find(val.first);
		}

		node_pointer insert2(node_pointer parent, node_pointer new_node, const data_type& val)
		{
			if (new_node == NULL || new_node == _end_node)
			{
				new_node = _node_alloc.allocate(1);
				_node_alloc.construct(new_node, Node(val));
				new_node->parent = parent;
				if (_root == _end_node)
					_root = new_node;
				++_size;
				return (new_node);
			}
			if (_comp(val.first, new_node->data.first))
				new_node->left = insert2(new_node, new_node->left, val);
			else if (_comp(new_node->data.first,  val.first))
				new_node->right = insert2(new_node, new_node->right, val);
			else
				return new_node;

			new_node->height = 1 + max(_node_height(new_node->left), _node_height(new_node->right));
			int balance = _node_balance(new_node);

			if (balance > 1 && _comp(val.first, new_node->left->data.first))
				return (_node_rotate_R(new_node));
			if (balance < -1 && _comp(new_node->right->data.first, val.first))
				return _node_rotate_L(new_node);
			if (balance > 1 && _comp(new_node->left->data.first, val.first))
			{
				new_node->left = _node_rotate_L(new_node->left);
				return (_node_rotate_R(new_node));
			}
			if (balance < -1 && _comp(val.first, new_node->right->data.first))
			{
				new_node->right = _node_rotate_R(new_node->right);
				return _node_rotate_L(new_node);
			}
			return (new_node);
		}


		iterator insert (iterator position, const data_type& val)
		{
			(void)position;
			return(iterator(insert(val)));
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
				return iterator(_end_node);
			return NULL;
		}

		const_iterator end() const
		{
			if (_root)
				return const_iterator(_end_node);
			return NULL;
		}

		size_type size() const { return _size; }

		bool empty() const { return size() == 0; }

		void clear(){ erase(this->begin(), this->end()); }

		iterator find(const Key& k)
		{
			iterator pos = lower_bound(k);

			if (pos != end() && !_comp(k, pos->first))
				return pos;
			return end();
		}

		const_iterator find(const Key &k) const {
			const_iterator pos = lower_bound(k);

			if (pos != end() && !_comp(k, pos->first))
				return pos;
			return end();
		}

		size_type count(const Key& k) const
		{
			if (this->find(k) != end())
				return 1;
			else
				return 0;
		}

		node_pointer _node_rotate_R(node_pointer node)
		{
			node_pointer x =  node->left;
			node_pointer t2 = x->right;


			x->right = node;
			x->parent = node->parent;
			node->parent = x;
			node->left = t2;
			if(t2)
				t2->parent = node;
			node->height = max(_node_height(node->left), _node_height(node->right)) + 1;
			x->height = max(_node_height(x->left), _node_height(x->right)) + 1;
			if(_root == node)
				_root = x;
			return x;
		}

		node_pointer _node_rotate_L(node_pointer node)
		{
			node_pointer x =  node->right;
			node_pointer t2 = x->left;


			x->left = node;
			x->parent = node->parent;
			node->parent = x;
			node->right = t2;
			if(t2)
				t2->parent = node;
			node->height = max(_node_height(node->left), _node_height(node->right)) + 1;
			x->height = max(_node_height(x->left), _node_height(x->right)) + 1;
			if(_root == node)
				_root = x;
			return x;
		}

		void erase(const Key& k)
		{
			if (_root != _end_node)
			{
				_end_node->parent->right = NULL;
				_end_node->parent = NULL;
			}
			erase2(_root, k);
			if (_root != _end_node)
			{
				_end_node->parent = _node_true_max(_root);
				(_node_true_max(_root))->right = _end_node;
			}
		}

		node_pointer erase2(node_pointer to_delete, const Key &k)
		{
			if (to_delete == NULL)
		        return to_delete;
		    if ( k < to_delete->data.first )
		        to_delete->left = erase2(to_delete->left, k);
		    else if( k > to_delete->data.first )
		        to_delete->right = erase2(to_delete->right, k);
		    else
		    {
		        if( (to_delete->left == NULL) || (to_delete->right == NULL))
		        {
		            node_pointer temp = to_delete->left ? to_delete->left : to_delete->right;

					if (temp == NULL)
					{
						if (to_delete == _root)
							_root = _end_node;
							if (_is_right_node(to_delete))
								to_delete->parent->right = NULL;
							else if (_is_left_node(to_delete))
								to_delete->parent->left = NULL;
						temp = to_delete;
						to_delete = NULL;
					}
					else
					{
						if (_is_left_node(temp))
							to_delete->left = NULL;
						if (_is_right_node(temp))
							to_delete->right = NULL;
						temp->parent = to_delete->parent;
						if (_is_left_node(to_delete))
							to_delete->parent->left = temp;
						else if (_is_right_node(to_delete))
							to_delete->parent->right = temp;
						temp->right = to_delete->right;
						temp->left = to_delete->left;
						temp->height = to_delete->height;
						if (to_delete == _root)
							_root = temp;
						node_pointer temp2 = temp;
						temp = to_delete;
						to_delete = temp2;
						temp2 = NULL;
					}
					_node_alloc.destroy(temp);
					_node_alloc.deallocate(temp, 1);
					_size--;
		        }
		        else
		        {
					Node* temp = _node_min(to_delete->right);
					int is_root = 0;
					if (to_delete == _root)
						is_root = 1;
					_node_alloc.construct(to_delete, Node(temp->data,
							to_delete->parent, to_delete->right, to_delete->left, to_delete->height));
					if (is_root == 1)
						_root = to_delete;
					to_delete->right = erase2(to_delete->right, temp->data.first);
				}
			}
			if (to_delete == NULL)
				return to_delete;
			to_delete->height = 1 + max(_node_height(to_delete->left),
					_node_height(to_delete->right));

			int balance = _node_balance(to_delete);

			// Left Left Case
			if (balance > 1 && _node_balance(to_delete->left) >= 0)
				return _node_rotate_R(to_delete);
			// Left Right Case
			if (balance > 1 && _node_balance(to_delete->left) < 0)
			{
				to_delete->left = _node_rotate_L(to_delete->left);
				return _node_rotate_R(to_delete);
			}
			// Right Right Case
			if (balance < -1 && _node_balance(to_delete->right) <= 0)
				return _node_rotate_L(to_delete);
			// Right Left Case
			if (balance < -1 && _node_balance(to_delete->right) > 0)
			{
				to_delete->right = _node_rotate_R(to_delete->right);
				return _node_rotate_L(to_delete);
			}
			return to_delete;
		}

		void erase(iterator position) {
			(void)position;
			erase(position->first);
		}

		void erase(iterator first, iterator last)
		{
			while (first != last)
				erase(first++);
		}

		iterator lower_bound(const Key& k)
		{
			iterator ite = this->begin();
			while (ite != this->end() && _comp(ite->first, k))
				ite++;
			return (ite);
		}

		const_iterator lower_bound(const Key& k) const
		{
			const_iterator ite = this->begin();
			while (ite != this->end() && _comp(ite->first, k))
				ite++;
			return (ite);
		}

		iterator upper_bound(const Key& k)
		{
			iterator ite = this->begin();
			while (ite != this->end() && !(_comp(k, ite->first)))
				ite++;
			return (ite++);
		}

		const_iterator upper_bound(const Key& k) const
		{
			const_iterator ite = this->begin();
			while (ite != this->end() && !(_comp(k, ite->first)))
				ite++;
			return (ite++);
		}

		size_type max_size() const {
			return node_alloc().max_size();
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
		node_pointer _start;
		node_pointer _end;
		node_pointer _end_node;
		node_pointer _root;

		node_alloc	_node_alloc;
		Compare		_comp;
		size_type	_size;
	};
}
