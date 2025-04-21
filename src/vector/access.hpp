#ifndef VECTOR_ACCESS_HPP
#define VECTOR_ACCESS_HPP

#include "declaration.hpp"
#include <stdexcept>

template< class T, class Allocator >
typename src::Vector< T, Allocator >::reference src::Vector< T, Allocator >::operator[](size_type index)
{
	return data_[index];
}
template< class T, class Allocator >
typename src::Vector< T, Allocator >::const_reference src::Vector< T, Allocator >::operator[](size_type index) const
{
	return data_[index];
}
template< class T, class Allocator >
typename src::Vector< T, Allocator >::reference src::Vector< T, Allocator >::at(size_type index)
{
	if (index >= size_)
	{
		throw std::range_error("index out of range");
	}
	return data_[index];
}
template< class T, class Allocator >
typename src::Vector< T, Allocator >::const_reference src::Vector< T, Allocator >::at(size_type index) const
{
	if (index >= size_)
	{
		throw std::range_error("index out of range");
	}
	return data_[index];
}

template< class T, class Allocator >
bool src::Vector< T, Allocator >::empty() const noexcept
{
	return size_ == 0;
}
template< class T, class Allocator >
typename src::Vector< T, Allocator >::size_type src::Vector< T, Allocator >::size() const noexcept
{
	return size_;
}
template< class T, class Allocator >
typename src::Vector< T, Allocator >::size_type src::Vector< T, Allocator >::capacity() const noexcept
{
	return capacity_;
}
template< class T, class Allocator >
typename src::Vector< T, Allocator >::reference src::Vector< T, Allocator >::front() noexcept
{
	return *data_;
}
template< class T, class Allocator >
typename src::Vector< T, Allocator >::reference src::Vector< T, Allocator >::back() noexcept
{
	return data_[size_ - 1];
}
template< class T, class Allocator >
typename src::Vector< T, Allocator >::const_reference src::Vector< T, Allocator >::front() const noexcept
{
	return *data_;
}
template< class T, class Allocator >
typename src::Vector< T, Allocator >::const_reference src::Vector< T, Allocator >::back() const noexcept
{
	return data_[size_ - 1];
}


template< class T, class Allocator >
typename src::Vector< T, Allocator >::iterator src::Vector< T, Allocator >::begin() noexcept
{
	return {data_};
}
template< class T, class Allocator >
typename src::Vector< T, Allocator >::const_iterator src::Vector< T, Allocator >::begin() const noexcept
{
	return {data_};
}
template< class T, class Allocator >
typename src::Vector< T, Allocator >::const_iterator src::Vector< T, Allocator >::cbegin() const noexcept
{
	return {data_};
}
template< class T, class Allocator >
typename src::Vector< T, Allocator >::reverse_iterator src::Vector< T, Allocator >::rbegin() noexcept
{
	return {data_ + (size_ - 1)};
}
template< class T, class Allocator >
typename src::Vector< T, Allocator >::const_reverse_iterator src::Vector< T, Allocator >::rbegin() const noexcept
{
	return {data_ + (size_ - 1)};
}
template< class T, class Allocator >
typename src::Vector< T, Allocator >::const_reverse_iterator src::Vector< T, Allocator >::crbegin() const noexcept
{
	return {data_ + (size_ - 1)};
}

template< class T, class Allocator >
typename src::Vector< T, Allocator >::iterator src::Vector< T, Allocator >::end() noexcept
{
	return {};
}
template< class T, class Allocator >
typename src::Vector< T, Allocator >::const_iterator src::Vector< T, Allocator >::end() const noexcept
{
	return {};
}
template< class T, class Allocator >
typename src::Vector< T, Allocator >::const_iterator src::Vector< T, Allocator >::cend() const noexcept
{
	return {};
}
template< class T, class Allocator >
typename src::Vector< T, Allocator >::reverse_iterator src::Vector< T, Allocator >::rend() noexcept
{
	return {};
}
template< class T, class Allocator >
typename src::Vector< T, Allocator >::const_reverse_iterator src::Vector< T, Allocator >::rend() const noexcept
{
	return {};
}
template< class T, class Allocator >
typename src::Vector< T, Allocator >::const_reverse_iterator src::Vector< T, Allocator >::crend() const noexcept
{
	return {};
}
template< class T, class Allocator >
typename src::Vector< T, Allocator >::pointer src::Vector< T, Allocator >::data() noexcept
{
	return data_;
}
template< class T, class Allocator >
typename src::Vector< T, Allocator >::const_pointer src::Vector< T, Allocator >::data() const noexcept
{
	return data_;
}

#endif
