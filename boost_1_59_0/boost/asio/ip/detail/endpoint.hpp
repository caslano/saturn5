//
// ip/detail/endpoint.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_DETAIL_ENDPOINT_HPP
#define BOOST_ASIO_IP_DETAIL_ENDPOINT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <string>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/detail/winsock_init.hpp>
#include <boost/system/error_code.hpp>
#include <boost/asio/ip/address.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {
namespace detail {

// Helper class for implementating an IP endpoint.
class endpoint
{
public:
  // Default constructor.
  BOOST_ASIO_DECL endpoint() BOOST_ASIO_NOEXCEPT;

  // Construct an endpoint using a family and port number.
  BOOST_ASIO_DECL endpoint(int family,
      unsigned short port_num) BOOST_ASIO_NOEXCEPT;

  // Construct an endpoint using an address and port number.
  BOOST_ASIO_DECL endpoint(const boost::asio::ip::address& addr,
      unsigned short port_num) BOOST_ASIO_NOEXCEPT;

  // Copy constructor.
  endpoint(const endpoint& other) BOOST_ASIO_NOEXCEPT
    : data_(other.data_)
  {
  }

  // Assign from another endpoint.
  endpoint& operator=(const endpoint& other) BOOST_ASIO_NOEXCEPT
  {
    data_ = other.data_;
    return *this;
  }

  // Get the underlying endpoint in the native type.
  boost::asio::detail::socket_addr_type* data() BOOST_ASIO_NOEXCEPT
  {
    return &data_.base;
  }

  // Get the underlying endpoint in the native type.
  const boost::asio::detail::socket_addr_type* data() const BOOST_ASIO_NOEXCEPT
  {
    return &data_.base;
  }

  // Get the underlying size of the endpoint in the native type.
  std::size_t size() const BOOST_ASIO_NOEXCEPT
  {
    if (is_v4())
      return sizeof(boost::asio::detail::sockaddr_in4_type);
    else
      return sizeof(boost::asio::detail::sockaddr_in6_type);
  }

  // Set the underlying size of the endpoint in the native type.
  BOOST_ASIO_DECL void resize(std::size_t new_size);

  // Get the capacity of the endpoint in the native type.
  std::size_t capacity() const BOOST_ASIO_NOEXCEPT
  {
    return sizeof(data_);
  }

  // Get the port associated with the endpoint.
  BOOST_ASIO_DECL unsigned short port() const BOOST_ASIO_NOEXCEPT;

  // Set the port associated with the endpoint.
  BOOST_ASIO_DECL void port(unsigned short port_num) BOOST_ASIO_NOEXCEPT;

  // Get the IP address associated with the endpoint.
  BOOST_ASIO_DECL boost::asio::ip::address address() const BOOST_ASIO_NOEXCEPT;

  // Set the IP address associated with the endpoint.
  BOOST_ASIO_DECL void address(
      const boost::asio::ip::address& addr) BOOST_ASIO_NOEXCEPT;

  // Compare two endpoints for equality.
  BOOST_ASIO_DECL friend bool operator==(const endpoint& e1,
      const endpoint& e2) BOOST_ASIO_NOEXCEPT;

  // Compare endpoints for ordering.
  BOOST_ASIO_DECL friend bool operator<(const endpoint& e1,
      const endpoint& e2) BOOST_ASIO_NOEXCEPT;

  // Determine whether the endpoint is IPv4.
  bool is_v4() const BOOST_ASIO_NOEXCEPT
  {
    return data_.base.sa_family == BOOST_ASIO_OS_DEF(AF_INET);
  }

#if !defined(BOOST_ASIO_NO_IOSTREAM)
  // Convert to a string.
  BOOST_ASIO_DECL std::string to_string() const;
#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

private:
  // The underlying IP socket address.
  union data_union
  {
    boost::asio::detail::socket_addr_type base;
    boost::asio::detail::sockaddr_in4_type v4;
    boost::asio::detail::sockaddr_in6_type v6;
  } data_;
};

} // namespace detail
} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/ip/detail/impl/endpoint.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_IP_DETAIL_ENDPOINT_HPP

/* endpoint.hpp
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
*/