/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:26:33 by allanganoun       #+#    #+#             */
/*   Updated: 2022/03/01 19:48:11 by allanganoun      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>

namespace ft
{


template <typename T>
class	iterator
{
public:

	typedef T						value_type;
	typedef value_type&				reference;
	typedef const value_type&		const_reference;
	typedef value_type*				pointer;
	typedef const value_type*		const_pointer;
	typedef typename std::ptrdiff_t difference_type;

	iterator(void) {};
	iterator(pointer ptr) { _ptr = ptr; };
	iterator(const iterator &src) { *this = src; } ;


	virtual ~iterator() {};

	iterator &operator=(iterator const &src) { _ptr = src.operator->(); return (*this); };

	// BOOLEANS
	bool operator ==(iterator const& b) const { return (_ptr == b._ptr); };
	bool operator !=(iterator const& b) const { return (_ptr != b._ptr); };
	bool operator >(iterator const& b) const { return (_ptr > b._ptr); };
	bool operator <(iterator const& b) const { return (_ptr < b._ptr); };
	bool operator >=(iterator const& b) const { return (_ptr >= b._ptr); };
	bool operator <=(iterator const& b) const { return (_ptr <= b._ptr); };

	// ARITHMETICS
	iterator operator +(difference_type b) const { return (iterator(_ptr + b)); }; // a + n
	iterator operator -(difference_type b) const { return (iterator(_ptr - b)); }; // a - n

	difference_type operator +(iterator b) { return (_ptr + b._ptr); }; // a + b
	difference_type operator -(iterator b) { return (_ptr - b._ptr); }; // a - b

	// INCREMENTERS
	iterator operator ++() { _ptr++; return (*this); };			// ++a
	iterator operator ++(int) { _ptr++; return (iterator(_ptr - 1)); };	// a++
	iterator operator --() { _ptr--; return (*this); };			// --a
	iterator operator --(int) { _ptr--; return (iterator(_ptr + 1)); };	// a--

	//COMPOUND ASSIGNMENTS
	iterator operator +=(difference_type b) {return _ptr += b; };	// a += b
	iterator operator -=(difference_type b) {return _ptr -= b; };	// a -= b

	//DEREFERENCING & ADDRESS STUFF
	reference operator *() { return (*_ptr); };											// *a
	const_reference operator *() const { return (*_ptr); };								// *a
	reference operator [](difference_type b) { return (*(_ptr + b)); };					// a[]
	const_reference operator [](difference_type b) const { return (*(_ptr + b)); };		// a[]
	pointer operator ->() { return (_ptr); };											// a->b
	pointer operator ->() const { return (_ptr); };											// a->b

	pointer base() const { return _ptr; }

	static const bool input_iter = true;


	private:
		pointer _ptr;
};

	template < class One, class Two>
	bool operator==(const One &lhs, const Two &rhs) {
		return lhs.base() == rhs.base();
	}

	template < class One, class Two>
	bool operator!=(const One &lhs, const Two &rhs) {
		return lhs.base() != rhs.base();
	}

	template < class One, class Two>
	bool operator<(const One &lhs, const Two &rhs) {
		return lhs.base() < rhs.base();
	}

	template < class One, class Two>
	bool operator<=(const One &lhs, const Two &rhs) {
		return rhs.base() <= lhs.base();
	}

	template < class One, class Two>
	bool operator>(const One &lhs, const Two &rhs) {
		return (rhs.base() > lhs.base());
	}

	template < class One, class Two>
	bool operator>=(const One &lhs, const Two &rhs) {
		return lhs.base() >= rhs.base();
	}

	template <class InputIterator>
	typename InputIterator::difference_type operator-(const InputIterator &lhs, const InputIterator&rhs) {
		return lhs.base() - rhs.base();
	}

	template <class InputIterator>
	InputIterator operator+( const typename InputIterator::difference_type &lhs, const InputIterator&rhs) {
		return rhs + lhs;
	}

	template <class InputIterator>
	std::ostream &operator<<(std::ostream &out, InputIterator const &temp)
{
	out << temp.base();
	return (out);
}

}
