#ifndef MAP_BASE_ACCESS_HPP
#define MAP_BASE_ACCESS_HPP

#include "declaration.hpp"

template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
bool src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::empty() const noexcept
{
	return root_ == nullptr;
}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::size_type
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::size() const noexcept
{
	return size_;
}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
bool src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::contains(const key_type& key) const
{
	const_iterator iter = find(key);
	return iter != end();
}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::iterator
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::lower_bound(const key_type& key)
{
	return {lower_bound_impl(key).data_, max_};
}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::const_iterator
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::lower_bound(const key_type& key) const
{
	return lower_bound_impl(key);
}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::iterator
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::upper_bound(const key_type& key)
{
	return {upper_bound_impl(key).data_, max_};
}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::const_iterator
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::upper_bound(const key_type& key) const
{
	return upper_bound_impl(key);
}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::iterator
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::find(const key_type& key)
{
	iterator iter = lower_bound(key);
	if ((iter != end()) && !compare_(key, get_key(*iter)))
	{
		return iter;
	}
	return end();
}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::const_iterator
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::find(const key_type& key) const
{
	const_iterator iter = lower_bound(key);
	if ((iter != end()) && !compare_(key, get_key(*iter)))
	{
		return iter;
	}
	return end();
}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
template< class V >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::key_type&
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::get_key
		(std::enable_if_t< std::is_same< key_type, V >::value, V& > value)
{
	return value;
}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
template< class V >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::key_type&
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::get_key
		(std::enable_if_t< !std::is_same< key_type, V >::value, V& > value)
{
	return value.first;
}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
template< class V >
const typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::key_type&
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::get_key
		(std::enable_if_t< std::is_same< key_type, V >::value, const V& > value)
{
	return value;
}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
template< class V >
const typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::key_type&
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::get_key
		(std::enable_if_t< !std::is_same< key_type, V >::value, const V& > value)
{
	return value.first;
}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::const_iterator
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::lower_bound_impl(const key_type& key) const
{
	if (empty())
	{
		return end();
	}
	const_iterator current = {root_, max_};
	const_iterator cashed = end();
	while (true)
	{
		if (compare_(key, get_key(current.data_->value_)))
		{
			cashed = current;
			if (current.data_->left_ == nullptr)
			{
				return cashed;
			}
			current.data_ = current.data_->left_;
		}
		else if (!compare_(get_key(current.data_->value_), key))
		{
			return current;
		}
		else
		{
			if (current.data_->right_ == nullptr)
			{
				return cashed;
			}
			current.data_ = current.data_->right_;
		}
	}
}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::const_iterator
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::upper_bound_impl(const key_type& key) const
{
	if (empty())
	{
		return end();
	}
	const_iterator current = {root_, max_};
	const_iterator cashed = end();
	while (true)
	{
		if (compare_(key, get_key(current.data_->value_)))
		{
			cashed = current;
			if (current.data_->left_ == nullptr)
			{
				return cashed;
			}
			current.data_ = current.data_->left_;
		}
		else
		{
			if (current.data_->right_ == nullptr)
			{
				return cashed;
			}
			current.data_ = current.data_->right_;
		}
	}
}

#endif
