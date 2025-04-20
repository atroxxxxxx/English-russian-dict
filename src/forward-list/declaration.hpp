#ifndef FORWARD_LIST_DECL_HPP
#define FORWARD_LIST_DECL_HPP

#include <cstddef>
#include "node.hpp"

namespace src
{
	namespace forward_list
	{
		template< class T, class Compare >
		class ForwardList
		{
		public:
			using value_type = T;
			using reference = value_type&;
			using const_reference = const value_type&;
			using size_type = size_t;
			using value_compare = Compare;
			using node_type = Node_t< value_type >;

		private:

		};
	}
}

#endif
