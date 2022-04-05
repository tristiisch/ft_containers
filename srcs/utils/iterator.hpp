/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:26:33 by allanganoun       #+#    #+#             */
/*   Updated: 2022/04/05 19:27:19 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>
#include <iostream>

namespace ft
{


template <typename T>
class	iterator
{
public:

	typedef T							value_type;
	typedef value_type&						reference;
	typedef value_type*						pointer;
	typedef typename std::ptrdiff_t 	difference_type;

	iterator(void) : _ptr(NULL) {}
	iterator(pointer other) : _ptr(other) {}
	iterator(const iterator &src) : _ptr(src._ptr) {}

	virtual ~iterator() {}

	iterator &operator=(iterator const &src) { this->_ptr = src._ptr; return (*this); }

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
	//const_reference operator [](difference_type b) const { return (*(_ptr + b)); };		// a[]
	reference operator *() { return *_ptr; }											// *a
	//const_reference operator *() const { return *_ptr; }								// *a
	pointer operator ->() { return &(this->operator*()); }											// a->b
	//const_pointer operator ->() const { return _ptr; }											// a->b

	operator iterator<const T> () const
        { return (iterator<const T>(this->_ptr)); }

	T* base() const {return this->_ptr;};

	static const bool input_iter = true;

	private:
		T* _ptr;
};

	template <typename T>
    bool operator==(const ft::iterator<T> lhs,
              const ft::iterator<T> rhs)
    {
        return (lhs.base() == rhs.base());
    }

    /* For iterator == const_iterator */
    template<typename T_L, typename T_R>
    bool operator==(const ft::iterator<T_L> lhs,
              const ft::iterator<T_R> rhs)
    {
        return (lhs.base() == rhs.base());
    }

    /*
    ** @brief Check if the pointer of "lhs"
    ** is different than "rhs" in the memory.
    **
    ** @param lhs the random access iterator to compare.
    ** @param rhs the random access iterator with who check.
    ** @return true if the pointer of lhs
    ** if different than "rhs", otherwise false.
    */
    template <typename T>
    bool operator!=(const ft::iterator<T> lhs,
              const ft::iterator<T> rhs)
    {
        return (lhs.base() != rhs.base());
    }

    /* For iterator != const_iterator */
    template<typename T_L, typename T_R>
    bool operator!=(const ft::iterator<T_L> lhs,
              const ft::iterator<T_R> rhs)
    {
        return (lhs.base() != rhs.base());
    }

    /*
    ** @brief Check if the pointer of "lhs"
    ** is lower than "rhs" in the memory.
    **
    ** @param lhs the random access iterator to compare.
    ** @param rhs the random access iterator with who check.
    ** @return true if the pointer of lhs
    ** if lower than "rhs", otherwise false.
    */
    template <typename T>
    bool operator<(const ft::iterator<T> lhs,
              const ft::iterator<T> rhs)
    {
        return (lhs.base() < rhs.base());
    }

    /* For iterator < const_iterator */
    template<typename T_L, typename T_R>
    bool operator<(const ft::iterator<T_L> lhs,
              const ft::iterator<T_R> rhs)
    {
        return (lhs.base() < rhs.base());
    }

    /*
    ** @brief Check if the pointer of "lhs"
    ** is upper than "rhs" in the memory.
    **
    ** @param lhs the random access iterator to compare.
    ** @param rhs the random access iterator with who check.
    ** @return true if the pointer of lhs
    ** if upper than "rhs", otherwise false.
    */
    template <typename T>
    bool operator>(const ft::iterator<T> lhs,
              const ft::iterator<T> rhs)
    {
        return (lhs.base() > rhs.base());
    }

    /* For iterator > const_iterator */
    template<typename T_L,
             typename T_R>
    bool operator>(const ft::iterator<T_L> lhs,
              const ft::iterator<T_R> rhs)
    {
        return (lhs.base() > rhs.base());
    }

    /*
    ** @brief Check if the pointer of "lhs"
    ** is lower or equal than "rhs" in the memory.
    **
    ** @param lhs the random access iterator to compare.
    ** @param rhs the random access iterator with who check.
    ** @return true if the pointer of lhs
    ** if lower or equal than "rhs", otherwise false.
    */
    template <typename T>
    bool operator<=(const ft::iterator<T> lhs,
              const ft::iterator<T> rhs)
    {
        return (lhs.base() <= rhs.base());
    }

    /* For iterator <= const_iterator */
    template<typename T_L, typename T_R>
    bool operator<=(const ft::iterator<T_L> lhs,
              const ft::iterator<T_R> rhs)
    {
        return (lhs.base() <= rhs.base());
    }

    /*
    ** @brief Check if the pointer of "lhs"
    ** is upper or equal than "rhs" in the memory.
    **
    ** @param lhs the random access iterator to compare.
    ** @param rhs the random access iterator with who check.
    ** @return true if the pointer of lhs
    ** if upper or equal than "rhs", otherwise false.
    */
    template <typename T>
    bool operator>=(const ft::iterator<T> lhs,
              const ft::iterator<T> rhs)
    {
        return (lhs.base() >= rhs.base());
    }

    /* For iterator >= const_iterator */
    template<typename T_L,
             typename T_R>
    bool operator>=(const ft::iterator<T_L> lhs,
              const ft::iterator<T_R> rhs)
    {
        return (lhs.base() >= rhs.base());
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
