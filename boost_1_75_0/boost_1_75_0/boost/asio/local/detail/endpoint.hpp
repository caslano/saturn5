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
iebLGK2Br+S/8qnCJ/SQCGHBzosP9+X8mezAZP7ChBp9+8BDwbhjWm+9J7B80BFt4AnzeMRcxVfCQJn/Wr3puMzjBP5IKFkCVJeQs7qzr0yYXc/Pti0aWqCY0Fg4kIdBUJSm9HksTMUl3wDkj+ESvrYJ6iL8Vt9jPl9bHsB12Eb9OD7qyoSoev2Ia+FmmR7GNvgDA9Y9HvG37glvMMXfKjmh3wa4oJb8Gf17+LTrDix/qHWjNMqzNHxVn/hbNNiCq+Z4RR3S6nuWHGP7+Cy/wvpJ0rBbLI/ROHK9AiJ8R7MG0i2hdjIVw5cEy/XB4oJqL0MjPiaqT0TtRN5HPcs+Eli+B39q2zpVCHxYEjgSg4Ks/Scc1CsDy0tOLD5l7UOQ4eJqB/A5rb+HRgFBYRWB5VaAwGtQN/xp0zhcSsWa4fe528loYFye1lTiYiv5jSSy3rrVnBBy205WWleSlVbT8mI3i60V4njAFL6aK//UVBKJLGroq14xoRdZbl3eRUVm12CQsfgGE/mFJbw8Hr6O/lIZHwKDqzLhh6hCRpnCNwu/kxa+DtXrzGi7foP5aC9B7lk/8A8gitWB4KADr12/2a4vM78ijb1ZiC2iPdiUm0AuXbXdCDT++VXbz1DrOA2MPxMGxvHF1nafCQPjbw2HezPt6EgBOpAFzRdt6SufkWxWJDs2Ul2CE9Gzl4SfoyLEXmg8/3I3rCYX37O7
*/