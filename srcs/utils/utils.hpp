/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 01:39:02 by tglory            #+#    #+#             */
/*   Updated: 2022/02/22 01:02:19 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define C_RESET "\033[0m"
#define C_YELLOW "\033[33m"
#define C_RED "\033[31m"
#define C_GREEN "\033[32m"
#define C_CYAN "\033[36m"

namespace ft {

	template<class InputIter1, class InputIter2>
	bool equal(InputIter1 first1, InputIter1 last1, InputIter2 first2) {
		while (first1 != last1) {
			if (!(*(first1++) == *(first2++))) {
				return false;
			}
		}

		return true;
	}

	template<class InputIter1, class InputIter2>
	bool lexicographical_compare(InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2) {
		while (first1 != last1) {
			// Check if we reach the end of the second iterator or if
			// the element in the first iterator is bigger than the one
			// in the second.
			if (first2 == last2 || *first2 < *first1) {
				return false;
			}

			if (*first1 < *first2) {
				return true;
			}

			++first1;
			++first2;
		}

		return (first2 != last2);
	}
}