/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tglory_main.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 21:35:17 by tglory            #+#    #+#             */
/*   Updated: 2022/03/28 03:46:41 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <deque>

#if IS_STL
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	#include "srcs/map.hpp"
	#include "srcs/stack.hpp"
	#include "srcs/vector.hpp"
#endif

#include <stdlib.h>

template <typename T, typename U>
std::ostream &operator<<(std::ostream &outputFile, const ft::map<T, U> &map)
{
	outputFile	<< "\033[1;36mSize\t" << map.size()
				<< "\033[0m" << std::endl
				<< "\033[1;36mContent ";
	if (map.empty())
		outputFile << "<empty>";
	else
	{

		typename ft::map<T, U>::const_iterator it = map.begin();
		while (true)
		{
			outputFile << it->first << "=" << it->second;
			if (++it != map.end())
				outputFile << ", ";
			else
				break;
		}
	}
	outputFile << "\033[0m";
	return outputFile;
}

int main()
{
	ft::map<char, int> map;

	map.insert(ft::pair<char,int>('a', 30));
	map.insert(ft::pair<char,int>('c', 70));
	map.insert(ft::pair<char,int>('b', 20));
	/*map.insert(ft::pair<char,int>('d', 10));
	map.insert(ft::pair<char,int>('e', 50));
	map.insert(ft::pair<char,int>('0', 101));
	map.insert(ft::pair<char,int>('f', 40));
	map.insert(ft::pair<char,int>('g', 60));
	map.insert(ft::pair<char,int>('2', 100));*/
	std::cout << map << std::endl;

	return 0;
}