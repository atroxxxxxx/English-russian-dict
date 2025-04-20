#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include <iterator>

namespace src
{
	namespace details
	{
		template< class T, bool isConst, bool isReversed >
		class VectorIterator
		{
		public:
			using value_type = T;
			using difference_type = std::ptrdiff_t;
			using reference = value_type&;
			using const_reference = const value_type&;

			VectorIterator() noexcept;
			VectorIterator(value_type* pointer) noexcept;
			template< bool isConst1 = isConst >
			VectorIterator(std::enable_if_t< isConst && isConst1, VectorIterator< T, false, isReversed > > rhs) noexcept;

			VectorIterator& operator+(difference_type shift) noexcept;
			VectorIterator& operator-(difference_type shift) noexcept;
			VectorIterator& operator+=(difference_type shift) noexcept;
			VectorIterator& operator-=(difference_type shift) noexcept;
			VectorIterator& operator++() noexcept;
			VectorIterator& operator--() noexcept;
			VectorIterator operator++(int) noexcept;
			VectorIterator operator--(int) noexcept;

			bool operator==(const VectorIterator& rhs) noexcept;
			bool operator!=(const VectorIterator& rhs) noexcept;

			template< bool isConst1 = isConst >
			std::enable_if_t< !isConst && !isConst1, reference > operator*() noexcept;
			const_reference operator*() const noexcept;
			template< bool isConst1 = isConst >
			std::enable_if_t< !isConst && !isConst1, value_type* > operator->() noexcept;
			value_type* operator->() const noexcept;
		private:
			value_type* data_;
		};
	}
}

#endif
