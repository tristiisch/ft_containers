/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const_const_iterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alganoun <alganoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:30:41 by alganoun          #+#    #+#             */
/*   Updated: 2022/02/28 18:30:41 by alganoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>
#include "./iterator.hpp"

namespace ft
{


template <typename T>
class	const_iterator
{
public:

	typedef T							value_type;
	typedef const value_type&					reference;
	typedef const value_type*					pointer;
	typedef typename std::ptrdiff_t 	difference_type;

	const_iterator(void) : _ptr(NULL) {}
	const_iterator(T* other) : _ptr(other) {}
	const_iterator(const const_iterator &src) { *this = src; }
	const_iterator(const iterator<value_type> &src) { _ptr = src.base(); }

	virtual ~const_iterator() {}

	const_iterator &operator=(const_iterator const &src) { _ptr = src._ptr; return (*this); }

	// BOOLEANS : pas besoin dans ce cas
	bool operator ==(T* const base) const { return (_ptr == base); }
	bool operator ==(const_iterator const& b) const { return (_ptr == b._ptr); };
	bool operator !=(const_iterator const& b) const { return (_ptr != b._ptr); };
	bool operator >(const_iterator const& b) const { return (_ptr > b._ptr); };
	bool operator <(const_iterator const& b) const { return (_ptr < b._ptr); };
	bool operator >=(const_iterator const& b) const { return (_ptr >= b._ptr); };
	bool operator <=(const_iterator const& b) const { return (_ptr <= b._ptr); };

	const_iterator operator +(difference_type b) const { return const_iterator(_ptr + b); }; // a + n
	const_iterator operator -(difference_type b) const { return const_iterator(_ptr - b); }; // a - n

	difference_type operator +(const_iterator b) { return (_ptr + b._ptr); }; // a + b
	difference_type operator -(const_iterator b) { return (_ptr - b._ptr); }; // a - b

	const_iterator& operator +=(difference_type b) {_ptr += b; return *this; };	// a += b
	const_iterator& operator -=(difference_type b) {_ptr -= b; return *this; };	// a -= b
	// INCREMENTERS
	const_iterator& operator ++() { _ptr++; return ((*this)); }			// ++a
	const_iterator operator ++(int) 														// a++
	{
		T* tmp = _ptr;
		_ptr++;
		return const_iterator(tmp);
	}
	const_iterator& operator --() { _ptr--; return ((*this)); }			// --a
	const_iterator operator --(int)														// a--
	{
		T* tmp = _ptr;
		_ptr--;
		return const_iterator(tmp);
	}

	reference operator [](difference_type b) { return (*(_ptr + b)); }
	reference operator *() const { return *_ptr; }								// *a
 	pointer operator ->() const { return _ptr; }

 	T* base() const {return _ptr;};									// a->b

	static const bool input_iter = true;

 	private:
 		T* _ptr;

};
}
