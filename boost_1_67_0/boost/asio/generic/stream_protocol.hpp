//
// generic/stream_protocol.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_GENERIC_STREAM_PROTOCOL_HPP
#define BOOST_ASIO_GENERIC_STREAM_PROTOCOL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <typeinfo>
#include <boost/asio/basic_socket_iostream.hpp>
#include <boost/asio/basic_stream_socket.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/detail/throw_exception.hpp>
#include <boost/asio/generic/basic_endpoint.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace generic {

/// Encapsulates the flags needed for a generic stream-oriented socket.
/**
 * The boost::asio::generic::stream_protocol class contains flags necessary for
 * stream-oriented sockets of any address family and protocol.
 *
 * @par Examples
 * Constructing using a native address family and socket protocol:
 * @code stream_protocol p(AF_INET, IPPROTO_TCP); @endcode
 * Constructing from a specific protocol type:
 * @code stream_protocol p(boost::asio::ip::tcp::v4()); @endcode
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Safe.
 *
 * @par Concepts:
 * Protocol.
 */
class stream_protocol
{
public:
  /// Construct a protocol object for a specific address family and protocol.
  stream_protocol(int address_family, int socket_protocol)
    : family_(address_family),
      protocol_(socket_protocol)
  {
  }

  /// Construct a generic protocol object from a specific protocol.
  /**
   * @throws @c bad_cast Thrown if the source protocol is not stream-oriented.
   */
  template <typename Protocol>
  stream_protocol(const Protocol& source_protocol)
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
    return BOOST_ASIO_OS_DEF(SOCK_STREAM);
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
  friend bool operator==(const stream_protocol& p1, const stream_protocol& p2)
  {
    return p1.family_ == p2.family_ && p1.protocol_ == p2.protocol_;
  }

  /// Compare two protocols for inequality.
  friend bool operator!=(const stream_protocol& p1, const stream_protocol& p2)
  {
    return !(p1 == p2);
  }

  /// The type of an endpoint.
  typedef basic_endpoint<stream_protocol> endpoint;

  /// The generic socket type.
  typedef basic_stream_socket<stream_protocol> socket;

#if !defined(BOOST_ASIO_NO_IOSTREAM)
  /// The generic socket iostream type.
  typedef basic_socket_iostream<stream_protocol> iostream;
#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

private:
  int family_;
  int protocol_;
};

} // namespace generic
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_GENERIC_STREAM_PROTOCOL_HPP

/* stream_protocol.hpp
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
*/