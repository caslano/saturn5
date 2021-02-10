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
kLFOxEAMRPv9iilBYk9UgNIhKK6go6A2iZOstLFXu45y/D3OCQilZb03o3lTmToUqpQz55iWhYdExuHMuXR4VYgaNkqGUSuWNVsqmS9JJtxsyWbE+Evfhudh4KHD4+nh6XQf3pkj5aaH/wha6BJePGfS+tWhVxHuLamgX2sOMcbwMbNg0D3oD7dK0kau7Q42pwYtV2ZLOSNJs7r2djX4mwxeus265iFUspkrSmWnHWPZvWvBopX/xTfXHHGuUOkZP7Q7JexT7KwpGjPSCOHtKIaeBJ8M2pcAtWMxP70g0+K1BeSzujMc0afwDVBLAwQKAAAACAAtZ0pSmIqmr7gAAAAZAQAALAAJAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL3BhcmFsbGVsLW1heC5kVVQFAAG2SCRgbc49bsMwDAXgnafgASIjSxPAW9ClQzulQGfCon9QiTRECohvHwVJmyUrH/k9fqpMPa5UKCVOIdMFPjitPX7RZck146Ay1FJYhg1HLf+r6IXERi4Gpxg59njsDoduD2fmQMn0qcI7OU9atv6mCQ++qGBTE4QQ4GdmQbJfjuiKUV9U7LDaIhOG8Jft0OfFUNe7peJFk4HPjPnxOWWt4qjj03kUWMuTk7BWS1sH8N3O
*/