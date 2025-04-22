#ifndef VECTOR_MODIFIERS_HPP
#define VECTOR_MODIFIERS_HPP

#include "declaration.hpp"
#include <utility>
#include <memory>

template< class T, class Allocator >
void src::Vector< T, Allocator >::reserve(size_type newCapacity)
{
	if (newCapacity < capacity_)
	{
		return;
	}
	Vector temp;
	temp.data_ = std::allocator_traits< allocator >::allocate(allocator_, newCapacity);
	temp.capacity_ = newCapacity;
	while (temp.size_ < size_)
	{
		temp.emplace_back(std::move_if_noexcept(data_[temp.size_]));
	}
	swap(temp);
}
template< class T, class Allocator >
void src::Vector< T, Allocator >::resize(size_type newSize, const value_type& value)
{
	if (newSize > capacity_)
	{
		reserve(newSize);
	}
	if (newSize > size_)
	{
		while (size_ < newSize)
		{
			push_back(value);
		}
	}
	else
	{
		while (size_ > newSize)
		{
			pop_back();
		}
	}
}
template< class T, class Allocator >
void src::Vector< T, Allocator >::resize(size_type newSize)
{
	if (newSize > capacity_)
	{
		reserve(newSize);
	}
	if (newSize > size_)
	{
		while (size_ < newSize)
		{
			emplace_back();
		}
	}
	else
	{
		while (size_ > newSize)
		{
			pop_back();
		}
	}
}
template< class T, class Allocator >
void src::Vector< T, Allocator >::shrink_to_fit()
{
	if (capacity_ == size_)
	{
		return;
	}
	Vector temp;
	temp.reserve(size_);
	while (temp.size_ < size_)
	{
		emplace_back(std::move_if_noexcept(data_[temp.size_]));
	}
	swap(temp);
}

// pls fix it
template< class T, class Allocator >
typename src::Vector< T, Allocator >::iterator
		src::Vector< T, Allocator >::errase(const_iterator beginIter, const_iterator endIter)
{
	size_type index = beginIter.data_ - data_;
	size_type deleted = 0;
	if (std::is_nothrow_move_constructible< value_type >::value || (endIter == cend()))
	{
		if (beginIter == cend())
		{
			std::allocator_traits< allocator >::destroy(allocator_, data_ + size_ - 1);
			size_ --;
			return {data_ + size_ - 1};
		}
		for (; beginIter != endIter; ++beginIter, deleted++)
		{
			std::allocator_traits< allocator >::destroy(allocator_, beginIter.data_);
		}
		for (; endIter != end(); ++endIter, index++)
		{
			std::allocator_traits< allocator >::construct(allocator_, data_ + index, std::move(*endIter));
		}
		for (size_type i = size_ - deleted; i < size_; i++)
		{
			std::allocator_traits< allocator >::destroy(allocator_, data_ + i);
		}
	}
	size_ -= deleted;
	return {data_ + index + deleted};
}
template< class T, class Allocator >
typename src::Vector< T, Allocator >::iterator
		src::Vector< T, Allocator >::errase(const_iterator it)
{
	return errase(it, it + (it != end()));
}
template< class T, class Allocator >
void src::Vector< T, Allocator >::pop_back()
{
	errase(end());
}

#endif
