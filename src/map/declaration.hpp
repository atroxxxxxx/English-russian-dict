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

		RBTree() noexcept:
			root_(nullptr),
			size_(0)
		{}
		RBTree(const RBTree&) = delete;
		~RBTree()
		{
			clear();
		}

		void clear()
		{
			destroy(root_);
			root_ = nullptr;
		}
		size_type size() const noexcept {return size_;}
		bool empty() const noexcept {return size_ == 0;}
		bool insert(key_type key, mapped_type meaning);
		std::pair< bool, mapped_type* > search(const key_type& key) const;
		bool remove(const key_type& key);
	private:
		enum Color{BLACK, RED};
		struct Node
		{
			value_type value_;
			Color color_;
			Node* parent_ = nullptr;
			Node* left_ = nullptr;
			Node* right_ = nullptr;
		};
		using node_type = Node;
		node_type* root_;
		key_compare compare_;
		size_type size_;

		void rotate_left(node_type* node);
		void rotate_right(node_type* node);
		void insert_fix(node_type* node);
		void remove_fix(node_type* node);
		void destroy(node_type* node)
		{
			if (!node) {
				return;
			}
			destroy(node->right_);
			destroy(node->left_);
			delete node;
		}
		node_type* find(const key_type& key) const;
	};
}

#endif
