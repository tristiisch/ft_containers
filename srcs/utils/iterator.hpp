/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:26:33 by allanganoun       #+#    #+#             */
/*   Updated: 2022/02/24 01:55:53 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>

namespace ft
{


template <typename T, class Container>
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
	iterator(const iterator<typename Container::pointer, Container> &src) { *this = src; } ;

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

	iterator base() const { return _ptr; }

	static const bool input_iter = true;


	private:
		pointer _ptr;
};
	template <class I1, class I2, class Container>
	bool operator==(const iterator<I1, Container> &lhs, const iterator<I2, Container> &rhs) {
		return lhs.base() == rhs.base();
	}

	template <class I1, class I2, class Container>
	bool operator!=(const iterator<I1, Container> &lhs, const iterator<I2, Container> &rhs) {
		return !(lhs == rhs);
	}

	template <class I1, class I2, class Container>
	bool operator<(const iterator<I1, Container> &lhs, const iterator<I2, Container> &rhs) {
		return lhs.base() < rhs.base();
	}

	template <class I1, class I2, class Container>
	bool operator<=(const iterator<I1, Container> &lhs, const iterator<I2, Container> &rhs) {
		return !(rhs < lhs);
	}

	template <class I1, class I2, class Container>
	bool operator>(const iterator<I1, Container> &lhs, const iterator<I2, Container> &rhs) {
		return (rhs < lhs);
	}

	template <class I1, class I2, class Container>
	bool operator>=(const iterator<I1, Container> &lhs, const iterator<I2, Container> &rhs) {
		return !(lhs < rhs);
	}

	template <class I1, class I2, class Container>
	typename iterator<I1, Container>::difference_type operator-(const iterator<I1, Container> &lhs, const iterator<I2, Container> &rhs) {
		return lhs.base() - rhs.base();
	}

	template <class Iter, class Container>
	iterator<Iter, Container> operator+(const typename iterator<Iter, Container>::difference_type &lhs, const iterator<Iter, Container> &rhs) {
		return rhs + lhs;
	}
}
