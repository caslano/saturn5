//
// ip/network_v6.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2014 Oliver Kowalke (oliver dot kowalke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_NETWORK_V6_HPP
#define BOOST_ASIO_IP_NETWORK_V6_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <string>
#include <boost/asio/detail/string_view.hpp>
#include <boost/system/error_code.hpp>
#include <boost/asio/ip/address_v6_range.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

/// Represents an IPv6 network.
/**
 * The boost::asio::ip::network_v6 class provides the ability to use and
 * manipulate IP version 6 networks.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 */
class network_v6
{
public:
  /// Default constructor.
  network_v6() BOOST_ASIO_NOEXCEPT
    : address_(),
      prefix_length_(0)
  {
  }

  /// Construct a network based on the specified address and prefix length.
  BOOST_ASIO_DECL network_v6(const address_v6& addr,
      unsigned short prefix_len);

  /// Copy constructor.
  network_v6(const network_v6& other) BOOST_ASIO_NOEXCEPT
    : address_(other.address_),
      prefix_length_(other.prefix_length_)
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  /// Move constructor.
  network_v6(network_v6&& other) BOOST_ASIO_NOEXCEPT
    : address_(BOOST_ASIO_MOVE_CAST(address_v6)(other.address_)),
      prefix_length_(other.prefix_length_)
  {
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  /// Assign from another network.
  network_v6& operator=(const network_v6& other) BOOST_ASIO_NOEXCEPT
  {
    address_ = other.address_;
    prefix_length_ = other.prefix_length_;
    return *this;
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  /// Move-assign from another network.
  network_v6& operator=(network_v6&& other) BOOST_ASIO_NOEXCEPT
  {
    address_ = BOOST_ASIO_MOVE_CAST(address_v6)(other.address_);
    prefix_length_ = other.prefix_length_;
    return *this;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  /// Obtain the address object specified when the network object was created.
  address_v6 address() const BOOST_ASIO_NOEXCEPT
  {
    return address_;
  }

  /// Obtain the prefix length that was specified when the network object was
  /// created.
  unsigned short prefix_length() const BOOST_ASIO_NOEXCEPT
  {
    return prefix_length_;
  }

  /// Obtain an address object that represents the network address.
  BOOST_ASIO_DECL address_v6 network() const BOOST_ASIO_NOEXCEPT;

  /// Obtain an address range corresponding to the hosts in the network.
  BOOST_ASIO_DECL address_v6_range hosts() const BOOST_ASIO_NOEXCEPT;

  /// Obtain the true network address, omitting any host bits.
  network_v6 canonical() const BOOST_ASIO_NOEXCEPT
  {
    return network_v6(network(), prefix_length());
  }

  /// Test if network is a valid host address.
  bool is_host() const BOOST_ASIO_NOEXCEPT
  {
    return prefix_length_ == 128;
  }

  /// Test if a network is a real subnet of another network.
  BOOST_ASIO_DECL bool is_subnet_of(const network_v6& other) const;

  /// Get the network as an address in dotted decimal format.
  BOOST_ASIO_DECL std::string to_string() const;

  /// Get the network as an address in dotted decimal format.
  BOOST_ASIO_DECL std::string to_string(boost::system::error_code& ec) const;

  /// Compare two networks for equality.
  friend bool operator==(const network_v6& a, const network_v6& b)
  {
    return a.address_ == b.address_ && a.prefix_length_ == b.prefix_length_;
  }

  /// Compare two networks for inequality.
  friend bool operator!=(const network_v6& a, const network_v6& b)
  {
    return !(a == b);
  }

private:
  address_v6 address_;
  unsigned short prefix_length_;
};

/// Create an IPv6 network from an address and prefix length.
/**
 * @relates address_v6
 */
inline network_v6 make_network_v6(
    const address_v6& addr, unsigned short prefix_len)
{
  return network_v6(addr, prefix_len);
}

/// Create an IPv6 network from a string containing IP address and prefix
/// length.
/**
 * @relates network_v6
 */
BOOST_ASIO_DECL network_v6 make_network_v6(const char* str);

/// Create an IPv6 network from a string containing IP address and prefix
/// length.
/**
 * @relates network_v6
 */
BOOST_ASIO_DECL network_v6 make_network_v6(
    const char* str, boost::system::error_code& ec);

/// Create an IPv6 network from a string containing IP address and prefix
/// length.
/**
 * @relates network_v6
 */
BOOST_ASIO_DECL network_v6 make_network_v6(const std::string& str);

/// Create an IPv6 network from a string containing IP address and prefix
/// length.
/**
 * @relates network_v6
 */
BOOST_ASIO_DECL network_v6 make_network_v6(
    const std::string& str, boost::system::error_code& ec);

#if defined(BOOST_ASIO_HAS_STRING_VIEW) \
  || defined(GENERATING_DOCUMENTATION)

/// Create an IPv6 network from a string containing IP address and prefix
/// length.
/**
 * @relates network_v6
 */
BOOST_ASIO_DECL network_v6 make_network_v6(string_view str);

/// Create an IPv6 network from a string containing IP address and prefix
/// length.
/**
 * @relates network_v6
 */
BOOST_ASIO_DECL network_v6 make_network_v6(
    string_view str, boost::system::error_code& ec);

#endif // defined(BOOST_ASIO_HAS_STRING_VIEW)
       //  || defined(GENERATING_DOCUMENTATION)

#if !defined(BOOST_ASIO_NO_IOSTREAM)

/// Output a network as a string.
/**
 * Used to output a human-readable string for a specified network.
 *
 * @param os The output stream to which the string will be written.
 *
 * @param net The network to be written.
 *
 * @return The output stream.
 *
 * @relates boost::asio::ip::address_v6
 */
template <typename Elem, typename Traits>
std::basic_ostream<Elem, Traits>& operator<<(
    std::basic_ostream<Elem, Traits>& os, const network_v6& net);

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/ip/impl/network_v6.hpp>
#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/ip/impl/network_v6.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_IP_NETWORK_V6_HPP

/* network_v6.hpp
/AH4MPgj8DHwafA74I/B74LPgKHyy/okkPSO8j8ve8QPijy/AheAL4A14CGwDXwRvBT8LbgHfAm8FfwdeDv4e8mvOrz+BmyX/AaC6yS/OdRLLjgPnAieAU4DzwLngPPB9eCZ4AZwIVgHLgAbQmHZsyrrQEA/1Bm1Z7WMdCaWg6ngDHAAOBNMB08DMyQcsj9okrf9VYj9LRb7WyL2t1TsrxIslPAYCfNc2ijPkuc2m3/LGowU0JC9/Gb4GGjyvSb2+LrY49/FHt+QevkHuBJ8E2wEDfLZYQL4YTAJ3AumgLeCqeAdYBrYDaaDj4KDwMfBAPgkmAX2gsPAn4A54CFwOPgKmAeahSgAk8AR4FBwJBgAR4FjwLHgAnAcuBQsBteA48H14AQwdHaB/I4vf3dGnV3wR9kj/bLo4wg4FfwTeBr4ZzAI/gVcDr4ieiGsnn8P1CPP75XnZ4G3yfPhUfW1AhwPwqvscTU4DawCK8DN4DKwFlwL1oEbwK3gRnAbuANcB14GngdeDZJG1cNG8E55zqPgReCT4CZpr9Wg6EN+b4XHRR/vkjNuOuVsmSvBEvBqcA54FXgOuAtcBe4G10i81ve00POfc3l+k/RLO8CbwXZwH9gBfha8BHxQ4g+AbeAj4KWW51eXeMv/QZF/j8j/YZF/r8j/UZH/BpH/RpF/r/UMB3n+cpf2GeRWHngOOAWskPIsAedKeL6ZHgzKfemvZF4de3Hpr26R53wcnA3eDp4BfgI8G+wCLwA/Cb4L/BR4I3in1PtdFvnLSr3lnyPyzxX5z5R8zxL5zxT554n8Z1nPAJHnrnTR+whpRyPB0Lm4cpaL5DNG+pcicL6EKyUcPuvkiDz/OjMc/X1vef5kcBQ4RfqxWWA5OFX6reny3FJQ6ULaUTnYIPebwZngFcL/PnCGPjND5qfAXJHDemZGjpxJMBwMgLnWvfYWvoNRe+3xVyQdcXGmM8rjS1dkSZcele4Ci3zBONNVx5muM850XXGm6+kj3bo4zyowzynw32M/p+BLu5LjPqvgeM8pOMSzY51VkLI7Oe7zCv5dZxWs3538H3FeQTxnFbQga+S8gtjnFHSR9gAUOq8g/rMK5JyCWGcUyPkE7mcTHNydfFznE8R7NsEbPNf7fILI2QQjr062nU+wgrDbGQXVVyf3+a34WOcT7II/ckZB39+N/185n+BByh19RsGT3Avyd8sV0ecTHN/ZBMXjU4xKqB3qgp6CjkJFE7gPtUC3QQegQ5B/YooxE1oPdUJd0JPQESh7EnHQOmgn1AU9CR2F8ianGMHJifMIElfiSlyJK3H9518p0DtO8f7/9k0mmLv/T3zv/2+nGHrN1rPyqn0GN6UY/DL4KoP9lmF6DcWmmo6d5lcum8J7WW7JVGteOqxrUj+m0n8mSX77Ev6JUd97WKh+p7pNxd2n0i7XaWcZubKO6U4VTk56l/nlAt8Buc8OkWy15s9Xzv0DxiOWdTR8YK4O8USeev3MGSp8MeFPqvAdScLDxfH9DbUsRo18f1zW7nLVNDbUtOn1MjtyVFkk7DNuyonsqXw1L7Q+V7b66D1br4X057OuM8yVtY+vqLiBSfONZsrxL/bOBD6q4gzgb4+EkAQIAUIgFAJyREAIh4iAGo5AkBQiN0olgRASCCSQcKloUARUrBQvtB6gCLSgpUoRFSXeFI/Sai1VFGqp9ariVWm9+n/ffjv7NrsbAqi99v0y+e/MfDNvrjfvmG9mBrv8e0afJvk71VVmjVBZf57nuQZYZUjG446sKYuZ4t7edaqkZbcoJJSVFMo2E758ZWm+yiFf7krmVVSKrlA252sncfR2XWRlqZvGS6ooY8L581c5bz4=
*/