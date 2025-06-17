#ifndef MAP_BASE_ERASE_HPP
#define MAP_BASE_ERASE_HPP

#include "modifiers.hpp"

template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::iterator
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::erase(const_iterator pos)
{
	if (pos == end())
	{
		return end();
	}
	iterator result = {pos.data_, max_};
	++result;
	if (pos == begin())
	{
		min_ = (++begin()).data_;
	}
	if (pos.data_ == max_)
	{
		max_ = (----end()).data_;
	}

	node_type* toDelete = pos.data_;
	node_type* replacement = nullptr;
	node_type* child = nullptr;

	if ((toDelete->left_ != nullptr) && (toDelete->right_ != nullptr))
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
		replacement = (toDelete->left_ != nullptr) ? toDelete->left_ : toDelete->right_;
		child = replacement;
	}
	if ((replacement != nullptr) && (replacement->parent_ != toDelete))
	{
		if (replacement == replacement->parent_->left_)
		{
			replacement->parent_->left_ = child;
		}
		else
		{
			replacement->parent_->right_ = child;
		}
		if (child != nullptr)
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
	if (replacement != nullptr)
	{
		replacement->parent_ = toDelete->parent_;
		if (toDelete->left_ != replacement)
		{
			replacement->left_ = toDelete->left_;
			if (replacement->left_ != nullptr)
			{
				replacement->left_->parent_ = replacement;
			}
		}
		if (toDelete->right_ != replacement)
		{
			replacement->right_ = toDelete->right_;
			if (replacement->right_ != nullptr)
			{
				replacement->right_->parent_ = replacement;
			}
		}
		replacement->isRed_ = toDelete->isRed_;
	}
	if (!toDelete->isRed_)
	{
		node_type* current = ((child != nullptr) ? child : toDelete->parent_);
		while ((current != nullptr) && (current != root_) && !current->isRed_)
		{
			node_type* parent = current->parent_;
			if (current == parent->left_)
			{
				node_type* sibling = parent->right_;
				if (sibling->isRed_)
				{
					sibling->isRed_ = false;
					parent->isRed_ = true;
					rotate_left(parent);
					sibling = parent->right_;
				}
				if (((sibling->left_ == nullptr) || (!sibling->left_->isRed_))
						&& ((sibling->right_ == nullptr) || (!sibling->right_->isRed_)))
				{
					sibling->isRed_ = true;
					current = parent;
				}
				else
				{
					if ((sibling->right_ == nullptr) || (!sibling->right_->isRed_))
					{
						if (sibling->left_ != nullptr)
						{
							sibling->left_->isRed_ = false;
						}
						sibling->isRed_ = true;
						rotate_right(sibling);
						sibling = parent->right_;
					}
					sibling->isRed_ = parent->isRed_;
					parent->isRed_ = false;
					if (sibling->right_ != nullptr)
					{
						sibling->right_->isRed_ = false;
					}
					rotate_left(parent);
					current = root_;
				}
			}
			else
			{
				node_type* sibling = parent->left_;
				if (sibling->isRed_)
				{
					sibling->isRed_ = false;
					parent->isRed_ = true;
					rotate_right(parent);
					sibling = parent->left_;
				}
				if (((sibling->left_ == nullptr) || (!sibling->left_->isRed_))
				    && ((sibling->right_ == nullptr) || (!sibling->right_->isRed_)))
				{
					sibling->isRed_ = true;
					current = parent;
				}
				else
				{
					if ((sibling->left_ == nullptr) || (!sibling->left_->isRed_))
					{
						if (sibling->right_ != nullptr)
						{
							sibling->right_->isRed_ = false;
						}
						sibling->isRed_ = true;
						rotate_left(sibling);
						sibling = parent->left_;
					}
					sibling->isRed_ = parent->isRed_;
					parent->isRed_ = false;
					if (sibling->left_ != nullptr)
					{
						sibling->left_->isRed_ = false;
					}
					rotate_right(parent);
					current = root_;
				}
			}
		}
		if (current != nullptr)
		{
			current->isRed_ = false;
		}
	}
	delete toDelete;
	--size_;
	return result;
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
