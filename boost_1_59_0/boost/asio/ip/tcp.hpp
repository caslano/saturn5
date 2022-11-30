//
// ip/tcp.hpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_TCP_HPP
#define BOOST_ASIO_IP_TCP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/basic_socket_acceptor.hpp>
#include <boost/asio/basic_socket_iostream.hpp>
#include <boost/asio/basic_stream_socket.hpp>
#include <boost/asio/detail/socket_option.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/ip/basic_endpoint.hpp>
#include <boost/asio/ip/basic_resolver.hpp>
#include <boost/asio/ip/basic_resolver_iterator.hpp>
#include <boost/asio/ip/basic_resolver_query.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

/// Encapsulates the flags needed for TCP.
/**
 * The boost::asio::ip::tcp class contains flags necessary for TCP sockets.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Safe.
 *
 * @par Concepts:
 * Protocol, InternetProtocol.
 */
class tcp
{
public:
  /// The type of a TCP endpoint.
  typedef basic_endpoint<tcp> endpoint;

  /// Construct to represent the IPv4 TCP protocol.
  static tcp v4() BOOST_ASIO_NOEXCEPT
  {
    return tcp(BOOST_ASIO_OS_DEF(AF_INET));
  }

  /// Construct to represent the IPv6 TCP protocol.
  static tcp v6() BOOST_ASIO_NOEXCEPT
  {
    return tcp(BOOST_ASIO_OS_DEF(AF_INET6));
  }

  /// Obtain an identifier for the type of the protocol.
  int type() const BOOST_ASIO_NOEXCEPT
  {
    return BOOST_ASIO_OS_DEF(SOCK_STREAM);
  }

  /// Obtain an identifier for the protocol.
  int protocol() const BOOST_ASIO_NOEXCEPT
  {
    return BOOST_ASIO_OS_DEF(IPPROTO_TCP);
  }

  /// Obtain an identifier for the protocol family.
  int family() const BOOST_ASIO_NOEXCEPT
  {
    return family_;
  }

  /// The TCP socket type.
  typedef basic_stream_socket<tcp> socket;

  /// The TCP acceptor type.
  typedef basic_socket_acceptor<tcp> acceptor;

  /// The TCP resolver type.
  typedef basic_resolver<tcp> resolver;

#if !defined(BOOST_ASIO_NO_IOSTREAM)
  /// The TCP iostream type.
  typedef basic_socket_iostream<tcp> iostream;
#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

  /// Socket option for disabling the Nagle algorithm.
  /**
   * Implements the IPPROTO_TCP/TCP_NODELAY socket option.
   *
   * @par Examples
   * Setting the option:
   * @code
   * boost::asio::ip::tcp::socket socket(my_context);
   * ...
   * boost::asio::ip::tcp::no_delay option(true);
   * socket.set_option(option);
   * @endcode
   *
   * @par
   * Getting the current option value:
   * @code
   * boost::asio::ip::tcp::socket socket(my_context);
   * ...
   * boost::asio::ip::tcp::no_delay option;
   * socket.get_option(option);
   * bool is_set = option.value();
   * @endcode
   *
   * @par Concepts:
   * Socket_Option, Boolean_Socket_Option.
   */
#if defined(GENERATING_DOCUMENTATION)
  typedef implementation_defined no_delay;
#else
  typedef boost::asio::detail::socket_option::boolean<
    BOOST_ASIO_OS_DEF(IPPROTO_TCP), BOOST_ASIO_OS_DEF(TCP_NODELAY)> no_delay;
#endif

  /// Compare two protocols for equality.
  friend bool operator==(const tcp& p1, const tcp& p2)
  {
    return p1.family_ == p2.family_;
  }

  /// Compare two protocols for inequality.
  friend bool operator!=(const tcp& p1, const tcp& p2)
  {
    return p1.family_ != p2.family_;
  }

private:
  // Construct with a specific family.
  explicit tcp(int protocol_family) BOOST_ASIO_NOEXCEPT
    : family_(protocol_family)
  {
  }

  int family_;
};

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IP_TCP_HPP

/* tcp.hpp
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
*/