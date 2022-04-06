/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:26:33 by allanganoun       #+#    #+#             */
/*   Updated: 2022/04/06 16:46:22 by tglory           ###   ########lyon.fr   */
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

        // BOOLEANS
        bool operator ==(T* const base) const { return (_ptr == base); }
        bool operator ==(iterator const& b) const { return (_ptr == b._ptr); };
        bool operator !=(iterator const& b) const { return (_ptr != b._ptr); };
        bool operator >(iterator const& b) const { return (_ptr > b._ptr); };
        bool operator <(iterator const& b) const { return (_ptr < b._ptr); };
        bool operator >=(iterator const& b) const { return (_ptr >= b._ptr); };
        bool operator <=(iterator const& b) const { return (_ptr <= b._ptr); };

        // ARITHMETICS
        iterator operator +(difference_type b) const { return (iterator(_ptr + b)); };      // a + n
        iterator operator -(difference_type b) const { return (iterator(_ptr - b)); };      // a - n

        difference_type operator +(iterator b) { return (_ptr + b._ptr); };                 // a + b
        difference_type operator -(iterator b) { return (_ptr - b._ptr); };                 // a - b
        
        iterator& operator +=(difference_type b) {_ptr += b; return *this; };	            // a += b
        iterator& operator -=(difference_type b) {_ptr -= b; return *this; };	            // a -= b


        // INCREMENTERS
        iterator& operator ++() { _ptr++; return ((*this)); }			                    // ++a
        iterator operator ++(int) 															// a++
        {
            T* tmp = _ptr;
            _ptr++;
            return iterator(tmp);
        }
        iterator& operator --() { _ptr--; return ((*this)); }			                    // --a
        iterator operator --(int)														    // a--
        {
            T* tmp = _ptr;
            _ptr--;
            return iterator(tmp);
        }

        //DEREFERENCING & ADDRESS STUFF
        reference operator [](difference_type b) { return (*(_ptr + b)); };					// a[]
        reference operator *() { return *_ptr; }											// *a
        pointer operator ->() { return &(this->operator*()); }								// a->b

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

    template <typename T_L, typename T_R>
    bool operator==(const ft::iterator<T_L> lhs,
                const ft::iterator<T_R> rhs)
    {
        return (lhs.base() == rhs.base());
    }

    template <typename T>
    bool operator!=(const ft::iterator<T> lhs,
                const ft::iterator<T> rhs)
    {
        return (lhs.base() != rhs.base());
    }

    template <typename T_L, typename T_R>
    bool operator!=(const ft::iterator<T_L> lhs,
                const ft::iterator<T_R> rhs)
    {
        return (lhs.base() != rhs.base());
    }

    template <typename T>
    bool operator<(const ft::iterator<T> lhs,
                const ft::iterator<T> rhs)
    {
        return (lhs.base() < rhs.base());
    }

    template <typename T_L, typename T_R>
    bool operator<(const ft::iterator<T_L> lhs, const ft::iterator<T_R> rhs)
    {
        return (lhs.base() < rhs.base());
    }

    template <typename T>
    bool operator>(const ft::iterator<T> lhs, const ft::iterator<T> rhs)
    {
        return (lhs.base() > rhs.base());
    }

    template <typename T_L, typename T_R>
    bool operator>(const ft::iterator<T_L> lhs,
                const ft::iterator<T_R> rhs)
    {
        return (lhs.base() > rhs.base());
    }

    template <typename T>
    bool operator<=(const ft::iterator<T> lhs, const ft::iterator<T> rhs)
    {
        return (lhs.base() <= rhs.base());
    }

    template <typename T_L, typename T_R>
    bool operator<=(const ft::iterator<T_L> lhs, const ft::iterator<T_R> rhs)
    {
        return (lhs.base() <= rhs.base());
    }

    template <typename T>
    bool operator>=(const ft::iterator<T> lhs, const ft::iterator<T> rhs)
    {
        return (lhs.base() >= rhs.base());
    }

    template <typename T_L, typename T_R>
    bool operator>=(const ft::iterator<T_L> lhs, const ft::iterator<T_R> rhs)
    {
        return (lhs.base() >= rhs.base());
    }

    template <class InputIterator>
    typename InputIterator::difference_type operator-(const InputIterator &lhs, const InputIterator&rhs) {
        return lhs.base() - rhs.base();
    }

    template <class InputIterator>
    InputIterator operator+(const typename InputIterator::difference_type &lhs, const InputIterator&rhs) {
        return rhs + lhs;
    }
}
