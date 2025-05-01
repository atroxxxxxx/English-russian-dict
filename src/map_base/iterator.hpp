#ifndef MAP_BASE_ITERATOR_HPP
#define MAP_BASE_ITERATOR_HPP

#include <iterator>
#include "node.hpp"

namespace src
{
	template< class Value, bool isConst, bool isReversed >
	class MapIterator
	{
	public:
		using value_type = Value;
		using node_type = details::map_node_t< value_type >;
		MapIterator() noexcept:
			data_(nullptr),
			prev_(nullptr)
		{}
		template< bool isConst1 = isConst >
		MapIterator(std::enable_if_t< isConst && isConst1, MapIterator< Value, false, isReversed > > iter) noexcept:
			data_(iter.data_),
			prev_(iter.prev_)
		{}
		MapIterator(node_type* pointer, node_type* rbegin) noexcept:
			data_(pointer),
			prev_(rbegin)
		{}
		template< bool isConst1 = isConst >
		std::enable_if_t< !isConst && !isConst1, value_type& > operator*() noexcept
		{
			return data_->value_;
		}
		template< bool isConst1 = isConst >
		std::enable_if_t< !isConst && !isConst1, value_type* > operator->() noexcept
		{
			return std::addressof(data_->value_);
		}
		const value_type& operator*() const noexcept
		{
			return data_->value_;
		}
		const value_type* operator->() const noexcept
		{
			return std::addressof(data_->value_);
		}

		MapIterator& operator++() noexcept
		{
			if (isReversed)
			{
				shift_left();
			}
			else
			{
				shift_right();
			}
			return *this;
		}
		MapIterator& operator--() noexcept
		{
			if (data_ == nullptr)
			{
				data_ = prev_;
			}
			else if (isReversed)
			{
				shift_right();
			}
			else
			{
				shift_left();
			}
			return *this;
		}
		MapIterator operator++(int) noexcept
		{
			MapIterator temp = *this;
			operator++();
			return temp;
		}
		MapIterator operator--(int) noexcept
		{
			MapIterator temp = *this;
			operator--();
			return temp;
		}
	private:
		template< class Key, class Mapped, class Compare, class Value1, class ValueCompare >
		friend class MapBase;
		friend class MapIterator< Value, true, isReversed >;

		node_type* data_;
		node_type* prev_;
		void shift_left() noexcept
		{
			if (data_->left_)
			{
				for (data_ = data_->left_; data_->right_ != nullptr; data_ = data_->right_)
				{}
			}
			else
			{
				for (prev_ = data_; (data_ != nullptr) && (data_->left_ == prev_); prev_ = data_, data_ = data_->parent_)
				{}
			}
		}
		void shift_right() noexcept
		{
			if (data_->right_)
			{
				for (data_ = data_->right_; data_->left_ != nullptr; data_ = data_->left_)
				{}
			}
			else
			{
				for (prev_ = data_; (data_ != nullptr) && (data_->right_ == prev_); prev_ = data_, data_ = data_->parent_)
				{}
			}
		}
	};
}

#endif
