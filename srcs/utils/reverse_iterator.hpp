/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alganoun <alganoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 13:30:07 by alganoun          #+#    #+#             */
/*   Updated: 2022/02/18 16:03:26 by alganoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>
namespace ft
{

template <typename T>
class	reverse_iterator
{
public:

	typedef T						value_type;
	typedef value_type&				reference;
	typedef const value_type&		const_reference;
	typedef value_type*				pointer;
	typedef const value_type*		const_pointer;
	typedef typename std::ptrdiff_t difference_type;

	reverse_iterator(void) {};
	reverse_iterator(pointer ptr) { _ptr = ptr; };
	reverse_iterator(reverse_iterator const &src) { *this = src; } ;

	virtual ~reverse_iterator() {};

	reverse_iterator &operator=(reverse_iterator const &src) { _ptr = src.operator->(); return (*this); };

	// BOOLEANS
	bool operator ==(reverse_iterator const& b) const { return (_ptr == b._ptr); };
	bool operator !=(reverse_iterator const& b) const { return (_ptr != b._ptr); };
	bool operator >(reverse_iterator const& b) const { return (_ptr > b._ptr); };
	bool operator <(reverse_iterator const& b) const { return (_ptr < b._ptr); };
	bool operator >=(reverse_iterator const& b) const { return (_ptr >= b._ptr); };
	bool operator <=(reverse_iterator const& b) const { return (_ptr <= b._ptr); };

	// ARITHMETICS (à faire)
	reverse_iterator operator +(difference_type b) { return (reverse_iterator(_ptr - b)); }; // a + n
	reverse_iterator operator -(difference_type b) { return (reverse_iterator(_ptr + b)); }; // a - n

	difference_type operator +(reverse_iterator b) { return (_ptr + b._ptr); }; // a + b
	difference_type operator -(reverse_iterator b) { return (_ptr - b._ptr); }; // a - b

	// INCREMENTERS (à faire)
	reverse_iterator operator ++() { _ptr--; return (*this); };			// ++a
	reverse_iterator operator ++(int) { _ptr--; return (reverse_iterator(_ptr + 1)); };	// a++
	reverse_iterator operator --() { _ptr++; return (*this); };			// --a
	reverse_iterator operator --(int) { _ptr++; return (reverse_iterator(_ptr - 1)); };	// a--

	//COMPOUND ASSIGNMENTS
	void operator +=(difference_type b) { _ptr -= b; };	// a += b
	void operator -=(difference_type b) { _ptr += b; };	// a -= b

	//DEREFERENCING & ADDRESS STUFF
	reference operator *() { return (*_ptr); };											// *a
	const_reference operator *() const { return (*_ptr); };								// *a
	reference operator [](difference_type b) { return (*(_ptr - b)); };					// a[]
	const_reference operator [](difference_type b) const { return (*(_ptr - b)); };		// a[]
	pointer operator ->() { return (_ptr); };											// a->b
	pointer operator ->() const { return (_ptr); };											// a->b

	static const bool input_iter = true;

	value_type base() { return _ptr; }

	private:
		pointer _ptr;

};

}
