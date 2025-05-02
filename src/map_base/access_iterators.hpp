#ifndef MAP_BASE_ACCESS_ITERATORS_HPP
#define MAP_BASE_ACCESS_ITERATORS_HPP

#include "declaration.hpp"

template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::iterator
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::begin() noexcept
{}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::const_iterator
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::begin() const noexcept
{}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::const_iterator
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::cbegin() const noexcept
{}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::reverse_iterator
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::rbegin() noexcept
{}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::const_reverse_iterator
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::rbegin() const noexcept
{}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::const_reverse_iterator
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::crbegin() const noexcept
{}

template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::iterator
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::end() noexcept
{}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::const_iterator
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::end() const noexcept
{}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::const_iterator
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::cend() const noexcept
{}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::reverse_iterator
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::rend() noexcept
{}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::const_reverse_iterator
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::rend() const noexcept
{}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::const_reverse_iterator
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::crend() const noexcept
{}

#endif
