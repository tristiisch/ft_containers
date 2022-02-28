/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAIterator.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alganoun <alganoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:40:25 by alganoun          #+#    #+#             */
/*   Updated: 2022/02/28 18:40:25 by alganoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

#include <cstddef>

namespace ft
{


template <typename T>
class	AIterator
{
public:

	typedef T						value_type;
	typedef value_type&				reference;
	typedef const value_type&		const_reference;
	typedef value_type*				pointer;
	typedef const value_type*		const_pointer;
	typedef typename std::ptrdiff_t difference_type;

	AIterator(void) {};
	AIterator(pointer ptr) { _ptr = ptr; };
	AIterator(const AIterator &src) { *this = src; } ;


	virtual ~AIterator() {} = 0;

	AIterator &operator=(AIterator const &src) { _ptr = src.operator->(); return (*this); };

	// BOOLEANS
	bool operator ==(AIterator const& b) const { return (_ptr == b._ptr); };
	bool operator !=(AIterator const& b) const { return (_ptr != b._ptr); };
	bool operator >(AIterator const& b) const { return (_ptr > b._ptr); };
	bool operator <(AIterator const& b) const { return (_ptr < b._ptr); };
	bool operator >=(AIterator const& b) const { return (_ptr >= b._ptr); };
	bool operator <=(AIterator const& b) const { return (_ptr <= b._ptr); };

	// ARITHMETICS
	AIterator operator +(difference_type b) const { return (AIterator(_ptr + b)); }; // a + n
	AIterator operator -(difference_type b) const { return (AIterator(_ptr - b)); }; // a - n

	difference_type operator +(AIterator b) { return (_ptr + b._ptr); }; // a + b
	difference_type operator -(AIterator b) { return (_ptr - b._ptr); }; // a - b

	// INCREMENTERS
	AIterator operator ++() { _ptr++; return (*this); };			// ++a
	AIterator operator ++(int) { _ptr++; return (AIterator(_ptr - 1)); };	// a++
	AIterator operator --() { _ptr--; return (*this); };			// --a
	AIterator operator --(int) { _ptr--; return (AIterator(_ptr + 1)); };	// a--

	//COMPOUND ASSIGNMENTS
	AIterator operator +=(difference_type b) {return _ptr += b; };	// a += b
	AIterator operator -=(difference_type b) {return _ptr -= b; };	// a -= b

	//DEREFERENCING & ADDRESS STUFF
	reference operator *() { return (*_ptr); };											// *a
	const_reference operator *() const { return (*_ptr); };								// *a
	reference operator [](difference_type b) { return (*(_ptr + b)); };					// a[]
	const_reference operator [](difference_type b) const { return (*(_ptr + b)); };		// a[]
	pointer operator ->() { return (_ptr); };											// a->b
	pointer operator ->() const { return (_ptr); };											// a->b

	AIterator base() const { return _ptr; }

	static const bool input_iter = true;


	private:
		pointer _ptr;
};

	template <typename T>
	bool operator==(const AIterator<T> &lhs, const AIterator<T> &rhs) {
		return lhs.base() == rhs.base();
	}

	template <typename T>
	bool operator!=(const AIterator<T> &lhs, const AIterator<T> &rhs) {
		return !(lhs == rhs);
	}

	template <typename T>
	bool operator<(const AIterator<T> &lhs, const AIterator<T> &rhs) {
		return lhs.base() < rhs.base();
	}

	template <typename T>
	bool operator<=(const AIterator<T> &lhs, const AIterator<T> &rhs) {
		return !(rhs < lhs);
	}

	template <typename T>
	bool operator>(const AIterator<T> &lhs, const AIterator<T> &rhs) {
		return (rhs < lhs);
	}

	template <typename T>
	bool operator>=(const AIterator<T> &lhs, const AIterator<T> &rhs) {
		return !(lhs < rhs);
	}

	template <typename T>
	typename AIterator<T>::difference_type operator-(const AIterator<T> &lhs, const AIterator<T> &rhs) {
		return lhs.base() - rhs.base();
	}

	template <typename T>
	AIterator<T> operator+(const typename AIterator<T>::difference_type &lhs, const AIterator<T> &rhs) {
		return rhs + lhs;
	}	

}