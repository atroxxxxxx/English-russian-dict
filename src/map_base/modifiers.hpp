#ifndef MAP_BASE_MODIFIERS_HPP
#define MAP_BASE_MODIFIERS_HPP

#include "declaration.hpp"

template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
void src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::clear()
{
	destroy(root_);
	root_ = nullptr;
}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
void src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::swap(const MapBase& rhs) noexcept
{}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
template< class... Args >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::iterator
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::emplace_hint(const_iterator hint, Args&&... args)
{}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
template< class... Args >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::iterator
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::emplace(Args&&... args)
{}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
src::Pair< typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::iterator, bool >
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::insert(const value_type& value)
{}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
src::Pair< typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::iterator, bool >
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::insert(value_type&& value)
{}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::iterator
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::erase(const_iterator iter)
{}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::size_type
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::erase(const key_type& key)
{}

template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
void src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::destroy(node_type* node)
{
	if (node == nullptr)
	{
		return;
	}
	destroy(node->left_);
	destroy(node->right_);
	delete node;
}

#endif
