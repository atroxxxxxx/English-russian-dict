#ifndef MAP_VALUE_COMPARE_HPP
#define MAP_VALUE_COMPARE_HPP

#include <utility>

namespace src
{
	namespace details
	{
		template< class Value, class Compare >
		struct ValueCompare
		{
			using value_type = Value;
			using key_compare = Compare;
			using key_type = typename value_type::first_type;
			key_compare compare;
			bool operator()(const value_type& lhs, const value_type& rhs) const
			{
				return compare(lhs.first, rhs.first);
			}
			bool operator()(const key_type& lhs, const key_type& rhs) const
			{
				return compare(lhs, rhs);
			}
		};
	}
}

#endif
