
#include <iostream>
#include <iterator>
/**
  * Main de test pour les fonctions associé à Vector
  * Permet d'effectuer le test avec notre code ou la STL
  * Il faut changer IS_STL par 0 ou 1
  * "clang++ -D IS_STL" permet de switch sans modifier le code
  */

#ifndef IS_STL
# define IS_STL 0
#endif

#if IS_STL
	#include <vector>
	namespace ft = std;
	#warning "Using STL"
#else
	#include "../vector.hpp"
#endif

template <typename T>
std::ostream &operator<<(std::ostream &outputFile, ft::vector<T> const &vector)
{
	outputFile << "Capacity\t" << vector.capacity() << std::endl;
	outputFile << "Size\t\t" << vector.size() << std::endl;
	outputFile << "Max Size\t" << vector.max_size() << std::endl;
	outputFile << "Content\t\t";
	if (vector.empty())
		outputFile << "empty";
	else
	{
		typename ft::vector<T>::const_iterator it = vector.begin();
		while (it != vector.end())
		{
			outputFile << *it;
			if (it + 1 != vector.end())
				outputFile << ", ";
			++it;
		}
	}
	return outputFile;
}

static void basicTest()
{
	ft::vector<int> vector;

	std::cout << "Basic Test :" << std::endl;
	std::cout << vector << std::endl;

	std::cout << std::endl;
	std::cout << "vector.push_back(42)" << std::endl;
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

	std::cout << "vector.pop_back()" << std::endl;
	vector.pop_back();
	std::cout << vector << std::endl;
	std::cout << std::endl;

	std::cout << "vector.clear()" << std::endl;
	vector.clear();
	std::cout << vector << std::endl;
}

static void outRangePop()
{
	ft::vector<int> vector(10);

	std::cout << "Out range pop_back Test :" << std::endl;

	vector.pop_back();
	std::cout << vector << std::endl;
}

static void segfault_test()
{
	ft::vector<int> vector;

	std::cout << "SegFault test" << std::endl;
	std::cout << vector << std::endl;

	std::cout << "vector.pop_back()" << std::endl;
	vector.pop_back();
	std::cout << vector << std::endl;
	std::cout << std::endl;
}

static void insertTest()
{
	ft::vector<int> vector1(10), vector2, vector3(10);

	std::cout << "Insert test 1:" << std::endl;

	vector1.push_back(95623);
	vector1.push_back(150);
	vector1.push_back(6);
	std::cout << vector1 << std::endl;
	std::cout << "vector.insert(vector.begin(), 8) and more" << std::endl;
	vector1.insert(vector1.begin(), 8);
	vector1.insert(vector1.end(), 999);
	vector1.insert(vector1.begin() + 6, 42);
	vector1.insert(vector1.begin() + 8, 1000);
	std::cout << vector1 << std::endl;


	std::cout << "Insert test 2:" << std::endl;
	vector2.push_back(95623);
	vector2.push_back(150);
	vector2.push_back(6);

	vector3.insert(vector3.begin(), vector2.begin(), vector2.end());
	std::cout << vector3 << std::endl;
	/*vector3.insert(vector3.begin(), vector1.begin(), vector1.end() - 1); // NOT WORKING
	std::cout << vector3 << std::endl;*/
}

static void atTest()
{
	ft::vector<int> vector;

	std::cout << "At test :" << std::endl;

	vector.push_back(95623);
	vector.push_back(8);
	vector.push_back(6);
	std::cout << vector << std::endl;

	std::cout << "vector.at(0) " << vector.at(0) << std::endl;
	std::cout << "vector.at(2) " << vector.at(2) << std::endl;
	std::cout << "vector[0] " << vector[0] << std::endl;
	std::cout << "vector[2] " << vector[2] << std::endl;

	try {
		std::cout << "vector.at(-1) " << vector.at(-1) << std::endl;
	} catch (std::out_of_range &e) {
		std::cout << "\033[0;31mException on Vector > " << -1 << " is out of range.\033[0m" << std::endl;
	}
	try {
		std::cout << "vector.at(3) " << vector.at(3) << std::endl;
	} catch (std::out_of_range &e) {
		std::cout << "\033[0;31mException on Vector > " << 3 << " is out of range.\033[0m" << std::endl;
	}
	std::cout << vector << std::endl;
}

static void eraseTest()
{
	ft::vector<int> vector1, vector2;

	std::cout << "Erase test 1:" << std::endl;
	vector1.push_back(95623);
	vector1.push_back(8);
	vector1.push_back(6);
	vector1.push_back(42);
	std::cout << vector1 << std::endl;

	vector1.erase(vector1.begin() + 1);
	std::cout << "vector1.erase(vector1.begin() + 1)" << std::endl;
	std::cout << vector1 << std::endl;

	std::cout << "Erase test 2:" << std::endl;
	vector2.push_back(95623);
	vector2.push_back(8);
	vector2.push_back(6);
	vector2.push_back(42);
	std::cout << vector2 << std::endl;

	vector2.erase(vector2.begin() + 1, vector2.end() - 1);
	std::cout << "vector2.erase(vector2.begin() + 1, vector2.end() - 1)" << std::endl;
	std::cout << vector2 << std::endl;
}

static void assignTest()
{
	ft::vector<int> vector;

	std::cout << "Assign test :" << std::endl;
	std::cout << vector << std::endl;

	vector.assign(10, 42);
	std::cout << "vector.assign(10, 42)" << std::endl;
	std::cout << vector << std::endl;
}
/*
int main()
{
	(void)&basicTest;
	(void)&insertTest;
	(void)&atTest;
	(void)&segfault_test;
	(void)&outRangePop;
	(void)&assignTest;
	(void)&eraseTest;


	ft::vector<int> vector1;

	vector1.push_back(95623);
	vector1.push_back(8);
	vector1.push_back(6);

	std::cout << vector1.end() - vector1.begin() << std::endl;
}*/


int main()
{
	(void)&basicTest;
	basicTest();

	std::cout << std::endl << std::endl;
	(void)&outRangePop;
	outRangePop();

	//std::cout << std::endl << std::endl;
	(void)&segfault_test;
	// segfault_test();

	std::cout << std::endl << std::endl;
	insertTest();
	(void)&insertTest;
	
	std::cout << std::endl << std::endl;
	atTest();
	(void)&atTest;	

	std::cout << std::endl << std::endl;
	eraseTest();
	(void)&eraseTest;

	//std::cout << std::endl << std::endl;
	//assignTest(); // NOT WORKING
	(void)&assignTest;
}
