/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 22:36:36 by tglory            #+#    #+#             */
/*   Updated: 2022/03/13 21:29:31 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vector_test.cpp"
#include "stack_test.cpp"
//#include "map_test.cpp"

int main()
{
	std::cout << "\033[1;35mVector :\033[0m" << std::endl;
	vector_tests();
	std::cout << "\033[1;35mStack :\033[0m" << std::endl;
	stack_tests();
}
