/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tglory_main.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 21:35:17 by tglory            #+#    #+#             */
/*   Updated: 2022/03/28 21:47:30 by tglory           ###   ########lyon.fr   */
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

static void mapInsert()
{
	ft::map<char, int> map1, map2;
	ft::map<int, int> map3;

	std::cout << "Map Basic insert :" << std::endl;
	map1.insert(ft::pair<char,int>('a', 30));
	map1.insert(ft::pair<char,int>('c', 70));
	map1.insert(ft::pair<char,int>('b', 20));
	map1.insert(ft::pair<char,int>('d', 10));
	map1.insert(ft::pair<char,int>('e', 50));
	map1.insert(ft::pair<char,int>('0', 101));
	map1.insert(ft::pair<char,int>('f', 40));
	map1.insert(ft::pair<char,int>('g', 60));
	map1.insert(ft::pair<char,int>('2', 100));
	
	std::cout << map1 << std::endl;

	std::cout << "Map Iterator insert :" << std::endl;
  	ft::map<char,int>::iterator it = map1.begin();
  	map1.insert(it, ft::pair<char,int>('Z', 300));
	map1.insert(it, ft::pair<char,int>('5', 400));
	std::cout << map1 << std::endl;

	std::cout << "Map First/Last insert :" << std::endl;
	map2.insert(map1.begin(), map1.find('e'));
	std::cout << map2 << std::endl;

	srand(time(NULL));
	std::cout << "Map Random Basic insert :" << std::endl;
	for (int i = 0; i < 100; ++i)
		map3.insert(ft::pair<int,int>((rand() % 1000), i));
	std::cout << map3 << std::endl;
}

int main()
{
	/*ft::map<char, int> map;

	map.insert(ft::pair<char,int>('a', 30));
	map.insert(ft::pair<char,int>('c', 70));
	map.insert(ft::pair<char,int>('b', 20));
	map.insert(ft::pair<char,int>('d', 10));
	map.insert(ft::pair<char,int>('e', 50));
	map.insert(ft::pair<char,int>('0', 101));
	map.insert(ft::pair<char,int>('f', 40));
	map.insert(ft::pair<char,int>('g', 60));
	map.insert(ft::pair<char,int>('2', 100));
	std::cout << map << std::endl;*/
	//mapInsert();

	ft::map<char,int> mymap;

	// first insert function version (single parameter):
	mymap.insert ( ft::pair<char,int>('a',100) );
	mymap.insert ( ft::pair<char,int>('z',200) );

	ft::pair<ft::map<char,int>::iterator,bool> ret;
	ret = mymap.insert ( ft::pair<char,int>('z',500) );
	if (ret.second==false) {
		std::cout << "element 'z' already existed";
		std::cout << " with a value of " << ret.first->second << '\n';
	}

	// second insert function version (with hint position):
	ft::map<char,int>::iterator it = mymap.begin();
	mymap.insert (it, ft::pair<char,int>('b',300));  // max efficiency inserting
	mymap.insert (it, ft::pair<char,int>('c',400));  // no max efficiency inserting

	// third insert function version (range insertion):
	ft::map<char,int> anothermap;
	anothermap.insert(mymap.begin(),mymap.find('c'));

	// showing contents:
	std::cout << "mymap contains:\n";
	for (it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "anothermap contains:\n";
	for (it=anothermap.begin(); it!=anothermap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	return 0;
}