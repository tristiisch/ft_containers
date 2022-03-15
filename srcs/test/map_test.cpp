
#include <iostream>
#include <iterator>
/**
  * Main de test pour les fonctions associé à Map
  * Permet d'effectuer le test avec notre code ou la STL
  * Il faut changer IS_STL par 0 ou 1
  * "clang++ -D IS_STL" permet de switch sans modifier le code
  */

#ifndef IS_STL
# define IS_STL 1
#endif


#if IS_STL
	#include <map>
	namespace ft = std;
	#warning "Using STL"
#else
	#include "../map.hpp"
#endif

template <typename T, typename U>
std::ostream &operator<<(std::ostream &outputFile, ft::map<T, U> const &map)
{
	outputFile	<< "\033[1;36mSize|Max_Size\t" << map.size()
				<< "|" << map.max_size()
				<< "\033[0m" << std::endl
				<< "\033[1;36mContent ";
	if (map.empty())
		outputFile << "<empty>";
	else
	{

		ft::map<char, int>::const_iterator it = map.begin();
		while (true)
		{
			std::cout << it->first << "=" << it->second;
			if (++it != map.end())
				std::cout << ", ";
			else
				break;
		}
	}
	outputFile << "\033[0m";
	return outputFile;
}

void mapOperatorInsert()
{
	ft::map<char, int> map;

	map['a'] = 30;
	map['c'] = 70;
	map['b'] = 20;
	map['d'] = 10;
	map['e'] = 50;
	map['0'] = 101;
	map['f'] = 40;
	map['g'] = 60;
	map['2'] = 100;

	std::cout << map << std::endl;
}

void mapInsert()
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
}

int main()
{
	mapInsert();

	std::cout << std::endl;
	(void)&mapOperatorInsert;
	//mapOperatorInsert();
}
