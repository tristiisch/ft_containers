#pragma once

#include <iterator>
#include "./iterator_traits.hpp"
#include "pair.hpp"
#include "reverse_iterator.hpp"
#include <limits>
#include <algorithm>

// Algorithms used for the red black tree can be found here:
// * https://en.wikipedia.org/wiki/Red%E2%80%93black_tree
// * https://en.wikipedia.org/wiki/Tree_rotation
// * https://www.geeksforgeeks.org/c-program-red-black-tree-insertion/
// * https://www.geeksforgeeks.org/red-black-tree-set-3-delete-2/
// * https://www.programiz.com/dsa/deletion-from-a-red-black-tree

namespace ft {
enum COLOR {
	RED = false,
	BLACK = true
};

enum DIRECTION {
	LEFT = false,
	RIGHT = true
};

// Implementing these functions as template and not directly on classes
// ease the implementation for const and non const pointers.

template <class Node>
bool _node_parent_direction(Node node) {
	return node->parent->child[LEFT] == node ? LEFT : RIGHT;
}

template <class Node>
bool _node_is_black(Node node) {
	return node == NULL || node->color == BLACK;
}

template <class Node>
bool _node_has_leaf(Node node) {
	return node->child[LEFT] == NULL || node->child[RIGHT] == NULL;
}

template <class Node>
bool _node_has_red_child(Node node) {
	return !_node_is_black(node->child[LEFT]) || !_node_is_black(node->child[RIGHT]);
}

template <class Node>
Node _node_sibling(Node node) {
	return node->parent->child[!_node_parent_direction(node->parent)];
}

template <class Node>
Node _node_minimum(Node node) {
	while (node->child[LEFT] != NULL) {
		node = node->child[LEFT];
	}

	return node;
}

template <class Node>
Node _node_maximum(Node node) {
	while (node->child[RIGHT] != NULL) {
		node = node->child[RIGHT];
	}

	return node;
}

template <class Node>
Node _node_next(Node node) {
	if (node->child[RIGHT] != NULL) {
		return _node_minimum(node->child[RIGHT]);
	}

	while (_node_parent_direction(node) == RIGHT) {
		node = node->parent;
	}

	return node->parent;
}

template <class Node>
Node _node_prev(Node node) {
	if (node->child[LEFT] != NULL) {
		return _node_maximum(node->child[LEFT]);
	}

	while (_node_parent_direction(node) == LEFT) {
		node = node->parent;
	}

	return node->parent;
}

struct _node_base {
	_node_base *parent;
	_node_base *child[2];

	bool color;

	// Incredibly weird but this allow to have the same max_size as the STL.
	_node_base() : parent(0), color(RED) {
	}
};

// Implementation of a node having a value (which is a pair<key, mapped_type>).

template <class Value> struct _node : public _node_base {
	Value value;

	_node(const Value &value) : _node_base(), value(value) {
	}
};

template <class T> struct _tree_iterator {
	typedef std::bidirectional_iterator_tag iterator_category;
	typedef typename ft::iterator_traits<T*>::value_type value_type;
	typedef typename ft::iterator_traits<T*>::difference_type difference_type;
	typedef typename ft::iterator_traits<T*>::reference reference;
	typedef typename ft::iterator_traits<T*>::pointer pointer;

	_node_base *_ptr;

	_tree_iterator() : _ptr(0) {
	}

	explicit _tree_iterator(_node_base *node) : _ptr(node) {
	}

	_tree_iterator(const _tree_iterator &other) : _ptr(other._ptr) {
	}

	~_tree_iterator() {
	}

	_tree_iterator operator=(const _tree_iterator &other) {
		_ptr = other._ptr;
		return *this;
	}

	reference operator*() const {
		return static_cast<_node<T>*>(_ptr)->value;
	}

	pointer operator->() const {
		return &static_cast<_node<T>*>(_ptr)->value;
	}

	_tree_iterator &operator++() {
		_ptr = _node_next(_ptr);
		return *this;
	}

	_tree_iterator operator++(int) {
		_tree_iterator copy(*this);
		operator++();
		return copy;
	}

	_tree_iterator &operator--() {
		_ptr = _node_prev(_ptr);
		return *this;
	}

	_tree_iterator operator--(int) {
		_tree_iterator copy(*this);
		operator--();
		return copy;
	}

	bool operator==(const _tree_iterator &other) {
		return _ptr == other._ptr;
	}

	bool operator!=(const _tree_iterator &other) {
		return !operator==(other);
	}
};

template <class T> struct _tree_const_iterator {
	typedef std::bidirectional_iterator_tag iterator_category;
	typedef typename ft::iterator_traits<const T*>::value_type value_type;
	typedef typename ft::iterator_traits<const T*>::difference_type difference_type;
	typedef typename ft::iterator_traits<const T*>::reference reference;
	typedef typename ft::iterator_traits<const T*>::pointer pointer;

	const _node_base *_ptr;

	_tree_const_iterator() : _ptr() {
	}

	explicit _tree_const_iterator(const _node_base *node) : _ptr(node) {
	}

	_tree_const_iterator(const _tree_const_iterator &other) : _ptr(other._ptr) {
	}

	_tree_const_iterator(const _tree_iterator<T> &other) : _ptr(other._ptr) {
	}

	~_tree_const_iterator() {
	}

	_tree_const_iterator operator=(const _tree_const_iterator &other) {
		_ptr = other._ptr;
		return *this;
	}

	reference operator*() const {
		return static_cast<const _node<T>*>(_ptr)->value;
	}

	pointer operator->() const {
		return &static_cast<const _node<T>*>(_ptr)->value;
	}

	_tree_const_iterator &operator++() {
		_ptr = _node_next(_ptr);
		return *this;
	}

	_tree_const_iterator operator++(int) {
		_tree_const_iterator copy(*this);
		operator++();
		return copy;
	}

	_tree_const_iterator &operator--() {
		_ptr = _node_prev(_ptr);
		return *this;
	}

	_tree_const_iterator operator--(int) {
		_tree_const_iterator copy(*this);
		operator--();
		return copy;
	}

	bool operator==(const _tree_const_iterator &other) {
		return _ptr == other._ptr;
	}

	bool operator!=(const _tree_const_iterator &other) {
		return !operator==(other);
	}
};

template <class Value, class Compare, class Allocator> class _tree {
	public:
		typedef typename Value::first_type key_type;
		typedef Value value_type;
		typedef Compare key_compare;
		typedef _node<value_type> node_type;
		typedef typename Allocator::template rebind<node_type>::other allocator_type;

		typedef _tree_iterator<value_type> iterator;
		typedef _tree_const_iterator<value_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;

	private:
		key_compare _compare;
		allocator_type _allocator;

		size_type _node_count;

		_node_base *_begin_node;
		_node_base _end_node;


	public:
		explicit _tree(const key_compare &comp = key_compare(), const allocator_type &allocator = allocator_type())
			: _compare(comp), _allocator(allocator), _node_count(0), _begin_node(&_end_node), _end_node() {
			_end_node.color = RED;
			_end_node.child[LEFT] = NULL;
			_end_node.child[RIGHT] = NULL;
		}

		_tree(const _tree &other)
			: _compare(other._compare), _allocator(other._allocator), _node_count(0), _begin_node(&_end_node), _end_node() {
			_end_node.color = RED;
			_end_node.child[LEFT] = NULL;
			_end_node.child[RIGHT] = NULL;
			insert(other.begin(), other.end());
		}

		~_tree() {
			clear();
		}

		_tree& operator=(const _tree &other) {
			if (&other != this) {
				clear();
				insert(other.begin(), other.end());
			}

			return *this;
		}

		allocator_type get_allocator() const {
			return _allocator;
		}

		void swap(_tree &other) {
			std::swap(_compare, other._compare);
			std::swap(_allocator, other._allocator);
			std::swap(_node_count, other._node_count);
			std::swap(_begin_node, other._begin_node);
			std::swap(_end_node, other._end_node);

			// If empty update begin node otherwise update root's parent.
			if (empty()) {
				_begin_node = &_end_node;
			} else {
				_root()->parent = &_end_node;
			}

			// Do the same thing with the other tree.
			if (other.empty()) {
				other._begin_node = &other._end_node;
			} else {
				other._root()->parent = &other._end_node;
			}
		}

		key_compare key_comp() const {
			return _compare;
		}

		const_iterator lower_bound(const key_type &key) const {
			const node_type *node = static_cast<const node_type *>(_root());
			const _node_base * result = &_end_node;

			while (node != NULL) {
				bool direction = _compare(node->value.first, key) ? RIGHT : LEFT;

				if (direction == LEFT) {
					result = node;
				}

				node = static_cast<const node_type *>(node->child[direction]);
			}

			return const_iterator(result);

		}

		iterator lower_bound(const key_type &key) {
			return iterator(const_cast<_node_base*>(const_cast<const _tree*>(this)->lower_bound(key)._ptr));
		}

		const_iterator upper_bound(const key_type &key) const {
			const node_type *node = static_cast<const node_type *>(_root());
			const _node_base * result = &_end_node;

			while (node != NULL) {
				bool direction = _compare(key, node->value.first) ? LEFT : RIGHT;

				if (direction == LEFT) {
					result = node;
				}

				node = static_cast<const node_type *>(node->child[direction]);
			}

			return const_iterator(result);

		}

		iterator upper_bound(const key_type &key) {
			return iterator(const_cast<_node_base*>(const_cast<const _tree*>(this)->upper_bound(key)._ptr));
		}

		pair<const_iterator, const_iterator> equal_range(const key_type &key) const {
			const node_type *node = static_cast<const node_type *>(_root());
			const _node_base * result = &_end_node;

			while (node != NULL) {
				bool direction = _compare(key, node->value.first) ? LEFT : RIGHT;

				if (direction == LEFT) {
					result = node;
				}

				if (direction == RIGHT && !_compare(node->value.first, key)) {
					// If key is neither less nor greater we're in the equivalent case.
					return ft::make_pair(
						const_iterator(node),
						const_iterator(node->child[RIGHT] == NULL ? result : _node_minimum(node->child[RIGHT]))
					);
				}

				node = static_cast<const node_type*>(node->child[direction]);
			}

			return ft::make_pair(
				const_iterator(result),
				const_iterator(result)
			);
		}

		pair<iterator, iterator> equal_range(const key_type &key) {
			pair<const_iterator, const_iterator> iterators = const_cast<const _tree*>(this)->equal_range(key);

			return ft::make_pair(
				iterator(const_cast<_node_base *>(iterators.first._ptr)),
				iterator(const_cast<_node_base *>(iterators.second._ptr))
			);
		}

		pair<iterator, bool> insert(const value_type &value) {
			_node_base * parent;
			_node_base * &child = _find_equal(parent, value.first);

			if (child) {
				// If an equivalent node is already present in the tree do not create a new one.
				return ft::make_pair(iterator(child), false);
			}

			node_type *new_node = _allocator.allocate(1);

			try {
				_allocator.construct(new_node, value);
			} catch (...) {
				// If an exception happens during node's creation, deallocate memory.
				_allocator.deallocate(new_node, 1);
				throw;
			}

			_insert(parent, child, new_node);
			return ft::make_pair(iterator(new_node), true);
		}

		iterator insert(iterator hint, const value_type &value) {
			(void)hint;
			return insert(value).first;
		}

		template<class InputIter>
		void insert(InputIter first, InputIter last) {
			for (; first != last; first++) {
				insert(*first);
			}
		}

		iterator begin() {
			return iterator(_begin_node);
		}

		const_iterator begin() const {
			return const_iterator(_begin_node);
		}

		iterator end() {
			return iterator(&_end_node);
		}

		const_iterator end() const {
			return const_iterator(&_end_node);
		}

		reverse_iterator rbegin() {
			return reverse_iterator(end());
		}

		const_reverse_iterator rbegin() const {
			return const_reverse_iterator(end());
		}

		reverse_iterator rend() {
			return reverse_iterator(begin());
		}

		const_reverse_iterator rend() const {
			return const_reverse_iterator(begin());
		}

		void clear() {
			erase(begin(), end());
		}

		size_type size() const {
			return _node_count;
		}

		bool empty() const {
			return _node_count == 0;
		}

		size_type max_size() const {
			// The school's mac is using an implementation that takes the minimum between the max size of the allocator
			// and the maximum value of the difference_type.
			return std::min<size_type>(_allocator.max_size(), std::numeric_limits<difference_type>::max());
		}

		void erase(iterator pos) {
			if (pos == end()) return;

			_node_base * node = pos._ptr;

			if (_begin_node == node) {
				_begin_node = _node_next(node);
			}

			_erase(node);

			_allocator.destroy(static_cast<node_type*>(node));
			_allocator.deallocate(static_cast<node_type*>(node), 1);

			_node_count -= 1;
		}


		void erase(iterator first, iterator last) {
			while (first != last && first != end()) {
				erase(first++);
			}
		}

		const_iterator find(const key_type &key) const {
			const_iterator pos = lower_bound(key);

			if (pos != end() && !_compare(key, pos->first)) {
				return pos;
			}

			return end();
		}

		iterator find(const key_type &key) {
			return iterator(const_cast<_node_base*>(const_cast<const _tree *>(this)->find(key)._ptr));
		}

	private:
		void _rotate(_node_base *node, bool direction) {
			_node_base * pivot = node->child[!direction];

			node->child[!direction] = pivot->child[direction];

			if (node->child[!direction] != NULL) {
				node->child[!direction]->parent = node;
			}
			
			pivot->parent = node->parent;

			if (node->parent->child[LEFT] == node) {
				node->parent->child[LEFT] = pivot;
			} else {
				node->parent->child[RIGHT] = pivot;
			}

			pivot->child[direction] = node;
			node->parent = pivot;
		}

		void _insert_balance(_node_base *node) {
			_node_base *root = _root();

			node->color = node == root ? BLACK : RED;

			while (node != root && node->parent->color == RED) {
				bool direction = node->parent->parent->child[LEFT] == node->parent ? LEFT : RIGHT;

				_node_base * uncle = node->parent->parent->child[!direction];

				if (_node_is_black(uncle)) {
					if (node->parent->child[!direction] == node) {
						node = node->parent;
						_rotate(node, direction);
					}

					node->parent->color = BLACK;
					node = node->parent->parent;
					node->color = RED;
					_rotate(node, !direction);
					return;
				}

				node->parent->color = BLACK;
				node = node->parent->parent;
				node->color = node == root ? BLACK : RED;
				uncle->color = BLACK;
			}
		}

		void _insert(_node_base *parent, _node_base * & child, _node_base *new_node) {
			new_node->child[LEFT] = NULL;
			new_node->child[RIGHT] = NULL;
			new_node->parent = parent;
			child = new_node;

			// If the begin node has a left element (which could happen when we set `child`) update it
			// to points to the element the most at left.
			if (_begin_node->child[LEFT] != NULL) {
				_begin_node = _begin_node->child[LEFT];
			}

			_insert_balance(new_node);
			_node_count += 1;
		}

		_node_base * _root() {
			return _end_node.child[LEFT];
		}

		const _node_base * _root() const {
			return _end_node.child[LEFT];
		}

		_node_base * &_find_equal(_node_base * &parent, const key_type &key) {
			node_type * node = static_cast<node_type *>(_root());

			if (node == NULL) {
				parent = &_end_node;
				return parent->child[LEFT];
			}

			while (true) {
				bool less = _compare(key, node->value.first);
				bool direction = less ? LEFT : RIGHT;

				if (!less && !_compare(node->value.first, key)) {
					// If the key is not less nor greater than the node's key
					// They are equivalent.

					parent = static_cast<node_type *>(node);
					return parent;
				}

				if (node->child[direction] == NULL) {
					// We reached a leaf node.

					parent = static_cast<_node_base *>(node);
					return parent->child[direction];
				}

				node = static_cast<node_type *>(node->child[direction]);
			}
		}

		void _erase(_node_base *to_erase) {
			_node_base* root = _root();
			_node_base* hole = _node_has_leaf(to_erase) ? to_erase : _node_next(to_erase);
			_node_base* x = hole->child[LEFT] != NULL ? hole->child[LEFT] : hole->child[RIGHT];
			_node_base* y = NULL;

			if (x != NULL) {
				x->parent = hole->parent;
			}

			bool direction = _node_parent_direction(hole);

			hole->parent->child[direction] = x;

			if (hole == root) {
				root = x;
			} else {
				y = hole->parent->child[!direction];
			}

			bool removed_black = hole->color == BLACK;

			if (hole != to_erase) {
				hole->parent = to_erase->parent;

				hole->parent->child[_node_parent_direction(to_erase)] = hole;

				hole->child[LEFT] = to_erase->child[LEFT];
				hole->child[LEFT]->parent = hole;
				hole->child[RIGHT] = to_erase->child[RIGHT];

				if (hole->child[RIGHT] != NULL) {
					hole->child[RIGHT]->parent = hole;
				}

				hole->color = to_erase->color;

				if (root == to_erase) {
					root = hole;
				}
			}

			if (removed_black && root != NULL) {
				if (x != NULL) {
					x->color = BLACK;
					return;
				}

				while (true) {
					bool direction = _node_parent_direction(y);

					if (y->color == RED) {
						y->color = BLACK;
						y->parent->color = RED;
						_rotate(y->parent, !direction);

						if (root == y->child[!direction]) {
							root = y;
						}

						y = y->child[!direction]->child[direction];
					}

					if (_node_has_red_child(y)) {
						if (_node_is_black(y->child[direction])) {
							y->child[!direction]->color = BLACK;
							y->color = RED;
							_rotate(y, direction);
							y = y->parent;
						}

						y->color = y->parent->color;
						y->parent->color = BLACK;
						y->child[direction]->color = BLACK;
						_rotate(y->parent, !direction);
						return;
					}

					y->color = RED;
					x = y->parent;

					if (x == root || x->color == RED) {
						x->color = BLACK;
						return;
					}

					y = _node_sibling(x);
				}
			}
		}
};
}
