/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alganoun <alganoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 17:48:15 by allanganoun       #+#    #+#             */
/*   Updated: 2022/02/21 19:16:41 by alganoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <iostream>
# include "utils/utils.hpp"
# include "utils/iterator.hpp"
# include "utils/reverse_iterator.hpp"

namespace ft
{
	template<typename T, typename Allocator = std::allocator<T> >
	class vector
	{
	public:
		typedef T												value_type;
		typedef Allocator										allocator_type;
		typedef typename allocator_type::size_type				size_type;
		typedef typename allocator_type::difference_type		difference_type;
		typedef	typename allocator_type::reference				reference;
		typedef	typename allocator_type::const_reference		const_reference;
		typedef typename allocator_type::pointer				pointer;

		typedef ft::iterator<value_type>						iterator;
		typedef ft::iterator<const value_type>					const_iterator;
		typedef ft::reverse_iterator<value_type>				reverse_iterator;
		typedef	ft::reverse_iterator<const value_type>			const_reverse_iterator;

		// il faut appeler tous les types d'iterateurs ici et les definir via iterator.hpp, etc.. 

		// constructeur par defaut
		explicit vector(const allocator_type& alloc = allocator_type())
		:	
			_alloc(alloc),
			_start(NULL),
			_end(NULL),
			_end_capacity(NULL)

		{};

		// constructeur avec capacity par default
		explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
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
                 const allocator_type& alloc = allocator_type()) // checker pour la verif des iterator + comprendre pourquoi "InputIterator"
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

		vector (const vector& x)
		:
			_alloc(x._alloc),
			_start(NULL),
			_end(NULL),
			_end_capacity(NULL)
		{
			this->insert(this->begin(), x.begin(), x.end());
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
			this->clear(); // a CHECK
			this->insert(this->end(), x.begin(), x.end());
			return (*this);
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
			return allocator_type().max_size();
		}

		void resize (size_type n, value_type val = value_type())
		{
			/*if (n > this->max_size())
				throw une exception.*/
			/*else*/ if (n < this->size())
			{
				while (this->size() > n)
				{
					_end--;
					_alloc.destroy(_end);
				}
			}
			else if(n > this->size())
				this->insert(this->end(), n - this->size(), val);
		}

		// Ajoute une valeur au Top du vector
		// Si la capacity est dépassé, alloue le double de la capacity actuelle
		void push_back(const value_type& value)
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

		iterator insert(iterator pos, const value_type& value)
		{
			size_type posIndex = pos - _start;
			if (size_type(_end_capacity - _end) >= 1) 
			{
				for (size_type i = 0; i < this->size() - posIndex; ++i)
					_alloc.construct(_end - i, *(_end - i - 1));
				_alloc.construct(&(*pos), value);
				_end++;
			}
			else
			{
				int newCapacity;
				newCapacity = (this->size() * 2 > 0) ? this->size() * 2 : 1;
				// std::cout << C_CYAN << "Hey2 " << newCapacity << C_RESET << std::endl;
				pointer new_start = pointer();
				pointer new_end = pointer();
				pointer new_endcap = pointer();
				new_start = _alloc.allocate(newCapacity);
				new_end = new_start + this->size() + 1;
				new_endcap = new_start + newCapacity;
				for (size_type i = 0; i < posIndex; ++i) // realloue du debut jusqu'a posIndex
					_alloc.construct(new_start + i, *(_start + i));

				_alloc.construct(new_start + posIndex, value); // ajoute notre valeur

				for (size_type i = 0; i < this->size() - posIndex; ++i)  // realloue de notre valeur à la fin
					_alloc.construct(new_end - i - 1, *(_end - i - 1));

				for (size_type i = 0; i < this->size(); ++i) // détruit l'ancien
					_alloc.destroy(_start + i);
				if (_start)
					_alloc.deallocate(_start, this->capacity());

				_start = new_start;
				_end = new_end;
				_end_capacity = new_endcap;
			}
			return (iterator(_start + posIndex));
		}

		void insert (iterator position, size_type n, const value_type& val)
		{
			size_type posIndex = position - _start;
			if (size_type(_end_capacity - _end) >= n) 
			{
				for (size_type i = 0; i < this->size() - posIndex; ++i)
					_alloc.construct(_end + (n - 1) - i, *(_end - i - 1));
				for (size_type i = 0 ; i < n ; ++i)
					_alloc.construct(&(*position) + i, val);
				_end = _end + n;
			}
			else
			{
				int new_cap = n;
				if (this->size() > 0)
					new_cap = this->size() * 2;
				pointer new_start = pointer();
				pointer new_end = pointer();
				pointer new_endcap = pointer();
				new_start = _alloc.allocate(new_cap);
				new_end = new_start + this->size() + n;
				new_endcap = new_start + new_cap;
				for (size_type i = 0; i < posIndex; ++i) // realloue du debut jusqu'a posIndex
					_alloc.construct(new_start + i, *(_start + i));

				for (size_type i = 0 ; i < n ; ++i)
					_alloc.construct(new_start + posIndex + i, val); // ajoute notre valeur

				for (size_type i = 0 ; i < this->size() - posIndex ; ++i)  // realloue de notre valeur à la fin
					_alloc.construct(new_end - i - 1, *(_end - i - 1));

				for (size_type i = 0; i < this->size(); ++i) // détruit l'ancien
					_alloc.destroy(_start + i);
				if (_start)
					_alloc.deallocate(_start, this->capacity());

				_start = new_start;
				_end = new_end;
				_end_capacity = new_endcap;
			}
		}

		/*void assign(size_type n, const value_type& val)
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
		}*/

		template <class InputIterator>
  			void assign (InputIterator first, InputIterator last) // il faut vérifier que ce truc marche comme prévu
		{
			this->clear();
			//this->insert(this->begin(), iterator(first) , iterator(last)); TODO insert first-last
		}

		void	assign(size_t n, const value_type& val) // il faut vérifier que ce truc marche comme prévu
		{
			this->clear();
			this->insert(this->begin(), n, val);
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
		allocator_type get_allocator() const
		{
			return _alloc;
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

	private:
		allocator_type		_alloc;
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
