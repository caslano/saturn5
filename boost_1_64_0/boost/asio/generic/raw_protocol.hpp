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
jhU6ayMvgb8ZU6MqxS99+9DhSwkTaEBh2IIGHPoXP84i8k2SKKZoX02CPHfpUqNA7ihzPSQHaT72A0bW0wQELh5vr8WjL/8eXgoHVvarHhtezkn3jkwLx7hyrifjoEVfI2X5MsMwqb/8DGiKv7l+tOfxPmYnPXTHQSFyTvohzv7UgZIQhWJnLO7YBK978lfBuT01K7ch/qNqMRkXiJ3V2DzwPRoQ7mNrMdufkCSc5xuyfr3eJKw66GrKX8R8M0yIZg0r2i85kY6vsIf5Bf5ogC43x+iiu3XndSrq9kdfxbJozvUr1XLq8vd5bp+kv2QlF4+83MhDBH8SYL5hiv029abzdK4eN70yVNsmkijFLhLCCBfbCKI2sqNrSCIEGyTM71d0yKB+1no6EOgta4/2lOW3VqJ5HaADIwDPO0PNa+ezupniUj+4158Id4/Y40n80mIs4p+KxCA2kVk2V0mDZL58zNbUMOLHGiLBG0A68QRPK4LwbPU67bM2lqOTXnGmKM2W0dWJDpThkhLNMoITqrycII9GxxI0e+ZDLdRX/GORbybS0hKzZEVo3A==
*/