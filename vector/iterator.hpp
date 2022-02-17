/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:26:33 by allanganoun       #+#    #+#             */
/*   Updated: 2022/02/10 17:06:17 by allanganoun      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

namespace ft
{

template <typename T>
class	vectorIterator
{
public:

	typedef T						value_type;
	typedef value_type&				reference;
	typedef const value_type&		const_reference;
	typedef value_type*				pointer;
	typedef const value_type*		const_pointer;
	typedef typename std::ptrdiff_t difference_type;

	vectorIterator(void) {};
	vectorIterator(pointer ptr) { _ptr = ptr; };
	vectorIterator(vectorIterator const &src) { *this = src; } ;

	virtual ~vectorIterator() {};

	vectorIterator &operator=(vectorIterator const &src) { _ptr = src.operator->(); return (*this); };

	// BOOLEANS
	bool operator ==(vectorIterator const& b) const { return (_ptr == b._ptr); };
	bool operator !=(vectorIterator const& b) const { return (_ptr != b._ptr); };
	bool operator >(vectorIterator const& b) const { return (_ptr > b._ptr); };
	bool operator <(vectorIterator const& b) const { return (_ptr < b._ptr); };
	bool operator >=(vectorIterator const& b) const { return (_ptr >= b._ptr); };
	bool operator <=(vectorIterator const& b) const { return (_ptr <= b._ptr); };

	// ARITHMETICS
	vectorIterator operator +(difference_type b) { return (vectorIterator(_ptr + b)); }; // a + n
	vectorIterator operator -(difference_type b) { return (vectorIterator(_ptr - b)); }; // a - n

	difference_type operator +(vectorIterator b) { return (_ptr + b._ptr); }; // a + b
	difference_type operator -(vectorIterator b) { return (_ptr - b._ptr); }; // a - b

	// INCREMENTERS
	vectorIterator operator ++() { _ptr++; return (*this); };			// ++a
	vectorIterator operator ++(int) { _ptr++; return (vectorIterator(_ptr - 1)); };	// a++
	vectorIterator operator --() { _ptr--; return (*this); };			// --a
	vectorIterator operator --(int) { _ptr--; return (vectorIterator(_ptr + 1)); };	// a--

	//COMPOUND ASSIGNMENTS
	void operator +=(difference_type b) { _ptr += b; };	// a += b
	void operator -=(difference_type b) { _ptr -= b; };	// a -= b

	//DEREFERENCING & ADDRESS STUFF
	reference operator *() { return (*_ptr); };											// *a
	const_reference operator *() const { return (*_ptr); };								// *a
	reference operator [](difference_type b) { return (*(_ptr + b)); };					// a[]
	const_reference operator [](difference_type b) const { return (*(_ptr + b)); };		// a[]
	pointer operator ->() { return (_ptr); };											// a->b
	pointer operator ->() const { return (_ptr); };											// a->b

	static const bool input_iter = true;

	private:
		pointer _ptr;

};

}

#endif
