/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alganoun <alganoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 22:29:55 by tglory            #+#    #+#             */
/*   Updated: 2022/04/15 11:53:00 by alganoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "./vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
		public:
			typedef Container container_type;
			typedef typename container_type::value_type value_type;
			typedef typename container_type::size_type size_type;
			
			typedef typename container_type::reference reference;
			typedef typename container_type::const_reference const_reference;

			explicit stack(const container_type &container = container_type()) : c(container) {}

			stack(const stack &other) : c(other.c) {}

			~stack() {}

			stack& operator=(const stack &other)
			{
				c = other.c;
				return *this;
			}

			reference top()
			{
				return c.back();
			}

			const_reference top() const
			{
				return c.back();
			}

			bool empty() const
			{
				return c.empty();
			}

			size_type size() const
			{
				return c.size();
			}

			void push(const value_type &value)
			{
				c.push_back(value);
			}

			void pop()
			{
				c.pop_back();
			}

		protected:
			container_type c;
		private:
			template <class T2, class Container2>
			friend bool operator==(const stack<T2, Container2>&, const stack<T2, Container2>&);

			template <class T2, class Container2>
			friend bool operator<(const stack<T2, Container2>&, const stack<T2, Container2>&);
};

	template <class T, class Container>
	bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return lhs.c == rhs.c;
	}

	template <class T, class Container>
	bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Container>
	bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return lhs.c < rhs.c;
	}

	template <class T, class Container>
	bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return !(rhs < lhs);
	}

	template <class T, class Container>
	bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return rhs < lhs;
	}

	template <class T, class Container>
	bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return !(lhs < rhs);
	}
}
