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
void src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::swap(MapBase& rhs)
{
	if (this != &rhs)
	{
		std::swap(compare_, rhs.compare_);
		std::swap(root_, rhs.root_);
		std::swap(size_, rhs.size_);
		std::swap(min_, rhs.min_);
		std::swap(max_, rhs.max_);
	}
}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
template< class... Args >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::iterator
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::emplace_hint(const_iterator hint, Args&&... args)
{
	return insert(hint, new node_type{{args...}, true, hint.data_});
}
template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
template< class... Args >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::iterator
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::emplace(Args&&... args)
{
	node_type* current = new node_type{{args...}, true};
	key_type& key = get_key(current->value_);
	const_iterator hint = end();
	try
	{
		hint = lower_bound(key);
		if ((hint != end()) && !compare_(get_key(hint.data_->value_), key))
		{
			current->parent_ = *hint;
			return insert(hint, current);
		}
	}
	catch (...)
	{
		delete current;
		throw;
	}
	delete current;
	return end();
}

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

template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
void src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::rotate_left(node_type* node) noexcept
{
	node_type* parent = node->parent_;
	if ((parent->parent_ != nullptr) && (parent == parent->parent_->left_))
	{
		parent->parent_->left_ = node;
	}
	else if ((parent->parent_ != nullptr) && (parent == parent->parent_->right_))
	{
		parent->parent_->right_ = node;
	}
	else
	{
		root_ = node;
	}
	node->parent_ = parent->parent_;
	node->isRed_ = parent->isRed_;
	parent->isRed_ = true;
	parent->parent_ = node;
	parent->right_ = node->left_;
	if (node->left_ != nullptr)
	{
		node->left_->parent_ = parent;
	}
	node->left_ = parent;
}

template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
void src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::rotate_right(node_type* node) noexcept
{
	node_type* parent = node->parent_;
	if ((parent->parent_ != nullptr) && (parent == parent->parent_->left_))
	{
		parent->parent_->left_ = node;
	}
	else if ((parent->parent_ != nullptr) && (parent == parent->parent_->right_))
	{
		parent->parent_->right_ = node;
	}
	else
	{
		root_ = node;
	}
	node->parent_ = parent->parent_;
	node->isRed_ = parent->isRed_;
	parent->isRed_ = true;
	parent->parent_ = node;
	parent->left_ = node->right_;
	if (node->right_ != nullptr)
	{
		node->right_->parent_ = parent;
	}
	node->right_ = parent;
}

#endif
