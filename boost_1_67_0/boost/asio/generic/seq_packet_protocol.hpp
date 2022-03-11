//
// generic/seq_packet_protocol.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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