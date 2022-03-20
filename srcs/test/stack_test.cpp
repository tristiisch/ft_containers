
#include <iostream>
#include <iterator>
#include <stdlib.h>
/**
  * Main de test pour les fonctions associé à stack
  * Permet d'effectuer le test avec notre code ou la STL
  * Il faut changer IS_STL par 0 ou 1
  * "clang++ -D IS_STL" permet de switch sans modifier le code
  */

#ifndef IS_STL
# define IS_STL 0
#endif

#if IS_STL
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	#include "../stack.hpp"
#endif

template <typename T>
std::ostream &operator<<(std::ostream &outputFile, ft::stack<T> const &stack)
{
	ft::stack<T> stackCopy = stack;
	outputFile << "\033[1;36mSize\t" << stackCopy.size() << "\033[0m" << std::endl;
	outputFile << "\033[1;36mContent ";
	if (stackCopy.empty())
		outputFile << "<empty>";
	else
	{
		while (!stackCopy.empty())
		{
			T w = stackCopy.top();
			outputFile << w;
			stackCopy.pop();
			if (stackCopy.size() >= 2)
				outputFile << ", ";
		}
	}
	outputFile << "\033[0m";
	return outputFile;
}

static void stackPushPopTest()
{
	ft::stack<int> stack1, stack2;

	std::cout << "Push/Pop Test :" << std::endl;
	std::cout << stack1 << std::endl;

	std::cout << "stack.push(42)" << std::endl;
	stack1.push(42);
	std::cout << stack1 << std::endl;

	std::cout << "stack.push(122)" << std::endl;
	stack1.push(122);
	std::cout << stack1 << std::endl;

	std::cout << "stack.push(99)" << std::endl;
	stack1.push(99);
	std::cout << stack1 << std::endl;

	std::cout << "stack.push(2)" << std::endl;
	stack1.push(2);
	std::cout << stack1 << std::endl;

	std::cout << "stack.push(2147483647)" << std::endl;
	stack1.push(2147483647);
	std::cout << stack1 << std::endl;

	std::cout << "stack.pop()" << std::endl;
	stack1.pop();
	std::cout << stack1 << std::endl;

	for (int i = 0; i < 100; ++i)
		stack2.push((rand() % 100) + 1);
	std::cout << stack2 << std::endl;
}

void stack_tests()
{
	(void)&stackPushPopTest;
	stackPushPopTest();
}
