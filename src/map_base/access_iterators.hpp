#ifndef MAP_BASE_ACCESS_ITERATORS_HPP
#define MAP_BASE_ACCESS_ITERATORS_HPP

#include "declaration.hpp"

template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::iterator
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::begin() noexcept
{
	return {min_, max_};
}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::const_iterator
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::begin() const noexcept
{
	return {min_, max_};
}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::const_iterator
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::cbegin() const noexcept
{
	return begin();
}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::reverse_iterator
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::rbegin() noexcept
{
	return {max_, min_};
}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::const_reverse_iterator
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::rbegin() const noexcept
{
	return {max_, min_};
}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::const_reverse_iterator
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::crbegin() const noexcept
{
	return rbegin();
}

template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::iterator
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::end() noexcept
{
	return {nullptr, max_};
}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::const_iterator
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::end() const noexcept
{
	return {nullptr, max_};
}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::const_iterator
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::cend() const noexcept
{
	return end();
}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::reverse_iterator
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::rend() noexcept
{
	return {nullptr, min_};
}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::const_reverse_iterator
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::rend() const noexcept
{
	return {nullptr, min_};
}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::const_reverse_iterator
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::crend() const noexcept
{
	return rend();
}

#endif
