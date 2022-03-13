
#include <iostream>
#include <iterator>
/**
  * Main de test pour les fonctions associé à Map
  * Permet d'effectuer le test avec notre code ou la STL
  * Il faut changer IS_STL par 0 ou 1
  * "clang++ -D IS_STL" permet de switch sans modifier le code
  */

#ifndef IS_STL
# define IS_STL 0
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
		typename ft::map<T, U>::const_iterator it = map.begin();
		while (it != map.end())
		{
			outputFile << *it;
			if (it + 1 != map.end())
				outputFile << ", ";
			++it;
		}
	}
	outputFile << "\033[0m";
	return outputFile;
}

int main()
{
	ft::map<std::string, int> map;

	map['a'] = 10;
	map['b'] = 30;
	map['c'] = 50;
	map['d'] = 70;

	std::cout << map << std::endl;
}
