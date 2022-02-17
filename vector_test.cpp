
#include <iostream>

/**
  * Main de test pour les fonctions associé à Vector
  * Permet d'effectuer le test avec notre code ou la STL
  * Il faut changer <nb> de 'if <nb>' par 0 ou 1
  */

#if 0
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
	#warning "Using STL"
#else
	#include "vector/iterator.hpp"
	#include "vector/vector.hpp"
#endif

template <typename T>
std::ostream &operator<<(std::ostream &outputFile, ft::vector<T> const &vector)
{
	outputFile << "Capacity\t" << vector.capacity() << std::endl;
	outputFile << "Size\t\t" << vector.size() << std::endl;
	outputFile << "Max Size\t" << vector.max_size() << std::endl;

	std::cout << "Content\t\t";
	if (!vector.empty())
	{
		auto it = vector.begin();
		while (it != vector.end())
		{
			std::cout << *it;
			if (it + 1 != vector.end())
				std::cout << ", ";
			it++;
		}
	}
	else
	{
		std::cout << "empty";
	}
	return outputFile;
}

int main()
{
	ft::vector<int> vector;

	std::cout << vector << std::endl;

	std::cout << std::endl;
	std::cout << "vector.insert(42)" << std::endl;
	vector.push_back(42);
	std::cout << vector << std::endl;
	std::cout << std::endl;

	std::cout << "vector.push_back(122)" << std::endl;
	vector.push_back(122);
	std::cout << vector << std::endl;
	std::cout << std::endl;

	std::cout << "vector.push_back(99)" << std::endl;
	vector.push_back(99);
	std::cout << vector << std::endl;
	std::cout << std::endl;

	std::cout << "vector.push_back(2)" << std::endl;
	vector.push_back(2);
	std::cout << vector << std::endl;
	std::cout << std::endl;

	std::cout << "vector.push_back(2147483647)" << std::endl;
	vector.push_back(2147483647);
	std::cout << vector << std::endl;
	std::cout << std::endl;

	std::cout << "vector.clear()" << std::endl;
	vector.clear();
	std::cout << vector << std::endl;
}
