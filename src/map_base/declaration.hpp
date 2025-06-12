#ifndef MAP_BASE_DECLARATION_HPP
#define MAP_BASE_DECLARATION_HPP

#include <initializer_list>
#include <type_traits>
#include <cstddef>
#include "pair.hpp"
#include "node.hpp"
#include "iterator.hpp"

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
			using value_type = Value;
			using size_type = size_t;
			using key_compare = Compare;
			using value_compare = ValueCompare;

			using iterator = MapIterator< value_type, false, false >;
			using const_iterator = MapIterator< value_type, true, false >;
			using reverse_iterator = MapIterator< value_type, false, true >;
			using const_reverse_iterator = MapIterator< value_type, true, true >;

			MapBase() noexcept(std::is_nothrow_default_constructible< value_compare >::value);
			MapBase(const key_compare& compare);
			MapBase(const MapBase& rhs);
			MapBase(MapBase&& rhs) noexcept(std::is_nothrow_default_constructible< value_compare >::value);
			template< class InIter >
			MapBase(InIter from, InIter to, const key_compare& compare = key_compare());
			MapBase(std::initializer_list< value_type > list, const key_compare& compare = key_compare());
			~MapBase();

			MapBase& operator=(const MapBase& rhs);
			MapBase& operator=(MapBase&& rhs) noexcept(std::is_nothrow_default_constructible< value_compare >::value);
			MapBase& operator=(std::initializer_list< value_type > list);

			iterator begin() noexcept;
			const_iterator begin() const noexcept;
			const_iterator cbegin() const noexcept;
			reverse_iterator rbegin() noexcept;
			const_reverse_iterator rbegin() const noexcept;
			const_reverse_iterator crbegin() const noexcept;

			iterator end() noexcept;
			const_iterator end() const noexcept;
			const_iterator cend() const noexcept;
			reverse_iterator rend() noexcept;
			const_reverse_iterator rend() const noexcept;
			const_reverse_iterator crend() const noexcept;

			bool empty() const noexcept;
			size_type size() const noexcept;

			bool contains(const key_type& key) const;
			iterator lower_bound(const key_type& key);
			const_iterator lower_bound(const key_type& key) const;
			iterator upper_bound(const key_type& key);
			const_iterator upper_bound(const key_type& key) const;
			iterator find(const key_type& key);
			const_iterator find(const key_type& key) const;

			void clear();
			void swap(MapBase& rhs);

			template< class... Args >
			iterator emplace_hint(const_iterator hint, Args&&... args);
			template< class... Args >
			iterator emplace(Args&&... args);
			Pair< iterator, bool > insert(const value_type& value);
			Pair< iterator, bool > insert(value_type&& value);
			iterator erase(const_iterator iter);
			size_type erase(const key_type& key);
		private:
			using node_type = map_node_t< value_type >;
			value_compare compare_;
			node_type* root_;
			size_type size_;
			node_type* min_;
			node_type* max_;

			static node_type* copy(node_type* current);
			static void destroy(node_type* node);

			bool compare_with_key(const key_type& lhs, const key_type& rhs) const;
			template< class V = value_type >
			bool compare_with_key(std::enable_if_t< !std::is_same< key_type, V >::value, const V& > lhs,
					const key_type& rhs) const;
			template< class V = value_type >
			bool compare_with_key(const key_type& lhs,
					std::enable_if_t< !std::is_same< key_type, V >::value, const V& > rhs) const;
			template< class V = value_type >
			static const key_type& get_key(std::enable_if_t< std::is_same< key_type, V >::value, const V& > value);
			template< class V = value_type >
			static const key_type& get_key(std::enable_if_t< !std::is_same< key_type, V >::value, const V& > value);

			const_iterator lower_bound_impl(const key_type& key) const;
			const_iterator upper_bound_impl(const key_type& key) const;
			iterator insert(const_iterator hint, node_type* node);

			void rotate_left(node_type* node) noexcept;
			void rotate_right(node_type* node) noexcept;
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
