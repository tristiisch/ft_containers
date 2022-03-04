/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const_reverse_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 20:11:58 by allanganoun       #+#    #+#             */
/*   Updated: 2022/03/04 09:33:54 by allanganoun      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>
#include "./reverse_iterator.hpp"
#include "./const_iterator.hpp"

namespace ft
{
template <typename iterator>
class	const_reverse_iterator
{
public:

	typedef typename iterator::value_type			value_type;
	typedef typename iterator::reference			reference;
	typedef typename iterator::const_reference		const_reference;
	typedef typename iterator::pointer				pointer;
	typedef typename iterator::const_pointer		const_pointer;
	typedef typename iterator::difference_type		difference_type;

	const_reverse_iterator(void) {};
	const_reverse_iterator(pointer ptr) { _ptr = ptr; };
	const_reverse_iterator(const ft::reverse_iterator<iterator> &src) { _ptr = src.operator->(); } ;
	const_reverse_iterator(const ft::const_iterator<value_type> &src) { _ptr = src.operator->(); } ;
	const_reverse_iterator(const ft::iterator<value_type> &src) { _ptr = src.operator->(); } ;
	const_reverse_iterator(const const_reverse_iterator &src) { *this = src; } ;


	virtual ~const_reverse_iterator() {};

	const_reverse_iterator &operator=(const_reverse_iterator const &src) { _ptr = src.operator->(); return (*this); };

	// BOOLEANS
	bool operator ==(const_reverse_iterator const& b) const { return (_ptr == b._ptr); };
	bool operator !=(const_reverse_iterator const& b) const { return (_ptr != b._ptr); };
	bool operator >(const_reverse_iterator const& b) const { return (_ptr < b._ptr); };//à verifier
	bool operator <(const_reverse_iterator const& b) const { return (_ptr > b._ptr); };//à verifier
	bool operator >=(const_reverse_iterator const& b) const { return (_ptr <= b._ptr); };//à verifier
	bool operator <=(const_reverse_iterator const& b) const { return (_ptr >= b._ptr); };//à verifier

	// ARITHMETICS
	const_reverse_iterator operator +(difference_type b) const { return (const_reverse_iterator(_ptr - b)); }; // a + n
	const_reverse_iterator operator -(difference_type b) const { return (const_reverse_iterator(_ptr + b)); }; // a - n

	difference_type operator +(const_reverse_iterator b) { return (_ptr - b._ptr); }; // a + b
	difference_type operator -(const_reverse_iterator b) { return (_ptr + b._ptr); }; // a - b

	// INCREMENTERS
	const_reverse_iterator& operator ++() { _ptr--; return (*this); };			// ++a
	const_reverse_iterator operator ++(int) { return (const_reverse_iterator(_ptr--)); };	// a++
	const_reverse_iterator& operator --() { _ptr++; return (*this); };			// --a
	const_reverse_iterator operator --(int) { return (const_reverse_iterator(_ptr++)); };	// a--

	//COMPOUND ASSIGNMENTS
	const_reverse_iterator& operator +=(difference_type b) {_ptr -= b; return *this; };	// a += b
	const_reverse_iterator& operator -=(difference_type b) {_ptr += b; return *this; };	// a -= b

	//DEREFERENCING & ADDRESS STUFF
	const_reference operator *() const { return (*_ptr); };								// *a
	const_reference operator [](difference_type b) const { return *(*this + b); };		// a[]
	pointer operator ->() const { return (_ptr); };											// a->b

	pointer base() const { return _ptr + 1; }

	static const bool input_iter = true;


	private:
		pointer _ptr;
};

}
