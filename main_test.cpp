#include <map>
#include <iostream>
#include <cstddef>
#include <list>

#include "srcs/map.hpp"

#define T1 char
#define T2 int
typedef ft::pair<const T1, T2> T3;

int		main(void)
{
	ft::map<char, int> mp;

	mp.insert(T3('a', 2));
	mp.insert(T3('b', 2));
	mp.insert(T3('d', 2));
	mp.insert(T3('e', 2));
	mp.insert(T3('f', 2));
	mp.insert(T3('g', 2));
	mp.insert(T3('h', 2));

	ft::map<T1, T2>::iterator it = mp.begin(), ite = mp.end();
	while (ite != it)
		std::cout << (*(--ite)).first << std::endl;

	mp.clear();
	//std::map<T1, T2> mp_range(it, --(--ite));

}
