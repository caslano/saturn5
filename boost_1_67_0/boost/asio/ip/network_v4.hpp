//
// ip/network_v4.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
    return network_v4(network(), netmask());
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