//
// ip/address_v4_range.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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