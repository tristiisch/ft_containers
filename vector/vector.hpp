/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 17:48:15 by allanganoun       #+#    #+#             */
/*   Updated: 2022/02/21 04:11:10 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <iostream>
# include "utils.hpp"
# include "iterator.hpp"
# include "reverse_iterator.hpp"

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

		typedef ft::iterator<T>							iterator;
		typedef ft::iterator<const T>					const_iterator;
		typedef ft::reverse_iterator<T>					reverse_iterator;
		typedef	ft::reverse_iterator<const T>			const_reverse_iterator;

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

		template <class InputIterator>
         	vector (InputIterator first, InputIterator last,
                 const Allocator& alloc = Allocator()) // checker pour la verif des iterator + comprendre pourquoi "InputIterator"
		:
			_alloc(alloc),
			_start(NULL),
			_end(NULL),
			_end_capacity(NULL)
		{
			size_t size = 0;
			iterator i = iterator(first);
			while (i != last)
			{
				i++;
				size++;
			}
			_start = _alloc.allocate(size);
			_end = _start;
			_end_capacity = _start + size;
			for (; size > 0; --size)
				_alloc.construct(_end++, *(first++));

		}

		//Destructeur par défaut
		~vector()
		{
			_alloc.deallocate(_start, this->capacity());
		}

		vector &operator=(const vector& x)
		{
			if (x == *this)
				return (*this);
			this->clear();
			this->insert(this->end(), x.begin(), x.end());
			return (*this);
		}

		void assign(size_type n, const T& val)
		{
			this->clear();
			if (n == 0)
				return;
			if (size_type(_end_capacity - _start) >= n)
			{
				while (n)
				{
					_alloc.construct(_end++ , val);
					n--;
				}
			}
			else
			{
				_alloc.deallocate(_start, this->capacity());
				_start = _alloc.allocate(n);
				_end = _start;
				_end_capacity = _start + n;
				while (n)
				{
					_alloc.construct(_end++, val);
					n--;
				}
			}
		}

		iterator erase(iterator position)
		{
			pointer p_pos = &(*position);
			_alloc.destroy(&(*position));
			if (&(*position) + 1 == _end)
				_alloc.destroy(&(*position));
			else
			{
				for (int i = 0; i < _end - &(*position) - 1; ++i)
				{
					_alloc.construct(&(*position) + i, *(&(*position) + i + 1));
					_alloc.destroy(&(*position) + i + 1);
				}
			}
			_end -= 1;
			return (iterator(p_pos));
		}

		iterator erase(iterator first, iterator last)
		{
			pointer p_first = &(*first);
			for (; &(*first) != &(*last); ++first)
				_alloc.destroy(&(*first));
			for (int i = 0; i < _end - &(*last); ++i)
			{
				_alloc.construct(p_first + i, *(&(*last) + i));
				_alloc.destroy(&(*last) + i);
			}
			_end -= (&(*last) - p_first);
			return (iterator(p_first));
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

		// à opti
		iterator insert(iterator pos, const T& value)
		{
			size_type posIndex = pos - _start;
			if (size_type(_end_capacity - _end) >= this->size() + 1) 
			{
				// std::cout << C_CYAN << "Hey" << C_RESET << std::endl;
				for (size_type i = 0; i < posIndex; ++i)
					_alloc.construct(_end - i, *(_end - i - 1));
				_alloc.construct(&(*pos), value);
				_end++;
			}
			// Si il y au moins une place dispo entre end & capacity
			// déplace tous ce qui a après de 1 à droite, et on ajoute value
			/*else if (size_type(_end_capacity - _end) >= 1)
			{
				std::cout << C_CYAN << "Hey3 " << C_RESET << std::endl;
				// for (iterator it = this->end(); it >= pos; --it)
				// {
				// 	// *(it + 1) = *it;
				// 	_alloc.construct(it + 1, *it);
				// }
				for (size_type i = 0; i < this->size() - posIndex - 1; ++i) 
					_alloc.construct(_end - i, *(_end - i + 1));
				// *pos = value;
				// this->at(posIndex) = this->at(value);
				_alloc.construct(_start + posIndex, value); // ajoute notre valeur

			}*/
			// Sinon alloue le double
			else
			{
				int newCapacity;
				if (size_type(_end_capacity - _end) >= 1) // TEMP FIX
					newCapacity = this->capacity();
				else
					newCapacity = (this->size() * 2 > 0) ? this->size() * 2 : 1;
				// std::cout << C_CYAN << "Hey2 " << newCapacity << C_RESET << std::endl;
				pointer newStart = pointer();
				pointer newEnd = pointer();
				pointer newEndCapacity = pointer();
				newStart = _alloc.allocate(newCapacity);
				newEnd = newStart + this->size() + 1;
				newEndCapacity = newStart + newCapacity;
				for (size_type i = 0; i < posIndex; ++i) // realloue du debut jusqu'a posIndex
					_alloc.construct(newStart + i, *(_start + i));

				_alloc.construct(newStart + posIndex, value); // ajoute notre valeur

				for (size_type i = 0; i < this->size() - posIndex; ++i)  // realloue de notre valeur à la fin
					_alloc.construct(newEnd - i - 1, *(_end - i - 1));

				for (size_type i = 0; i < this->size(); ++i) // détruit l'ancien
					_alloc.destroy(_start + i);
				if (_start)
					_alloc.deallocate(_start, this->capacity());

				_start = newStart;
				_end = newEnd;
				_end_capacity = newEndCapacity;
			}
			return (iterator(_start + posIndex));
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
			return iterator(_start);
		}

		const_iterator begin() const
		{
			return const_iterator(_start);
		}

		
		// iterator at the end
		iterator end()
		{
			if (this->empty() == false)
				return iterator(_end);
			else
				return iterator(_start);
		}

		const_iterator end() const
		{
			if (this->empty() == false)
				return const_iterator(_end);
			else
				return const_iterator(_start);
		}

		reverse_iterator rbegin()
		{
			return(reverse_iterator(_end - 1));
		}

		reverse_iterator rend()
		{
			return(reverse_iterator(_start - 1));
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
			if (this->size() == 0)
				return (true);
			else
				return (false);
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

template <class T, class Alloc>
bool operator==(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
{
	if (lhs.size() != rhs.size())
		return false;
	typename ft::vector<T>::const_iterator first1 = lhs.begin();
	typename ft::vector<T>::const_iterator first2 = rhs.begin();
	while (first1 != lhs.end())
	{
		if (first2 == rhs.end() || *first1 != *first2)
			return false;
		++first1;
		++first2;
	}
	return true;
}

template <class T, class Alloc>
bool operator!=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
{
	return !(lhs == rhs);
}

template <class T, class Alloc>
bool operator<=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
{
	return !(rhs < lhs);
}

template <class T, class Alloc>
bool operator>=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
{
	return !(lhs < rhs);
}

#endif
