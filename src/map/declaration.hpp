#ifndef MAP_DECLARATION_HPP
#define MAP_DECLARATION_HPP

#include "../map_base.hpp"
#include <functional>

namespace src
{
	template< class Key, class Mapped, class Compare = std::less<> >
	class Map: public details::MapBase< const Key,
			Mapped,
			Compare,
			Pair< const Key, Mapped >,
			details::ValueCompare< Pair< const Key, Mapped >, Compare > >
	{
	public:
		using base = details::MapBase< const Key,
			Mapped,
			Compare,
			Pair< const Key, Mapped >,
			details::ValueCompare< Pair< const Key, Mapped >, Compare > >;
		using key_type = typename base::key_type;
		using mapped_type = typename base::mapped_type;
		using value_type = typename base::value_type;
		using size_type = typename base::size_type;
		using key_compare = typename base::key_compare;
		using value_compare = typename base::value_compare;

		using iterator = typename base::iterator;
		using const_iterator = typename base::const_iterator;
		using reverse_iterator = typename base::reverse_iterator;
		using const_reverse_iterator = typename base::const_reverse_iterator;

		Map() noexcept(std::is_nothrow_default_constructible< value_compare >::value): base()
		{}
		Map(const key_compare& compare): base(compare)
		{}
		Map(const Map& rhs): base(rhs)
		{}
		Map(Map&& rhs) noexcept(std::is_nothrow_default_constructible< value_compare >::value): base(std::move(rhs))
		{}
		template< class InIter >
		Map(InIter from, InIter to, const key_compare& compare = key_compare()): base(from, to, compare)
		{}
		Map(std::initializer_list< value_type > list, const key_compare& compare = key_compare()): base(list, compare)
		{}

		mapped_type& at(const key_type& key);
		const mapped_type& at(const key_type& key) const;
		mapped_type& operator[](const key_type& key);
		mapped_type& operator[](key_type&& key);
	};
}

#endif
