#ifndef SET_HPP
#define SET_HPP

#include "map_base/declaration.hpp"
#include <functional>

namespace src
{
	template< class Key, class Compare = std::less<> >
	class Set: public details::MapBase< Key, void, Compare, Key, Compare >
	{
	public:
		using base = details::MapBase< Key, void, Compare, Key, Compare >;
		using key_type = typename base::key_type;
		using value_type = typename base::value_type;
		using size_type = typename base::size_type;
		using key_compare = typename base::key_compare;
		using value_compare = typename base::value_compare;

		using iterator = typename base::iterator;
		using const_iterator = typename base::const_iterator;
		using reverse_iterator = typename base::reverse_iterator;
		using const_reverse_iterator = typename base::const_reverse_iterator;
	};
}

#endif
