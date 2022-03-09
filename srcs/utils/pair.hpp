/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alganoun <alganoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 16:43:18 by alganoun          #+#    #+#             */
/*   Updated: 2022/03/09 18:00:22 by alganoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{
	template<typename T1, typename T2>
	class pair
	{
	public:
		typedef T1		first_type;
		typedef T2		second_type;

		pair(){};
	private:
		first_type 		first;
		second_type		second;
	};
		
}

#endif