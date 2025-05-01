#ifndef MAP_BASE_DECLARATION_HPP
#define MAP_BASE_DECLARATION_HPP

#include <iterator>
#include <initializer_list>
#include <cstddef>
#include "pair.hpp"
#include "node.hpp"

namespace src
{
	namespace details
	{
		template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
		class MapBase
		{
		public:
			using key_type = Key;
			using mapped_type = Mapped;
			using value_type = Pair< key_type, mapped_type >;
			using size_type = size_t;
			using key_compare = Compare;
			using value_compare = ValueCompare;

			using iterator = std::bidirectional_iterator_tag;
			using const_iterator = const std::bidirectional_iterator_tag;
			using reverse_iterator = std::bidirectional_iterator_tag;
			using const_reverse_iterator = const std::bidirectional_iterator_tag;

			MapBase() noexcept;
			MapBase(const MapBase& rhs);
			MapBase(MapBase&& rhs) noexcept;
			template< class InIter >
			MapBase(InIter from, InIter to);
			MapBase(std::initializer_list< value_type > list);
			~MapBase();

			MapBase& operator=(const MapBase& rhs);
			MapBase& operator=(MapBase&& rhs) noexcept;
			MapBase& operator=(std::initializer_list< value_type > list);

			iterator begin() noexcept;
			const_iterator begin() const noexcept;
			const_iterator cbegin() const noexcept;
			reverse_iterator rbegin() noexcept;
			const_reverse_iterator rbegin() const noexcept;
			const_reverse_iterator rcbegin() const noexcept;

			iterator end() noexcept;
			const_iterator end() const noexcept;
			const_iterator cend() const noexcept;
			reverse_iterator rend() noexcept;
			const_reverse_iterator rend() const noexcept;
			const_reverse_iterator crend() const noexcept;

			bool empty() const noexcept;
			size_type size() const noexcept;
			bool contains(const key_type& key) const;
			iterator lower_bound();
			const_iterator lower_bound() const;
			iterator upper_bound();
			const_iterator upper_bound() const;
			iterator find(const key_type& key);
			const_iterator find(const key_type& key) const;

			void clear();
			void swap(const MapBase& rhs) noexcept;

			template< class... Args >
			iterator emplace_hint(const_iterator hint, Args&&... args);
			template< class... Args >
			iterator emplace(Args&&... args);
			Pair< iterator, bool > insert(const value_type& key);
			Pair< iterator, bool > insert(value_type&& key);
			iterator erase(const_iterator iter);
			size_type erase(const key_type& key);

		private:
			using node_type = map_node_t< value_type >;
			value_compare compare_;
			node_type* root_;
			size_type size_;
		};
	}
}

namespace std
{
	template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
	void swap(src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >& lhs,
			src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >& rhs)
	{
		lhs.swap(rhs);
	}
}

#endif
