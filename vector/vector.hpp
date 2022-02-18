/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 17:48:15 by allanganoun       #+#    #+#             */
/*   Updated: 2022/02/18 18:37:34 by tglory           ###   ########lyon.fr   */
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
			for (; n > 0; --n)
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
			_alloc.construct(_end++, value);
		}

		// Supprime la valeur au Top du vector. N'affecte pas la memoire allouée
		void pop_back()
		{
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

		// A revoir totalement, ne fonctionne pas comme la STL
		iterator insert(iterator pos, const T& value)
		{
			size_type pos_len = pos - _start;
			//std::cout << "S " << _end_capacity - _end << std::endl;
			if (size_type(_end_capacity - _end) >= 1)
			{
				//std::cout << "Hey" << std::endl;
				for (size_type i = 0; i < pos_len; i++)
					_alloc.construct(_end - i, *(_end - i - 1));
				_end++;
				_alloc.construct(&(*pos), value);
			}
			else
			{
				//std::cout << "Hey2" << std::endl;
				pointer new_start = pointer();
				pointer new_end = pointer();
				pointer new_end_capacity = pointer();

				int next_capacity = (this->size() * 2 > 0) ? this->size() * 2 : 1;
				new_start = _alloc.allocate( next_capacity );
				new_end = new_start + this->size() + 1;
				new_end_capacity = new_start + next_capacity;

				for (size_type i = 0; i < pos_len; i++)
					_alloc.construct(new_start + i, *(_start + i));
				_alloc.construct(new_start + pos_len, value);
				for (size_type j = 0; j < this->size() - pos_len; j++)
					_alloc.construct(new_end - j - 1, *(_end - j - 1));

				for (size_type l = 0; l < this->size(); l++)
					_alloc.destroy(_start + l);
				if (_start)
					_alloc.deallocate(_start, this->capacity());

				_start = new_start;
				_end = new_end;
				_end_capacity = new_end_capacity;
			}
			return (iterator(_start + pos_len));
		}

		// Supprime les valeurs. N'affecte pas la memoire allouée
		void clear()
		{
			for (; _start != _end; --_end)
				_alloc.destroy(_end);
		}

		reference operator[](size_type n)
		{
			return *(_start + n);
		}

		const_reference operator[](size_type n) const
		{
			return *(_start + n);
		}

		reference at(size_type n)
		{
			if (n >= this->size())
				throw std::out_of_range("vector::out_of_range > n in not in range");
				// throw std::out_of_range("vector"); // STL MSG on MAC
			return (*this)[n];
		}

		const_reference at(size_type n) const
		{
			if (n >= this->size())
				throw std::out_of_range("vector::out_of_range > n in not in range");
				// throw std::out_of_range("vector"); // STL MSG on MAC
			return (*this)[n];
		}

		// Not needed ?
		Allocator get_allocator() const
		{
			return _alloc;
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
