//
// generic/raw_protocol.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
l+TDmSbjvXd7FsD5To7M85wCWKJ9pnfKnkLQy37WWDS6CFLD/cY2fyiCydZxe0xPF8OUbn11jk0ugUevzDRcV+Yy2z3mLw1lcpjrlQP9grvlMDOdZrpYrBcyIx889NAJzWYSNWvaVedkMRMXLq8zV89kMorGWuwVpjPdXx2gPx9NY/a0N76aPz+VeXfRbnlc/xTGbM3GQE3RC0ZkZb+axyQxuo9M/S0PJzI2R7TDfyxPYKrjpg5ebxnPrKnG6cUx6oWlow/XMoz59IClA68/ZzYsunswZdUzZvwsp0WLTaOYcQkfOuVRT5ndfL1FGnmPmGOak6/I3XrATLU8//jU7nBmw8PXmV7pd5g3dy5o3Tp2gzldapx/z+0KQ0+t2b9oXBhz4FmKocHUU8xt56OO8/RCGKeafRu11fn/6AfceNZr9u3T7PsVFPtsF8UpfAX3p6Lbww9/gd7s7wuU+kZtcrn3GXTzx6G/z6B8Rnb/vOJPoJO8Hv19gjKBr6yC6icQRsdptdz5CDa9ah/5zvoIhvcvxuyp+wCxS1e5fD31AXpeGYf+PkCJqfrx4E/v4XQo/r2HsveFP8KnvIfW7mcPxbXUwq361WpRd2qh+54l6A8h+6uF7/I7xjkLa9B85uM740ANTOq2yDtnYg14+iovLOtQA+LzGdXQbYVv1xW+1bCsr7JTinU1dOzq6OIrXw0O6keH7Eutgs+Ovia5
*/