/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alganoun <alganoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 13:53:21 by alganoun          #+#    #+#             */
/*   Updated: 2022/02/23 17:49:33 by alganoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include "srcs/vector.hpp"
#include "srcs/utils/reverse_iterator.hpp"
#include "srcs/utils/iterator.hpp"


typedef std::vector<int> vector;
typedef ft::vector<int> myvector;

void print_vector(vector v, myvector myv)
{
	for (std::vector<int>::iterator i = v.begin() ; i != v.end() ; i++)
		std::cout << *i << " ";
	std::cout << std::endl;

	for (ft::vector<int>::iterator i = myv.begin() ; i != myv.end() ; i++)
		std::cout << *i << " ";
	std::cout << std::endl;
}

int main()
{
	int tab[] = {0,1,2,3,4,5,6,7,8,9};
	/*depuis un tab d'int*/
	vector v;
	myvector myv;
	//std::vector<int> v(tab, tab + sizeof(tab) / sizeof(int));
	//ft::vector<int> myv(tab, tab + sizeof(tab) / sizeof(int));

	//depuis une size
	//std::vector<int> v(9);
	//ft::vector<int> myv(9);
	//for (int i = 1 ; i < 10 ; i++)
	//{
	//	v.push_back(i);
	//	myv.push_back(i);
	//}
	
	//print_vector(v, myv);

	/*reverse iterator test*/
	std::vector<int>::reverse_iterator i = v.rbegin();
	ft::vector<int>::reverse_iterator x = myv.rbegin();

	v.insert(v.end(), 42);
	myv.insert(myv.end(), 42);
	v.insert(v.begin(), 2, 21);
	myv.insert(myv.begin(), 2, 21);
	v.insert(v.end() - 2, 42);
	myv.insert(myv.end() - 2, 42);

	
	/*iterator test*/
	// std::vector<int>::iterator i = v.begin();
	// ft::vector<int>::iterator x = myv.begin();

	// std::cout << "True iterator = " << *(i + 3 ) << std::endl;
	// std::cout << "My iterator = " << *(x + 3) << std::endl;
// 
	print_vector(v, myv);

	//v.erase(v.begin() + 2, v.begin() + 5);
	//myv.erase(myv.begin() + 2, myv.begin() + 5);
//
	//std::cout << std::endl;
	////print_vector(v, myv);
	std::cout << "True capacity = " << v.capacity() << std::endl;
	std::cout << "Mycapacity = " << myv.capacity() << std::endl;
//
//
	std::cout << "True size = " << v.size() << std::endl;
	std::cout << "My size = " << myv.size() << std::endl;
//
	return 0;
}