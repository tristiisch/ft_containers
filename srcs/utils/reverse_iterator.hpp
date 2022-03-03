/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 20:12:07 by allanganoun       #+#    #+#             */
/*   Updated: 2022/03/03 22:43:19 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>
#include "./iterator.hpp"

namespace ft
{


template <typename iterator>
class	reverse_iterator
{
public:

	typedef typename iterator::value_type			value_type;
	typedef typename iterator::reference			reference;
	typedef typename iterator::const_reference		const_reference;
	typedef typename iterator::pointer				pointer;
	typedef typename iterator::const_pointer		const_pointer;
	typedef typename iterator::difference_type		difference_type;

	reverse_iterator(void) {};
	reverse_iterator(pointer ptr) { _ptr = ptr; };
	reverse_iterator(const reverse_iterator &src) { *this = src; } ;
	reverse_iterator(const ft::iterator<value_type> &src) { _ptr = src.operator->(); } ;


	virtual ~reverse_iterator() {};

	reverse_iterator &operator=(reverse_iterator const &src) { _ptr = src.operator->(); return (*this); };

	// BOOLEANS
	bool operator ==(reverse_iterator const& b) const { return (_ptr == b._ptr); };
	bool operator !=(reverse_iterator const& b) const { return (_ptr != b._ptr); };
	bool operator >(reverse_iterator const& b) const { return (_ptr > b._ptr); };
	bool operator <(reverse_iterator const& b) const { return (_ptr < b._ptr); };
	bool operator >=(reverse_iterator const& b) const { return (_ptr >= b._ptr); };
	bool operator <=(reverse_iterator const& b) const { return (_ptr <= b._ptr); };

	// ARITHMETICS
	reverse_iterator operator +(difference_type b) const { return (reverse_iterator(_ptr - b)); }; // a + n
	reverse_iterator operator -(difference_type b) const { return (reverse_iterator(_ptr + b)); }; // a - n

	difference_type operator +(reverse_iterator b) { return (_ptr - b._ptr); }; // a + b
	difference_type operator -(reverse_iterator b) { return (_ptr + b._ptr); }; // a - b

	// INCREMENTERS
	reverse_iterator& operator ++() { _ptr--; return (*this); };			// ++a
	reverse_iterator operator ++(int) { return (reverse_iterator( _ptr--)); };	// a++
	reverse_iterator& operator --() { _ptr++; return (*this); };			// --a
	reverse_iterator operator --(int) { return (reverse_iterator(_ptr++)); };	// a--

	//COMPOUND ASSIGNMENTS
	reverse_iterator& operator +=(difference_type b) {_ptr -= b; return *this; };	// a += b
	reverse_iterator& operator -=(difference_type b) {_ptr += b; return *this; };	// a -= b

	//DEREFERENCING & ADDRESS STUFF
	reference operator *() { return (*_ptr); };											// *a
	const_reference operator *() const { return (*_ptr); };								// *a
	reference operator [](difference_type b) { return (*(_ptr - b)); };					// a[]
	const_reference operator [](difference_type b) const { return (*(_ptr + b)); };		// a[]
	pointer operator ->() { return (_ptr); };											// a->b
	pointer operator ->() const { return (_ptr); };											// a->b

	pointer base() const { return _ptr + 1; }

	static const bool input_iter = true;


	private:
		pointer _ptr;
};

}
