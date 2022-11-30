//
// ip/basic_endpoint.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/detail/cstdint.hpp>
#include <boost/asio/ip/address.hpp>
#include <boost/asio/ip/detail/endpoint.hpp>

#if defined(BOOST_ASIO_HAS_STD_HASH)
# include <functional>
#endif // defined(BOOST_ASIO_HAS_STD_HASH)

#if !defined(BOOST_ASIO_NO_IOSTREAM)
# include <iosfwd>
#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

/// Type used for storing port numbers.
typedef uint_least16_t port_type;

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
      port_type port_num) BOOST_ASIO_NOEXCEPT
    : impl_(internet_protocol.family(), port_num)
  {
  }

  /// Construct an endpoint using a port number and an IP address. This
  /// constructor may be used for accepting connections on a specific interface
  /// or for making a connection to a remote endpoint.
  basic_endpoint(const boost::asio::ip::address& addr,
      port_type port_num) BOOST_ASIO_NOEXCEPT
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
  port_type port() const BOOST_ASIO_NOEXCEPT
  {
    return impl_.port();
  }

  /// Set the port associated with the endpoint. The port number is always in
  /// the host's byte order.
  void port(port_type port_num) BOOST_ASIO_NOEXCEPT
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

#if defined(BOOST_ASIO_HAS_STD_HASH)
namespace std {

template <typename InternetProtocol>
struct hash<boost::asio::ip::basic_endpoint<InternetProtocol> >
{
  std::size_t operator()(
      const boost::asio::ip::basic_endpoint<InternetProtocol>& ep)
    const BOOST_ASIO_NOEXCEPT
  {
    std::size_t hash1 = std::hash<boost::asio::ip::address>()(ep.address());
    std::size_t hash2 = std::hash<unsigned short>()(ep.port());
    return hash1 ^ (hash2 + 0x9e3779b9 + (hash1 << 6) + (hash1 >> 2));
  }
};

} // namespace std
#endif // defined(BOOST_ASIO_HAS_STD_HASH)

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/ip/impl/basic_endpoint.hpp>

#endif // BOOST_ASIO_IP_BASIC_ENDPOINT_HPP

/* basic_endpoint.hpp
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
*/