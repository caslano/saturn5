//
// recycling_allocator.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_RECYCLING_ALLOCATOR_HPP
#define BOOST_ASIO_RECYCLING_ALLOCATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/recycling_allocator.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// An allocator that caches memory blocks in thread-local storage for reuse.
/**
 * The @recycling_allocator uses a simple strategy where a limited number of
 * small memory blocks are cached in thread-local storage, if the current
 * thread is running an @c io_context or is part of a @c thread_pool.
 */
template <typename T>
class recycling_allocator
{
public:
  /// The type of object allocated by the recycling allocator.
  typedef T value_type;

  /// Rebind the allocator to another value_type.
  template <typename U>
  struct rebind
  {
    /// The rebound @c allocator type.
    typedef recycling_allocator<U> other;
  };

  /// Default constructor.
  BOOST_ASIO_CONSTEXPR recycling_allocator() BOOST_ASIO_NOEXCEPT
  {
  }

  /// Converting constructor.
  template <typename U>
  BOOST_ASIO_CONSTEXPR recycling_allocator(
      const recycling_allocator<U>&) BOOST_ASIO_NOEXCEPT
  {
  }

  /// Equality operator. Always returns true.
  BOOST_ASIO_CONSTEXPR bool operator==(
      const recycling_allocator&) const BOOST_ASIO_NOEXCEPT
  {
    return true;
  }

  /// Inequality operator. Always returns false.
  BOOST_ASIO_CONSTEXPR bool operator!=(
      const recycling_allocator&) const BOOST_ASIO_NOEXCEPT
  {
    return false;
  }

  /// Allocate memory for the specified number of values.
  T* allocate(std::size_t n)
  {
    return detail::recycling_allocator<T>().allocate(n);
  }

  /// Deallocate memory for the specified number of values.
  void deallocate(T* p, std::size_t n)
  {
    detail::recycling_allocator<T>().deallocate(p, n);
  }
};

/// A proto-allocator that caches memory blocks in thread-local storage for
/// reuse.
/**
 * The @recycling_allocator uses a simple strategy where a limited number of
 * small memory blocks are cached in thread-local storage, if the current
 * thread is running an @c io_context or is part of a @c thread_pool.
 */
template <>
class recycling_allocator<void>
{
public:
  /// No values are allocated by a proto-allocator.
  typedef void value_type;

  /// Rebind the allocator to another value_type.
  template <typename U>
  struct rebind
  {
    /// The rebound @c allocator type.
    typedef recycling_allocator<U> other;
  };

  /// Default constructor.
  BOOST_ASIO_CONSTEXPR recycling_allocator() BOOST_ASIO_NOEXCEPT
  {
  }

  /// Converting constructor.
  template <typename U>
  BOOST_ASIO_CONSTEXPR recycling_allocator(
      const recycling_allocator<U>&) BOOST_ASIO_NOEXCEPT
  {
  }

  /// Equality operator. Always returns true.
  BOOST_ASIO_CONSTEXPR bool operator==(
      const recycling_allocator&) const BOOST_ASIO_NOEXCEPT
  {
    return true;
  }

  /// Inequality operator. Always returns false.
  BOOST_ASIO_CONSTEXPR bool operator!=(
      const recycling_allocator&) const BOOST_ASIO_NOEXCEPT
  {
    return false;
  }
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_RECYCLING_ALLOCATOR_HPP

/* recycling_allocator.hpp
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
*/