
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
	outputFile	<< "\033[1;36mSize | Capacity | Max_Size\t" << vector.size()
				<< " | " << vector.capacity() << " | " << vector.max_size()
				<< "\033[0m" << std::endl;
	outputFile << "\033[1;36mContent ";
	if (vector.empty())
		outputFile << "<empty>";
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
	outputFile << "\033[0m";
	return outputFile;
}

static void pushPopTest()
{
	ft::vector<int> vector;

	std::cout << "Push/Pop Test :" << std::endl;
	std::cout << vector << std::endl;

	std::cout << std::endl;
	std::cout << "vector.push_back(42)" << std::endl;
	vector.push_back(42);
	std::cout << vector << std::endl;

	std::cout << "vector.push_back(122)" << std::endl;
	vector.push_back(122);
	std::cout << vector << std::endl;

	std::cout << "vector.push_back(99)" << std::endl;
	vector.push_back(99);
	std::cout << vector << std::endl;

	std::cout << "vector.push_back(2)" << std::endl;
	vector.push_back(2);
	std::cout << vector << std::endl;

	std::cout << "vector.push_back(2147483647)" << std::endl;
	vector.push_back(2147483647);
	std::cout << vector << std::endl;

	std::cout << "vector.pop_back()" << std::endl;
	vector.pop_back();
	std::cout << vector << std::endl;

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
	ft::vector<int> vector1(10), vector2, vector3(10), vector4(10);

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
	//std::cout << vector3 << std::endl;
	//vector3.insert(vector3.begin(), vector1.begin(), vector1.end() - 1); //-> capacity not good on
	std::cout << vector3 << std::endl;
	std::cout << "vector4.insert(vector4.begin() + 2, 6, 69)" << std::endl;
	vector4.insert(vector4.begin() + 2, 6, 69);
	std::cout << vector4 << std::endl;
}



static void atTest()
{
	ft::vector<int> vector1;

	std::cout << "At test :" << std::endl;

	vector1.push_back(95623);
	vector1.push_back(8);
	vector1.push_back(6);
	std::cout << vector1 << std::endl;

	std::cout << "vector1.at(0) " << vector1.at(0) << std::endl;
	std::cout << "vector1.at(2) " << vector1.at(2) << std::endl;
	std::cout << "vector1[0] " << vector1[0] << std::endl;
	std::cout << "vector1[2] " << vector1[2] << std::endl;

	try {
		std::cout << "vector1.at(-1) " << vector1.at(-1) << std::endl;
	} catch (std::out_of_range &e) {
		std::cout << "\033[0;31mException on Vector > " << -1 << " is out of range.\033[0m" << std::endl;
	}
	try {
		std::cout << "vector1.at(3) " << vector1.at(3) << std::endl;
	} catch (std::out_of_range &e) {
		std::cout << "\033[0;31mException on Vector > " << 3 << " is out of range.\033[0m" << std::endl;
	}
	std::cout << vector1 << std::endl;

	const ft::vector<int> vector2(vector1);
	std::cout << "At test 2 const :" << std::endl;
	std::cout << vector2 << std::endl;

	std::cout << "vector.at(0) " << vector2.at(0) << std::endl;
	std::cout << "vector.at(2) " << vector2.at(2) << std::endl;
	std::cout << "vector[0] " << vector2[0] << std::endl;
	std::cout << "vector[2] " << vector2[2] << std::endl;

	try {
		std::cout << "vector2.at(-1) " << vector2.at(-1) << std::endl;
	} catch (std::out_of_range &e) {
		std::cout << "\033[0;31mException on Vector > " << -1 << " is out of range.\033[0m" << std::endl;
	}
	try {
		std::cout << "vector2.at(3) " << vector2.at(3) << std::endl;
	} catch (std::out_of_range &e) {
		std::cout << "\033[0;31mException on Vector > " << 3 << " is out of range.\033[0m" << std::endl;
	}
	std::cout << "At test 3 write :" << std::endl;
	ft::vector<int> vector3(vector2);
	std::cout << vector3 << std::endl;
	vector3[0] = 42;
	vector3[2] = 256;
	std::cout << "vector3.at(0) " << vector3.at(0) << std::endl;
	std::cout << "vector3.at(2) " << vector3.at(2) << std::endl;
	std::cout << "vector3[0] " << vector3[0] << std::endl;
	std::cout << "vector3[2] " << vector3[2] << std::endl;
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

	vector2.erase(vector2.begin(), vector2.end());
	std::cout << "vector2.erase(vector2.begin(), vector2.end())" << std::endl;
	std::cout << vector2 << std::endl;
}

static void assignTest()
{
	ft::vector<int> vector1, vector2;

	std::cout << "Assign test :" << std::endl;
	std::cout << vector1 << std::endl;

	vector1.assign(10, 42);
	std::cout << "vector1.assign(10, 42)" << std::endl;
	std::cout << vector1 << std::endl;

	vector2.assign(vector1.begin() + 1, vector1.end() - 1);
	std::cout << "vector2.assign(vector1.begin() + 1, vector1.end() - 1)" << std::endl;
	std::cout << vector2 << std::endl;
}

static void resizeTest()
{
	ft::vector<int> vector;

	std::cout << "Resize test :" << std::endl;
	vector.push_back(95623);
	vector.push_back(6);
	vector.push_back(186);
	std::cout << vector << std::endl;

	vector.resize(2, 42);
	std::cout << "vector.resize(2, 42)" << std::endl;
	std::cout << vector << std::endl;

	vector.resize(10, 42);
	std::cout << "vector.resize(10, 42)" << std::endl; 
	std::cout << vector << std::endl;
}

static void reserveTest()
{
	ft::vector<int> vector;

	std::cout << "Reserve test :" << std::endl;
	std::cout << vector << std::endl;

	vector.reserve(42);
	std::cout << "vector.reserve(42)" << std::endl;
	std::cout << vector << std::endl;

	vector.reserve(1);
	std::cout << "vector.reserve(1)" << std::endl;
	std::cout << vector << std::endl;
}

template<class InputIterator>
static void printIteratorTest(std::string itName, InputIterator begin, InputIterator last)
{
	std::cout << itName << " = " << *begin << std::endl;
	std::cout << "++" << itName << " = " << *++begin << std::endl;
	std::cout << itName << "++ = " << *begin++ << std::endl;
	std::cout << "--" << itName << " = " << *--begin << std::endl;
	std::cout << itName << "-- = " << *begin-- << std::endl;
	std::cout << itName << " + 1 = " << *(begin + 1) << std::endl;
	std::cout << itName << " += 5 = " << *(begin += 5) << std::endl;
	std::cout << itName << " - 1 = " << *(begin - 1) << std::endl;
	std::cout << itName << ".base = " << *begin.base() << std::endl;
	std::cout << itName << " -= 2 = " << *(begin -= 2) << std::endl;
	std::cout << itName << "[3] = " << begin[3] << std::endl;
	std::cout << itName << ".base = " << *begin.base() << std::endl;
	std::cout << "*(&" << itName << ")->base() = " << *(&begin)->base() << std::endl;
	std::cout << itName << " to last >";
	while (begin != last)
		std::cout << " " << *begin++;
	std::cout << std::endl;

	// 1 + begin; -> not working
}

static void iteratorTest()
{
	int tab[] = {86, -2147483648, 6, 9465, 472, 41, 2147483647, 74, 633, 6};
	ft::vector<int> vector(tab, tab + sizeof(tab) / sizeof(int));
	// ft::vector<int>::reverse_iterator it(vector.begin()); -> not working

	std::cout << "Iterator test :" << std::endl;
	std::cout << vector << std::endl;

	std::cout << "*vector.begin() = " << *vector.begin() << std::endl;
	std::cout << "*vector.end() - 1 = " << *(vector.end() - 1) << std::endl;
	printIteratorTest("it", vector.begin(), vector.end());

	ft::vector<int>::reverse_iterator rIt = vector.rbegin();
	std::cout << "Reverse Iterator test :" << std::endl;
	std::cout << "*vector.rbegin() = " << *vector.rbegin() << std::endl;
	std::cout << "*vector.rend() - 1 = " << *(vector.rend() - 1) << std::endl;
	std::cout << vector << std::endl;
	printIteratorTest("reverseIt", vector.rbegin(), vector.rend());

	// const ft::vector<int> constVector(vector);
	// std::cout << "Iterator const test :" << std::endl;
	// std::cout << constVector << std::endl;
	// std::cout << "*constVector.begin() = " << *constVector.begin() << std::endl;
	// std::cout << "*constVector.end() - 1 = " << *(constVector.end() - 1) << std::endl;
	// printIteratorTest("constIt", constVector.begin(), constVector.end());
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
	(void)&pushPopTest;
	pushPopTest();

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

	std::cout << std::endl << std::endl;
	assignTest();
	(void)&assignTest;

	std::cout << std::endl << std::endl;
	resizeTest();
	(void)&resizeTest;

	std::cout << std::endl << std::endl;
	reserveTest();
	(void)&reserveTest;

	std::cout << std::endl << std::endl;
	iteratorTest();
	(void)&iteratorTest;
}
