//
// generic/stream_protocol.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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