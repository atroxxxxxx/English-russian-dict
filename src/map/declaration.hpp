#ifndef MAP_DECLARATION_HPP
#define MAP_DECLARATION_HPP

#include <functional>
#include <cstddef>

namespace src
{
	template< class Key, class T, class Compare = std::less< Key > >
	class RBTree
	{
	public:
		using key_type = Key;
		using mapped_type = T;
		using value_type = std::pair< key_type, mapped_type >;
		using size_type = size_t;

		RBTree() noexcept;
		RBTree(const RBTree&) = delete;
		~RBTree();

		void clear();
		bool insert(const key_type& key, const mapped_type& meaning);
		bool search(const key_type& key);
		bool remove(const key_type& key);
	private:
		struct Node
		{
			value_type& value;
			enum Color{BLACK, RED};
			Node* parent;

		};
	};
}

#endif
