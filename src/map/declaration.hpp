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
		using key_compare = Compare;

		RBTree() noexcept;
		RBTree(const RBTree&) = delete;
		~RBTree();

		void clear();
		bool insert(const key_type& key, const mapped_type& meaning);
		std::pair< bool, const mapped_type* > search(const key_type& key);
		bool remove(const key_type& key);
	private:
		enum Color{BLACK, RED};
		struct Node
		{
			value_type& value_;
			Color color_;
			Node* parent_ = nullptr;
			Node* left_ = nullptr;
			Node* right_ = nullptr;
		};
		using node_type = Node;
		node_type* root_;
		key_compare compare_;

		void insert_fix(node_type* node);
		void remove_fix(node_type* node, node_type* parent);
		void destroy(node_type* node);
		node_type* find(const key_type& key) const;
	};
}

#endif
