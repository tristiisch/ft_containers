/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const_iterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:26:33 by allanganoun       #+#    #+#             */
/*   Updated: 2022/03/01 17:08:03 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONST_ITERATOR_HPP
# define CONST_ITERATOR_HPP
# include "AIterator.hpp"

namespace ft
{


template <typename T>
class	const_iterator : public AIterator<T>
{
	public:
		const_iterator(const AIterator<T> &src) { *this = src; } ;
		const_iterator(void) : AIterator<T>::_ptr(NULL){};
		const_iterator(typename AIterator<T>::pointer ptr) { AIterator<T>::_ptr = ptr; };

		virtual ~const_iterator() {};

		const_iterator &operator=(const_iterator const &src) { AIterator<typename AIterator<T>::value_type>::_ptr = src.operator->(); return (*this); };

		// ARITHMETICS
		virtual const_iterator operator +(typename AIterator<T>::difference_type b) const { return (const_iterator(AIterator<T>::_ptr + b)); }; // a + n
		virtual const_iterator operator -(typename AIterator<T>::difference_type b) const { return (const_iterator(AIterator<T>::_ptr - b)); }; // a - n

		// virtual typename AIterator<T>::difference_type operator +(const_iterator b) { return (this->_ptr + b._ptr); }; // a + b
		// virtual typename AIterator<T>::difference_type operator -(const_iterator b) { return (this->_ptr - b._ptr); }; // a - b

		// INCREMENTERS
		const_iterator operator ++() { AIterator<T>::_ptr++; return (*this); };			// ++a
		const_iterator operator ++(int) { AIterator<T>::_ptr++; return (const_iterator(AIterator<T>::_ptr - 1)); };	// a++
		const_iterator operator --() { AIterator<T>::_ptr--; return (*this); };			// --a
		const_iterator operator --(int) { AIterator<T>::_ptr--; return (const_iterator(AIterator<T>::_ptr + 1)); };	// a--


		//COMPOUND ASSIGNMENTS
		const_iterator operator +=(typename AIterator<T>::difference_type b) {return AIterator<T>::_ptr += b; };	// a += b
		const_iterator operator -=(typename AIterator<T>::difference_type b) {return AIterator<T>::_ptr -= b; };	// a -= b
		
		const_iterator base() const { return AIterator<T>::_ptr; };
	};

		
	template <typename T>
	bool operator==(const const_iterator<T> &lhs, const const_iterator<T> &rhs) {
		return lhs.base() == rhs.base();
	}

	template <typename T>
	bool operator!=(const const_iterator<T> &lhs, const const_iterator<T> &rhs) {
		return !(lhs == rhs);
	}

	template <typename T>
	bool operator<(const const_iterator<T> &lhs, const const_iterator<T> &rhs) {
		return lhs.base() < rhs.base();
	}

	template <typename T>
	bool operator<=(const const_iterator<T> &lhs, const const_iterator<T> &rhs) {
		return !(rhs < lhs);
	}

	template <typename T>
	bool operator>(const const_iterator<T> &lhs, const const_iterator<T> &rhs) {
		return (rhs < lhs);
	}

	template <typename T>
	bool operator>=(const const_iterator<T> &lhs, const const_iterator<T> &rhs) {
		return !(lhs < rhs);
	}

	template <typename T>
	typename const_iterator<T>::difference_type operator-(const const_iterator<T> &lhs, const const_iterator<T> &rhs) {
		return lhs.base() - rhs.base();
	}

	template <typename T>
	const_iterator<T> operator+(const typename const_iterator<T>::difference_type &lhs, const const_iterator<T> &rhs) {
		return rhs + lhs;
	}

}
#endif