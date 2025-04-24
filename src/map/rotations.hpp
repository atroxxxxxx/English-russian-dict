#ifndef MAP_ROTATIONS_HPP
#define MAP_ROTATIONS_HPP

#include "declaration.hpp"

template< class Key, class T, class Compare >
void src::RBTree< Key, T, Compare >::rotate_left(node_type* node)
{
	node_type* right = node->right_;
	node->right_ = right->left_;
	if (node->right_)
	{
		right->left_->parent_ = node;
	}
	right->parent_ = node->parent_;
	if (!node->parent_)
	{
		root_ = right;
	}
	else if (node->parent_->left_ == node)
	{
		node->parent_->left_ = right;
	}
	else
	{
		node->parent_->right_ = right;
	}
	right->left_ = node;
	node->parent_ = right;
}
template< class Key, class T, class Compare >
void src::RBTree< Key, T, Compare >::rotate_right(node_type* node)
{
	node_type* left = node->left_;
	node->left_ = left->right_;
	if (node->left_)
	{
		node->left_->parent_ = node;
	}
	left->parent_ = node->parent_;
	if (!node->parent_)
	{
		root_ = left;
	}
	else if (node->parent_->right_ == node)
	{
		node->parent_->right_ = left;
	}
	else
	{
		node->parent_->left_ = left;
	}
	left->right_ = node;
	node->parent_ = left;
}

template< class Key, class T, class Compare >
void src::RBTree< Key, T, Compare >::insert_fix(node_type* node)
{
	while ((node != root_) && node->parent_ && (node->parent_->color_ == RED))
	{
		if (node->parent_->parent_ && (node->parent_ == node->parent_->parent_->left_))
		{
			node_type* current = node->parent_->parent_->right_;
			if (current && (current->color_ == RED))
			{
				node->parent_->color_ = BLACK;
				current->color_ = BLACK;
				node->parent_->parent_->color_ = RED;
				node = node->parent_->parent_;
			}
			else
			{
				if (node == node->parent_->right_)
				{
					node = node->parent_;
					rotate_left(node);
				}
				node->parent_->color_ = BLACK;
				node->parent_->parent_->color_ = RED;
				rotate_right(node->parent_->parent_);
			}
		}
		else if (node->parent_->parent_)
		{
			node_type* current = node->parent_->parent_->left_;
			if (current && (current->color_ == RED))
			{
				node->parent_->color_ = BLACK;
				current->color_ = BLACK;
				node->parent_->parent_->color_ = RED;
				node = node->parent_->parent_;
			}
			else
			{
				if (node == node->parent_->left_)
				{
					node = node->parent_;
					rotate_right(node);
				}
				node->parent_->color_ = BLACK;
				node->parent_->parent_->color_ = RED;
				rotate_left(node->parent_->parent_);
			}
		}
		else
		{
			break;
		}
	}
	root_->color_ = BLACK;
}

template< class Key, class T, class Compare >
void src::RBTree< Key, T, Compare >::remove_fix(node_type* node)
{
	while (node != root_ && node->color_ == BLACK)
	{
		node_type* parent = node->parent_;
		if (node == parent->left_)
		{
			node_type* sibling = parent->right_;
			if (sibling->color_ == RED)
			{
				sibling->color_ = BLACK;
				parent->color_  = RED;
				rotate_left(parent);
				sibling = parent->right_;
			}
			if ((!sibling->left_  || sibling->left_->color_  == BLACK) &&
			    (!sibling->right_ || sibling->right_->color_ == BLACK))
			{
				sibling->color_ = RED;
				node = parent;
			}
			else
			{
				if (!sibling->right_ || sibling->right_->color_ == BLACK)
				{
					if (sibling->left_)
						sibling->left_->color_ = BLACK;
					sibling->color_ = RED;
					rotate_right(sibling);
					sibling = parent->right_;
				}
				sibling->color_      = parent->color_;
				parent->color_       = BLACK;
				if (sibling->right_)
					sibling->right_->color_ = BLACK;
				rotate_left(parent);
				node = root_;
			}
		}
		else
		{
			node_type* sibling = parent->left_;
			if (sibling->color_ == RED)
			{
				sibling->color_ = BLACK;
				parent->color_  = RED;
				rotate_right(parent);
				sibling = parent->left_;
			}
			if ((!sibling->left_  || sibling->left_->color_  == BLACK) &&
			    (!sibling->right_ || sibling->right_->color_ == BLACK))
			{
				sibling->color_ = RED;
				node = parent;
			}
			else
			{
				if (!sibling->left_ || sibling->left_->color_ == BLACK)
				{
					if (sibling->right_)
						sibling->right_->color_ = BLACK;
					sibling->color_ = RED;
					rotate_left(sibling);
					sibling = parent->left_;
				}
				sibling->color_      = parent->color_;
				parent->color_       = BLACK;
				if (sibling->left_)
					sibling->left_->color_ = BLACK;
				rotate_right(parent);
				node = root_;
			}
		}
	}
	if (node)
		node->color_ = BLACK;
}


#endif
