//
// ip/address_v6_range.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//                         Oliver Kowalke (oliver dot kowalke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_ADDRESS_V6_RANGE_HPP
#define BOOST_ASIO_IP_ADDRESS_V6_RANGE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/ip/address_v6_iterator.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

template <typename> class basic_address_range;

/// Represents a range of IPv6 addresses.
/**
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 */
template <> class basic_address_range<address_v6>
{
public:
  /// The type of an iterator that points into the range.
  typedef basic_address_iterator<address_v6> iterator;

  /// Construct an empty range.
  basic_address_range() BOOST_ASIO_NOEXCEPT
    : begin_(address_v6()),
      end_(address_v6())
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
    return begin_ == end_;
  }

  /// Find an address in the range.
  iterator find(const address_v6& addr) const BOOST_ASIO_NOEXCEPT
  {
    return addr >= *begin_ && addr < *end_ ? iterator(addr) : end_;
  }

private:
  iterator begin_;
  iterator end_;
};

/// Represents a range of IPv6 addresses.
typedef basic_address_range<address_v6> address_v6_range;

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IP_ADDRESS_V6_RANGE_HPP

/* address_v6_range.hpp
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
*/