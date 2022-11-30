//
// generic/seq_packet_protocol.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_GENERIC_SEQ_PACKET_PROTOCOL_HPP
#define BOOST_ASIO_GENERIC_SEQ_PACKET_PROTOCOL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <typeinfo>
#include <boost/asio/basic_seq_packet_socket.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/detail/throw_exception.hpp>
#include <boost/asio/generic/basic_endpoint.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace generic {

/// Encapsulates the flags needed for a generic sequenced packet socket.
/**
 * The boost::asio::generic::seq_packet_protocol class contains flags necessary
 * for seq_packet-oriented sockets of any address family and protocol.
 *
 * @par Examples
 * Constructing using a native address family and socket protocol:
 * @code seq_packet_protocol p(AF_INET, IPPROTO_SCTP); @endcode
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Safe.
 *
 * @par Concepts:
 * Protocol.
 */
class seq_packet_protocol
{
public:
  /// Construct a protocol object for a specific address family and protocol.
  seq_packet_protocol(int address_family, int socket_protocol)
    : family_(address_family),
      protocol_(socket_protocol)
  {
  }

  /// Construct a generic protocol object from a specific protocol.
  /**
   * @throws @c bad_cast Thrown if the source protocol is not based around
   * sequenced packets.
   */
  template <typename Protocol>
  seq_packet_protocol(const Protocol& source_protocol)
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
    return BOOST_ASIO_OS_DEF(SOCK_SEQPACKET);
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
  friend bool operator==(const seq_packet_protocol& p1,
      const seq_packet_protocol& p2)
  {
    return p1.family_ == p2.family_ && p1.protocol_ == p2.protocol_;
  }

  /// Compare two protocols for inequality.
  friend bool operator!=(const seq_packet_protocol& p1,
      const seq_packet_protocol& p2)
  {
    return !(p1 == p2);
  }

  /// The type of an endpoint.
  typedef basic_endpoint<seq_packet_protocol> endpoint;

  /// The generic socket type.
  typedef basic_seq_packet_socket<seq_packet_protocol> socket;

private:
  int family_;
  int protocol_;
};

} // namespace generic
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_GENERIC_SEQ_PACKET_PROTOCOL_HPP

/* seq_packet_protocol.hpp
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
*/