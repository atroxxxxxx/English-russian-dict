#ifndef PAIR_HPP
#define PAIR_HPP

namespace src
{
	template< class T, class U >
	struct Pair
	{
		using first_type = T;
		using second_type = U;
		first_type first;
		second_type second;
	};
}

#endif
