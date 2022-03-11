//
// ip/tcp.hpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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