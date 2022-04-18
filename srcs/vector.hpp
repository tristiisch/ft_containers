/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 17:48:15 by tglory            #+#    #+#             */
/*   Updated: 2022/04/18 21:30:28 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <algorithm>
# include <cstddef>
# include "./utils/utils.hpp"
# include "./utils/iterator.hpp"
# include "./utils/reverse_iterator.hpp"

namespace ft
{
	template<typename T, typename Allocator = std::allocator<T> >
	class vector
	{
	public:
		typedef T												value_type;
		typedef Allocator										allocator_type;
		typedef typename allocator_type::size_type				size_type;
		typedef typename allocator_type::difference_type		difference_type;
		typedef	typename allocator_type::reference				reference;
		typedef	typename allocator_type::const_reference		const_reference;
		typedef typename allocator_type::pointer				pointer;
		typedef typename allocator_type::const_pointer			const_pointer;

		typedef ft::iterator<value_type>						iterator;
		typedef ft::iterator<const value_type>					const_iterator;
		typedef ft::reverse_iterator<iterator>					reverse_iterator;
		typedef	ft::reverse_iterator<const_iterator>			const_reverse_iterator;

		explicit vector(const allocator_type& alloc = allocator_type())
		:	_alloc(alloc),
			_start(NULL),
			_end(NULL),
			_end_capacity(NULL)
		{};

		explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
		:	_alloc(alloc),
			_start(NULL),
			_end(NULL),
			_end_capacity(NULL)
		{
			_start = _alloc.allocate(n);
			_end = _start;
			_end_capacity = _start + n;
			for (; n > 0; --n)
				_alloc.construct(_end++, val);
		}

		template<class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
		:	_alloc(alloc),
			_start(NULL),
			_end(NULL),
			_end_capacity(NULL)
		{
			size_t size = 0;
			InputIterator i = first;
			while (i != last)
			{
				i++;
				size++;
			}
			_start = _alloc.allocate(size);
			_end = _start;
			_end_capacity = _start + size;
			for (; size > 0; --size)
				_alloc.construct(_end++, *(first++));
		}

		vector(const vector& x)
		:	_alloc(x.get_allocator()),
			_start(NULL),
			_end(NULL),
			_end_capacity(NULL)
		{
			this->insert(this->begin(), x.begin(), x.end());
		}

		~vector()
		{
			_alloc.deallocate(_start, this->capacity());
		}

		vector &operator=(const vector& x)
		{
			if (x != *this)
			{
				if (!this->empty())
					this->clear();
				this->insert(this->end(), x.begin(), x.end());
			}
			return (*this);
		}

		iterator erase(iterator position)
		{
			pointer p_pos = &(*position);
			_alloc.destroy(&(*position));
			if (&(*position) + 1 == _end)
				_alloc.destroy(&(*position));
			else
			{
				for (int i = 0; i < _end - &(*position) - 1; ++i)
				{
					_alloc.construct(&(*position) + i, *(&(*position) + i + 1));
					_alloc.destroy(&(*position) + i + 1);
				}
			}
			_end -= 1;
			return (iterator(p_pos));
		}

		iterator erase(iterator first, iterator last)
		{
			pointer p_first = &(*first);
			for (; &(*first) != &(*last); ++first)
				_alloc.destroy(&(*first));
			for (int i = 0; i < _end - &(*last); ++i)
			{
				_alloc.construct(p_first + i, *(&(*last) + i));
				_alloc.destroy(&(*last) + i);
			}
			_end -= (&(*last) - p_first);
			return (iterator(p_first));
		}

		iterator begin()
		{
			return _start;
		}

		const_iterator begin() const
		{
			return _start;
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(_end);
		}

		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(_end);
		}

		iterator end()
		{
			if (this->empty() == false)
				return _end;
			else
				return _start;
		}

		const_iterator end() const
		{
			if (this->empty() == false)
				return _end;
			else
				return _start;
		}

		reverse_iterator rend()
		{
			if (this->empty() == false)
				return reverse_iterator(_start);
			else
				return reverse_iterator(_start);
		}

		const_reverse_iterator rend() const
		{
			if (this->empty() == false)
				return const_reverse_iterator(_start);
			else
				return const_reverse_iterator(_start);
		}

		size_type size() const
		{
			return _end - _start;
		}

		reference front()
		{
			return (*_start);
		}
		const_reference front() const
		{
			return (*_start);
		}

		reference back()
		{
			return *(_end - 1);
		}

		const_reference back() const
		{
			return *(_end - 1);
		}

		size_type max_size() const
		{
			return allocator_type().max_size();
		}

		void resize(size_type n, value_type val = value_type())
		{
			if (n < this->size())
			{
				while (this->size() > n)
				{
					--_end;
					_alloc.destroy(_end);
				}
			}
			else if (n > this->size())
			{
				reserve(n);
				this->insert(this->end(), n - this->size(), val);
			}
		}

		void push_back(const value_type& value)
		{
			if (_end == _end_capacity)
			{
				int next_capacity = (this->size() > 0) ? this->size() * 2 : 1;
				this->reserve(next_capacity);
			}
			_alloc.construct(_end++, value);
		}

		void pop_back()
		{
			_alloc.destroy(_end--);
		}

		void reserve(size_type new_cap)
		{
			if (new_cap > this->max_size())
				throw std::length_error("vector::reserve > new capacity greater than max size");
			else if (new_cap > this->capacity())
			{
				pointer prev_start = _start;
				pointer prev_end = _end;
				size_type prev_size = this->size();
				size_type prev_capacity = this->capacity();

				_start = _alloc.allocate(new_cap);
				_end_capacity = _start + new_cap;
				_end = _start;
				while (prev_start != prev_end)
					_alloc.construct(_end++, *prev_start++);
				_alloc.deallocate(prev_start - prev_size, prev_capacity);
			}
		}

		iterator insert(iterator pos, const value_type& value)
		{
			size_type posIndex = pos - _start;
			if (size_type(_end_capacity - _end) >= 1)
			{
				for (size_type i = 0; i < this->size() - posIndex; ++i)
					_alloc.construct(_end - i, *(_end - i - 1));
				_alloc.construct(&(*pos), value);
				_end++;
			}
			else
			{
				 int newCapacity;
				newCapacity = (this->size() * 2 > 0) ? this->size() * 2 : 1;
				pointer newStart = _alloc.allocate(newCapacity);
				pointer newEnd = newStart + this->size() + 1;
				pointer newEndCapacity = newStart + newCapacity;
				for (size_type i = 0; i < posIndex; ++i)
					_alloc.construct(newStart + i, *(_start + i));

				_alloc.construct(newStart + posIndex, value);

				for (size_type i = 0; i < this->size() - posIndex; ++i)
					_alloc.construct(newEnd - i - 1, *(_end - i - 1));
				for (size_type i = 0; i < this->size(); ++i)
					_alloc.destroy(_start + i);
				if (_start)
					_alloc.deallocate(_start, this->capacity());

				this->_start = newStart;
				this->_end = newEnd;
				this->_end_capacity = newEndCapacity;
			}
			return (iterator(_start + posIndex));
		}

		void insert(iterator position, size_type n, const value_type& val)
		{
			size_type posIndex = position - _start;
			if (size_type(_end_capacity - _end) >= n)
			{
				for (size_type i = 0; i < this->size() - posIndex; ++i)
					_alloc.construct(_end + (n - 1) - i, *(_end - i - 1));
				for (size_type i = 0 ; i < n ; ++i)
					_alloc.construct(&(*position) + i, val);
				_end = _end + n;
			}
			else
			{
				int new_cap = n;
				if (this->size() > 1)
					new_cap = this->size() * 2;
				pointer new_start;
				pointer new_endcap;
				pointer new_end;

				if ((this->size() * 2) >= (this->size() + n))
				{
					new_start = _alloc.allocate(new_cap);
					new_end = new_start + this->size() + n;
					new_endcap = new_start + new_cap;
				}
				else
				{
					new_cap = this->size() + n;
					new_start = _alloc.allocate(new_cap);
					new_end = new_start + this->size() + n;
					new_endcap = new_start + new_cap;
				}
				for (size_type i = 0; i < posIndex; ++i)
					_alloc.construct(new_start + i, *(_start + i));
				for (size_type i = 0 ; i < n ; ++i)
					_alloc.construct(new_start + posIndex + i, val);
				for (size_type i = 0 ; i < this->size() - posIndex ; ++i)
					_alloc.construct(new_end - i - 1, *(_end - i - 1));
				for (size_type i = 0; i < this->size(); ++i)
					_alloc.destroy(_start + i);
				if (_start)
					_alloc.deallocate(_start, this->capacity());
				_start = new_start;
				_end = new_end;
				_end_capacity = new_endcap;
			}
		}

		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
		{
			size_type dist = ft::distance(first, last);
			if (size_type(_end_capacity - _end) >= dist)
			{
				for (size_type i = 0; i < this->size() - (&(*position) - _start); ++i)
					_alloc.construct(_end - i + (dist - 1), *(_end - i - 1));
				_end += dist;
				for (; &(*first) != &(*last); ++first, ++position)
					_alloc.construct(&(*position), *first);
			}
			else
			{
				pointer newStart, newEnd, newEndCapacity;

				if (this->size() + dist >= this->size() * 2)
				{
					newStart = _alloc.allocate(this->size() + dist);
					newEnd = newStart + this->size() + dist;
					newEndCapacity = newEnd;
				}
				else
				{
					newStart = _alloc.allocate(this->size() * 2);
					newEnd = newStart + this->size() + dist;
					newEndCapacity = newStart + (this->size() * 2);
				}
				for (int i = 0; i < &(*position) - _start; ++i)
					_alloc.construct(newStart + i, *(_start + i));
				for (int i = 0; &(*first) != &(*last); ++first, ++i)
					_alloc.construct(newStart + (&(*position) - _start) + i, *first);
				for (size_type i = 0; i < this->size() - (&(*position) - _start); ++i)
					_alloc.construct(newStart + (&(*position) - _start) + dist + i, *(_start + (&(*position) - _start) + i));
				for (size_type i = 0; i < this->size(); ++i)
					_alloc.destroy(_start + i);
				_alloc.deallocate(_start, this->capacity());
				_start = newStart;
				_end = newEnd;
				_end_capacity = newEndCapacity;
			}
		}

		void assign(size_t n, const value_type& val)
		{
			this->clear();
			this->insert(this->begin(), n, val);
		}

		template<class InputIterator>
  		void assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL) // il faut vérifier que ce truc marche comme prévu
		{
			this->clear();
			this->insert(this->begin(), first, last);
		}

		void swap(vector& x)
		{
			allocator_type save_alloc;
			pointer save_start;
			pointer	save_end;
			pointer save_endcap;

			save_alloc = x._alloc;
			save_start = x._start;
			save_end = x._end;
			save_endcap = x._end_capacity;

			x._alloc = this->_alloc;
			x._start = this->_start;
			x._end = this->_end;
			x._end_capacity = this->_end_capacity;

			this->_alloc = save_alloc;
			this->_start = save_start;
			this->_end = save_end;
			this->_end_capacity = save_endcap;
		}

		void clear()
		{
			for (; _start != _end; --_end)
				_alloc.destroy(_end);
		}

		reference operator[](size_type n)
		{
			return *(_start + n);
		}

		const_reference operator[](size_type n) const
		{
			return *(_start + n);
		}

		reference at(size_type n)
		{
			if (n >= size())
				throw std::out_of_range("vector");
			return *(_start + n);
		}

		const_reference at(size_type n) const
		{
			if (n >= size())
				throw std::out_of_range("vector");
			return *(_start + n);
		}

		allocator_type get_allocator() const
		{
			return _alloc;
		}

		size_type capacity() const
		{
			return _end_capacity - _start;
		}

		bool empty() const
		{
			if (this->size() == 0)
				return (true);
			else
				return (false);
		}

	private:
		allocator_type	_alloc;
		pointer			_start;
		pointer			_end;
		pointer			_end_capacity;
	};

	template<class T, class Alloc>
	bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		if (lhs.size() && rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()) != false)
			return lhs.size() == rhs.size();
		return false;
	}

	template<class T, class Alloc>
	bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return !(lhs == rhs);
	}

	template<class T, class Alloc>
	bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template<class T, class Alloc>
	bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return !(lhs > rhs);
	}

	template<class T, class Alloc>
	bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
		return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
	}

	template<class T, class Alloc>
	bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return !(lhs < rhs);
	}

	template <class T, class Alloc>
 	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		x.swap(y);
	}
}

#endif
