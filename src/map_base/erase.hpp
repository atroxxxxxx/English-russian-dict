#ifndef MAP_BASE_ERASE_HPP
#define MAP_BASE_ERASE_HPP

#include "modifiers.hpp"

template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::iterator
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::erase(const_iterator iter)
{
	if (iter == end())
	{
		return end();
	}
	node_type* toDelete = iter.data_;
	node_type* current = toDelete;
	if (current->left_)
	{
		current = current->left_;
		if (current->right_)
		{
			while (current->right_)
			{
				current = current->right_;
			}
			current->parent_->right_ = current->left_;
			current->left_->parent_ = current->parent_;
		}
		current->right_ = toDelete->right_;
		if (toDelete->right_)
		{
			toDelete->right_->parent_ = current;
		}
	}
	else
	{
		current = toDelete->right_;
	}
	if (toDelete->parent_)
	{
		if (toDelete->parent_->left_ == toDelete)
		{
			toDelete->parent_->left_ = current;
		}
		else
		{
			toDelete->parent_->right_ = current;
		}
	}
	if (current)
	{
		current->parent_ = toDelete->parent_;
	}
	if (!toDelete->parent_)
	{
		root_ = current;
	}
	if (toDelete == min_)
	{
		++min_;
	}
	else if (toDelete == max_)
	{
		--max_;
	}
	delete toDelete;
	// erase_fix;
	return {current, max_};
}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::size_type
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::erase(const key_type& key)
{
	iterator current = find(key);
	if (current == end())
	{
		return 0;
	}
	erase(current);
	return 1;
}

#endif
