//
// ip/address_v4_range.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_ADDRESS_V4_RANGE_HPP
#define BOOST_ASIO_IP_ADDRESS_V4_RANGE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/ip/address_v4_iterator.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

template <typename> class basic_address_range;

/// Represents a range of IPv4 addresses.
/**
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 */
template <> class basic_address_range<address_v4>
{
public:
  /// The type of an iterator that points into the range.
  typedef basic_address_iterator<address_v4> iterator;

  /// Construct an empty range.
  basic_address_range() BOOST_ASIO_NOEXCEPT
    : begin_(address_v4()),
      end_(address_v4())
  {
  }

  /// Construct an range that represents the given range of addresses.
  explicit basic_address_range(const iterator& first,
      const iterator& last) BOOST_ASIO_NOEXCEPT
    : begin_(first),
      end_(last)
  {
  }

  /// Copy constructor.
  basic_address_range(const basic_address_range& other) BOOST_ASIO_NOEXCEPT
    : begin_(other.begin_),
      end_(other.end_)
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  /// Move constructor.
  basic_address_range(basic_address_range&& other) BOOST_ASIO_NOEXCEPT
    : begin_(BOOST_ASIO_MOVE_CAST(iterator)(other.begin_)),
      end_(BOOST_ASIO_MOVE_CAST(iterator)(other.end_))
  {
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  /// Assignment operator.
  basic_address_range& operator=(
      const basic_address_range& other) BOOST_ASIO_NOEXCEPT
  {
    begin_ = other.begin_;
    end_ = other.end_;
    return *this;
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  /// Move assignment operator.
  basic_address_range& operator=(
      basic_address_range&& other) BOOST_ASIO_NOEXCEPT
  {
    begin_ = BOOST_ASIO_MOVE_CAST(iterator)(other.begin_);
    end_ = BOOST_ASIO_MOVE_CAST(iterator)(other.end_);
    return *this;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  /// Obtain an iterator that points to the start of the range.
  iterator begin() const BOOST_ASIO_NOEXCEPT
  {
    return begin_;
  }

  /// Obtain an iterator that points to the end of the range.
  iterator end() const BOOST_ASIO_NOEXCEPT
  {
    return end_;
  }

  /// Determine whether the range is empty.
  bool empty() const BOOST_ASIO_NOEXCEPT
  {
    return size() == 0;
  }

  /// Return the size of the range.
  std::size_t size() const BOOST_ASIO_NOEXCEPT
  {
    return end_->to_uint() - begin_->to_uint();
  }

  /// Find an address in the range.
  iterator find(const address_v4& addr) const BOOST_ASIO_NOEXCEPT
  {
    return addr >= *begin_ && addr < *end_ ? iterator(addr) : end_;
  }

private:
  iterator begin_;
  iterator end_;
};

/// Represents a range of IPv4 addresses.
typedef basic_address_range<address_v4> address_v4_range;

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IP_ADDRESS_V4_RANGE_HPP

/* address_v4_range.hpp
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
*/