
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
		for (typename ft::map<T, U>::const_iterator it = map.begin(); it != map.end(); ++it)
		{
			outputFile << it->first << " " << it->second.first << " " << it->second.second << "\n";
			/*outputFile << *it;
			if (it + 1 != map.end())
				outputFile << ", ";*/
			outputFile << " ";
		}
	}
	outputFile << "\033[0m";
	return outputFile;
}

int main()
{
	ft::map<char, int> map;

	map['a'] = 30;
	map['c'] = 70;
	map['b'] = 20;
	map['d'] = 10;
	map['e'] = 50;
	map['f'] = 40;
	map['g'] = 60;
	map['0'] = 100;
	map['2'] = 100;

	for (typename ft::map<char, int>::const_iterator it = map.begin(); it != map.end(); ++it)
	{
		// std::cout << it->first << " " << it->second << " " << it->second.second << "\n";
		std::cout << it->first << " " << it->second << std::endl;

		it._M_node;
	}
	//std::cout << map << std::endl;
}
