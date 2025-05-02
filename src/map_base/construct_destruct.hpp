#ifndef MAP_BASE_CONSTRUCT_DESTRUCT_HPP
#define MAP_BASE_CONSTRUCT_DESTRUCT_HPP

#include "declaration.hpp"

template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::MapBase()
		noexcept(std::is_nothrow_default_constructible< value_compare >::value):
	MapBase(Compare())
{}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::MapBase(const key_compare& compare):
	compare_(compare),
	root_(nullptr),
	size_(0)
{}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::MapBase(const MapBase& rhs):
	MapBase()
{
	root_ = new node_type{rhs.root_->value_, rhs.root_->isRed_};

}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::MapBase(MapBase&& rhs)
		noexcept(std::is_nothrow_default_constructible< value_compare >::value)
{}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
template< class InIter >
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::MapBase
		(InIter from, InIter to,const key_compare &compare)
{}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::MapBase
		(std::initializer_list< value_type > list, const key_compare& compare)
{}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::~MapBase()
{}

template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >&
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::operator=(const MapBase& rhs)
{}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >&
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::operator=(MapBase&& rhs)
		noexcept(std::is_nothrow_default_constructible< value_compare >::value)
{}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >&
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::operator=
		(std::initializer_list< value_type > list)
{}

#endif
