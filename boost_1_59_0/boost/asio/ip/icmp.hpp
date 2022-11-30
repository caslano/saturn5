//
// ip/icmp.hpp
// ~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
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
*/