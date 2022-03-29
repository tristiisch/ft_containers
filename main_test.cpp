#include <map>
#include <iostream>
#include <cstddef>
#include <list>

#include "srcs/map.hpp"

#define T1 char
#define T2 int
typedef ft::pair<const T1, T2> T3;

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

int		main(void)
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
  	map1.insert(ft::pair<char,int>('Z', 300));
	map1.insert(ft::pair<char,int>('5', 400));
	std::cout << map1 << std::endl;

	//std::cout << "Map First/Last insert :" << std::endl;
	//map2.insert(map1.begin(), map1.find('e'));
	//std::cout << map2 << std::endl;
	//srand(time(NULL));
	//std::cout << "Map Random Basic insert :" << std::endl;
	//for (int i = 0; i < 15; ++i)
	//	map3.insert(ft::pair<int,int>((rand() % 1000), i));
	//std::cout << map3 << std::endl;

}
