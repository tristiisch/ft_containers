/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alganoun <alganoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 13:53:21 by alganoun          #+#    #+#             */
/*   Updated: 2022/02/18 19:25:17 by alganoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include "vector/vector.hpp"
#include "vector/reverse_iterator.hpp"
#include "vector/iterator.hpp"

int main()
{
	int tab[] = {0,1,2,3,4,5,6,7,8,9};
	/*depuis un tab d'int*/
	std::vector<int> v(tab, tab + sizeof(tab) / sizeof(int));
	ft::vector<int> myv(tab, tab + sizeof(tab) / sizeof(int));

	//depuis une size
	//std::vector<int> v(9);
	//ft::vector<int> myv(9);
	//for (int i = 1 ; i < 10 ; i++)
	//{
	//	v.push_back(i);
	//	myv.push_back(i);
	//}
	
	for (std::vector<int>::iterator i = v.begin() ; i != v.end() ; i++)
		std::cout << *i << " ";
	std::cout << std::endl;

	for (ft::vector<int>::iterator i = myv.begin() ; i != myv.end() ; i++)
		std::cout << *i << " ";
	std::cout << std::endl;
	
	/*reverse iterator test*/
	std::vector<int>::reverse_iterator i = v.rbegin();
	ft::vector<int>::reverse_iterator x = myv.rbegin();

	/*iterator test*/
	// std::vector<int>::iterator i = v.begin();
	// ft::vector<int>::iterator x = myv.begin();

	std::cout << "True iterator = " << *(i + 3 ) << std::endl;
	std::cout << "My iterator = " << *(x + 3) << std::endl;

	std::cout << "True capacity = " << v.capacity() << std::endl;
	std::cout << "Mycapacity = " << myv.capacity() << std::endl;


	return 0;
}