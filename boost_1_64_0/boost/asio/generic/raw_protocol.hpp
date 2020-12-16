//
// generic/raw_protocol.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_GENERIC_RAW_PROTOCOL_HPP
#define BOOST_ASIO_GENERIC_RAW_PROTOCOL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <typeinfo>
#include <boost/asio/basic_raw_socket.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/detail/throw_exception.hpp>
#include <boost/asio/generic/basic_endpoint.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace generic {

/// Encapsulates the flags needed for a generic raw socket.
/**
 * The boost::asio::generic::raw_protocol class contains flags necessary for
 * raw sockets of any address family and protocol.
 *
 * @par Examples
 * Constructing using a native address family and socket protocol:
 * @code raw_protocol p(AF_INET, IPPROTO_ICMP); @endcode
 * Constructing from a specific protocol type:
 * @code raw_protocol p(boost::asio::ip::icmp::v4()); @endcode
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Safe.
 *
 * @par Concepts:
 * Protocol.
 */
class raw_protocol
{
public:
  /// Construct a protocol object for a specific address family and protocol.
  raw_protocol(int address_family, int socket_protocol)
    : family_(address_family),
      protocol_(socket_protocol)
  {
  }

  /// Construct a generic protocol object from a specific protocol.
  /**
   * @throws @c bad_cast Thrown if the source protocol is not raw-oriented.
   */
  template <typename Protocol>
  raw_protocol(const Protocol& source_protocol)
    : family_(source_protocol.family()),
      protocol_(source_protocol.protocol())
  {
    if (source_protocol.type() != type())
    {
      std::bad_cast ex;
      boost::asio::detail::throw_exception(ex);
    }
  }

  /// Obtain an identifier for the type of the protocol.
  int type() const BOOST_ASIO_NOEXCEPT
  {
    return BOOST_ASIO_OS_DEF(SOCK_RAW);
  }

  /// Obtain an identifier for the protocol.
  int protocol() const BOOST_ASIO_NOEXCEPT
  {
    return protocol_;
  }

  /// Obtain an identifier for the protocol family.
  int family() const BOOST_ASIO_NOEXCEPT
  {
    return family_;
  }

  /// Compare two protocols for equality.
  friend bool operator==(const raw_protocol& p1, const raw_protocol& p2)
  {
    return p1.family_ == p2.family_ && p1.protocol_ == p2.protocol_;
  }

  /// Compare two protocols for inequality.
  friend bool operator!=(const raw_protocol& p1, const raw_protocol& p2)
  {
    return !(p1 == p2);
  }

  /// The type of an endpoint.
  typedef basic_endpoint<raw_protocol> endpoint;

  /// The generic socket type.
  typedef basic_raw_socket<raw_protocol> socket;

private:
  int family_;
  int protocol_;
};

} // namespace generic
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_GENERIC_RAW_PROTOCOL_HPP

/* raw_protocol.hpp
C7/1bAuZ29SHIYy/p/Nv+KWTZ3MUcIELaaq/ZQ9K/f2Y+lvmLyJ7Bf5+iH8PpN/wImXPKra+EtcLmK/57ULHHwqMAWYBPcDL6Fd3Bf3srgZ6gX76AbwOGAf8ODCe/p22afaQwId5Hw+wgvdJAt9Y+uubRv99C+j/twCYDqykP8JrgRnAHcCRwBvpv3c3MBO4h/57Pw+8RPmDo+0d7RTrTf7g/sDh7088U/gccCbwz8Bi+sGspl/MrcC/ARvoV+tL9KP1lQAAeXYFbdFQVryfOruCfgUB4mcwAlgI7AksBkYBi4AehrX0cpiexya9VUxvNdMrYHpXMr01wBiGlf9uphcOqjf54S5heqVAN3AD5faCiijXKnLGs1Zm0A/3TODlwNmsxznAauAVwK3A+cAv0D/i3fSXeC8wF/gQ/REfov/hZ+kf8QVgHvAHDL8OnAV8A7hC+ZenjQ5wm833jePAlwQcz3Y9iX64s4EzgJOBOfRbvAh4KfBqhqW/KHsSsbuR9Ee2+WuU32M8w+VJ+sV+in7MjwBn0M/oPPoVXUg/o0uAR4Er6A/sSuCzwELg94Drgc/xDJjjwKuAzwMrgC+wPb4IrAO+DPw4/cXtBDYDd9Ff3J3AE8B99Bf7FfqHvY/+Yh/mWSnPAFuAx4A/BT7H8Gv09/Y+/eWep39cN/L+W+AA4GngQOAvgcOAbwNHMDyS4UuBvwJOZXg6w3OA7wBZj3xHL+/mLPWIvi1nhn8RmAG8k2eEfxWYDdxHf/VfBq4GfgW4hvFMn+9X8Vy0SX8X6+8z7P+38IzwW4H1wAbgTsbvBn4WeAvwNv13vInO+u+n/geo/0Hq/wD1v5f630f976f+mj9OtH2+v0GdMf1E4EtMvxCXZD3IdlcGnAvcCJzP8EpgObCA4Y8wXAS8CgheCYNcV/Ps9ErgNUA/8AZgFc8iqgbeBrwe+EVgPf5vBN4AvJfh+xk+DMSYLf36E8Bm4AbgqxLWzijiewTuydSbzijKctFfLDCOZ7Yn8CymJOClwBSG0xhmuty7x9hik+4qllsB6+MjPHN+LXAawzOBa4CzeV19V810F9vU9yTqNYX6TAUOAyJNdebTZcDprC8Q6glhpl8Pamb6dzH93kBZMPHMp2SeETUIOB84BLiC7WkRx6FcYD5wMet5CceTpcDtvH49cDnwNsp/GZin8sl9PmCRTT5RB3KmU3+260SWYxIwCzgAmMMzo3IZ/gjDfE5zf0r24SzP6UH0OziUZ/gPA1bxTK5bgenAzwGHAx8BjgB+G5jB8WwUx7FMoHquDrw4Z0y9B0wD+ZmeD4Q5mPydwPQW6PgaQuRrCpGvuQO+Uxfz+/zub/O7v83/P/s2/0K/y0846HblgCpAe0FHQWdB3nvcrmxQCWgX6BCoBeS5Fz7zQAWgOtBB0EnQeVD6fTh7C1QC2g06dF/3t/7dv+5f96/795/w+1d9/7/+Ip7/9zXd+f+53M+I0OXnpxNd2JRqfyc+e3lu4JV4ViFeiUNvHOhWLXv9jWJjtb6qQr0L0OQiQv7OsFFsmyQNg63aaRu93oJeDXZ6BV7BrvTj5XSpo14NF0mvuh72ejXa6bUZBdaBXo0XSy8391cplAh6A3o12elVXb5xc3FNbVWpy1EvyCk7rD7J8g4OUnwHZ4ofnCTxxRWMz2uP71K+Ate8QNwX1+S+ci2QJ9wL1+ReBjtBb7i1XlqQ/2Zr/nFe4qqli+bOaXv/aJP35k7WSYTS3ajTfhud3oROLTY6lVdX16J7OtZHSyd1cmon0yKsOr2XjT1eq076buVYVq2d1CvCQa+TDnq5elv1QrfqUC9X7wvTa5bWr3i2fzL392NBCyahvdk=
*/