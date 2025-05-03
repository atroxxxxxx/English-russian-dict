#ifndef MAP_BASE_ERASE_HPP
#define MAP_BASE_ERASE_HPP

#include "modifiers.hpp"
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::iterator
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::erase(const_iterator iter)
{
	return end();
}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::size_type
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::erase(const key_type& key)
{
	return 0;
}

#endif
