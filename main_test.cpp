/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 13:53:21 by alganoun          #+#    #+#             */
/*   Updated: 2022/03/02 20:22:14 by allanganoun      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include "srcs/vector.hpp"
#include "srcs/utils/reverse_iterator.hpp"
#include "srcs/utils/iterator.hpp"


#define TESTED_TYPE int

int		main(void)
{
	ft::vector<TESTED_TYPE> vct;
	ft::vector<TESTED_TYPE>::iterator it = vct.begin();
	ft::vector<TESTED_TYPE>::const_iterator cit = vct.begin();

	//ft::vector<TESTED_TYPE>::reverse_iterator rit(it);

	//ft::vector<TESTED_TYPE>::const_reverse_iterator crit(rit);
	//ft::vector<TESTED_TYPE>::const_reverse_iterator crit_(it);
	//ft::vector<TESTED_TYPE>::const_reverse_iterator crit_2(cit);

	/* error expected
	ft::vector<TESTED_TYPE>::reverse_iterator rit_(crit);
	ft::vector<TESTED_TYPE>::reverse_iterator rit2(cit);
	ft::vector<TESTED_TYPE>::iterator it2(rit);
	ft::vector<TESTED_TYPE>::const_iterator cit2(crit);
	*/

	std::cout << "OK" << std::endl;
	return (0);
}
