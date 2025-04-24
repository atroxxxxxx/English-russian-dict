#ifndef MAP_MODIFIERS_HPP
#define MAP_MODIFIERS_HPP

#include "declaration.hpp"

template< class Key, class T, class Compare >
bool src::RBTree< Key, T, Compare >::insert(key_type key, mapped_type meaning)
{
	if (!root_) {
		root_ = new node_type {value_type{key, meaning}, BLACK};
		size_++;
		return true;
	}
	node_type* current = root_;
	while (current) {
		if (key_compare()(key, current->value_.first))
		{
			if (!current->left_)
			{
				current->left_ = new node_type {value_type{key, meaning}, RED, current};
				insert_fix(current->left_);
				size_++;
				return true;
			}
			current = current->left_;
		}
		else
		{
			if (!key_compare()(current->value_.first, key))
			{
				return false;
			}
			if (!current->right_)
			{
				current->right_ = new node_type {value_type{key, meaning}, RED, current};
				insert_fix(current->right_);
				size_++;
				return true;
			}
			current = current->right_;
		}
	}
	return false;
}

template< class Key, class T, class Compare >
std::pair< bool, typename src::RBTree< Key, T, Compare >::mapped_type* >
		src::RBTree< Key, T, Compare >::search(const key_type& key) const
{
	node_type* finded = find(key);
	if (!finded)
	{
		return {false, nullptr};
	}
	return std::pair< bool, mapped_type* >(true, &finded->value_.second);
}

template< class Key, class T, class Compare >
bool src::RBTree< Key, T, Compare >::remove(const key_type& key)
{
	node_type* toDelete = find(key);
	if (!toDelete)
	{
		return false;
	}
	node_type* replacement = nullptr;
	node_type* child = nullptr;

	if (toDelete->left_ && toDelete->right_)
	{
		replacement = toDelete->right_;
		while (replacement->left_)
		{
			replacement = replacement->left_;
		}
		child = replacement->right_;
	}
	else
	{
		replacement = (toDelete->left_) ? toDelete->left_ : toDelete->right_;
		child = replacement;
	}
	if (replacement && replacement->parent_ != toDelete)
	{
		if (replacement == replacement->parent_->left_)
		{
			replacement->parent_->left_ = child;
		}
		else
		{
			replacement->parent_->right_ = child;
		}
		if (child)
		{
			child->parent_ = replacement->parent_;
		}
	}
	if (!toDelete->parent_)
	{
		root_ = replacement;
	}
	else if (toDelete == toDelete->parent_->left_)
	{
		toDelete->parent_->left_ = replacement;
	}
	else
	{
		toDelete->parent_->right_ = replacement;
	}
	if (replacement)
	{
		replacement->parent_ = toDelete->parent_;
		if (toDelete->left_ != replacement)
		{
			replacement->left_ = toDelete->left_;
			if (replacement->left_)
			{
				replacement->left_->parent_ = replacement;
			}
		}
		if (toDelete->right_ != replacement)
		{
			replacement->right_ = toDelete->right_;
			if (replacement->right_)
			{
				replacement->right_->parent_ = replacement;
			}
		}
		replacement->color_ = toDelete->color_;
	}

	if (toDelete->color_ == Color::BLACK)
	{
		remove_fix(child ? child : toDelete->parent_);
	}
	delete toDelete;
	size_--;
	return true;
}

template< class Key, class T, class Compare >
typename src::RBTree< Key, T, Compare >::node_type*
		src::RBTree< Key, T, Compare >::find(const key_type& key) const
{
	if (!root_)
	{
		return nullptr;
	}
	node_type* current = root_;
	while (current)
	{
		if (key_compare()(key, current->value_.first))
		{
			current = current->left_;
		}
		else
		{
			if (!key_compare()(current->value_.first, key))
			{
				return current;
			}
			current = current->right_;
		}
	}
	return nullptr;
}

#endif
