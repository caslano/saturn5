//
// ip/udp.hpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
6FBXkfUnyYgPzC+O1QxJ+x25GessY+W882pGQcFgImNZldwp0RS3hDhdoFInOOaY3M0ejVJwZg7Ypov+4QzwuYMqhyFKnUpj3j1auKf/BnvXs7crR6t/nv2/CkNjx70SXfloRYy+HNljL5uXGqykvRjR5a5H7/gWB8s077i/Pc8XVRagXX+uL7+zgg6snZBkoCvV5w2anWBvK1hMxg8Z2OQOlvna4lCwb4yKOg68s46LnqMaVrt3O80zniEgfhYGw2UyD7EhhoMP4QvSWxL2NPRHuMp2eZ9l0cib6avHgq09P6UnIhE268+ZuTU0Pb2L//YK7KnMpbfBk3YVsMhNX0XdJ4w1Ku9EEMJHiPLFwKfLX5oMCmaY7OMnUa0bTdA9/lVuE1XAIA1S4xO4zmQ+TB8L1VmeQh+/fouG4HT4VPffcY+6op+XeuoBAqSUElpijthPmWU/4IgBg5CqUTxwpYmvowOQxykmNlheZ0RALfXzY9qxFrjEDoiVLIYDzImO0nE35msPBC5gRGNaod91KBruM06xi5stdliS1KwrfcAG6jLPw7MC17hmCg==
*/