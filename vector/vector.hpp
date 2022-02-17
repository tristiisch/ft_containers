/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alganoun <alganoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 17:48:15 by allanganoun       #+#    #+#             */
/*   Updated: 2022/02/17 18:53:59 by alganoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP  

# include "iterator.hpp"

namespace ft
{
	template <typename T>
	class vector
	{
	public:
		typedef Allocator								allocator_type;
		typedef typename Allocator::size_type			size_type;
		typedef typename Allocator::difference_type		difference_type;
		typedef	typename Allocator::reference			reference;
		typedef	typename Allocator::const_reference		const_reference;

		// il faut appeler tous les types d'iterateurs ici et les definir via iterator.hpp, etc.. 

		// constructeur par defaut
		explicit vector(const allocator_type& alloc = allocator_type())
		:	
			_alloc(alloc),
			_start(NULL),
			_end(NULL),
			_end_capacity(NULL)

		{};

		// constructeur avec paramètres
		explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
		:
			_alloc(alloc),
			_start(NULL),
			_end(NULL),
			_end_capacity(NULL)
		{
			_start = _alloc.allocate(n);
			_end = _start;
			_end_capacity = _start + n;
			while (n < 0)
			{
				_alloc.construct(_end, val);
				_end++;
				n--;
			}
		}

		//Destructeur par défaut
		~vector();

	private:
	};



}

#endif
