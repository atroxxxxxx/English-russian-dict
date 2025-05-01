#ifndef MAP_HPP
#define MAP_HPP

#include "map_base/declaration.hpp"
#include "map_base/value_compare.hpp"

namespace src
{
	template< class Key, class Mapped, class Compare >
	class Map: public details::MapBase< Key,
		Mapped,
		Compare,
		Pair< Key, Mapped >,
		details::ValueCompare< Pair< Key, Mapped >, Compare > >
	{
	public:
		using base = details::MapBase< Key,
				Mapped,
				Compare,
				Pair< Key, Mapped >,
				details::ValueCompare< Pair< Key, Mapped >, Compare > >;
		using key_type = base::key_type;
		using mapped_type = base::mapped_type;
		using value_type = base::value_type;
		using size_type = base::size_type;
		using key_compare = base::key_compare;
		using value_compare = base::value_compare;

		using iterator = base::iterator;
		using const_iterator = base::const_iterator;
		using reverse_iterator = base::reverse_iterator;
		using const_reverse_iterator = base::const_reverse_iterator;

		mapped_type& at(const key_type& key);
		const mapped_type& at(const key_type& key) const;
		mapped_type& operator[](const key_type& key);
		mapped_type& operator[](key_type&& key);
	};
}

#endif
