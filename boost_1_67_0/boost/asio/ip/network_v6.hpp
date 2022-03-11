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
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
*/