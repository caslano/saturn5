//
// ip/multicast.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_MULTICAST_HPP
#define BOOST_ASIO_IP_MULTICAST_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <cstddef>
#include <boost/asio/ip/detail/socket_option.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {
namespace multicast {

/// Socket option to join a multicast group on a specified interface.
/**
 * Implements the IPPROTO_IP/IP_ADD_MEMBERSHIP socket option.
 *
 * @par Examples
 * Setting the option to join a multicast group:
 * @code
 * boost::asio::ip::udp::socket socket(my_context);
 * ...
 * boost::asio::ip::address multicast_address =
 *   boost::asio::ip::address::from_string("225.0.0.1");
 * boost::asio::ip::multicast::join_group option(multicast_address);
 * socket.set_option(option);
 * @endcode
 *
 * @par Concepts:
 * SettableSocketOption.
 */
#if defined(GENERATING_DOCUMENTATION)
typedef implementation_defined join_group;
#else
typedef boost::asio::ip::detail::socket_option::multicast_request<
  BOOST_ASIO_OS_DEF(IPPROTO_IP),
  BOOST_ASIO_OS_DEF(IP_ADD_MEMBERSHIP),
  BOOST_ASIO_OS_DEF(IPPROTO_IPV6),
  BOOST_ASIO_OS_DEF(IPV6_JOIN_GROUP)> join_group;
#endif

/// Socket option to leave a multicast group on a specified interface.
/**
 * Implements the IPPROTO_IP/IP_DROP_MEMBERSHIP socket option.
 *
 * @par Examples
 * Setting the option to leave a multicast group:
 * @code
 * boost::asio::ip::udp::socket socket(my_context);
 * ...
 * boost::asio::ip::address multicast_address =
 *   boost::asio::ip::address::from_string("225.0.0.1");
 * boost::asio::ip::multicast::leave_group option(multicast_address);
 * socket.set_option(option);
 * @endcode
 *
 * @par Concepts:
 * SettableSocketOption.
 */
#if defined(GENERATING_DOCUMENTATION)
typedef implementation_defined leave_group;
#else
typedef boost::asio::ip::detail::socket_option::multicast_request<
  BOOST_ASIO_OS_DEF(IPPROTO_IP),
  BOOST_ASIO_OS_DEF(IP_DROP_MEMBERSHIP),
  BOOST_ASIO_OS_DEF(IPPROTO_IPV6),
  BOOST_ASIO_OS_DEF(IPV6_LEAVE_GROUP)> leave_group;
#endif

/// Socket option for local interface to use for outgoing multicast packets.
/**
 * Implements the IPPROTO_IP/IP_MULTICAST_IF socket option.
 *
 * @par Examples
 * Setting the option:
 * @code
 * boost::asio::ip::udp::socket socket(my_context);
 * ...
 * boost::asio::ip::address_v4 local_interface =
 *   boost::asio::ip::address_v4::from_string("1.2.3.4");
 * boost::asio::ip::multicast::outbound_interface option(local_interface);
 * socket.set_option(option);
 * @endcode
 *
 * @par Concepts:
 * SettableSocketOption.
 */
#if defined(GENERATING_DOCUMENTATION)
typedef implementation_defined outbound_interface;
#else
typedef boost::asio::ip::detail::socket_option::network_interface<
  BOOST_ASIO_OS_DEF(IPPROTO_IP),
  BOOST_ASIO_OS_DEF(IP_MULTICAST_IF),
  BOOST_ASIO_OS_DEF(IPPROTO_IPV6),
  BOOST_ASIO_OS_DEF(IPV6_MULTICAST_IF)> outbound_interface;
#endif

/// Socket option for time-to-live associated with outgoing multicast packets.
/**
 * Implements the IPPROTO_IP/IP_MULTICAST_TTL socket option.
 *
 * @par Examples
 * Setting the option:
 * @code
 * boost::asio::ip::udp::socket socket(my_context);
 * ...
 * boost::asio::ip::multicast::hops option(4);
 * socket.set_option(option);
 * @endcode
 *
 * @par
 * Getting the current option value:
 * @code
 * boost::asio::ip::udp::socket socket(my_context);
 * ...
 * boost::asio::ip::multicast::hops option;
 * socket.get_option(option);
 * int ttl = option.value();
 * @endcode
 *
 * @par Concepts:
 * GettableSocketOption, SettableSocketOption.
 */
#if defined(GENERATING_DOCUMENTATION)
typedef implementation_defined hops;
#else
typedef boost::asio::ip::detail::socket_option::multicast_hops<
  BOOST_ASIO_OS_DEF(IPPROTO_IP),
  BOOST_ASIO_OS_DEF(IP_MULTICAST_TTL),
  BOOST_ASIO_OS_DEF(IPPROTO_IPV6),
  BOOST_ASIO_OS_DEF(IPV6_MULTICAST_HOPS)> hops;
#endif

/// Socket option determining whether outgoing multicast packets will be
/// received on the same socket if it is a member of the multicast group.
/**
 * Implements the IPPROTO_IP/IP_MULTICAST_LOOP socket option.
 *
 * @par Examples
 * Setting the option:
 * @code
 * boost::asio::ip::udp::socket socket(my_context);
 * ...
 * boost::asio::ip::multicast::enable_loopback option(true);
 * socket.set_option(option);
 * @endcode
 *
 * @par
 * Getting the current option value:
 * @code
 * boost::asio::ip::udp::socket socket(my_context);
 * ...
 * boost::asio::ip::multicast::enable_loopback option;
 * socket.get_option(option);
 * bool is_set = option.value();
 * @endcode
 *
 * @par Concepts:
 * GettableSocketOption, SettableSocketOption.
 */
#if defined(GENERATING_DOCUMENTATION)
typedef implementation_defined enable_loopback;
#else
typedef boost::asio::ip::detail::socket_option::multicast_enable_loopback<
  BOOST_ASIO_OS_DEF(IPPROTO_IP),
  BOOST_ASIO_OS_DEF(IP_MULTICAST_LOOP),
  BOOST_ASIO_OS_DEF(IPPROTO_IPV6),
  BOOST_ASIO_OS_DEF(IPV6_MULTICAST_LOOP)> enable_loopback;
#endif

} // namespace multicast
} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IP_MULTICAST_HPP

/* multicast.hpp
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
*/