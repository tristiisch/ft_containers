/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 13:53:21 by alganoun          #+#    #+#             */
/*   Updated: 2022/03/01 18:47:53 by allanganoun      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include "srcs/vector.hpp"
#include "srcs/utils/reverse_iterator.hpp"
#include "srcs/utils/iterator.hpp"


#include <list>

#define TESTED_TYPE int

int		main(void)
{
	const int size = 5;
	ft::vector<int> vct(size);
	ft::vector<TESTED_TYPE>::iterator it = vct.begin();
	ft::vector<TESTED_TYPE>::const_iterator ite = vct.end();

	for (int i = 1; it != ite; ++i)
		*it++ = i;

	return (0);
}
