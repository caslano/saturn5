//
// ip/network_v4.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2014 Oliver Kowalke (oliver dot kowalke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_NETWORK_V4_HPP
#define BOOST_ASIO_IP_NETWORK_V4_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <string>
#include <boost/asio/detail/string_view.hpp>
#include <boost/system/error_code.hpp>
#include <boost/asio/ip/address_v4_range.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

/// Represents an IPv4 network.
/**
 * The boost::asio::ip::network_v4 class provides the ability to use and
 * manipulate IP version 4 networks.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 */
class network_v4
{
public:
  /// Default constructor.
  network_v4() BOOST_ASIO_NOEXCEPT
    : address_(),
      prefix_length_(0)
  {
  }

  /// Construct a network based on the specified address and prefix length.
  BOOST_ASIO_DECL network_v4(const address_v4& addr,
      unsigned short prefix_len);

  /// Construct network based on the specified address and netmask.
  BOOST_ASIO_DECL network_v4(const address_v4& addr,
      const address_v4& mask);

  /// Copy constructor.
  network_v4(const network_v4& other) BOOST_ASIO_NOEXCEPT
    : address_(other.address_),
      prefix_length_(other.prefix_length_)
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  /// Move constructor.
  network_v4(network_v4&& other) BOOST_ASIO_NOEXCEPT
    : address_(BOOST_ASIO_MOVE_CAST(address_v4)(other.address_)),
      prefix_length_(other.prefix_length_)
  {
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  /// Assign from another network.
  network_v4& operator=(const network_v4& other) BOOST_ASIO_NOEXCEPT
  {
    address_ = other.address_;
    prefix_length_ = other.prefix_length_;
    return *this;
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  /// Move-assign from another network.
  network_v4& operator=(network_v4&& other) BOOST_ASIO_NOEXCEPT
  {
    address_ = BOOST_ASIO_MOVE_CAST(address_v4)(other.address_);
    prefix_length_ = other.prefix_length_;
    return *this;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  /// Obtain the address object specified when the network object was created.
  address_v4 address() const BOOST_ASIO_NOEXCEPT
  {
    return address_;
  }

  /// Obtain the prefix length that was specified when the network object was
  /// created.
  unsigned short prefix_length() const BOOST_ASIO_NOEXCEPT
  {
    return prefix_length_;
  }

  /// Obtain the netmask that was specified when the network object was created.
  BOOST_ASIO_DECL address_v4 netmask() const BOOST_ASIO_NOEXCEPT;

  /// Obtain an address object that represents the network address.
  address_v4 network() const BOOST_ASIO_NOEXCEPT
  {
    return address_v4(address_.to_uint() & netmask().to_uint());
  }

  /// Obtain an address object that represents the network's broadcast address.
  address_v4 broadcast() const BOOST_ASIO_NOEXCEPT
  {
    return address_v4(network().to_uint() | (netmask().to_uint() ^ 0xFFFFFFFF));
  }

  /// Obtain an address range corresponding to the hosts in the network.
  BOOST_ASIO_DECL address_v4_range hosts() const BOOST_ASIO_NOEXCEPT;

  /// Obtain the true network address, omitting any host bits.
  network_v4 canonical() const BOOST_ASIO_NOEXCEPT
  {
    return network_v4(network(), prefix_length());
  }

  /// Test if network is a valid host address.
  bool is_host() const BOOST_ASIO_NOEXCEPT
  {
    return prefix_length_ == 32;
  }

  /// Test if a network is a real subnet of another network.
  BOOST_ASIO_DECL bool is_subnet_of(const network_v4& other) const;

  /// Get the network as an address in dotted decimal format.
  BOOST_ASIO_DECL std::string to_string() const;

  /// Get the network as an address in dotted decimal format.
  BOOST_ASIO_DECL std::string to_string(boost::system::error_code& ec) const;

  /// Compare two networks for equality.
  friend bool operator==(const network_v4& a, const network_v4& b)
  {
    return a.address_ == b.address_ && a.prefix_length_ == b.prefix_length_;
  }

  /// Compare two networks for inequality.
  friend bool operator!=(const network_v4& a, const network_v4& b)
  {
    return !(a == b);
  }

private:
  address_v4 address_;
  unsigned short prefix_length_;
};

/// Create an IPv4 network from an address and prefix length.
/**
 * @relates address_v4
 */
inline network_v4 make_network_v4(
    const address_v4& addr, unsigned short prefix_len)
{
  return network_v4(addr, prefix_len);
}

/// Create an IPv4 network from an address and netmask.
/**
 * @relates address_v4
 */
inline network_v4 make_network_v4(
    const address_v4& addr, const address_v4& mask)
{
  return network_v4(addr, mask);
}

/// Create an IPv4 network from a string containing IP address and prefix
/// length.
/**
 * @relates network_v4
 */
BOOST_ASIO_DECL network_v4 make_network_v4(const char* str);

/// Create an IPv4 network from a string containing IP address and prefix
/// length.
/**
 * @relates network_v4
 */
BOOST_ASIO_DECL network_v4 make_network_v4(
    const char* str, boost::system::error_code& ec);

/// Create an IPv4 network from a string containing IP address and prefix
/// length.
/**
 * @relates network_v4
 */
BOOST_ASIO_DECL network_v4 make_network_v4(const std::string& str);

/// Create an IPv4 network from a string containing IP address and prefix
/// length.
/**
 * @relates network_v4
 */
BOOST_ASIO_DECL network_v4 make_network_v4(
    const std::string& str, boost::system::error_code& ec);

#if defined(BOOST_ASIO_HAS_STRING_VIEW) \
  || defined(GENERATING_DOCUMENTATION)

/// Create an IPv4 network from a string containing IP address and prefix
/// length.
/**
 * @relates network_v4
 */
BOOST_ASIO_DECL network_v4 make_network_v4(string_view str);

/// Create an IPv4 network from a string containing IP address and prefix
/// length.
/**
 * @relates network_v4
 */
BOOST_ASIO_DECL network_v4 make_network_v4(
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
 * @relates boost::asio::ip::address_v4
 */
template <typename Elem, typename Traits>
std::basic_ostream<Elem, Traits>& operator<<(
    std::basic_ostream<Elem, Traits>& os, const network_v4& net);

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/ip/impl/network_v4.hpp>
#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/ip/impl/network_v4.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_IP_NETWORK_V4_HPP

/* network_v4.hpp
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
*/