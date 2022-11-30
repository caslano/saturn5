//
// local/detail/endpoint.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Derived from a public domain implementation written by Daniel Casimiro.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_LOCAL_DETAIL_ENDPOINT_HPP
#define BOOST_ASIO_LOCAL_DETAIL_ENDPOINT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_LOCAL_SOCKETS)

#include <cstddef>
#include <string>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/detail/string_view.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace local {
namespace detail {

// Helper class for implementing a UNIX domain endpoint.
class endpoint
{
public:
  // Default constructor.
  BOOST_ASIO_DECL endpoint();

  // Construct an endpoint using the specified path name.
  BOOST_ASIO_DECL endpoint(const char* path_name);

  // Construct an endpoint using the specified path name.
  BOOST_ASIO_DECL endpoint(const std::string& path_name);

  #if defined(BOOST_ASIO_HAS_STRING_VIEW)
  // Construct an endpoint using the specified path name.
  BOOST_ASIO_DECL endpoint(string_view path_name);
  #endif // defined(BOOST_ASIO_HAS_STRING_VIEW)

  // Copy constructor.
  endpoint(const endpoint& other)
    : data_(other.data_),
      path_length_(other.path_length_)
  {
  }

  // Assign from another endpoint.
  endpoint& operator=(const endpoint& other)
  {
    data_ = other.data_;
    path_length_ = other.path_length_;
    return *this;
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
    return path_length_
      + offsetof(boost::asio::detail::sockaddr_un_type, sun_path);
  }

  // Set the underlying size of the endpoint in the native type.
  BOOST_ASIO_DECL void resize(std::size_t size);

  // Get the capacity of the endpoint in the native type.
  std::size_t capacity() const
  {
    return sizeof(boost::asio::detail::sockaddr_un_type);
  }

  // Get the path associated with the endpoint.
  BOOST_ASIO_DECL std::string path() const;

  // Set the path associated with the endpoint.
  BOOST_ASIO_DECL void path(const char* p);

  // Set the path associated with the endpoint.
  BOOST_ASIO_DECL void path(const std::string& p);

  // Compare two endpoints for equality.
  BOOST_ASIO_DECL friend bool operator==(
      const endpoint& e1, const endpoint& e2);

  // Compare endpoints for ordering.
  BOOST_ASIO_DECL friend bool operator<(
      const endpoint& e1, const endpoint& e2);

private:
  // The underlying UNIX socket address.
  union data_union
  {
    boost::asio::detail::socket_addr_type base;
    boost::asio::detail::sockaddr_un_type local;
  } data_;

  // The length of the path associated with the endpoint.
  std::size_t path_length_;

  // Initialise with a specified path.
  BOOST_ASIO_DECL void init(const char* path, std::size_t path_length);
};

} // namespace detail
} // namespace local
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/local/detail/impl/endpoint.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_HAS_LOCAL_SOCKETS)

#endif // BOOST_ASIO_LOCAL_DETAIL_ENDPOINT_HPP

/* endpoint.hpp
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
*/