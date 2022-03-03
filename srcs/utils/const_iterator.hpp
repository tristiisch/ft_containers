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
	typedef value_type&					reference;
	typedef const value_type&			const_reference;
	typedef value_type*					pointer;
	typedef const value_type*			const_pointer;
	typedef typename std::ptrdiff_t 	difference_type;

	const_iterator(void) {};
	const_iterator(pointer ptr) { _ptr = ptr; };
	const_iterator(ft::iterator<T> const &src) { _ptr = src.operator->(); } ;
	const_iterator(const_iterator const &src) { *this = src; } ;


	virtual ~const_iterator() {};

	const_iterator &operator=(const_iterator const &src) { _ptr = src.operator->(); return (*this); };

	// BOOLEANS
	bool operator ==(const_iterator const& b) const { return (_ptr == b._ptr); };
	bool operator !=(const_iterator const& b) const { return (_ptr != b._ptr); };
	bool operator >(const_iterator const& b) const { return (_ptr > b._ptr); };
	bool operator <(const_iterator const& b) const { return (_ptr < b._ptr); };
	bool operator >=(const_iterator const& b) const { return (_ptr >= b._ptr); };
	bool operator <=(const_iterator const& b) const { return (_ptr <= b._ptr); };

	// ARITHMETICS
	const_iterator operator +(difference_type b) const { return (const_iterator(_ptr + b)); }; // a + n
	const_iterator operator -(difference_type b) const { return (const_iterator(_ptr - b)); }; // a - n

	difference_type operator +(const_iterator b) { return (_ptr + b._ptr); }; // a + b
	difference_type operator -(const_iterator b) { return (_ptr - b._ptr); }; // a - b

	// INCREMENTERS
	const_iterator& operator ++() { _ptr++; return (*this); };			// ++a
	const_iterator operator ++(int) { return (const_iterator(_ptr++)); };	// a++
	const_iterator& operator --() { _ptr--; return (*this); };			// --a
	const_iterator operator --(int) { return (const_iterator( _ptr--)); };	// a--

	//COMPOUND ASSIGNMENTS
	const_iterator& operator +=(difference_type b) { _ptr += b; return *this; };	// a += b
	const_iterator& operator -=(difference_type b) { _ptr -= b; return *this; };	// a -= b

	//DEREFERENCING & ADDRESS STUFF
	const_reference operator *() const { return (*_ptr); };								// *a
	const_reference operator [](difference_type b) const { return (*(_ptr + b)); };		// a[]
	pointer operator ->() const { return _ptr; };											// a->b

	pointer base() const { return _ptr; }

	static const bool input_iter = true;


	private:
		pointer _ptr;
};
}
