/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alganoun <alganoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:26:33 by allanganoun       #+#    #+#             */
/*   Updated: 2022/02/28 16:22:29 by alganoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	iterator(void) :_ptr(NULL){};
	iterator(pointer ptr) { _ptr = ptr; };
	iterator(const iterator<value_type> &src) { *this = src; } ;

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

	template <typename T>
	iterator<T> operator+(const typename iterator<T>::difference_type &lhs, const iterator<T> &rhs) {
		return rhs + lhs;
	}	

}