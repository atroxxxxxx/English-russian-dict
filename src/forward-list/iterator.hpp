#ifndef FORWARD_LIST_ITERATOR_HPP
#define FORWARD_LIST_ITERATOR_HPP

#include <memory>
#include <type_traits>
#include "node.hpp"

namespace src
{
	namespace forward_list
	{
		template< class T, bool isConst = false >
		class ForwardIterator
		{
		public:
			using value_type = T;
			using reference_type = std::conditional_t< isConst, const value_type&, value_type& >;
			using pointer_type = std::conditional_t< isConst, const value_type*, value_type* >;
			using iterator_category = std::forward_iterator_tag;

			ForwardIterator() noexcept:
				node_(nullptr)
			{}
			ForwardIterator(const ForwardIterator< value_type, false >& iterator) noexcept:
				node_(iterator.node_)
			{}

			bool operator!=(ForwardIterator iterator) const noexcept
			{
				return iterator.node_ != node_;
			}
			bool operator==(ForwardIterator iterator) const noexcept
			{
				return !(iterator != *this);
			}

			reference_type operator*() const noexcept
			{
				return node_->key;
			}
			pointer_type operator->() const noexcept
			{
				return std::addressof(node_->key);
			}

			ForwardIterator& operator++() noexcept
			{
				node_ = node_->next;
				return *this;
			}
			ForwardIterator operator++(int) noexcept
			{
				ForwardIterator< value_type, isConst > temp = *this;
				++(*this);
				return temp;
			}
		private:
			using node_type = Node_t< value_type >;
			node_type* node_;
			ForwardIterator(node_type* node) noexcept:
				node_(node)
			{}

			template< class U >
			friend class ForwardList;
			friend class ForwardIterator< value_type, true >;
		};
	}
}

#endif
