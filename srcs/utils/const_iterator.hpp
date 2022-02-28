/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const_iterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:26:33 by allanganoun       #+#    #+#             */
/*   Updated: 2022/02/28 19:56:26 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "AIterator.hpp"

namespace ft
{


template <typename T>
class	const_iterator : public AIterator<T>
{
	public:
		const_iterator(const const_iterator<T> &src) { *this = src; } ;
		const_iterator(void) : AIterator<T>::_ptr(NULL){};
		const_iterator(typename AIterator<T>::pointer ptr) { AIterator<T>::_ptr = ptr; };
	};

}