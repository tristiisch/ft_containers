/* ************************************************************************** */
/*	*/
/*	:::	  ::::::::   */
/*   iter.hpp	   :+:	  :+:	:+:   */
/*	+:+ +:+	 +:+	 */
/*   By: allanganoun <allanganoun@student.42lyon	+#+  +:+	   +#+	*/
/*	+#+#+#+#+#+   +#+	   */
/*   Created: 2021/12/02 18:05:40 by allanganoun	   #+#	#+#	 */
/*   Updated: 2021/12/02 18:05:40 by allanganoun	  ###   ########lyon.fr   */
/*	*/
/* ************************************************************************** */

#ifndef ITER_HPP
# define ITER_HPP

template <typename T>

class iter
{
public:
	iter(void);
	iter(T *ptr);
	iter(const iter &src);
	~iter();
	iter &operator=(const iter &rhs);

	typedef T val_type;
	typedef val_type *pointer;
	typedef val_type const *const_pointer;
	typedef val_type &reference;
	typedef val_type const &const_reference;
	typedef std::ptrdiff_t difference_type;

	reference operator*(void) const;
	pointer operator->(void) const;
	iter &operator++();
	iter &operator--();
	iter operator++(int a);
	iter operator--(int a);
	iter &operator+=(const difference_type &offset);
	iter &operator-=(const difference_type &offset);
	iter operator+(const difference_type offset) const;
	iter operator-(const difference_type offset) const;
	bool operator==(const iter &rhs) const;
	bool operator!=(const iter &rhs) const;

	pointer p;

};

template <typename T>
iter<T>::iter(void)
{
	p = NULL;
};

template <typename T>
iter<T>::iter(T *ptr)
{
	this->p = ptr;
};

template <typename T>
iter<T>::iter(const iter &src)
{
	this = src;
};

template <typename T>
iter<T>::~iter(){
};

template <typename T>
iter<T> &iter<T>::operator=(const iter &rhs)
{
	if (this != &rhs)
	{
		this->p = rhs.p;
	}
	return (*this);
};

template <typename T>
typename iter<T>::reference iter<T>::operator*(void) const
{
	return *(this->ptr);
}

template <typename T>
typename iter<T>::pointer iter<T>::operator->(void) const
{
	return this->ptr;
}

template <typename T>
iter<T> &iter<T>::operator++()
{
	ptr++;
	return (*this);
}

template <typename T>
iter<T> &iter<T>::operator--()
{
	ptr--;
	return (*this);
}

template <typename T>
iter<T> iter<T>::operator++(int dummy)
{
	(void)dummy;
	iter<T> copy = *this;
	this->ptr++;
	return (copy);
}

template <typename T>
iter<T> iter<T>::operator--(int dummy)
{
	(void)dummy;
	iter<T> copy = *this;
	this->ptr--;
	return (copy);
}

template <typename T>
bool iter<T>::operator==(const iter &rhs) const
{
	return this->ptr == rhs.ptr;
}

template <typename T>
bool iter<T>::operator!=(const iter &rhs) const
{
	return this->ptr != rhs.ptr;
}

template <typename T>
iter<T> &iter<T>::operator+=(const difference_type &offset)
{
	this->ptr += offset;
	return (*this);
}

template <typename T>
iter<T> &iter<T>::operator-=(const difference_type &offset)
{
	this->ptr -= offset;
	return (*this);
}

template <typename T>
iter<T> iter<T>::operator+(difference_type offset) const
{
	iter copy(*this);

	copy.ptr += offset;

	return (copy);
}

template <typename T>
iter<T> iter<T>::operator-(difference_type offset) const
{
	iter copy(*this);

	copy.ptr -= offset;

	return (copy);
}

template <typename T>
typename iter<T>::difference_type operator-(const iter<T> &lhs, const iter<T> &rhs)
{
	return lhs.ptr - rhs.ptr;
}

template <typename T>
bool operator<(const iter<T> &lhs, const iter<T> &rhs)
{
	return lhs.ptr < rhs.ptr;
}

template <typename T>
bool operator<=(const iter<T> &lhs, const iter<T> &rhs)
{
	return lhs.ptr <= rhs.ptr;
}

template <typename T>
bool operator>(const iter<T> &lhs, const iter<T> &rhs)
{
	return lhs.ptr > rhs.ptr;
}
template <typename T>
bool operator>=(const iter<T> &lhs, const iter<T> &rhs)
{
	return lhs.ptr >= rhs.ptr;
}

template <typename T>
bool operator==(const iter<T> &lhs, const iter<T> &rhs)
{
	return lhs.ptr == rhs.ptr;
}

template <typename T>
bool operator!=(const iter<T> &lhs, const iter<T> &rhs)
{
	return lhs.ptr != rhs.ptr;
}

#endif
