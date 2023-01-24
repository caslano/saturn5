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
dtfzfDXfL0t/66fu7D4++HJXIG10xotoKHYZDZaqascFmwMD5iFkZwqBPvEednM54MVol8LvQ73jC+x0oI26sHrxfFNan56brXg1Jp+krVCtz4oyHjBrPxXbc/E+spZX/zcv1wvEzuudkllskRkmjbSwRuRR8jsg8+XNBRTcPLBR9tt2BOnnwQWdSN9G+YdSVTLA0/R8xJtXb6uL/9UV8g3FEzvgTkDrgZ6uxNvfkQ7kfNSnK2v+doQcaAt2BLJ9L9X963sr+giZqK5/U113PLpGGJt7pXsvNT9p3FJTrhZxviO3KbwAipb9o/MX8Bw+Vfmn/9EIZeb7mKjI+dW6+fh08oyNWO51d9+by0zjVx+b0CCitmnJZ2Vml1FK82uPWkHho3TLK+RV9vdk5NUyBfAlZvQHtZvpl6Pxp2Uo+wYoQz7wDFLf20v8TgdiEimMD9yuVZ7dxyPPNByjqOLZe4lqOvgErDB2fwcSvpndOxB0lkZU1sg4lL9n4mq0t9VtoALOiMUbNgYvIMMX76ir3gWKoRXol6ZkGacuHQ2iImd/uIrGjqCWZBXTaURplP7NwDiyKvWmHxtL9tXvBH0Vtw+lj+GvAT6/YLUy++XAPcrrUGOyg6G1c7qJnEqqGwbVt30OB/8fMVUPgvG2b3vdcYE2B9m7GhtHgOVUW+eVP10N1CPAOgQVQrznKeyTJYD5Ce+uXFbfRcXbVib4
*/