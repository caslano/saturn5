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
TdJsZn3+bfo5rjGWZM2aP+/VOi0/xlCQ94HdJn9yvT7Li8W6nrdOxl7IQ0Hrgcqmd3o9O+te2FrfavVvHMVEx1v5brj5r3PeuPzgxndub9TR7aF1GuKXhIXLa2CyYPkDsfbL1OMDIZ1E/0cqi1Bs7gHkrD2ZJeSs+f+8xahLLotF8/7SvmAlINzSWzEUOesam3uXymJQsj8NaAdAYnzFUH0iybrm4z6w9Q+ES71BVB0l4iYx7/cMXPhLkRXnY8G7HTLhi1z+Nx/E90xCp4HPCFGwpAXil0OiDKOyx2UWZSlTGCGalqzY2ffJMYGMavt89rSFStrQ6Rpj1UP0xW8garV/wRPEXccEKuxTTIXG8mf3KS5BYxdu1Q61F79JMPwbnhLf71xSofn82WClfyMfTNK7LgumVrvDXPw37jEH92EFMJnAS+jFJrtDoAYTzsmEQFJrqGalMf9qat/8M99PqqgXmGhQddU7x4comVKqZXiAqsoNMsg/R1SBY6cy/0/r5UeJZzHeVHXvV4mNaqWmp7Cz0nnuT/ablrdfHEPnGb0Yo+3sFWOjUbZXut1Lf3aLxz34EXNgOtDNHDHUhjt8vqpevFBvmaMwWwwk1kqX6oAmxvKvtNfoGVbyN4y+Mo3ipHOrDuuxeBKylomElwB0S7/21YAE3HXJWllV8yWV8usPvORdaWmV56iDhVnggwBy18Mxpzi1rBUN0ukl
*/