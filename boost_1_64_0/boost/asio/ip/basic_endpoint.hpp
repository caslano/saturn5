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
7udT7lv65pY/rzx1S7/lz3h9i9LrW5f/n9+oLPHJnpb0kRZ+l6qyt/xOs/zOkN+v8zvd8jvT/B0cGw7ze7J6FhX+zf4jZhzePwn6T+L3KsvvesvvtZbfq8O/GR/DaV5n+X2t5Xep5fca83fwHajdvuD85xL5PUSN8/J7Or8vlt/L+L1Uft/A78vkdyWyWH7vQObJ77uRRfL7BWSJ/H4VCX4TUfbGh1QfYfZvItbINxBrYX94DRwEN8MhsA4OE39Jjz3evdO7StLbIOlVSXobJb1KSa/Kkl51lPRKJb3Vkl6ZpLdW0lsj6ZVJekVIk6Q3VtLrBGdJepdJesskvcvhYLgSDodXwDy4HI5W/pJuCdIq6U6UdDvDYkl3nqQ7H2bCBbAXXAL7wYVwqLhHwkWS/mI4Nugv5SF7PcPZLuUxiHiKubAHHCL5HwpHwGFwGhwu6S1HGiW9CyS9JG2n7NEpdk8Quy+CveEkmCvuYXCy2D0F5it/Sb8caZX06yT9LnClpN9D0kW0fk/Rz4bjYG94MewDL4d94RUwB66D/WGFuCU/7F3snZ8Cyc90qPub5GcmzBX3MDhL7LlY7MHfTL9F0l/skj7uBsW7YQ9xZ8J74ED4eTgKfg6Oh/fDefABGKxf2RsYprnUb72kfx3sAj8Iu8EtsDu8HqaK2+w/UdL7kKTXIOndJOndLOlt1enhlvTykZ2Snl/SU8yV9G6V9G6DcXC76E1EGkWvl+jFwzzRe94XrJcXYAr8EUwXd6jcm0X/cpdy/4jo75By/hgcCj8OL4E74Ry4Cy6Ed8BicUs7lf1eafMu7fRlKY9XYZq4M8SdDX8K+8NjcAD8mRz/NZgn7vPE/SfYhDTI8fy+4PFUe9kjx7soLjguFMDBcDocAWfAPFgMp8JZcK64Lxf3GjgbVsOL4Q2wED4C58IDcB78FlwAD8OF8BXR+zW8FP5e0n0fLoZSTrJ/Jja6lNMGqYdK2AvWwX5wMxwEa+BQcY8Udz6shuPEf6K4pb3JHpi0F5f2Nt8fbG8LoPJfCJXeMB+6ondIyle1iz5Q/b1J+r3hCTgCvgVnwt/DRfBteAf8M7wPvgMfgKfgV+G78Bn4V/gs7EH5vAhP434FvgePw/ehqt+/w07QIF4m9MEsqPTGwAQ4DibCieK+UNwFsBNcCJPgEtgZroBdYIXEuxqmwgaYBm+W9D8Nk+GDMAAfhV1hM+wm9WrIPoDA+IGUV19+n5RyziTeAJgFh8BsOFHcF4q7BvaFn4OD4F6YC78MB8Pn4RD4YzgUvgGHwRNwOGyFeVAZMQp2g6NhGhwDs2E+HA7z4HlwgpTPRFgIJ8Er4HnwKng+rIFj4VY4Dt4C+8OnYA58Fg6Aur2Z+5dxb0DKYZDKB9RX6MTLgWXwSlgBS+BnYB3cAK+V8AZ4FbxZ/LfDSngv3Ajvg1XwQbgJNsEa6Ze1Uk518BjcDH8Br4G/gdfCt+H1Ul43wu7wQ3AobID58GYpn21wMbwVXga3wyp4O/wQ/Ii0l13wHtF7BN4Nn4Sfht+F98AfwHvhq5B8y3gme0fBwS7jWaKMi51kPAxIP+8K9TdDYDVMgdfDVLgTpsF7YA/4bZgOn5Xwl2Av+FOYDX8OM+AbsC/8DewH/whzpP8NhAE4KDzuy1442Ooynp2S+d+7cDU8DdfB92CF+G8SdwN8H26Hf4c7oI/jfBzGyfFaDdkrBi6XclLj0BtyvCEybg6T89gIGS9HwuHwYjgZ5sEb4Wh4OzwP7hD/j8ExUn75cJeEfxGOhV+DF8Dn4Hj4OzgJvgUnw3fhhfBv4n5P3D5snQq7wwKYCqfDXnAG7AtnwgvhbDgDXmzmW/Y/gatd8j0=
*/