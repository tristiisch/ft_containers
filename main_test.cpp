/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alganoun <alganoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 13:53:21 by alganoun          #+#    #+#             */
/*   Updated: 2022/02/18 15:57:40 by alganoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>

int main()
{
	int tab[] = {0,1,2,3,4,5,6,7,8,9};
	std::vector<int> v(tab, tab + sizeof(tab) / sizeof(int));

	std::vector<int>::reverse_iterator i = v.rbegin();
	
	std::cout << "value = " << *(i + 3) << std::endl;

	while ( i != v.rend())
	{	
		std::cout << *i << std::endl;
		i++;
	}
	return 0;
}