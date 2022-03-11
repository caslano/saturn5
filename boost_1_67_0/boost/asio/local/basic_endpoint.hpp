//
// local/basic_endpoint.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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