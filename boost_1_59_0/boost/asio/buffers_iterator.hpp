//
// buffers_iterator.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_BUFFERS_ITERATOR_HPP
#define BOOST_ASIO_BUFFERS_ITERATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <cstddef>
#include <iterator>
#include <boost/asio/buffer.hpp>
#include <boost/asio/detail/assert.hpp>
#include <boost/asio/detail/type_traits.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

namespace detail
{
  template <bool IsMutable>
  struct buffers_iterator_types_helper;

  template <>
  struct buffers_iterator_types_helper<false>
  {
    typedef const_buffer buffer_type;
    template <typename ByteType>
    struct byte_type
    {
      typedef typename add_const<ByteType>::type type;
    };
  };

  template <>
  struct buffers_iterator_types_helper<true>
  {
    typedef mutable_buffer buffer_type;
    template <typename ByteType>
    struct byte_type
    {
      typedef ByteType type;
    };
  };

  template <typename BufferSequence, typename ByteType>
  struct buffers_iterator_types
  {
    enum
    {
      is_mutable = is_convertible<
          typename BufferSequence::value_type,
          mutable_buffer>::value
    };
    typedef buffers_iterator_types_helper<is_mutable> helper;
    typedef typename helper::buffer_type buffer_type;
    typedef typename helper::template byte_type<ByteType>::type byte_type;
    typedef typename BufferSequence::const_iterator const_iterator;
  };

  template <typename ByteType>
  struct buffers_iterator_types<mutable_buffer, ByteType>
  {
    typedef mutable_buffer buffer_type;
    typedef ByteType byte_type;
    typedef const mutable_buffer* const_iterator;
  };

  template <typename ByteType>
  struct buffers_iterator_types<const_buffer, ByteType>
  {
    typedef const_buffer buffer_type;
    typedef typename add_const<ByteType>::type byte_type;
    typedef const const_buffer* const_iterator;
  };

#if !defined(BOOST_ASIO_NO_DEPRECATED)

  template <typename ByteType>
  struct buffers_iterator_types<mutable_buffers_1, ByteType>
  {
    typedef mutable_buffer buffer_type;
    typedef ByteType byte_type;
    typedef const mutable_buffer* const_iterator;
  };

  template <typename ByteType>
  struct buffers_iterator_types<const_buffers_1, ByteType>
  {
    typedef const_buffer buffer_type;
    typedef typename add_const<ByteType>::type byte_type;
    typedef const const_buffer* const_iterator;
  };

#endif // !defined(BOOST_ASIO_NO_DEPRECATED)
}

/// A random access iterator over the bytes in a buffer sequence.
template <typename BufferSequence, typename ByteType = char>
class buffers_iterator
{
private:
  typedef typename detail::buffers_iterator_types<
      BufferSequence, ByteType>::buffer_type buffer_type;

  typedef typename detail::buffers_iterator_types<BufferSequence,
          ByteType>::const_iterator buffer_sequence_iterator_type;

public:
  /// The type used for the distance between two iterators.
  typedef std::ptrdiff_t difference_type;

  /// The type of the value pointed to by the iterator.
  typedef ByteType value_type;

#if defined(GENERATING_DOCUMENTATION)
  /// The type of the result of applying operator->() to the iterator.
  /**
   * If the buffer sequence stores buffer objects that are convertible to
   * mutable_buffer, this is a pointer to a non-const ByteType. Otherwise, a
   * pointer to a const ByteType.
   */
  typedef const_or_non_const_ByteType* pointer;
#else // defined(GENERATING_DOCUMENTATION)
  typedef typename detail::buffers_iterator_types<
      BufferSequence, ByteType>::byte_type* pointer;
#endif // defined(GENERATING_DOCUMENTATION)

#if defined(GENERATING_DOCUMENTATION)
  /// The type of the result of applying operator*() to the iterator.
  /**
   * If the buffer sequence stores buffer objects that are convertible to
   * mutable_buffer, this is a reference to a non-const ByteType. Otherwise, a
   * reference to a const ByteType.
   */
  typedef const_or_non_const_ByteType& reference;
#else // defined(GENERATING_DOCUMENTATION)
  typedef typename detail::buffers_iterator_types<
      BufferSequence, ByteType>::byte_type& reference;
#endif // defined(GENERATING_DOCUMENTATION)

  /// The iterator category.
  typedef std::random_access_iterator_tag iterator_category;

  /// Default constructor. Creates an iterator in an undefined state.
  buffers_iterator()
    : current_buffer_(),
      current_buffer_position_(0),
      begin_(),
      current_(),
      end_(),
      position_(0)
  {
  }

  /// Construct an iterator representing the beginning of the buffers' data.
  static buffers_iterator begin(const BufferSequence& buffers)
#if defined(__GNUC__) && (__GNUC__ == 4) && (__GNUC_MINOR__ == 3)
    __attribute__ ((__noinline__))
#endif // defined(__GNUC__) && (__GNUC__ == 4) && (__GNUC_MINOR__ == 3)
  {
    buffers_iterator new_iter;
    new_iter.begin_ = boost::asio::buffer_sequence_begin(buffers);
    new_iter.current_ = boost::asio::buffer_sequence_begin(buffers);
    new_iter.end_ = boost::asio::buffer_sequence_end(buffers);
    while (new_iter.current_ != new_iter.end_)
    {
      new_iter.current_buffer_ = *new_iter.current_;
      if (new_iter.current_buffer_.size() > 0)
        break;
      ++new_iter.current_;
    }
    return new_iter;
  }

  /// Construct an iterator representing the end of the buffers' data.
  static buffers_iterator end(const BufferSequence& buffers)
#if defined(__GNUC__) && (__GNUC__ == 4) && (__GNUC_MINOR__ == 3)
    __attribute__ ((__noinline__))
#endif // defined(__GNUC__) && (__GNUC__ == 4) && (__GNUC_MINOR__ == 3)
  {
    buffers_iterator new_iter;
    new_iter.begin_ = boost::asio::buffer_sequence_begin(buffers);
    new_iter.current_ = boost::asio::buffer_sequence_begin(buffers);
    new_iter.end_ = boost::asio::buffer_sequence_end(buffers);
    while (new_iter.current_ != new_iter.end_)
    {
      buffer_type buffer = *new_iter.current_;
      new_iter.position_ += buffer.size();
      ++new_iter.current_;
    }
    return new_iter;
  }

  /// Dereference an iterator.
  reference operator*() const
  {
    return dereference();
  }

  /// Dereference an iterator.
  pointer operator->() const
  {
    return &dereference();
  }

  /// Access an individual element.
  reference operator[](std::ptrdiff_t difference) const
  {
    buffers_iterator tmp(*this);
    tmp.advance(difference);
    return *tmp;
  }

  /// Increment operator (prefix).
  buffers_iterator& operator++()
  {
    increment();
    return *this;
  }

  /// Increment operator (postfix).
  buffers_iterator operator++(int)
  {
    buffers_iterator tmp(*this);
    ++*this;
    return tmp;
  }

  /// Decrement operator (prefix).
  buffers_iterator& operator--()
  {
    decrement();
    return *this;
  }

  /// Decrement operator (postfix).
  buffers_iterator operator--(int)
  {
    buffers_iterator tmp(*this);
    --*this;
    return tmp;
  }

  /// Addition operator.
  buffers_iterator& operator+=(std::ptrdiff_t difference)
  {
    advance(difference);
    return *this;
  }

  /// Subtraction operator.
  buffers_iterator& operator-=(std::ptrdiff_t difference)
  {
    advance(-difference);
    return *this;
  }

  /// Addition operator.
  friend buffers_iterator operator+(const buffers_iterator& iter,
      std::ptrdiff_t difference)
  {
    buffers_iterator tmp(iter);
    tmp.advance(difference);
    return tmp;
  }

  /// Addition operator.
  friend buffers_iterator operator+(std::ptrdiff_t difference,
      const buffers_iterator& iter)
  {
    buffers_iterator tmp(iter);
    tmp.advance(difference);
    return tmp;
  }

  /// Subtraction operator.
  friend buffers_iterator operator-(const buffers_iterator& iter,
      std::ptrdiff_t difference)
  {
    buffers_iterator tmp(iter);
    tmp.advance(-difference);
    return tmp;
  }

  /// Subtraction operator.
  friend std::ptrdiff_t operator-(const buffers_iterator& a,
      const buffers_iterator& b)
  {
    return b.distance_to(a);
  }

  /// Test two iterators for equality.
  friend bool operator==(const buffers_iterator& a, const buffers_iterator& b)
  {
    return a.equal(b);
  }

  /// Test two iterators for inequality.
  friend bool operator!=(const buffers_iterator& a, const buffers_iterator& b)
  {
    return !a.equal(b);
  }

  /// Compare two iterators.
  friend bool operator<(const buffers_iterator& a, const buffers_iterator& b)
  {
    return a.distance_to(b) > 0;
  }

  /// Compare two iterators.
  friend bool operator<=(const buffers_iterator& a, const buffers_iterator& b)
  {
    return !(b < a);
  }

  /// Compare two iterators.
  friend bool operator>(const buffers_iterator& a, const buffers_iterator& b)
  {
    return b < a;
  }

  /// Compare two iterators.
  friend bool operator>=(const buffers_iterator& a, const buffers_iterator& b)
  {
    return !(a < b);
  }

private:
  // Dereference the iterator.
  reference dereference() const
  {
    return static_cast<pointer>(
        current_buffer_.data())[current_buffer_position_];
  }

  // Compare two iterators for equality.
  bool equal(const buffers_iterator& other) const
  {
    return position_ == other.position_;
  }

  // Increment the iterator.
  void increment()
  {
    BOOST_ASIO_ASSERT(current_ != end_ && "iterator out of bounds");
    ++position_;

    // Check if the increment can be satisfied by the current buffer.
    ++current_buffer_position_;
    if (current_buffer_position_ != current_buffer_.size())
      return;

    // Find the next non-empty buffer.
    ++current_;
    current_buffer_position_ = 0;
    while (current_ != end_)
    {
      current_buffer_ = *current_;
      if (current_buffer_.size() > 0)
        return;
      ++current_;
    }
  }

  // Decrement the iterator.
  void decrement()
  {
    BOOST_ASIO_ASSERT(position_ > 0 && "iterator out of bounds");
    --position_;

    // Check if the decrement can be satisfied by the current buffer.
    if (current_buffer_position_ != 0)
    {
      --current_buffer_position_;
      return;
    }

    // Find the previous non-empty buffer.
    buffer_sequence_iterator_type iter = current_;
    while (iter != begin_)
    {
      --iter;
      buffer_type buffer = *iter;
      std::size_t buffer_size = buffer.size();
      if (buffer_size > 0)
      {
        current_ = iter;
        current_buffer_ = buffer;
        current_buffer_position_ = buffer_size - 1;
        return;
      }
    }
  }

  // Advance the iterator by the specified distance.
  void advance(std::ptrdiff_t n)
  {
    if (n > 0)
    {
      BOOST_ASIO_ASSERT(current_ != end_ && "iterator out of bounds");
      for (;;)
      {
        std::ptrdiff_t current_buffer_balance
          = current_buffer_.size() - current_buffer_position_;

        // Check if the advance can be satisfied by the current buffer.
        if (current_buffer_balance > n)
        {
          position_ += n;
          current_buffer_position_ += n;
          return;
        }

        // Update position.
        n -= current_buffer_balance;
        position_ += current_buffer_balance;

        // Move to next buffer. If it is empty then it will be skipped on the
        // next iteration of this loop.
        if (++current_ == end_)
        {
          BOOST_ASIO_ASSERT(n == 0 && "iterator out of bounds");
          current_buffer_ = buffer_type();
          current_buffer_position_ = 0;
          return;
        }
        current_buffer_ = *current_;
        current_buffer_position_ = 0;
      }
    }
    else if (n < 0)
    {
      std::size_t abs_n = -n;
      BOOST_ASIO_ASSERT(position_ >= abs_n && "iterator out of bounds");
      for (;;)
      {
        // Check if the advance can be satisfied by the current buffer.
        if (current_buffer_position_ >= abs_n)
        {
          position_ -= abs_n;
          current_buffer_position_ -= abs_n;
          return;
        }

        // Update position.
        abs_n -= current_buffer_position_;
        position_ -= current_buffer_position_;

        // Check if we've reached the beginning of the buffers.
        if (current_ == begin_)
        {
          BOOST_ASIO_ASSERT(abs_n == 0 && "iterator out of bounds");
          current_buffer_position_ = 0;
          return;
        }

        // Find the previous non-empty buffer.
        buffer_sequence_iterator_type iter = current_;
        while (iter != begin_)
        {
          --iter;
          buffer_type buffer = *iter;
          std::size_t buffer_size = buffer.size();
          if (buffer_size > 0)
          {
            current_ = iter;
            current_buffer_ = buffer;
            current_buffer_position_ = buffer_size;
            break;
          }
        }
      }
    }
  }

  // Determine the distance between two iterators.
  std::ptrdiff_t distance_to(const buffers_iterator& other) const
  {
    return other.position_ - position_;
  }

  buffer_type current_buffer_;
  std::size_t current_buffer_position_;
  buffer_sequence_iterator_type begin_;
  buffer_sequence_iterator_type current_;
  buffer_sequence_iterator_type end_;
  std::size_t position_;
};

/// Construct an iterator representing the beginning of the buffers' data.
template <typename BufferSequence>
inline buffers_iterator<BufferSequence> buffers_begin(
    const BufferSequence& buffers)
{
  return buffers_iterator<BufferSequence>::begin(buffers);
}

/// Construct an iterator representing the end of the buffers' data.
template <typename BufferSequence>
inline buffers_iterator<BufferSequence> buffers_end(
    const BufferSequence& buffers)
{
  return buffers_iterator<BufferSequence>::end(buffers);
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_BUFFERS_ITERATOR_HPP

/* buffers_iterator.hpp
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
*/