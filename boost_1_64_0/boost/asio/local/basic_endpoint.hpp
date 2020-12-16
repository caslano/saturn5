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
/Npg/kLcssPjVh1bvQ2ESxeZB0bZMhrIjKcZma8c/+A8OvTjrvrD2+6R0dOVF5Gu2Ot8XkTaNKBzzuxRTZvqD7tn73ukrSgibbG1F0UR6dJAzr2yjmq6VH9YW/POqMh0fYZbXUS6mt7W1AXjj8zDksZIBc701n3N9PbU9HIt3KNey/3tfnRk2j8nbH1E2mNrv+od9/RBSa8GMmlE5mumMXhP0Y+76I9I1zVjoqdrV0S6Ymv7dkWkSwOZdCFzVNNl9LvGnQ5pujIxrTRdEwfR95p0sZ+t432pcmDj7xbOZ/QpxwQ8PtdxjAOYvxEf63GHfvccFN7FouaZhvGbsQy/2PfLPlVXY/T53oy7+3VsbJDIPWkNJF4rMfb4+GHSvWMs42wyxr6FEfa0NOc7oXMe2yc69nCkXeg71lkdYn9vvF+un9Lo2EVwXzN0hvdzZh/fomMDAW7U70iXwRNIc94TwfykjhaXVlc3sNduqcie49N81bB9zFiQpWNBHflrs/g9H74vpBmzvkD8FzAXs5eZv2Axp5Apbubb4CKRqfHZ3zamUR7GjtNxo4SitMTktIQhaYlJOs7D+BEmOA6p8vPHBceHvmWFjw91U5n1RmfdK6hLSxjBv8g1pHe70Vv3idEbNgaalB2456/HMPZkf6s8/0n3t8q8KHu7LntCZKy/jwrYn1P7F2o/FOY/+Um3//ewq7/rWeEwZSN8j+cjyBT8Olg2qqOOhbR21TlT3zRccqPtj75TOcqtuw04ND5yDORLZItC8Wp0DATZhsZA1D8Le3AO4MIVS8zaMeNvys+iozRGovdY5+TJNV1p3zEhcl86PK26UNpjGqMIyLeIeq9OFv/Y9rCLGMNQt/QG7t80naybGkfBhh/78CcN651p0PGDBtKg8kNNu/Arsb/u89jXVOVzzNyQh8W+zzEnxbknJPfZhGnj+x6Tx7ayM1SGuDPD/Cnc2eGnlTXUF2rnKkw793sJt0N0X9pD9/lcVLoiOD88F4b7DVO/PJhi2r4q084+KDpf89lt1MOUg5KJgXnYaXG9U4fQ46S04p+E1pFzwbXfeFTC94icc61xfkD8B0l71ZNy3ULHya8Xo+2WslbnXRdZjewF6ph3XRelnKxzjp1EfNty3A+tO+QX7pqXpo9zuwfnVE99yr3n5Txjd+9xeUjLYxeNfGfMJxm8jz0t5dEeMSKjRthqo+YtZVFlu3jOZ+8p/p0aqE/ZznF8Tb99DW2TNa6PHx+QHqvPVsN1X/GCQFwXVlRUFi80W0OChcX0r95rIpdIuGwrM7Q3p+rqiAzPNeTNFccH5wd0ilg3I9/xmriPujPvV0/SvaI0PRdhOlAe6gPpsT9Sen+P0DQ8gKyjbdewfj37zzlHKPZ5xRpvR9l034feU/WMPq7XUfk7u298RuK9xH6PW1hRGLwfjc6XI1zgu7zOlaoW+yzfCK7axxfnPQ/HhM02c/urxH7AGmP5zNr77z1ru7VrdE00umQOjV/ndi0V+1zfGCuBfdYSos6b82v7e47InuWzd27uS6uo8wZUZ5bX/DkzL2KbyLXzvWq1cc4nILx7XVqWtLehvJBP2QsXVbjnFbjDrdQ6cI/0dTL4a2THumWlnfKba7i+QZgweRKmaWu4p7nD0M55z319TO5XnFkXt13sbczc1zVi76T+YvdcJzdf/Mp5X2kfUR4c/YxpEz6QOD5jXR/Qj5vRL/OJ7MP4dp2g84nWtHXNJ6rD/WFMoL1Ykxl1PpHqeP+E4HyiNTPSUlMj5hPp+xL9jTGONYWNPz/rfKGIORtzPeb2FTUwt6/MY25flcfcvm74rTTPdhHl1PSHlEf8pTyizznfw1XuvNfLa18=
*/