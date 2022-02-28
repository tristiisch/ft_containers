/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:26:33 by allanganoun       #+#    #+#             */
/*   Updated: 2022/02/28 20:01:50 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cstddef>
#include "AIterator.hpp"

namespace ft
{


template <typename T>
class	iterator : public AIterator<T>
{
	public:
		iterator(const iterator<typename AIterator<T>::value_type> &src) { *this = src; } ;
		iterator(void) : AIterator<typename AIterator<T>::value_type>::_ptr(NULL){};
		iterator(typename AIterator<typename AIterator<T>::value_type>::pointer ptr) { AIterator<typename AIterator<T>::value_type>::_ptr = ptr; };


		// INCREMENTERS
		iterator operator ++() { AIterator<T>::_ptr++; return (*this); };			// ++a
		iterator operator ++(int) { AIterator<T>::_ptr++; return (iterator(AIterator<T>::_ptr - 1)); };	// a++
		iterator operator --() { AIterator<T>::_ptr--; return (*this); };			// --a
		iterator operator --(int) { AIterator<T>::_ptr--; return (iterator(AIterator<T>::_ptr + 1)); };	// a--


		//COMPOUND ASSIGNMENTS
		iterator operator +=(typename AIterator<T>::difference_type b) {return AIterator<T>::_ptr += b; };	// a += b
		iterator operator -=(typename AIterator<T>::difference_type b) {return AIterator<T>::_ptr -= b; };	// a -= b


		// ARITHMETICS
		iterator operator +(difference_type b) const { return (iterator(_ptr + b)); }; // a + n
		iterator operator -(difference_type b) const { return (iterator(_ptr - b)); }; // a - n

		difference_type operator +(iterator b) { return (_ptr + b._ptr); }; // a + b
		difference_type operator -(iterator b) { return (_ptr - b._ptr); }; // a - b
	};
}