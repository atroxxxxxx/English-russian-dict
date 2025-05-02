#ifndef MAP_BASE_ACCESS_HPP
#define MAP_BASE_ACCESS_HPP

#include "declaration.hpp"

template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
bool src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::empty() const noexcept
{}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::size_type
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::size() const noexcept
{}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
bool src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::contains(const key_type &key) const
{}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::iterator
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::lower_bound()
{}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::const_iterator
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::lower_bound() const
{}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::iterator
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::upper_bound()
{}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::const_iterator
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::upper_bound() const
{}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::iterator
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::find(const key_type& key)
{}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::const_iterator
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::find(const key_type& key) const
{}

#endif
