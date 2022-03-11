//
// ip/detail/endpoint.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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