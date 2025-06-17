#ifndef MAP_BASE_INSERT_HPP
#define MAP_BASE_INSERT_HPP

#include "modifiers.hpp"

template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
src::Pair< typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::iterator, bool >
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::insert(const value_type& value)
{
	const_iterator hint = end();
	hint = lower_bound(get_key(value));
	if ((hint == end()) || compare_(value, *hint))
	{
		return {insert(hint, new node_type{value, true, hint.data_}), true};
	}
	return {end(), false};
}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
src::Pair< typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::iterator, bool >
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::insert(value_type&& value)
{
	const_iterator hint = lower_bound(get_key(value));
	if ((hint == end()) || compare_(value, *hint))
	{
		node_type* node = new node_type{std::move(value), true, hint.data_};
		return {insert(hint, node), true};
	}
	return {end(), false};
}

template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::iterator
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::insert(const_iterator hint, node_type* node)
{
	bool insertToLeft = true;
	if (empty())
	{
		root_ = node;
		root_->isRed_ = false;
		size_++;
		min_ = max_ = root_;
		return begin();
	}
	if ((hint == end()) || (hint.data_->left_ != nullptr))
	{
		--hint;
		insertToLeft = false;
	}
	node->parent_ = hint.data_;
	if (insertToLeft)
	{
		hint.data_->left_ = node;
		if (hint.data_ == min_)
		{
			min_ = hint.data_->left_;
		}
	}
	else
	{
		hint.data_->right_ = node;
		if (hint.data_ == max_)
		{
			max_ = hint.data_->right_;
		}
	}
	if (node->parent_->isRed_)
	{
		node_type* current = node;
		while ((current != nullptr) && (current != root_) && current->parent_->isRed_)
		{
			if (current->parent_ == root_)
			{
				root_->isRed_ = false;
				break;
			}
			node_type* grandpa = current->parent_->parent_;
			if (current == current->parent_->left_)
			{
				if (grandpa->left_ != current->parent_)
				{
					rotate_right(current);
					current = current->right_;
					continue;
				}
				grandpa->isRed_ = true;
				if ((grandpa->right_ == nullptr) || !grandpa->right_->isRed_)
				{
					if (grandpa->right_ != nullptr)
					{
						grandpa->right_->isRed_ = false;
					}
					rotate_right(current->parent_);
					current->parent_->isRed_ = false;
					current = current->parent_->parent_;
				}
				else
				{
					grandpa->right_->isRed_ = false;
					current->parent_->isRed_ = false;
					current = grandpa;
				}
			}
			else
			{
				if (grandpa->right_ != current->parent_)
				{
					rotate_left(current);
					current = current->left_;
					continue;
				}
				grandpa->isRed_ = true;
				if ((grandpa->left_ == nullptr) || !grandpa->left_->isRed_)
				{
					if (grandpa->left_ != nullptr)
					{
						grandpa->left_->isRed_ = false;
					}
					rotate_left(current->parent_);
					current->parent_->isRed_ = false;
					current = current->parent_->parent_;
				}
				else
				{
					grandpa->left_->isRed_ = false;
					current->parent_->isRed_ = false;
					current = grandpa;
				}
			}
		}
	}
	size_++;
	return {node, min_};
}

#endif
