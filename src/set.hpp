#ifndef SET_HPP
#define SET_HPP

#include "map_base/declaration.hpp"

namespace src
{
	template< class Key, class Compare >
	class Set: public details::MapBase< Key, void, Compare, Key, Compare >
	{
	public:
		using base = details::MapBase< Key, void, Compare, Key, Compare >;
		using key_type = base::key_type;
		using value_type = base::value_type;
		using size_type = base::size_type;
		using key_compare = base::key_compare;
		using value_compare = base::value_compare;

		using iterator = base::iterator;
		using const_iterator = base::const_iterator;
		using reverse_iterator = base::reverse_iterator;
		using const_reverse_iterator = base::const_reverse_iterator;
	};
}

#endif
