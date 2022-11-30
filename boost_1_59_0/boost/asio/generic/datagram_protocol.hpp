//
// generic/datagram_protocol.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_GENERIC_DATAGRAM_PROTOCOL_HPP
#define BOOST_ASIO_GENERIC_DATAGRAM_PROTOCOL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <typeinfo>
#include <boost/asio/basic_datagram_socket.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/detail/throw_exception.hpp>
#include <boost/asio/generic/basic_endpoint.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace generic {

/// Encapsulates the flags needed for a generic datagram-oriented socket.
/**
 * The boost::asio::generic::datagram_protocol class contains flags necessary
 * for datagram-oriented sockets of any address family and protocol.
 *
 * @par Examples
 * Constructing using a native address family and socket protocol:
 * @code datagram_protocol p(AF_INET, IPPROTO_UDP); @endcode
 * Constructing from a specific protocol type:
 * @code datagram_protocol p(boost::asio::ip::udp::v4()); @endcode
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Safe.
 *
 * @par Concepts:
 * Protocol.
 */
class datagram_protocol
{
public:
  /// Construct a protocol object for a specific address family and protocol.
  datagram_protocol(int address_family, int socket_protocol)
    : family_(address_family),
      protocol_(socket_protocol)
  {
  }

  /// Construct a generic protocol object from a specific protocol.
  /**
   * @throws @c bad_cast Thrown if the source protocol is not datagram-oriented.
   */
  template <typename Protocol>
  datagram_protocol(const Protocol& source_protocol)
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
    return BOOST_ASIO_OS_DEF(SOCK_DGRAM);
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
  friend bool operator==(const datagram_protocol& p1,
      const datagram_protocol& p2)
  {
    return p1.family_ == p2.family_ && p1.protocol_ == p2.protocol_;
  }

  /// Compare two protocols for inequality.
  friend bool operator!=(const datagram_protocol& p1,
      const datagram_protocol& p2)
  {
    return !(p1 == p2);
  }

  /// The type of an endpoint.
  typedef basic_endpoint<datagram_protocol> endpoint;

  /// The generic socket type.
  typedef basic_datagram_socket<datagram_protocol> socket;

private:
  int family_;
  int protocol_;
};

} // namespace generic
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_GENERIC_DATAGRAM_PROTOCOL_HPP

/* datagram_protocol.hpp
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
*/