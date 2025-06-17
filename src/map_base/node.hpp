#ifndef MAP_BASE_NODE_HPP
#define MAP_BASE_NODE_HPP

namespace src
{
	namespace details
	{
		template< class Value >
		struct map_node_t
		{
			using value_type = Value;
			value_type value_;
			bool isRed_ = true;
			map_node_t* parent_ = nullptr;
			map_node_t* left_ = nullptr;
			map_node_t* right_ = nullptr;
		};
	}
}

#endif
