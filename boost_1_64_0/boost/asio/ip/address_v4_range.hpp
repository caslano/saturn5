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
TsIbszLCUncsrBLYUUItdNCQE6TyVPjtrVvuHyHpyer/CRCmYllydP4AK7z/6JO4SzpSI7UWtNrz1ns28R8WmHx/xhN5mkV0lYRYwzi/OLrUImr4hgzRSA8bOJM+aCtXCRNCgXLJIiB2Rym/rkj7Ci3tfFKEZxxkGxcp7DeoKI99Jf5qfXa7jEdibMVAA8xlvZUuJlzrcyk+/rUhJfzYpoIyrZkXA5lcDSY9Id6TsW/DAXg4PeG6E/NGf8CRVuTnWP/VeoXXRv3X1OHKx/HGAd9b50sO1cuaP5Z6b4lnXWxVo9VoCdBgrUVy7vRZ8JTqWGm+QcZKTiBwPAGu0b3cWcaszXRMgWqxHxYVRZu/cd94k6kamJKEIB+YR2TWQ8gY0jvziipLW13mLABXRYFTp12UXo71KZr+ReDsBiGwDpXGDAt7k2Wremp1/08j+ZT3lzf6/NNeEh+/YtanHvQFBh153l+cSpI+hv4MMuUejqmExPmDYWkG8K/doszjZhw2vyuesI0AIYzpHmOCFdOG6YwwZf8v1gCS9IW0JxmvhGph/4TkbjwCT3m4Fg==
*/