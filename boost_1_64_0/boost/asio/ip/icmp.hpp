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
b9JfiP4tkxqjVFrsTe38EonkVKpOT99qmX1ybLEK28FwmvUnWABS3JWxy0xvkoNwHQae4SiZRIIJcCihsoCqrfWTgj3CQCbdD7Pr7OxSR8YgVeWg3F0HcesqNcG1fI+sTKws6cmUEka5HTbYs1QHeYrWLRKjhXPQrg9WeLsagAWl/q/SVufP1uhbodCXAa10ihC5Kb9WsF2SEw270cVLmj6LzIzjVlP0zhGr1/C6bbBc2FOnZAdAbeFVRMX9Hu1J4Hu97Th8rkQ2XIAduGVAUrPwHjDPaQSp7Fy//3FDNeFtFksfPl2zWHN3QHZj6AY/tvYi382776XiA247uwG+aDrdtGMWWD9tB29b5JqprxXfUiBCpt2oz3aCN7dw9supzrQEYR0kNLa9XSHBMgYrLOOLOMJ8QeWG4FAgv07IB0cpE2E9pVYChRxbtdltrpksGE7tIfYYgSqV1x8QldLIOZ1ziZNObEBeBTWoKRqNwIyRRjq/2ma+kU2Uwh3vvVEZ8fU8IQPakjQ41qlMoglIYnZOuMX8PRnLtQpnY+HeTIrVMDXWl4dooG/eBw==
*/