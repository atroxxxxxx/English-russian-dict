#ifndef VECTOR_DECLARATION_HPP
#define VECTOR_DECLARATION_HPP

#include <cstddef>
#include <memory>
#include <initializer_list>

#include <vector/iterator.hpp>

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

		using iterator = details::VectorIterator< value_type, false, false >;
		using const_iterator = details::VectorIterator< value_type, true, false >;
		using reverse_iterator = details::VectorIterator< value_type, false, true >;
		using const_reverse_iterator = details::VectorIterator< value_type, true, true >;

		Vector() noexcept;
		Vector(const Vector& rhs);
		Vector(Vector&& rhs) noexcept;
		Vector(std::initializer_list< value_type > data);
		Vector(size_type repetitions, const value_type& value);
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
		reference front() noexcept;
		reference back() noexcept;
		const_reference front() const noexcept;
		const_reference back() const noexcept;
		pointer data() noexcept;
		const_pointer data() const noexcept;

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
		void reserve(size_type newCapacity);
		void resize(size_type newSize);
		void resize(size_type newSize, const value_type& value);
		void shrink_to_fit();
		void swap(Vector& rhs) noexcept;

		template< class... Args >
		reference emplace(const_iterator it, Args&&... args);
		template< class... Args >
		reference emplace_back(Args&&... args);

		iterator insert(const_iterator it, const value_type& value);
		iterator insert(const_iterator it, value_type&& value);
		iterator insert(const_iterator it, size_type count, const value_type& value);
		template< class It >
		iterator insert(const_iterator it, It beginIter, It endIter);
		iterator insert(const_iterator it, std::initializer_list< value_type > data);

		void push_back(const value_type& value);
		void push_back(value_type&& value);
		void assign(size_type count, const value_type& value);
		template< class It >
		void assign(It beginIter, It endIter);
		void assign(std::initializer_list< value_type > data);

		iterator errase(const_iterator beginIter, const_iterator endIter);
		iterator errase(const_iterator it);
		void pop_back();
	private:
		pointer data_;
		size_type capacity_;
		size_type size_;
		allocator allocator_;
	};
}

#endif
