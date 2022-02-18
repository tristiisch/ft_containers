/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 17:48:15 by allanganoun       #+#    #+#             */
/*   Updated: 2022/02/18 02:52:50 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP  

# include <memory>
# include <iostream>
# include "iterator.hpp"

namespace ft
{
	template<typename T, typename Allocator = std::allocator<T> >
	class vector
	{
	public:
		typedef typename Allocator::size_type			size_type;
		typedef typename Allocator::difference_type		difference_type;
		typedef	typename Allocator::reference			reference;
		typedef	typename Allocator::const_reference		const_reference;
		typedef typename Allocator::pointer				pointer;

		typedef ft::vectorIterator<T>					iterator;
		typedef ft::vectorIterator<const T>				const_iterator;

		// il faut appeler tous les types d'iterateurs ici et les definir via iterator.hpp, etc.. 

		// constructeur par defaut
		explicit vector(const Allocator& alloc = Allocator())
		:	
			_alloc(alloc),
			_start(NULL),
			_end(NULL),
			_end_capacity(NULL)

		{};

		// constructeur avec capacity par default
		explicit vector(size_type n, const T& val = T(), const Allocator& alloc = Allocator())
		:
			_alloc(alloc),
			_start(NULL),
			_end(NULL),
			_end_capacity(NULL)
		{
			_start = _alloc.allocate(n);
			_end = _start;
			_end_capacity = _start + n;
			for (; n < 0; --n)
				_alloc.construct(_end++, val);
		}

		//Destructeur par défaut
		~vector()
		{
			_alloc.deallocate(_start, this->capacity());
		}

		// Ajoute une valeur au Top du vector
		// Si la capacity est dépassé, alloue le double de la capacity actuelle
		void push_back(const T& value)
		{
			if (_end == _end_capacity)
			{
				int next_capacity = (this->size() > 0) ? this->size() * 2 : 1;
				this->reserve(next_capacity);
			}
			_alloc.construct(_end, value);
			++_end;
		}

		// Supprime la valeur au Top du vector
		void pop_back()
		{
			if (empty())
				return;
			_alloc.destroy(_end--);
		}

		// Réalloue de la mémoire pour avoir une capacity de new_cap
		// Si capacity >= new_cap -> ne fait rien
		// Si new_cap > ram dispo -> renvoie une erreur
		// Sinon réalloue toute le vector
		void reserve(size_type new_cap)
		{
			if (new_cap > this->max_size())
				throw (std::length_error("vector::reserve > new capacity greater than max size"));
			else if (new_cap > this->capacity())
			{
				pointer prev_start = _start;
				pointer prev_end = _end;
				size_type prev_size = this->size();
				size_type prev_capacity = this->capacity();
				
				_start = _alloc.allocate(new_cap);
				_end_capacity = _start + new_cap;
				_end = _start;
				while (prev_start != prev_end)
					_alloc.construct(_end++, *prev_start++);
				_alloc.deallocate(prev_start - prev_size, prev_capacity);
			}
		}

		// Supprime les valeurs. N'affecte pas la memoire allouée
		void clear()
		{
			for (; _start != _end; --_end)
				_alloc.destroy(_end);
		}

		// iterator from start
		iterator begin()
		{
			return _start;
		}

		// iterator from start
		const_iterator begin() const
		{
			return _start;
		}

		iterator end()
		{
			return _end;
		}

		const_iterator end() const
		{
			return _end;
		}

		// Number of elements
		size_type size() const
		{
			return _end - _start;
		}

		// Le nombre maximum d'octet que notre vector peux contenir.
		// Défini en fonction de la RAM
		size_type max_size() const
		{
			return Allocator().max_size();
		}

		// Max elements
		size_type capacity() const
		{
			return _end_capacity - _start;
		}

		bool empty() const
		{
			return this->size() == 0;
		}

		reference front()
		{
			return *_start;
		}

		const_reference front() const
		{
			return *_start;
		}
		
		reference back()
		{
			return *(_end - 1);
		}

		const_reference back() const
		{
			return *(_end - 1);
		}

	private:
		Allocator		_alloc;
		pointer			_start;
		pointer			_end;
		pointer			_end_capacity;
	};
}


#endif
