//
// generic/datagram_protocol.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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