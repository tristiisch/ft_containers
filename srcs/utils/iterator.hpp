/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alganoun <alganoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:26:33 by allanganoun       #+#    #+#             */
/*   Updated: 2022/04/04 22:19:02 by alganoun         ###   ########.fr       */
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

	typedef T							value_type;
	typedef value_type&						reference;
	typedef const value_type&					const_reference;
	typedef value_type*						pointer;
	typedef const value_type*					const_pointer;
	typedef typename std::ptrdiff_t 	difference_type;

	iterator(void) : _ptr(NULL) {}
	iterator(T* other) : _ptr(other) {}
	iterator(const iterator &src) { *this = src; }

	virtual ~iterator() {}

	iterator &operator=(iterator const &src) { _ptr = src._ptr; return (*this); }

	// BOOLEANS : pas besoin dans ce cas
	bool operator ==(T* const base) const { return (_ptr == base); }
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
	
	iterator& operator +=(difference_type b) {_ptr += b; return *this; };	// a += b
	iterator& operator -=(difference_type b) {_ptr -= b; return *this; };	// a -= b
	// INCREMENTERS


	iterator& operator ++() { _ptr++; return ((*this)); }			// ++a //
	iterator operator ++(int) 															// a++
	{
		T* tmp = _ptr;
		_ptr++;
		return iterator(tmp);
	}
	iterator& operator --() { _ptr--; return ((*this)); }			// --a
	iterator operator --(int)															// a--
	{
		T* tmp = _ptr;
		_ptr--;
		return iterator(tmp);
	}

	//DEREFERENCING & ADDRESS STUFF
	reference operator [](difference_type b) { return (*(_ptr + b)); };					// a[]
	const_reference operator [](difference_type b) const { return (*(_ptr + b)); };		// a[]
	reference operator *() { return *_ptr; }											// *a
	const_reference operator *() const { return *_ptr; }								// *a
	pointer operator ->() { return _ptr; }											// a->b
	const_pointer operator ->() const { return _ptr; }											// a->b

	T* base() const {return _ptr;};

	static const bool input_iter = true;

	private:
		T* _ptr;
};

	template < class One, class Two>
	bool operator==(const One &lhs, const Two &rhs) {
		return lhs.base() == rhs.base();
	}

	template < class One, class Two>
	bool operator!=(const One &lhs, const Two &rhs) {
		return lhs.base() != rhs.base();
	}

/*********** USLESS : les comparaisons ne vont pas dedans ***********/
	// template <class One, class Two>
	// bool operator<(const iterator<One> &lhs, const iterator<Two> &rhs) {
	// 	return lhs.base() < rhs.base();
	// }

	// template <class One, class Two>
	// bool operator<=(const iterator<One> &lhs, const iterator<Two> &rhs) {
	// 	return !(rhs < lhs);
	// }

	// template <class One, class Two>
	// bool operator>(const iterator<One> &lhs, const iterator<Two> &rhs) {
	// 	return (rhs < lhs);
	// }

	// template <class One, class Two>
	// bool operator>=(const iterator<One> &lhs, const iterator<Two> &rhs) {
	// 	return !(lhs < rhs);
	// }

	template < class One, class Two>
	bool operator<(const One &lhs, const Two &rhs ) {
		
		std::cout << "COUCOU" << std::endl;
		return lhs.base() < rhs.base();
	}

	template < class One, class Two>
	bool operator<=(const One &lhs, const Two &rhs) {
		return lhs.base() <= rhs.base();
	}

	template < class One, class Two>
	bool operator>(const One &lhs, const Two &rhs) {
		return (lhs.base() > rhs.base());
	}

	template < class One, class Two>
	bool operator>=(const One &lhs, const Two &rhs) {
		return lhs.base() >= rhs.base();
	}

/********************************************************************/

	template <class InputIterator>
	typename InputIterator::difference_type operator-(const InputIterator &lhs, const InputIterator&rhs) {
		return lhs.base() - rhs.base();
	}

	template <class InputIterator>
	InputIterator operator+(const typename InputIterator::difference_type &lhs, const InputIterator&rhs) {
		return rhs + lhs;
	}

	// template <class One, class Two>
	// typename iterator<One>::difference_type operator-(const iterator<One> &lhs, const iterator<Two> &rhs)
	// {
	// 	return lhs.base() - rhs.base();
	// }

	// template <class T>
	// iterator<T> operator+(const typename iterator<T>::difference_type &lhs, const iterator<T> &rhs)
	// {
	// 	return rhs + lhs;
	// }


	//template <class InputIterator>
	//std::ostream &operator<<(std::ostream &out, InputIterator const &temp)
	//{
	//	out << temp.base();
	//	return (out);
	//}

}
