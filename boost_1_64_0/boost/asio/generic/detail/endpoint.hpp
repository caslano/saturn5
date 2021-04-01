//
// generic/detail/endpoint.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
hlCz6Nj9Ai5hp+hLooZBrppinQN3urugfmfugSbnuY3OtYwOBHQk4+ZvwGfazBhef3/bHAg8odq5vrOmIwDdX9fKOXUwNjwkJOp1BgbTANd/Am1TZ2BLcaH3LH05GLtiUmH04XCY5hOefIRVWi2Flnpo0z04Xk7KRC/3Ga3CsSUC1jq3qOA1e6B9Nbwi9HTnwRsvKqOD5VOkDcfUZZdwKrwqkBqTz7yXoMyl4p0oXpiSWDnbLbuMgQ8yVNdOMckc17M2PtxgJAgbv8uTgtAydLt4zJXVbKQLE400d8vh7clwIAlaSOowPA3ILSr1QaiBK7gqn3onHb9YD5CgIrLOk5nBBEwL8k6ghWeunkwMquWpjzufmU+MTGvQ27YqoATsmbJ05HfAU1sOv1sNCGioAsgzF1jAWVsFT42p4EKlyZLf8l/lp4N/Zjzbcv/fLK7nf40NZmhEX+GnrRe4s8fHQYQ71LrIRMl9mT+c+J4+mVLOphhj3o0crKvgCd3Q3IFQdyM7LRIw/nPZ3nOEf7xb5wjMc1mx2jv7ZnIDo9ys5Mf9JHa77YkKNydiUg==
*/