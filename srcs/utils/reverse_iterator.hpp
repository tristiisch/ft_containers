/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alganoun <alganoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 20:12:07 by allanganoun       #+#    #+#             */
/*   Updated: 2022/04/04 22:20:19 by alganoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>
#include "./iterator.hpp"

namespace ft
{


template <class Iterator>
    class reverse_iterator
    {
        public:
            typedef Iterator							iterator_type;
            typedef typename Iterator::value_type		value_type;
            typedef typename Iterator::difference_type	difference_type;
            typedef typename Iterator::pointer			pointer;
            typedef typename Iterator::reference		reference;

            reverse_iterator(): _elem() {}
			
            explicit reverse_iterator (iterator_type it): _elem(it) {}

            template <class Iter>
            reverse_iterator (const reverse_iterator<Iter>& rev_it): _elem(rev_it.base()) {}

            virtual ~reverse_iterator() {}

            iterator_type base() const { return (_elem); }
            reference operator*() const { iterator_type tmp = _elem; return (*(--tmp)); }
            reverse_iterator operator+ (difference_type n) const { return (reverse_iterator(_elem - n)); }
            reverse_iterator& operator++() { --_elem; return (*this); }
            reverse_iterator operator++(int)
            {
                reverse_iterator tmp = *this;
                ++(*this);
                return (tmp);
            }
            reverse_iterator& operator+= (difference_type n) { _elem -= n; return (*this); }
            reverse_iterator& operator-= (difference_type n) { _elem += n; return (*this); }
            reverse_iterator operator- (difference_type n) const { return (reverse_iterator(_elem + n)); }
            difference_type operator +(reverse_iterator b) { return (b._elem + _elem); }; // a + b
	        difference_type operator -(reverse_iterator b) { return (b._elem - _elem); }; // a - b
            reverse_iterator& operator--() { ++_elem; return (*this); }
            reverse_iterator operator--(int)
            {
                reverse_iterator tmp = *this;
                --(*this);
                return (tmp);
            }

            bool operator ==(reverse_iterator const& b) const { return (b._elem == _elem); };
            bool operator !=(reverse_iterator const& b) const { return (b._elem != _elem); };
            bool operator >(reverse_iterator const& b) const { return (b._elem < _elem); }; // à verifier
            bool operator <(reverse_iterator const& b) const { return (b._elem > _elem); }; //à verifier
            bool operator >=(reverse_iterator const& b) const { return (b._elem <= _elem); };//à verifier
            bool operator <=(reverse_iterator const& b) const { return (b._elem >= _elem); };//à verifier

            pointer operator->() const { return &(operator*()); }
            reference operator[] (difference_type n) const { return (this->base()[-n - 1]); }

            static const bool input_iter = false;

        private:
            iterator_type     _elem;
    };
}

