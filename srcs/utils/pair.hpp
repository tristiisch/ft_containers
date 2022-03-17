/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 02:38:50 by tglory            #+#    #+#             */
/*   Updated: 2022/03/18 00:14:51 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
template <class T1, class T2>
class pair
{
	public:
		typedef T1 first_type;
		typedef T2 second_type;

		pair() : first(), second() {
		}

		~pair() {
		}

		pair(const first_type &x, const second_type &y) : first(x), second(y) {
		}

		template<class U1, class U2>
		pair(const pair<U1, U2> &p) : first(p.getKey()), second(p.getValue()) {
		}

		pair& operator=(const pair &other) {
			first = other.getKey();
			second = other.getValue();
			return *this;
		}

		// To verify
		first_type getKey() const
		{
			return first;
		}

		// To verify
		second_type getValue() const
		{
			return second;
		}

	private:
		first_type first;
		second_type second;
};

template<class T1, class T2>
pair<T1, T2> make_pair(T1 x, T2 y) {
	return ft::pair<T1, T2>(x, y);
}

template <class T1, class T2>
bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
	return lhs.first == rhs.first && lhs.second == rhs.second;
}

template <class T1, class T2>
bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
	return !(lhs == rhs);
}

template <class T1, class T2>
bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
	return lhs.first < rhs.first || (lhs.first == rhs.first && lhs.second < rhs.second);
}

template <class T1, class T2>
bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
	return !(rhs < lhs);
}

template <class T1, class T2>
bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
	return rhs < lhs;
}

template <class T1, class T2>
bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
	return !(lhs < rhs);
}
}
