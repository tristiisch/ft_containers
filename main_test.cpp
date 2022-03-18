/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alganoun <alganoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 13:53:21 by alganoun          #+#    #+#             */
/*   Updated: 2022/03/18 16:36:49 by alganoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "./srcs/map.hpp"
#include "srcs/utils/iterator.hpp"
#include "srcs/utils/pair.hpp"


#define TESTED_LIB ft

int		main(void)
{
	TESTED_LIB::map<int, int> mp;
	TESTED_LIB::pair<int, int> p(12, 13);
	TESTED_LIB::map<int, int>::iterator ite = mp.begin();

	mp.insert(p);
	//while (ite != mp.end())
	//	std::cout << ite << std::endl;
	return (0);
}
