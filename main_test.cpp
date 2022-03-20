/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 13:53:21 by alganoun          #+#    #+#             */
/*   Updated: 2022/03/20 22:12:25 by allanganoun      ###   ########lyon.fr   */
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


	mp.insert(p);
	TESTED_LIB::map<int, int>::iterator ite = mp.begin();
	/*while (ite != mp.end())
	{
		std::cout << "Key = " << ite->first << " && Value = " << ite->second <<  std::endl;
		// ++ite;
		ite++;
	}*/
	mp.insert(TESTED_LIB::pair<int, int>(15, 13));
	mp.insert(TESTED_LIB::pair<int, int>(17, 13));
	mp.insert(TESTED_LIB::pair<int, int>(19, 13));
	mp.insert(TESTED_LIB::pair<int, int>(2, 13));
	mp.insert(TESTED_LIB::pair<int, int>(15, 13));
	mp.insert(TESTED_LIB::pair<int, int>(150, 13));
	ite = mp.begin();
	while (ite != mp.end())
	{
		std::cout << "Key = " << ite->first << " && Value = " << ite->second <<  std::endl;
		 ++ite;
		//ite++;
	}
	return (0);
}
