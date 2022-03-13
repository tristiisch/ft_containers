
#include <iostream>
#include <iterator>
/**
  * Main de test pour les fonctions associé à stack
  * Permet d'effectuer le test avec notre code ou la STL
  * Il faut changer IS_STL par 0 ou 1
  * "clang++ -D IS_STL" permet de switch sans modifier le code
  */

#ifndef IS_STL
# define IS_STL 1
#endif

#if IS_STL
	#include <stack>
	#include <vector>
	namespace ft = std;
	#warning "Using STL"
#else
	#include "../stack.hpp"
#endif

template <typename T>
std::ostream &operator<<(std::ostream &outputFile, ft::stack<T> const &stack)
{
	outputFile << "\033[1;36mSize\t" << stack.size() << "\033[0m" << std::endl;
	outputFile << "\033[1;36mContent ";
	if (stack.empty())
		outputFile << "<empty>";
	else
	{
		outputFile << "<can't show content now>";
		/*typename ft::vector<T>::const_iterator it = stack.c;
		while (it != stack.end())
		{
			outputFile << *it;
			if (it + 1 != stack.end())
				outputFile << ", ";
			++it;
		}*/
	}
	outputFile << "\033[0m";
	return outputFile;
}

static void stackPushPopTest()
{
	ft::stack<int> stack;

	std::cout << "Push/Pop Test :" << std::endl;
	std::cout << stack << std::endl;

	std::cout << std::endl;
	std::cout << "stack.push(42)" << std::endl;
	stack.push(42);
	std::cout << stack << std::endl;

	std::cout << "stack.push(122)" << std::endl;
	stack.push(122);
	std::cout << stack << std::endl;

	std::cout << "stack.push(99)" << std::endl;
	stack.push(99);
	std::cout << stack << std::endl;

	std::cout << "stack.push(2)" << std::endl;
	stack.push(2);
	std::cout << stack << std::endl;

	std::cout << "stack.push(2147483647)" << std::endl;
	stack.push(2147483647);
	std::cout << stack << std::endl;

	std::cout << "stack.pop()" << std::endl;
	stack.pop();
	std::cout << stack << std::endl;
}

static void stackOutRangePop()
{
	ft::stack<int> stack;

	std::cout << "Out range pop Test :" << std::endl;

	stack.pop();
	std::cout << stack << std::endl;
}

void stack_tests()
{
	(void)&stackPushPopTest;
	stackPushPopTest();

	std::cout << std::endl << std::endl;
	(void)&stackOutRangePop;
	stackOutRangePop();
}
