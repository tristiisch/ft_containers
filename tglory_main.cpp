/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tglory_main.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 21:35:17 by tglory            #+#    #+#             */
/*   Updated: 2022/03/29 21:23:23 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <deque>
#include <list>

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
/*
int main()
{
	ft::map<char, int> map;

	map.insert(ft::pair<char,int>('a', 30));
	map.insert(ft::pair<char,int>('c', 70));
	map.insert(ft::pair<char,int>('b', 20));
	map.insert(ft::pair<char,int>('d', 10));
	map.insert(ft::pair<char,int>('e', 50));
	map.insert(ft::pair<char,int>('0', 101));
	map.insert(ft::pair<char,int>('f', 40));
	map.insert(ft::pair<char,int>('g', 60));
	map.insert(ft::pair<char,int>('2', 100));
	std::cout << map << std::endl;
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
}*/

template <typename T>
T	inc(T it, int n)
{
	while (n-- > 0)
		++it;
	return (it);
}

template <typename T>
T	dec(T it, int n)
{
	while (n-- > 0)
		--it;
	return (it);
}

#define TESTED_NAMESPACE ft
#define T1 char
#define T2 int
typedef ft::pair<const T1, T2> T3;

template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "value: " << iterator->first;
	if (nl)
		o << std::endl;
	return ("");
}

template <typename T_SET>
void	printSize(T_SET const &st, bool print_content = 1)
{
	std::cout << "size: " << st.size() << std::endl;
	std::cout << "max_size: " << st.max_size() << std::endl;
	if (print_content)
	{
		typename T_SET::const_iterator it = st.begin(), ite = st.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << printPair(it, false) << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}
/*
template <typename T>
void	printReverse(TESTED_NAMESPACE::multiset<T> &st)
{
	typename TESTED_NAMESPACE::multiset<T>::iterator it = st.end(), ite = st.begin();

	std::cout << "printReverse:" << std::endl;
	while (it-- != ite)
		std::cout << "-> " << printPair(it, false) << std::endl;
	std::cout << "_______________________________________________" << std::endl;
}*/


int		main(void)
{
	std::list<T3> lst;
	unsigned int lst_size = 5;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(T3('a' + i, (i + 1) * 7));

	TESTED_NAMESPACE::map<T1, T2> mp(lst.begin(), lst.end());
	TESTED_NAMESPACE::map<T1, T2>::iterator it_ = mp.begin();
	TESTED_NAMESPACE::map<T1, T2>::reverse_iterator it(it_), ite;
	printSize(mp);

	std::cout << (it_ == it.base()) << std::endl;
	std::cout << (it_ == dec(it, 3).base()) << std::endl;

	std::cout << it.base() << std::endl;
	std::cout << inc(it.base(), 1) << std::endl;

	std::cout << "TEST OFFSET" << std::endl;
	--it;
	std::cout << *it << std::endl;
	std::cout << it.base() << std::endl;

	it = mp.rbegin(); ite = mp.rend();
	while (it != ite)
		std::cout << "[rev] " << *it++ << std::endl;
	//printReverse(mp);

	return (0);
}

