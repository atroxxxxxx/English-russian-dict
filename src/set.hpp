#ifndef SET_HPP
#define SET_HPP

#include "map_base.hpp"
#include <functional>

namespace src
{
	template< class Key, class Compare = std::less<> >
	class Set: public details::MapBase< const Key, void, Compare, const Key, Compare >
	{
	public:
		using base = details::MapBase< const Key, void, Compare, const Key, Compare >;
		using key_type = typename base::key_type;
		using value_type = typename base::value_type;
		using size_type = typename base::size_type;
		using key_compare = typename base::key_compare;
		using value_compare = typename base::value_compare;

		using iterator = typename base::iterator;
		using const_iterator = typename base::const_iterator;
		using reverse_iterator = typename base::reverse_iterator;
		using const_reverse_iterator = typename base::const_reverse_iterator;

		Set() noexcept(std::is_nothrow_default_constructible< value_compare >::value): base()
		{}
		Set(const key_compare& compare): base(compare)
		{}
		Set(const Set& rhs): base(rhs)
		{}
		Set(Set&& rhs) noexcept(std::is_nothrow_default_constructible< value_compare >::value): base(std::move(rhs))
		{}
		template< class InIter >
		Set(InIter from, InIter to, const key_compare& compare = key_compare()): base(from, to, compare)
		{}
		Set(std::initializer_list< value_type > list, const key_compare& compare = key_compare()): base(list, compare)
		{}

		Set& operator=(const Set& rhs)
		{
			base::operator=(rhs);
			return *this;
		}
		Set& operator=(Set&& rhs) noexcept(std::is_nothrow_default_constructible< value_compare >::value)
		{
			base::operator=(std::move(rhs));
			return *this;
		}
		Set& operator=(std::initializer_list< value_type > list)
		{
			base::operator=(list);
			return *this;
		}
	};
}

#endif
