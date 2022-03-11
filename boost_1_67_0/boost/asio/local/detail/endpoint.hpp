//
// local/detail/endpoint.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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