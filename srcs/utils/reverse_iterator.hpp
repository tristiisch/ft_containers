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
	reverse_iterator operator +=(difference_type b) { return _ptr -= b; };	// a += b
	reverse_iterator operator -=(difference_type b) { return _ptr += b; };	// a -= b

	//DEREFERENCING & ADDRESS STUFF
	reference operator *() { return (*_ptr); };											// *a
	const_reference operator *() const { return (*_ptr); };								// *a
	reference operator [](difference_type b) { return (*(_ptr - b)); };					// a[]
	const_reference operator [](difference_type b) const { return (*(_ptr - b)); };		// a[]
	pointer operator ->() { return (_ptr); };											// a->b
	pointer operator ->() const { return (_ptr); };											// a->b

	static const bool input_iter = true;

	reverse_iterator base() const { return _ptr + 1; }

	private:
		pointer _ptr;

};
	template <class I1, class I2>
	bool operator==(const reverse_iterator<I1> &lhs, const reverse_iterator<I2> &rhs) {
		return lhs.base() == rhs.base();
	}

	template <class I1, class I2>
	bool operator!=(const reverse_iterator<I1> &lhs, const reverse_iterator<I2> &rhs) {
		return !(lhs == rhs);
	}

	template <class I1, class I2>
	bool operator<(const reverse_iterator<I1> &lhs, const reverse_iterator<I2> &rhs) {
		return rhs.base() < lhs.base();
	}

	template <class I1, class I2>
	bool operator<=(const reverse_iterator<I1> &lhs, const reverse_iterator<I2> &rhs) {
		return !(rhs < lhs);
	}

	template <class I1, class I2>
	bool operator>(const reverse_iterator<I1> &lhs, const reverse_iterator<I2> &rhs) {
		return (rhs < lhs);
	}

	template <class I1, class I2>
	bool operator>=(const reverse_iterator<I1> &lhs, const reverse_iterator<I2> &rhs) {
		return !(lhs < rhs);
	}

	template <class I1, class I2>
	typename reverse_iterator<I1>::difference_type operator-(const reverse_iterator<I1> &lhs, const reverse_iterator<I2> &rhs) {
		return rhs.base() - lhs.base();
	}

	template <class Iter>
	reverse_iterator<Iter> operator+(const typename reverse_iterator<Iter>::difference_type &lhs, const reverse_iterator<Iter> &rhs) {
		return rhs + lhs;
	}
}
