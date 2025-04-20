#ifndef VECTOR_DECLARATION_HPP
#define VECTOR_DECLARATION_HPP

#include <cstddef>
#include <memory>
#include <utility>

#include <iterator>

namespace src
{
	template< class T, class Allocator = std::allocator< T > >
	class Vector
	{
	public:
		using value_type = T;
		using reference = value_type&;
		using const_reference = const value_type&;
		using size_type = size_t;
		using allocator = Allocator;
		using pointer = typename std::allocator_traits< allocator >::pointer;
		using const_pointer = typename std::allocator_traits< allocator >::const_pointer;

		using iterator = std::random_access_iterator_tag;
		using const_iterator = std::random_access_iterator_tag;
		using reverse_iterator = std::random_access_iterator_tag;
		using const_reverse_iterator = std::random_access_iterator_tag;

		Vector() noexcept;
		Vector(const Vector& rhs);
		Vector(Vector&& rhs) noexcept;
		Vector(std::initializer_list< value_type > data);
		Vector(size_type size, const value_type& value);
		template< class It >
		Vector(It beginIter, It endIter);
		~Vector();

		Vector& operator=(const Vector& rhs);
		Vector& operator=(Vector&& rhs) noexcept;
		Vector& operator=(std::initializer_list< value_type > data);

		reference operator[](size_type index);
		const_reference operator[](size_type index) const;
		reference at(size_type index);
		const_reference at(size_type index) const;

		bool empty() const noexcept;
		size_type size() const noexcept;
		size_type capacity() const noexcept;

		iterator begin() noexcept;
		const_iterator begin() const noexcept;
		const_iterator cbegin() const noexcept;
		reverse_iterator rbegin() noexcept;
		const_reverse_iterator rbegin() const noexcept;
		const_reverse_iterator crbegin() const noexcept;

		iterator end() noexcept;
		const_iterator end() const noexcept;
		const_iterator cend() const noexcept;
		reverse_iterator rend() noexcept;
		const_reverse_iterator rend() const noexcept;
		const_reverse_iterator crend() const noexcept;

		void clear();
		void reserve(size_type size);
		void resize(size_type size);
		void resize(size_type size, const value_type& value);
		void shrink_to_fit();
		void swap(Vector& rhs) noexcept;

		template< class... Args >
		void emplace(const_iterator it, Args&&... args);
		template< class... Args >
		void emplace_back(Args&&... args);
		void insert(const value_type& value);
		void push_back(const value_type& value);

		void errase(const_iterator beginIter, const_iterator endIter);
		void errase(const_iterator it);
		void pop_back();
	private:
		pointer data_;
		size_type capacity_;
		size_type size_;
	};
}

#endif
