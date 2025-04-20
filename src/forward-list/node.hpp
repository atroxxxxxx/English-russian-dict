#ifndef FORWARD_LIST_NODE_HPP
#define FORWARD_LIST_NODE_HPP

namespace src
{
	namespace forward_list
	{
		template< class T >
		struct Node_t
		{
			using value_type = T;
			value_type& key;
			Node_t* next = nullptr;
		};
	}
}

#endif
