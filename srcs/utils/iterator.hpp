/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:26:33 by allanganoun       #+#    #+#             */
/*   Updated: 2022/03/01 17:08:13 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP
# include <cstddef>
# include "AIterator.hpp"

namespace ft
{


template <typename T>
class	iterator : public AIterator<T>
{
	public:
		iterator(const iterator<typename AIterator<T>::value_type> &src) { *this = src; } ;
		// template <typename U>
		// iterator(const iterator<typename AIterator<U>::value_type> &src) { *this = src; } ;
		iterator(void) : AIterator<typename AIterator<T>::value_type>::_ptr(NULL){};
		iterator(typename AIterator<typename AIterator<T>::value_type>::pointer ptr) { AIterator<typename AIterator<T>::value_type>::_ptr = ptr; };

		virtual ~iterator() {};

		iterator &operator=(iterator const &src) { AIterator<typename AIterator<T>::value_type>::_ptr = src.operator->(); return (*this); };

		// ARITHMETICS
		virtual iterator operator +(typename AIterator<T>::difference_type b) const { return (iterator(this->_ptr + b)); }; // a + n
		virtual iterator operator -(typename AIterator<T>::difference_type b) const { return (iterator(this->_ptr - b)); }; // a - n

		// virtual typename AIterator<T>::difference_type operator +(iterator b) { return (this->_ptr + b._ptr); }; // a + b
		// virtual typename AIterator<T>::difference_type operator -(iterator b) { return (this->_ptr - b._ptr); }; // a - b

		// INCREMENTERS
		iterator operator ++() { this->_ptr++; return (*this); };			// ++a
		iterator operator ++(int) { this->_ptr++; return (iterator(this->_ptr - 1)); };	// a++
		iterator operator --() { this->_ptr--; return (*this); };			// --a
		iterator operator --(int) { this->_ptr--; return (iterator(this->_ptr + 1)); };	// a--


		//COMPOUND ASSIGNMENTS
		iterator operator +=(typename AIterator<T>::difference_type b) {return this->_ptr += b; };	// a += b
		iterator operator -=(typename AIterator<T>::difference_type b) {return this->_ptr -= b; };	// a -= b
		
		iterator base() const { return this->_ptr; }
	};
	
	template <typename T>
	bool operator==(const iterator<T> &lhs, const iterator<T> &rhs) {
		return lhs.base() == rhs.base();
	}

	template <typename T>
	bool operator!=(const iterator<T> &lhs, const iterator<T> &rhs) {
		return !(lhs == rhs);
	}

	template <typename T>
	bool operator<(const iterator<T> &lhs, const iterator<T> &rhs) {
		return lhs.base() < rhs.base();
	}

	template <typename T>
	bool operator<=(const iterator<T> &lhs, const iterator<T> &rhs) {
		return !(rhs < lhs);
	}

	template <typename T>
	bool operator>(const iterator<T> &lhs, const iterator<T> &rhs) {
		return (rhs < lhs);
	}

	template <typename T>
	bool operator>=(const iterator<T> &lhs, const iterator<T> &rhs) {
		return !(lhs < rhs);
	}

	template <typename T>
	typename iterator<T>::difference_type operator-(const iterator<T> &lhs, const iterator<T> &rhs) {
		return lhs.base() - rhs.base();
	}

	// template <typename T>
	// iterator<T> operator+(const typename iterator<T>::difference_type &lhs, const iterator<T> &rhs) {
	// 	return rhs + lhs;
	// }
}
#endif