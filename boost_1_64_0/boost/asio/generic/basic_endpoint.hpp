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
4h/KeHjAiQ2EIyz2CHGuubFLwZ+hdApDmc2JLWJee0upSUWod8bN4MP9ZW39XiAeZbG5pmq7S3/+s9wvynx/9T3Bn/m++CHUzW878b4YZY91Nsre8v4e5ctreeqalKlcK1Dv9KXc5FqR6d0/1uyqnbTwXf/DoKGgz/OFRlFsB+1k6ayFQdoJ5ceqsrxVwtcJf1Is+HVlvUjxZ0o4F+HdEt5u227KFP9ICW9G+FMSvtnabthOb5L4a9luNPnhQdsJeFQ7ETsTtgPlW4lt4AvCV6LqvCkT5Ql6BLQGFOQbkoVtey0ROJ9X1nTppVVVPE/X2gaygSg7XEPZqbZibQPzbdpAXpA2kNLTJb8n2Aa+AuqJNpAT10EbqNlWE6wNQF7V0SqEyyV8q+5d+Yby0oqS9nPFJd7PNqHJD1d96y0JR9i2CV8gfxJfwzaiyU+wtgm2sWskvo5tQuMfF6xNgCe0saNO+LYEHTteE54oS/6S0Y4iwPfX2Lax482LNH602Q5ImV/w+DFD8x3PttNbO4cOdDM2HLLi7dqOWKyUFNcUS7mtjbO0Gcr1DmIP4TLYQyAN5tO4Z5wXRX0oFAO6CXrlOOtVKTvH4HPQjbKeYLrNCqab8p9L3cIp5AZ9Errl2euGLWBHnSgT3mWdtHqcE8NzbkCpoDdAEYHngKNOqh7Rvi16Qc7Y9z8l4e/Z9t14F/nZ1xMDdSXh7zr23Z0Sf1TCeep+6Za+66Od3Q0S/7RrCcqqiGeelyu5wSgf8OGvn0nYhxYYof/eUNkJRibI/AT7Zh5ew4gh13pBogf67uLYMyjow9Ga7eDWmGExY8Rs0Mlm8JTcc4CyGfyThPs62gz+TuIj7HQWO0LtOXQO91oGpdcAe8WGPnagPk1jh3WcyLMZJwpsxgnVH9kRt4HiecauG+2rIcGpfan+aG5jyk/iPSK72pWp/CRq6SU5zTMY71N+D++WcDGeErAQRbmhL8o4exa0thPjrV2ZqWe1qf/nsacG9Ekl9kJZZPUzlUVxSUkhnxp276qQX8qMUna5V0p4lWsqLEKWyrMS19GmLvVJm7IdRxapdEao/rpawncwrMn30/evyvVAaYPAfOF3h73Bdlym0kxX7fQSSWMx+tU0XTqoaqbjAy5ry0/YWfQv9lGmM1hkInxiv6t9xytjwWaJ7x32rMun+iyuqm+Et0j8Otc4lMlikDbGrPGx37EfvxngQyhO4pW+2Esfj6tqLNgcyLePadwhMrlItTdaXQ9eR5+U63e6ihGzDffQjSWqH6+W9AfalY9h3rCVbzPjWDdnJe1bYU/ks9RPHMaffPS11/tgLj8a40/UDPXe78HYNr+dGs958HxBeCoVz2Ly+MiTDqOfxzLB465/xhMTqfjiBhnTmt+XaUXXf8WUluKp0Hii6j/jdL89fTW9bxjo6RHtqPthpgW+Sy33Yz9+PFP6MObgHffjwBw83Wecg+cY39+qfq2eoZZ1mPQJ01iI9m0aCw9BXqyUORauAfVB/2/2OfV/tTA3jwNqLPy1yGa7EtVYqKWX7LQ2Z/wwxzUW422fwcv08c7zZfAY5svW8YO8WSbeMoQtYwR5s028foSd/N4O6a/83qr+hH/U+H9O0pnq6qsb/x/MRB1lhtZurO3k4q/XcQ3lYW1j/iBtbF8/l/zu4ZruFpAXbSyvv2Mb46Le8VlD2bHqGXG9hLebn7WqTdZJ/Do8h3rxOaOlkdm+5ukffE23XeIr2SY1+ZGO88ItEr9Va6Pg73idDx79Ot+5jZp4C4K1URNvUZA2+qLw9WJYlQnaHr5DwVhxKqFt/eceGxnt7h0Z7vH1jfR6oiY77DdY9ynY1m+WdK82+G4+1PE=
*/