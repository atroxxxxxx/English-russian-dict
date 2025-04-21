#ifndef VECTOR_MODIFIERS_HPP
#define VECTOR_MODIFIERS_HPP

#include "declaration.hpp"
#include <utility>
#include <memory>
#include <vector>

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

template< class T, class Allocator >
template< class... Args >
typename src::Vector< T, Allocator >::reference src::Vector< T, Allocator >::emplace(const_iterator it, Args&&... args)
{
	size_type index = data_ - it.data_;
	if (std::is_nothrow_move_constructible< value_type >::value || (it == cend()))
	{
		if (size_ >= capacity_)
		{
			reserve(size_ * 2 + 1);
		}
		if (it == end())
		{
			std::allocator_traits< allocator >::construct(allocator_, data_ + size_, std::forward< Args >(args)...);
			size_++;
			return data_[size_ - 1];
		}
		else
		{
			value_type temp = {std::forward< Args >(args)...};
			std::allocator_traits< allocator >::construct(allocator_, data_ + size_ - 1, std::move(*(data_ + size_ - 1)));
			for (size_type i = index + 1; i < size_; i++)
			{
				data_[i] = std::move(data_[i - 1]);
			}
			data_[index] = std::move(temp);
		}
	}
	else
	{
		Vector temp;
		temp.reserve(size_ >= capacity_ ? size_ * 2 + 1 : capacity_);
		for (size_type i = 0; i < index; i++)
		{
			temp.push_back(data_[i]);
		}
		temp.emplace_back(std::forward< Args >(args)...);
		for (size_type i = index; i < size_; i++)
		{
			temp.push_back(data_[i]);
		}
	}
	size_++;
	return data_[index];
}
template< class T, class Allocator >
template< class... Args >
typename src::Vector< T, Allocator >::reference src::Vector< T, Allocator >::emplace_back(Args&&... args)
{
	return emplace(end(), std::forward< Args >(args)...);
}
template< class T, class Allocator >
void src::Vector< T, Allocator >::push_back(const value_type& value)
{
	emplace_back(value);
}
template< class T, class Allocator >
void src::Vector< T, Allocator >::push_back(value_type&& value)
{
	emplace_back(std::move(value));
}
template< class T, class Allocator >
void src::Vector< T, Allocator >::assign(size_type count, const value_type& value)
{
	reserve(size_ + count);
	for (size_t i = 0; i < count; i++)
	{
		push_back(value);
	}
}
template< class T, class Allocator >
template< class It >
void src::Vector< T, Allocator >::assign(It beginIter, It endIter)
{
	for (; beginIter != endIter; ++beginIter)
	{
		push_back(*beginIter);
	}
}
template< class T, class Allocator >
void src::Vector< T, Allocator >::assign(std::initializer_list< value_type > data)
{
	reserve(size_ + data.size());
	for (size_t i = 0; i < data.size(); i++)
	{
		push_back(data[i]);
	}
}
// [[deprecated(now it's 2:13, I want to sleep, but I want to finish it)]]
template< class T, class Allocator >
typename src::Vector< T, Allocator >::iterator
		src::Vector< T, Allocator >::insert(const_iterator it, const value_type& value)
{
	return {std::addressof(emplace(it, value))};
}
template< class T, class Allocator >
typename src::Vector< T, Allocator >::iterator
		src::Vector< T, Allocator >::insert(const_iterator it, value_type&& value)
{
	return {std::addressof(emplace(it, std::move(value)))};
}
template< class T, class Allocator >
typename src::Vector< T, Allocator >::iterator
		src::Vector< T, Allocator >::insert(const_iterator it, size_type count, const value_type& value)
{
	if (count == 0)
	{
		return it;
	}

	for (; count > 0; count--)
	{
		it = insert(it, value);
	}
	return end(); // !!! crutch
}
template< class T, class Allocator >
template< class It >
typename src::Vector< T, Allocator >::iterator
		src::Vector< T, Allocator >::insert(const_iterator it, It beginIter, It endIter)
{
	if (beginIter == endIter)
	{
		return it;
	}

	for (; beginIter != endIter; beginIter++)
	{
		it = {std::addressof(emplace(it, std::move(*beginIter))) + 1};
	}
	return end(); // !!! crutch
}
template< class T, class Allocator >
typename src::Vector< T, Allocator >::iterator
		src::Vector< T, Allocator >::insert(const_iterator it, std::initializer_list< value_type > data)
{
	return insert(it, data.begin(), data.end());
}

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
