/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tglory_main.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 21:35:17 by tglory            #+#    #+#             */
/*   Updated: 2022/03/24 21:39:47 by tglory           ###   ########lyon.fr   */
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
	return 0;
}