//
// generic/raw_protocol.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_GENERIC_RAW_PROTOCOL_HPP
#define BOOST_ASIO_GENERIC_RAW_PROTOCOL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <typeinfo>
#include <boost/asio/basic_raw_socket.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/detail/throw_exception.hpp>
#include <boost/asio/generic/basic_endpoint.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace generic {

/// Encapsulates the flags needed for a generic raw socket.
/**
 * The boost::asio::generic::raw_protocol class contains flags necessary for
 * raw sockets of any address family and protocol.
 *
 * @par Examples
 * Constructing using a native address family and socket protocol:
 * @code raw_protocol p(AF_INET, IPPROTO_ICMP); @endcode
 * Constructing from a specific protocol type:
 * @code raw_protocol p(boost::asio::ip::icmp::v4()); @endcode
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Safe.
 *
 * @par Concepts:
 * Protocol.
 */
class raw_protocol
{
public:
  /// Construct a protocol object for a specific address family and protocol.
  raw_protocol(int address_family, int socket_protocol)
    : family_(address_family),
      protocol_(socket_protocol)
  {
  }

  /// Construct a generic protocol object from a specific protocol.
  /**
   * @throws @c bad_cast Thrown if the source protocol is not raw-oriented.
   */
  template <typename Protocol>
  raw_protocol(const Protocol& source_protocol)
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
    return BOOST_ASIO_OS_DEF(SOCK_RAW);
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
  friend bool operator==(const raw_protocol& p1, const raw_protocol& p2)
  {
    return p1.family_ == p2.family_ && p1.protocol_ == p2.protocol_;
  }

  /// Compare two protocols for inequality.
  friend bool operator!=(const raw_protocol& p1, const raw_protocol& p2)
  {
    return !(p1 == p2);
  }

  /// The type of an endpoint.
  typedef basic_endpoint<raw_protocol> endpoint;

  /// The generic socket type.
  typedef basic_raw_socket<raw_protocol> socket;

private:
  int family_;
  int protocol_;
};

} // namespace generic
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_GENERIC_RAW_PROTOCOL_HPP

/* raw_protocol.hpp
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
*/