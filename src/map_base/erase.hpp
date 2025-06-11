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
	bool deletedRed = toDelete->isRed_;
	node_type* replacement = nullptr;
	node_type* successor = nullptr;
	if (toDelete->left_ && toDelete->right_)
	{
		successor = toDelete->right_;
		while (successor->left_)
		{
			successor = successor->left_;
		}
		toDelete->value_ = successor->value_;
		toDelete = successor;
		deletedRed = toDelete->isRed_;
	}
	replacement = toDelete->left_ ? toDelete->left_ : toDelete->right_;
	if (replacement)
	{
		replacement->parent_ = toDelete->parent_;
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
	if (toDelete == min_)
	{
		min_ = replacement ? replacement : toDelete->parent_;
		while (min_ && min_->left_)
		{
			min_ = min_->left_;
		}
	}
	if (toDelete == max_)
	{
		max_ = replacement ? replacement : toDelete->parent_;
		while (max_ && max_->right_)
		{
			max_ = max_->right_;
		}
	}
	if (!deletedRed)
	{
		node_type* fixNodeParent = toDelete->parent_;
		node_type* current = replacement;
		while (current != root_ && (!current || !current->isRed_))
		{
			if (current == (fixNodeParent ? fixNodeParent->left_ : nullptr))
			{
				node_type* brother = fixNodeParent ? fixNodeParent->right_ : nullptr;
				if (brother && brother->isRed_)
				{
					brother->isRed_ = false;
					fixNodeParent->isRed_ = true;
					rotate_left(fixNodeParent);
					brother = fixNodeParent->right_;
				}
				if ((!brother->left_ || !brother->left_->isRed_) &&
						(!brother->right_ || !brother->right_->isRed_))
				{
					if (brother)
					{
						brother->isRed_ = true;
					}
					current = fixNodeParent;
					fixNodeParent = current ? current->parent_ : nullptr;
				}
				else
				{
					if (!brother->right_ || !brother->right_->isRed_)
					{
						if (brother->left_)
						{
							brother->left_->isRed_ = false;
						}
						if (brother)
						{
							brother->isRed_ = true;
							rotate_right(brother);
							brother = fixNodeParent ? fixNodeParent->right_ : nullptr;
						}
					}
					if (brother)
					{
						brother->isRed_ = fixNodeParent ? fixNodeParent->isRed_ : false;
						if (brother->right_)
						{
							brother->right_->isRed_ = false;
						}
					}
					if (fixNodeParent)
					{
						fixNodeParent->isRed_ = false;
						rotate_left(fixNodeParent);
					}
					current = root_;
				}
			}
			else
			{
				node_type* brother = fixNodeParent ? fixNodeParent->left_ : nullptr;
				if (brother && brother->isRed_)
				{
					brother->isRed_ = false;
					fixNodeParent->isRed_ = true;
					rotate_right(fixNodeParent);
					brother = fixNodeParent->left_;
				}
				if ((!brother->left_ || !brother->left_->isRed_) &&
				    (!brother->right_ || !brother->right_->isRed_))
				{
					if (brother)
					{
						brother->isRed_ = true;
					}
					current = fixNodeParent;
					fixNodeParent = current ? current->parent_ : nullptr;
				}
				else
				{
					if (!brother->left_ || !brother->left_->isRed_)
					{
						if (brother->right_)
						{
							brother->right_->isRed_ = false;
						}
						if (brother)
						{
							brother->isRed_ = true;
							rotate_left(brother);
							brother = fixNodeParent ? fixNodeParent->left_ : nullptr;
						}
					}
					if (brother)
					{
						brother->isRed_ = fixNodeParent ? fixNodeParent->isRed_ : false;
						if (brother->left_)
						{
							brother->left_->isRed_ = false;
						}
					}
					if (fixNodeParent)
					{
						fixNodeParent->isRed_ = false;
						rotate_right(fixNodeParent);
					}
					current = root_;
				}
			}
		}
		if (current)
		{
			current->isRed_ = false;
		}
	}
	iterator result = {(--iter).data_, max_};
	delete toDelete;
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
