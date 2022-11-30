//
// ip/udp.hpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_UDP_HPP
#define BOOST_ASIO_IP_UDP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/basic_datagram_socket.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/ip/basic_endpoint.hpp>
#include <boost/asio/ip/basic_resolver.hpp>
#include <boost/asio/ip/basic_resolver_iterator.hpp>
#include <boost/asio/ip/basic_resolver_query.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

/// Encapsulates the flags needed for UDP.
/**
 * The boost::asio::ip::udp class contains flags necessary for UDP sockets.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Safe.
 *
 * @par Concepts:
 * Protocol, InternetProtocol.
 */
class udp
{
public:
  /// The type of a UDP endpoint.
  typedef basic_endpoint<udp> endpoint;

  /// Construct to represent the IPv4 UDP protocol.
  static udp v4() BOOST_ASIO_NOEXCEPT
  {
    return udp(BOOST_ASIO_OS_DEF(AF_INET));
  }

  /// Construct to represent the IPv6 UDP protocol.
  static udp v6() BOOST_ASIO_NOEXCEPT
  {
    return udp(BOOST_ASIO_OS_DEF(AF_INET6));
  }

  /// Obtain an identifier for the type of the protocol.
  int type() const BOOST_ASIO_NOEXCEPT
  {
    return BOOST_ASIO_OS_DEF(SOCK_DGRAM);
  }

  /// Obtain an identifier for the protocol.
  int protocol() const BOOST_ASIO_NOEXCEPT
  {
    return BOOST_ASIO_OS_DEF(IPPROTO_UDP);
  }

  /// Obtain an identifier for the protocol family.
  int family() const BOOST_ASIO_NOEXCEPT
  {
    return family_;
  }

  /// The UDP socket type.
  typedef basic_datagram_socket<udp> socket;

  /// The UDP resolver type.
  typedef basic_resolver<udp> resolver;

  /// Compare two protocols for equality.
  friend bool operator==(const udp& p1, const udp& p2)
  {
    return p1.family_ == p2.family_;
  }

  /// Compare two protocols for inequality.
  friend bool operator!=(const udp& p1, const udp& p2)
  {
    return p1.family_ != p2.family_;
  }

private:
  // Construct with a specific family.
  explicit udp(int protocol_family) BOOST_ASIO_NOEXCEPT
    : family_(protocol_family)
  {
  }

  int family_;
};

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IP_UDP_HPP

/* udp.hpp
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
*/