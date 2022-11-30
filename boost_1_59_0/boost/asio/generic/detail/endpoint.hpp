//
// generic/detail/endpoint.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_GENERIC_DETAIL_ENDPOINT_HPP
#define BOOST_ASIO_GENERIC_DETAIL_ENDPOINT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <cstddef>
#include <boost/asio/detail/socket_types.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace generic {
namespace detail {

// Helper class for implementing a generic socket endpoint.
class endpoint
{
public:
  // Default constructor.
  BOOST_ASIO_DECL endpoint();

  // Construct an endpoint from the specified raw bytes.
  BOOST_ASIO_DECL endpoint(const void* sock_addr,
      std::size_t sock_addr_size, int sock_protocol);

  // Copy constructor.
  endpoint(const endpoint& other)
    : data_(other.data_),
      size_(other.size_),
      protocol_(other.protocol_)
  {
  }

  // Assign from another endpoint.
  endpoint& operator=(const endpoint& other)
  {
    data_ = other.data_;
    size_ = other.size_;
    protocol_ = other.protocol_;
    return *this;
  }

  // Get the address family associated with the endpoint.
  int family() const
  {
    return data_.base.sa_family;
  }

  // Get the socket protocol associated with the endpoint.
  int protocol() const
  {
    return protocol_;
  }

  // Get the underlying endpoint in the native type.
  boost::asio::detail::socket_addr_type* data()
  {
    return &data_.base;
  }

  // Get the underlying endpoint in the native type.
  const boost::asio::detail::socket_addr_type* data() const
  {
    return &data_.base;
  }

  // Get the underlying size of the endpoint in the native type.
  std::size_t size() const
  {
    return size_;
  }

  // Set the underlying size of the endpoint in the native type.
  BOOST_ASIO_DECL void resize(std::size_t size);

  // Get the capacity of the endpoint in the native type.
  std::size_t capacity() const
  {
    return sizeof(boost::asio::detail::sockaddr_storage_type);
  }

  // Compare two endpoints for equality.
  BOOST_ASIO_DECL friend bool operator==(
      const endpoint& e1, const endpoint& e2);

  // Compare endpoints for ordering.
  BOOST_ASIO_DECL friend bool operator<(
      const endpoint& e1, const endpoint& e2);

private:
  // The underlying socket address.
  union data_union
  {
    boost::asio::detail::socket_addr_type base;
    boost::asio::detail::sockaddr_storage_type generic;
  } data_;

  // The length of the socket address stored in the endpoint.
  std::size_t size_;

  // The socket protocol associated with the endpoint.
  int protocol_;

  // Initialise with a specified memory.
  BOOST_ASIO_DECL void init(const void* sock_addr,
      std::size_t sock_addr_size, int sock_protocol);
};

} // namespace detail
} // namespace generic
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/generic/detail/impl/endpoint.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_GENERIC_DETAIL_ENDPOINT_HPP

/* endpoint.hpp
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
*/