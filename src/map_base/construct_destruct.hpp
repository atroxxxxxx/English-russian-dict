#ifndef MAP_BASE_CONSTRUCT_DESTRUCT_HPP
#define MAP_BASE_CONSTRUCT_DESTRUCT_HPP

#include "declaration.hpp"
#include <utility>

template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::MapBase()
		noexcept(std::is_nothrow_default_constructible< value_compare >::value):
	MapBase(Compare())
{}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::MapBase(const key_compare& compare):
	compare_{compare},
	root_(nullptr),
	size_(0),
	min_(nullptr),
	max_(nullptr)
{}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::MapBase(const MapBase& rhs):
	MapBase()
{
	if (rhs.empty())
	{
		return;
	}
	root_ = copy(rhs.root_);
	size_ = rhs.size_;
	for (min_ = root_; min_->left_ != nullptr; min_ = min_->left_)
	{}
	for (max_ = root_; max_->right_ != nullptr; max_ = max_->right_)
	{}
}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::MapBase(MapBase&& rhs)
		noexcept(std::is_nothrow_default_constructible< value_compare >::value):
	compare_(std::move(rhs.compare_)),
	root_(std::exchange(rhs.root_, nullptr)),
	size_(std::exchange(rhs.size_, 0)),
	min_(std::exchange(rhs.min_, nullptr)),
	max_(std::exchange(rhs.max_, nullptr))
{}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
template< class InIter >
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::MapBase
		(InIter from, InIter to, const key_compare& compare):
	MapBase(compare)
{
	for (; from != to; ++from)
	{
		insert(*from);
	}
}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::MapBase
		(std::initializer_list< value_type > list, const key_compare& compare):
	MapBase(list.begin(), list.end(), compare)
{}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::~MapBase()
{
	clear();
}

template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >&
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::operator=(const MapBase& rhs)
{
	if (this != &rhs)
	{
		MapBase temp(rhs);
		swap(temp);
	}
	return *this;
}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >&
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::operator=(MapBase&& rhs)
		noexcept(std::is_nothrow_default_constructible< value_compare >::value)
{
	if (this != &rhs)
	{
		MapBase temp(std::move(*this));
		swap(rhs);
	}
	return *this;
}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >&
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::operator=
		(std::initializer_list< value_type > list)
{
	MapBase temp(list);
	swap(temp);
	return *this;
}

template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::node_type*
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::copy(node_type* current)
{
	node_type* copied = nullptr;
	try
	{
		copied = new node_type{current->value_, current->isRed_};
		if (current->left_ != nullptr)
		{
			copied->left_ = copy(current->left_);
			copied->left_->parent_ = copied;
		}
		if (current->right_ != nullptr)
		{
			copied->right_ = copy(current->right_);
			copied->right_->parent_ = copied;
		}
	}
	catch (...)
	{
		destory(copied);
		throw;
	}
	return copied;
}

#endif
