/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alganoun <alganoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 13:53:21 by alganoun          #+#    #+#             */
/*   Updated: 2022/03/21 16:56:01 by alganoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <map>
#include "./srcs/map.hpp"
#include "srcs/utils/iterator.hpp"
#include "srcs/utils/pair.hpp"

#ifndef TESTED_LIB
# define TESTED_LIB ft
#endif

int		main(void)
{
	TESTED_LIB::map<char, int> mp;
	TESTED_LIB::map<char, int> mp2;
	
	/*while (ite != mp.end())
	{
		std::cout << "Key = " << ite->first << " && Value = " << ite->second <<  std::endl;
		// ++ite;
		ite++;
	}*/
	mp.insert(ft::pair<char,int>('a', 30));
    mp.insert(ft::pair<char,int>('c', 70));
    mp.insert(ft::pair<char,int>('b', 20));
    mp.insert(ft::pair<char,int>('d', 10));
   	mp.insert(ft::pair<char,int>('e', 50));
   	mp.insert(ft::pair<char,int>('0', 101));
    mp.insert(ft::pair<char,int>('f', 40));
    mp.insert(ft::pair<char,int>('g', 60));
    mp.insert(ft::pair<char,int>('3', 100));
	mp.insert(ft::pair<char,int>('6', 100));
	mp.insert(ft::pair<char,int>('4', 100));
	mp.insert(ft::pair<char,int>('1', 100));
	mp.insert(ft::pair<char,int>('2', 100));
	mp.insert(ft::pair<char,int>('%', 100));
	mp.insert(ft::pair<char,int>('1', 100));
	mp.insert(ft::pair<char,int>('E', 100));
	mp.insert(ft::pair<char,int>('B', 100));
	mp.insert(ft::pair<char,int>('D', 100));
	mp.insert(ft::pair<char,int>('A', 100));	
	//mp2.insert(mp.begin(), mp.end());
	TESTED_LIB::map<char, int>::iterator ite = mp.begin();
	while (ite != mp2.end())
	{
		std::cout << "Key = " << ite->first << " && Value = " << ite->second <<  std::endl;
		 ++ite;
		//ite++;
	}
	return (0);
}
