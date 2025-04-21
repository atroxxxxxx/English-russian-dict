#ifndef VECTOR_CONSTRUCT_DESTRUCT_HPP
#define VECTOR_CONSTRUCT_DESTRUCT_HPP

#include <vector/declaration.hpp>
#include <utility>

template< class T, class Allocator >
src::Vector< T, Allocator >::Vector() noexcept:
	data_(nullptr),
	capacity_(0),
	size_(0)
{}
template< class T, class Allocator >
src::Vector< T, Allocator >::Vector(const Vector& rhs):
	Vector()
{
	reserve(rhs.size_);
	while (size_ < rhs.size_)
	{
		push_back(rhs[size_]);
	}
}
template< class T, class Allocator >
src::Vector< T, Allocator >::Vector(Vector&& rhs) noexcept:
	data_(std::exchange(rhs.data_, nullptr)),
	capacity_(std::exchange(rhs.capacity_, 0)),
	size_(std::exchange(rhs.size_, 0))
{}
template< class T, class Allocator >
src::Vector< T, Allocator >::Vector(std::initializer_list< value_type > data):
	Vector()
{
	reserve(data.size());
	while (size_ < data.size())
	{
		push_back(data[size_]);
	}
}
template< class T, class Allocator >
src::Vector< T, Allocator >::Vector(size_type repetitions, const value_type& value):
	Vector()
{
	resize(repetitions, value);
}
template< class T, class Allocator >
template< class It >
src::Vector< T, Allocator >::Vector(It beginIter, It endIter):
	Vector()
{
	for (; beginIter != endIter; ++beginIter)
	{
		push_back(*beginIter);
	}
}
template< class T, class Allocator >
src::Vector< T, Allocator >::~Vector()
{
	clear();
}
template< class T, class Allocator >
void src::Vector< T, Allocator >::clear()
{
	while (!empty())
	{
		pop_back();
	}
	std::allocator_traits< allocator >::deallocate(allocator_, data_, capacity_);
}

template< class T, class Allocator >
src::Vector< T, Allocator >& src::Vector< T, Allocator >::operator=(const Vector& rhs)
{
	if (this != &rhs)
	{
		Vector temp(rhs);
		swap(temp);
	}
	return *this;
}
template< class T, class Allocator >
src::Vector< T, Allocator >& src::Vector< T, Allocator >::operator=(Vector&& rhs) noexcept
{
	if (this != &rhs)
	{
		Vector temp(*this);
		swap(rhs);
	}
	return *this;
}
template< class T, class Allocator >
void src::Vector< T, Allocator >::swap(Vector& rhs) noexcept
{
	std::swap(data_, rhs.data_);
	std::swap(capacity_, rhs.capacity_);
	std::swap(size_, rhs.size_);
	std::swap(allocator_, rhs.allocator_);
}

#endif
