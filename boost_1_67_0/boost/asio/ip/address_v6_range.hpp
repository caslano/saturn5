//
// ip/address_v6_range.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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