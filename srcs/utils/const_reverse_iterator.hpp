/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const_reverse_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alganoun <alganoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 20:11:58 by allanganoun       #+#    #+#             */
/*   Updated: 2022/04/04 16:23:08 by alganoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>
#include "./reverse_iterator.hpp"
#include "./const_iterator.hpp"

namespace ft
{
template <class iterator>
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
	const_reverse_iterator(pointer ptr) { _node = ptr; };
	const_reverse_iterator(const ft::reverse_iterator<iterator> &src) { _node = src.base(); } ;
	const_reverse_iterator(const ft::const_iterator<value_type> &src) { _node = src.base() - 1; } ;
	const_reverse_iterator(const iterator &src) { _node = src.base() - 1; } ;
	const_reverse_iterator(const const_reverse_iterator &src) { *this = src; } ;


	virtual ~const_reverse_iterator() {};

	const_reverse_iterator &operator=(const_reverse_iterator const &src) { _node = src.operator->(); return (*this); };

	// BOOLEANS
	bool operator ==(const_reverse_iterator const& b) const { return (_node == b._node); };
	bool operator !=(const_reverse_iterator const& b) const { return (_node != b._node); };
	bool operator >(const_reverse_iterator const& b) const { return (_node < b._node); };//à verifier
	bool operator <(const_reverse_iterator const& b) const { return (_node > b._node); };//à verifier
	bool operator >=(const_reverse_iterator const& b) const { return (_node <= b._node); };//à verifier
	bool operator <=(const_reverse_iterator const& b) const { return (_node >= b._node); };//à verifier

	// ARITHMETICS
	const_reverse_iterator operator +(difference_type b) const { return (const_reverse_iterator(_node - b)); }; // a + n
	const_reverse_iterator operator -(difference_type b) const { return (const_reverse_iterator(_node + b)); }; // a - n

	difference_type operator +(const_reverse_iterator b) { return (b._node + _node); }; // a + b
	difference_type operator -(const_reverse_iterator b) { return (b._node - _node); };

	// INCREMENTERS
	const_reverse_iterator& operator ++() { _node--; return (*this); };			// ++a
	const_reverse_iterator operator ++(int) { return (const_reverse_iterator(_node--)); };	// a++
	const_reverse_iterator& operator --() { _node++; return (*this); };			// --a
	const_reverse_iterator operator --(int) { return (const_reverse_iterator(_node++)); };	// a--

	//COMPOUND ASSIGNMENTS
	const_reverse_iterator& operator +=(difference_type b) {_node -= b; return *this; };	// a += b
	const_reverse_iterator& operator -=(difference_type b) {_node += b; return *this; };	// a -= b

	//DEREFERENCING & ADDRESS STUFF
	const_reference operator *() const { return (*_node); };								// *a
	const_reference operator [](difference_type b) const { return *(*this + b); };		// a[]
	const_pointer operator ->() const { return (_node); };											// a->b

	pointer base() const { return _node + 1; }

	static const bool input_iter = true;


	private:
		pointer _node;
};
}
