//
// ip/network_v6.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
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
*/