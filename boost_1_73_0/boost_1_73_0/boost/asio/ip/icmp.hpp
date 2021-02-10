//
// ip/icmp.hpp
// ~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_ICMP_HPP
#define BOOST_ASIO_IP_ICMP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/basic_raw_socket.hpp>
#include <boost/asio/ip/basic_endpoint.hpp>
#include <boost/asio/ip/basic_resolver.hpp>
#include <boost/asio/ip/basic_resolver_iterator.hpp>
#include <boost/asio/ip/basic_resolver_query.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

/// Encapsulates the flags needed for ICMP.
/**
 * The boost::asio::ip::icmp class contains flags necessary for ICMP sockets.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Safe.
 *
 * @par Concepts:
 * Protocol, InternetProtocol.
 */
class icmp
{
public:
  /// The type of a ICMP endpoint.
  typedef basic_endpoint<icmp> endpoint;

  /// Construct to represent the IPv4 ICMP protocol.
  static icmp v4() BOOST_ASIO_NOEXCEPT
  {
    return icmp(BOOST_ASIO_OS_DEF(IPPROTO_ICMP),
        BOOST_ASIO_OS_DEF(AF_INET));
  }

  /// Construct to represent the IPv6 ICMP protocol.
  static icmp v6() BOOST_ASIO_NOEXCEPT
  {
    return icmp(BOOST_ASIO_OS_DEF(IPPROTO_ICMPV6),
        BOOST_ASIO_OS_DEF(AF_INET6));
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

  /// The ICMP socket type.
  typedef basic_raw_socket<icmp> socket;

  /// The ICMP resolver type.
  typedef basic_resolver<icmp> resolver;

  /// Compare two protocols for equality.
  friend bool operator==(const icmp& p1, const icmp& p2)
  {
    return p1.protocol_ == p2.protocol_ && p1.family_ == p2.family_;
  }

  /// Compare two protocols for inequality.
  friend bool operator!=(const icmp& p1, const icmp& p2)
  {
    return p1.protocol_ != p2.protocol_ || p1.family_ != p2.family_;
  }

private:
  // Construct with a specific family.
  explicit icmp(int protocol_id, int protocol_family) BOOST_ASIO_NOEXCEPT
    : protocol_(protocol_id),
      family_(protocol_family)
  {
  }

  int protocol_;
  int family_;
};

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IP_ICMP_HPP

/* icmp.hpp
R6oa2lvPD1eVjqutV1WxMxBmjYIWbVNiOZgF47IKhk9VW2amkfFiiG6VaGUx+R+4bKN7pqoSWqnBq4k6mwzUTDvrUvXhbPru6v1UfXh1ff3qcvpRXb1Rry4/Rnn/d3Z5gtiwWLVR5r5ujIMWjbJFnVuT7Sz+X810EXlypS6vpur05Gw6Um9NaRrNfcwexAr0uKpjYi9NOapzOLZESC0N7zm6akZB2vRdGH+kBkfP1YmZIzOOng/U4JhPfxh9/3R02N1d6LLVOSZN3qnLVxenicz8PFS+0aVbwBJavb8+l98nHy+vxpOzSTJ6HRb4hLiy9PYBx7gvMurkdHJ8fTaenl1ddgMTOEfD1VVOf/eSM+21WjSIElgZP2jEWnNnGsSCs+USPjRdFLi2rqsGBklgBF/Nq9ypvZOz42mq3pydn+I6Hctlkqq3V+N3p9epejflM17x8Ozi1ThccXN+gpuEV9xc/GsKKeOr8bNwxaPr6cU4XOVmgpvJMS+yyuTitVwmvOJBwitupqfnl6dTSYYpBu6HrJ5XRcFHVmDELssQ9OuquVVrxFrVeuZlk9gSca/nggdJcEO1gJloulnr8kpntAbGLlrYsbHzW6LUrWFc3D90JkqDNN3CbKW3c02BYhrV1hQSTKLqymHsZHIO
*/