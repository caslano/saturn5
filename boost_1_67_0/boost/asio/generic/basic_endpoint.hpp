//
// generic/basic_endpoint.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_GENERIC_BASIC_ENDPOINT_HPP
#define BOOST_ASIO_GENERIC_BASIC_ENDPOINT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/generic/detail/endpoint.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace generic {

/// Describes an endpoint for any socket type.
/**
 * The boost::asio::generic::basic_endpoint class template describes an endpoint
 * that may be associated with any socket type.
 *
 * @note The socket types sockaddr type must be able to fit into a
 * @c sockaddr_storage structure.
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

  /// Construct an endpoint from the specified socket address.
  basic_endpoint(const void* socket_address,
      std::size_t socket_address_size, int socket_protocol = 0)
    : impl_(socket_address, socket_address_size, socket_protocol)
  {
  }

  /// Construct an endpoint from the specific endpoint type.
  template <typename Endpoint>
  basic_endpoint(const Endpoint& endpoint)
    : impl_(endpoint.data(), endpoint.size(), endpoint.protocol().protocol())
  {
  }

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
    return protocol_type(impl_.family(), impl_.protocol());
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
  // The underlying generic endpoint.
  boost::asio::generic::detail::endpoint impl_;
};

} // namespace generic
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_GENERIC_BASIC_ENDPOINT_HPP

/* basic_endpoint.hpp
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
*/