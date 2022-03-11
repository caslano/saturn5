//
// ip/basic_endpoint.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_BASIC_ENDPOINT_HPP
#define BOOST_ASIO_IP_BASIC_ENDPOINT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/ip/address.hpp>
#include <boost/asio/ip/detail/endpoint.hpp>

#if !defined(BOOST_ASIO_NO_IOSTREAM)
# include <iosfwd>
#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

/// Describes an endpoint for a version-independent IP socket.
/**
 * The boost::asio::ip::basic_endpoint class template describes an endpoint that
 * may be associated with a particular socket.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 *
 * @par Concepts:
 * Endpoint.
 */
template <typename InternetProtocol>
class basic_endpoint
{
public:
  /// The protocol type associated with the endpoint.
  typedef InternetProtocol protocol_type;

  /// The type of the endpoint structure. This type is dependent on the
  /// underlying implementation of the socket layer.
#if defined(GENERATING_DOCUMENTATION)
  typedef implementation_defined data_type;
#else
  typedef boost::asio::detail::socket_addr_type data_type;
#endif

  /// Default constructor.
  basic_endpoint() BOOST_ASIO_NOEXCEPT
    : impl_()
  {
  }

  /// Construct an endpoint using a port number, specified in the host's byte
  /// order. The IP address will be the any address (i.e. INADDR_ANY or
  /// in6addr_any). This constructor would typically be used for accepting new
  /// connections.
  /**
   * @par Examples
   * To initialise an IPv4 TCP endpoint for port 1234, use:
   * @code
   * boost::asio::ip::tcp::endpoint ep(boost::asio::ip::tcp::v4(), 1234);
   * @endcode
   *
   * To specify an IPv6 UDP endpoint for port 9876, use:
   * @code
   * boost::asio::ip::udp::endpoint ep(boost::asio::ip::udp::v6(), 9876);
   * @endcode
   */
  basic_endpoint(const InternetProtocol& internet_protocol,
      unsigned short port_num) BOOST_ASIO_NOEXCEPT
    : impl_(internet_protocol.family(), port_num)
  {
  }

  /// Construct an endpoint using a port number and an IP address. This
  /// constructor may be used for accepting connections on a specific interface
  /// or for making a connection to a remote endpoint.
  basic_endpoint(const boost::asio::ip::address& addr,
      unsigned short port_num) BOOST_ASIO_NOEXCEPT
    : impl_(addr, port_num)
  {
  }

  /// Copy constructor.
  basic_endpoint(const basic_endpoint& other) BOOST_ASIO_NOEXCEPT
    : impl_(other.impl_)
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move constructor.
  basic_endpoint(basic_endpoint&& other) BOOST_ASIO_NOEXCEPT
    : impl_(other.impl_)
  {
  }
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// Assign from another endpoint.
  basic_endpoint& operator=(const basic_endpoint& other) BOOST_ASIO_NOEXCEPT
  {
    impl_ = other.impl_;
    return *this;
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move-assign from another endpoint.
  basic_endpoint& operator=(basic_endpoint&& other) BOOST_ASIO_NOEXCEPT
  {
    impl_ = other.impl_;
    return *this;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// The protocol associated with the endpoint.
  protocol_type protocol() const BOOST_ASIO_NOEXCEPT
  {
    if (impl_.is_v4())
      return InternetProtocol::v4();
    return InternetProtocol::v6();
  }

  /// Get the underlying endpoint in the native type.
  data_type* data() BOOST_ASIO_NOEXCEPT
  {
    return impl_.data();
  }

  /// Get the underlying endpoint in the native type.
  const data_type* data() const BOOST_ASIO_NOEXCEPT
  {
    return impl_.data();
  }

  /// Get the underlying size of the endpoint in the native type.
  std::size_t size() const BOOST_ASIO_NOEXCEPT
  {
    return impl_.size();
  }

  /// Set the underlying size of the endpoint in the native type.
  void resize(std::size_t new_size)
  {
    impl_.resize(new_size);
  }

  /// Get the capacity of the endpoint in the native type.
  std::size_t capacity() const BOOST_ASIO_NOEXCEPT
  {
    return impl_.capacity();
  }

  /// Get the port associated with the endpoint. The port number is always in
  /// the host's byte order.
  unsigned short port() const BOOST_ASIO_NOEXCEPT
  {
    return impl_.port();
  }

  /// Set the port associated with the endpoint. The port number is always in
  /// the host's byte order.
  void port(unsigned short port_num) BOOST_ASIO_NOEXCEPT
  {
    impl_.port(port_num);
  }

  /// Get the IP address associated with the endpoint.
  boost::asio::ip::address address() const BOOST_ASIO_NOEXCEPT
  {
    return impl_.address();
  }

  /// Set the IP address associated with the endpoint.
  void address(const boost::asio::ip::address& addr) BOOST_ASIO_NOEXCEPT
  {
    impl_.address(addr);
  }

  /// Compare two endpoints for equality.
  friend bool operator==(const basic_endpoint<InternetProtocol>& e1,
      const basic_endpoint<InternetProtocol>& e2) BOOST_ASIO_NOEXCEPT
  {
    return e1.impl_ == e2.impl_;
  }

  /// Compare two endpoints for inequality.
  friend bool operator!=(const basic_endpoint<InternetProtocol>& e1,
      const basic_endpoint<InternetProtocol>& e2) BOOST_ASIO_NOEXCEPT
  {
    return !(e1 == e2);
  }

  /// Compare endpoints for ordering.
  friend bool operator<(const basic_endpoint<InternetProtocol>& e1,
      const basic_endpoint<InternetProtocol>& e2) BOOST_ASIO_NOEXCEPT
  {
    return e1.impl_ < e2.impl_;
  }

  /// Compare endpoints for ordering.
  friend bool operator>(const basic_endpoint<InternetProtocol>& e1,
      const basic_endpoint<InternetProtocol>& e2) BOOST_ASIO_NOEXCEPT
  {
    return e2.impl_ < e1.impl_;
  }

  /// Compare endpoints for ordering.
  friend bool operator<=(const basic_endpoint<InternetProtocol>& e1,
      const basic_endpoint<InternetProtocol>& e2) BOOST_ASIO_NOEXCEPT
  {
    return !(e2 < e1);
  }

  /// Compare endpoints for ordering.
  friend bool operator>=(const basic_endpoint<InternetProtocol>& e1,
      const basic_endpoint<InternetProtocol>& e2) BOOST_ASIO_NOEXCEPT
  {
    return !(e1 < e2);
  }

private:
  // The underlying IP endpoint.
  boost::asio::ip::detail::endpoint impl_;
};

#if !defined(BOOST_ASIO_NO_IOSTREAM)

/// Output an endpoint as a string.
/**
 * Used to output a human-readable string for a specified endpoint.
 *
 * @param os The output stream to which the string will be written.
 *
 * @param endpoint The endpoint to be written.
 *
 * @return The output stream.
 *
 * @relates boost::asio::ip::basic_endpoint
 */
template <typename Elem, typename Traits, typename InternetProtocol>
std::basic_ostream<Elem, Traits>& operator<<(
    std::basic_ostream<Elem, Traits>& os,
    const basic_endpoint<InternetProtocol>& endpoint);

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/ip/impl/basic_endpoint.hpp>

#endif // BOOST_ASIO_IP_BASIC_ENDPOINT_HPP

/* basic_endpoint.hpp
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
*/