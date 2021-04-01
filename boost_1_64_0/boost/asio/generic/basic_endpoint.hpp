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
FzMz2H1LnR0OXxSBXCTPFdIFCIOAO5mh12Pvywj/RmPkoypsatM/RLSNuZ5dCeZ8z5o51Sz1AUM2879XuOBU21M9HS5ktPt3FWbW61B77Q0tKnm/+tDsthUIb79kTULKeQ92SDAVzbQOeZr7Qn2lGqv4b4iv6t8/7EFA0K0hMJEDQMrpBddFNrBbzcOLde9VseBizvMMa6cOhzjeXgXAjLZCeG4mcAJyzjJ5CA5NPYco1yUQvTvpZnepxn56pNJYpbEhjgUryOMxi2bWRtw1RIkcKOod8vFtG48zFSJkybphPaE0vM8IBqW9HqcqNK8ZBeCDOkOX8vQpUtcdClA8996Wig2pzpumWZPPZEBNBQ5zwBGQJM9m8oDcyxv8vnlKprnl2jM9GCmuKpIYQRQ0v3xixOi36D3U6f+SQzLzeNAHNSQnV+YOVi10IOhvy3vOUudLnMIIo6bg7zKREPQ1QcZEzdt4zGRwM2ZVdJbBeste2E1p5hKL5dOx1L01F1BTUf0hukHEuUUjGhItoMERyPApxIBBcBthUAp1uUCNjfhs5daBo+uRoyzvCg==
*/