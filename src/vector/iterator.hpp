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

			VectorIterator() noexcept:
				data_(nullptr)
			{}
			VectorIterator(value_type* pointer) noexcept:
				data_(pointer)
			{}
			template< bool isConst1 = isConst >
			VectorIterator(std::enable_if_t< isConst && isConst1, VectorIterator< T, false, isReversed > > rhs) noexcept:
				data_(rhs.data_)
			{}

			VectorIterator operator+(difference_type shift) const noexcept
			{
				return VectorIterator(*this) += shift;
			}
			VectorIterator& operator-(difference_type shift) const noexcept
			{
				return operator+(-shift);
			}
			VectorIterator& operator+=(difference_type shift) noexcept
			{
				data_ += (isReversed ? shift : -shift);
				return *this;
			}
			VectorIterator& operator-=(difference_type shift) noexcept
			{
				return operator+=(-shift);
			}
			VectorIterator& operator++() noexcept
			{
				return operator+=(1);
			}
			VectorIterator& operator--() noexcept
			{
				return operator-=(1);
			}
			VectorIterator operator++(int) noexcept
			{
				VectorIterator temp(*this);
				operator++();
				return temp;
			}
			VectorIterator operator--(int) noexcept
			{
				VectorIterator temp(*this);
				operator--();
				return temp;
			}

			bool operator==(const VectorIterator& rhs) noexcept
			{
				return data_ == rhs.data_;
			}
			bool operator!=(const VectorIterator& rhs) noexcept
			{
				return !operator==(rhs);
			}

			template< bool isConst1 = isConst >
			std::enable_if_t< !isConst && !isConst1, reference > operator*() noexcept
			{
				return *data_;
			}
			const_reference operator*() const noexcept
			{
				return *data_;
			}
			template< bool isConst1 = isConst >
			std::enable_if_t< !isConst && !isConst1, value_type* > operator->() noexcept
			{
				return data_;
			}
			value_type* operator->() const noexcept
			{
				return data_;
			}
		private:
			value_type* data_;
		};
	}
}

#endif
