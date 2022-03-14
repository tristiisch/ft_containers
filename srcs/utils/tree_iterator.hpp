/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:42:23 by allanganoun       #+#    #+#             */
/*   Updated: 2022/03/14 17:48:24 by allanganoun      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include "pair.hpp"

template <class T1, class T2>
struct	node
{

	ft::pair	p(T1 key, T2 value);
	node 		*parent;
	node(T1 key, T2 value) : p(key, value){}
};

namespace ft
{
	class tree_iterator
	{
	public :
	private :
		node *n();
	};
}
