#ifndef MAP_DEFINITION_HPP
#define MAP_DEFINITION_HPP

#include "declaration.hpp"

template< class Key, class T, class Compare >
bool src::RBTree< Key, T, Compare >::insert(const key_type& key, const mapped_type& meaning)
{
	if (!root_) {
		root_ = new node_type {key, BLACK};
		return true;
	}
	node_type* current = root_;
	while (current) {
		if (key_compare()(key, current->key_)) {
			if (!current->left_) {
				current->left_ = new node_type {{key, meaning}, RED, current};
				insert_fix(current->left_);
				return true;
			}
			current = current->left_;
		}
		else {
			if (!key_compare()(current->key_, key)) {
				return false;
			}
			if (!current->right_) {
				current->right_ = new node_type {{key, meaning}, RED, current};
				insert_fix(current->right_);
				return true;
			}
			current = current->right_;
		}
	}
}

template< class Key, class T, class Compare >
std::pair< bool, const typename src::RBTree< Key, T, Compare >::mapped_type* >
		src::RBTree< Key, T, Compare >::search(const key_type& key)
{
	node_type* finded = find(key);
	if (!finded)
	{
		return {false, nullptr};
	}
	return {true, finded->value_.second};
}

template< class Key, class T, class Compare >
bool src::RBTree< Key, T, Compare >::remove(const key_type& key)
{
	node_type* current = find(key);
	if (!current) {
		return false;
	}
	node_type* toDelete = current;
	if (current->left_) {
		current = current->left_;
		if (current->right_) {
			while (current->right_) {
				current = current->right_;
			}
			current->parent_->right_ = current->left_;
			current->left_->parent_ = current->parent_;
		}
		current->right_ = toDelete->right_;
		if (toDelete->right_) {
			toDelete->right_->parent_ = current;
		}
	}
	else {
		current = toDelete->right_;
	}
	if (toDelete->parent_) {
		if (toDelete->parent_->left_ == toDelete) {
			toDelete->parent_->left_ = current;
		}
		else {
			toDelete->parent_->right_ = current;
		}
	}
	if (current) {
		current->parent_ = toDelete->parent_;
	}
	if (!toDelete->parent_) {
		root_ = current;
	}
	if (toDelete->color_ == BLACK)
	{
		remove_fix(toDelete);
	}
	delete toDelete;
	return true;
}

template< class Key, class T, class Compare >
typename src::RBTree< Key, T, Compare >::node_type*
		src::RBTree< Key, T, Compare >::find(const key_type& key) const
{
	if (!root_) {
		return nullptr;
	}
	node_type* current = root_;
	while (current) {
		if (key_compare()(key, current->key_)) {
			current = current->left_;
		}
		else {
			if (!key_compare()(current->key_, key)) {
				return current;
			}
			current = current->right_;
		}
	}
	return nullptr;
}

#endif
