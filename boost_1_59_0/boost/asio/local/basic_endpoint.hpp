//
// local/basic_endpoint.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Derived from a public domain implementation written by Daniel Casimiro.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_LOCAL_BASIC_ENDPOINT_HPP
#define BOOST_ASIO_LOCAL_BASIC_ENDPOINT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_LOCAL_SOCKETS) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/local/detail/endpoint.hpp>

#if !defined(BOOST_ASIO_NO_IOSTREAM)
# include <iosfwd>
#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace local {

/// Describes an endpoint for a UNIX socket.
/**
 * The boost::asio::local::basic_endpoint class template describes an endpoint
 * that may be associated with a particular UNIX socket.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 *
 * @par Concepts:
 * Endpoint.
 */
template <typename Protocol>
class basic_endpoint
{
public:
  /// The protocol type associated with the endpoint.
  typedef Protocol protocol_type;

  /// The type of the endpoint structure. This type is dependent on the
  /// underlying implementation of the socket layer.
#if defined(GENERATING_DOCUMENTATION)
  typedef implementation_defined data_type;
#else
  typedef boost::asio::detail::socket_addr_type data_type;
#endif

  /// Default constructor.
  basic_endpoint() BOOST_ASIO_NOEXCEPT
  {
  }

  /// Construct an endpoint using the specified path name.
  basic_endpoint(const char* path_name)
    : impl_(path_name)
  {
  }

  /// Construct an endpoint using the specified path name.
  basic_endpoint(const std::string& path_name)
    : impl_(path_name)
  {
  }

  #if defined(BOOST_ASIO_HAS_STRING_VIEW)
  /// Construct an endpoint using the specified path name.
  basic_endpoint(string_view path_name)
    : impl_(path_name)
  {
  }
  #endif // defined(BOOST_ASIO_HAS_STRING_VIEW)

  /// Copy constructor.
  basic_endpoint(const basic_endpoint& other)
    : impl_(other.impl_)
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  /// Move constructor.
  basic_endpoint(basic_endpoint&& other)
    : impl_(other.impl_)
  {
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  /// Assign from another endpoint.
  basic_endpoint& operator=(const basic_endpoint& other)
  {
    impl_ = other.impl_;
    return *this;
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  /// Move-assign from another endpoint.
  basic_endpoint& operator=(basic_endpoint&& other)
  {
    impl_ = other.impl_;
    return *this;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  /// The protocol associated with the endpoint.
  protocol_type protocol() const
  {
    return protocol_type();
  }

  /// Get the underlying endpoint in the native type.
  data_type* data()
  {
    return impl_.data();
  }

  /// Get the underlying endpoint in the native type.
  const data_type* data() const
  {
    return impl_.data();
  }

  /// Get the underlying size of the endpoint in the native type.
  std::size_t size() const
  {
    return impl_.size();
  }

  /// Set the underlying size of the endpoint in the native type.
  void resize(std::size_t new_size)
  {
    impl_.resize(new_size);
  }

  /// Get the capacity of the endpoint in the native type.
  std::size_t capacity() const
  {
    return impl_.capacity();
  }

  /// Get the path associated with the endpoint.
  std::string path() const
  {
    return impl_.path();
  }

  /// Set the path associated with the endpoint.
  void path(const char* p)
  {
    impl_.path(p);
  }

  /// Set the path associated with the endpoint.
  void path(const std::string& p)
  {
    impl_.path(p);
  }

  /// Compare two endpoints for equality.
  friend bool operator==(const basic_endpoint<Protocol>& e1,
      const basic_endpoint<Protocol>& e2)
  {
    return e1.impl_ == e2.impl_;
  }

  /// Compare two endpoints for inequality.
  friend bool operator!=(const basic_endpoint<Protocol>& e1,
      const basic_endpoint<Protocol>& e2)
  {
    return !(e1.impl_ == e2.impl_);
  }

  /// Compare endpoints for ordering.
  friend bool operator<(const basic_endpoint<Protocol>& e1,
      const basic_endpoint<Protocol>& e2)
  {
    return e1.impl_ < e2.impl_;
  }

  /// Compare endpoints for ordering.
  friend bool operator>(const basic_endpoint<Protocol>& e1,
      const basic_endpoint<Protocol>& e2)
  {
    return e2.impl_ < e1.impl_;
  }

  /// Compare endpoints for ordering.
  friend bool operator<=(const basic_endpoint<Protocol>& e1,
      const basic_endpoint<Protocol>& e2)
  {
    return !(e2 < e1);
  }

  /// Compare endpoints for ordering.
  friend bool operator>=(const basic_endpoint<Protocol>& e1,
      const basic_endpoint<Protocol>& e2)
  {
    return !(e1 < e2);
  }

private:
  // The underlying UNIX domain endpoint.
  boost::asio::local::detail::endpoint impl_;
};

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
 * @relates boost::asio::local::basic_endpoint
 */
template <typename Elem, typename Traits, typename Protocol>
std::basic_ostream<Elem, Traits>& operator<<(
    std::basic_ostream<Elem, Traits>& os,
    const basic_endpoint<Protocol>& endpoint)
{
  os << endpoint.path();
  return os;
}

} // namespace local
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_LOCAL_SOCKETS)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_LOCAL_BASIC_ENDPOINT_HPP

/* basic_endpoint.hpp
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
*/