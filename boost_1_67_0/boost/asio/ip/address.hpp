//
// ip/address.hpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_ADDRESS_HPP
#define BOOST_ASIO_IP_ADDRESS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <string>
#include <boost/asio/detail/throw_exception.hpp>
#include <boost/asio/detail/string_view.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/system/error_code.hpp>
#include <boost/asio/ip/address_v4.hpp>
#include <boost/asio/ip/address_v6.hpp>
#include <boost/asio/ip/bad_address_cast.hpp>

#if !defined(BOOST_ASIO_NO_IOSTREAM)
# include <iosfwd>
#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

/// Implements version-independent IP addresses.
/**
 * The boost::asio::ip::address class provides the ability to use either IP
 * version 4 or version 6 addresses.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 */
class address
{
public:
  /// Default constructor.
  BOOST_ASIO_DECL address() BOOST_ASIO_NOEXCEPT;

  /// Construct an address from an IPv4 address.
  BOOST_ASIO_DECL address(
      const boost::asio::ip::address_v4& ipv4_address) BOOST_ASIO_NOEXCEPT;

  /// Construct an address from an IPv6 address.
  BOOST_ASIO_DECL address(
      const boost::asio::ip::address_v6& ipv6_address) BOOST_ASIO_NOEXCEPT;

  /// Copy constructor.
  BOOST_ASIO_DECL address(const address& other) BOOST_ASIO_NOEXCEPT;

#if defined(BOOST_ASIO_HAS_MOVE)
  /// Move constructor.
  BOOST_ASIO_DECL address(address&& other) BOOST_ASIO_NOEXCEPT;
#endif // defined(BOOST_ASIO_HAS_MOVE)

  /// Assign from another address.
  BOOST_ASIO_DECL address& operator=(const address& other) BOOST_ASIO_NOEXCEPT;

#if defined(BOOST_ASIO_HAS_MOVE)
  /// Move-assign from another address.
  BOOST_ASIO_DECL address& operator=(address&& other) BOOST_ASIO_NOEXCEPT;
#endif // defined(BOOST_ASIO_HAS_MOVE)

  /// Assign from an IPv4 address.
  BOOST_ASIO_DECL address& operator=(
      const boost::asio::ip::address_v4& ipv4_address) BOOST_ASIO_NOEXCEPT;

  /// Assign from an IPv6 address.
  BOOST_ASIO_DECL address& operator=(
      const boost::asio::ip::address_v6& ipv6_address) BOOST_ASIO_NOEXCEPT;

  /// Get whether the address is an IP version 4 address.
  bool is_v4() const BOOST_ASIO_NOEXCEPT
  {
    return type_ == ipv4;
  }

  /// Get whether the address is an IP version 6 address.
  bool is_v6() const BOOST_ASIO_NOEXCEPT
  {
    return type_ == ipv6;
  }

  /// Get the address as an IP version 4 address.
  BOOST_ASIO_DECL boost::asio::ip::address_v4 to_v4() const;

  /// Get the address as an IP version 6 address.
  BOOST_ASIO_DECL boost::asio::ip::address_v6 to_v6() const;

  /// Get the address as a string.
  BOOST_ASIO_DECL std::string to_string() const;

#if !defined(BOOST_ASIO_NO_DEPRECATED)
  /// (Deprecated: Use other overload.) Get the address as a string.
  BOOST_ASIO_DECL std::string to_string(boost::system::error_code& ec) const;

  /// (Deprecated: Use make_address().) Create an address from an IPv4 address
  /// string in dotted decimal form, or from an IPv6 address in hexadecimal
  /// notation.
  static address from_string(const char* str);

  /// (Deprecated: Use make_address().) Create an address from an IPv4 address
  /// string in dotted decimal form, or from an IPv6 address in hexadecimal
  /// notation.
  static address from_string(const char* str, boost::system::error_code& ec);

  /// (Deprecated: Use make_address().) Create an address from an IPv4 address
  /// string in dotted decimal form, or from an IPv6 address in hexadecimal
  /// notation.
  static address from_string(const std::string& str);

  /// (Deprecated: Use make_address().) Create an address from an IPv4 address
  /// string in dotted decimal form, or from an IPv6 address in hexadecimal
  /// notation.
  static address from_string(
      const std::string& str, boost::system::error_code& ec);
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

  /// Determine whether the address is a loopback address.
  BOOST_ASIO_DECL bool is_loopback() const BOOST_ASIO_NOEXCEPT;

  /// Determine whether the address is unspecified.
  BOOST_ASIO_DECL bool is_unspecified() const BOOST_ASIO_NOEXCEPT;

  /// Determine whether the address is a multicast address.
  BOOST_ASIO_DECL bool is_multicast() const BOOST_ASIO_NOEXCEPT;

  /// Compare two addresses for equality.
  BOOST_ASIO_DECL friend bool operator==(const address& a1,
      const address& a2) BOOST_ASIO_NOEXCEPT;

  /// Compare two addresses for inequality.
  friend bool operator!=(const address& a1,
      const address& a2) BOOST_ASIO_NOEXCEPT
  {
    return !(a1 == a2);
  }

  /// Compare addresses for ordering.
  BOOST_ASIO_DECL friend bool operator<(const address& a1,
      const address& a2) BOOST_ASIO_NOEXCEPT;

  /// Compare addresses for ordering.
  friend bool operator>(const address& a1,
      const address& a2) BOOST_ASIO_NOEXCEPT
  {
    return a2 < a1;
  }

  /// Compare addresses for ordering.
  friend bool operator<=(const address& a1,
      const address& a2) BOOST_ASIO_NOEXCEPT
  {
    return !(a2 < a1);
  }

  /// Compare addresses for ordering.
  friend bool operator>=(const address& a1,
      const address& a2) BOOST_ASIO_NOEXCEPT
  {
    return !(a1 < a2);
  }

private:
  // The type of the address.
  enum { ipv4, ipv6 } type_;

  // The underlying IPv4 address.
  boost::asio::ip::address_v4 ipv4_address_;

  // The underlying IPv6 address.
  boost::asio::ip::address_v6 ipv6_address_;
};

/// Create an address from an IPv4 address string in dotted decimal form,
/// or from an IPv6 address in hexadecimal notation.
/**
 * @relates address
 */
BOOST_ASIO_DECL address make_address(const char* str);

/// Create an address from an IPv4 address string in dotted decimal form,
/// or from an IPv6 address in hexadecimal notation.
/**
 * @relates address
 */
BOOST_ASIO_DECL address make_address(const char* str,
    boost::system::error_code& ec) BOOST_ASIO_NOEXCEPT;

/// Create an address from an IPv4 address string in dotted decimal form,
/// or from an IPv6 address in hexadecimal notation.
/**
 * @relates address
 */
BOOST_ASIO_DECL address make_address(const std::string& str);

/// Create an address from an IPv4 address string in dotted decimal form,
/// or from an IPv6 address in hexadecimal notation.
/**
 * @relates address
 */
BOOST_ASIO_DECL address make_address(const std::string& str,
    boost::system::error_code& ec) BOOST_ASIO_NOEXCEPT;

#if defined(BOOST_ASIO_HAS_STRING_VIEW) \
  || defined(GENERATING_DOCUMENTATION)

/// Create an address from an IPv4 address string in dotted decimal form,
/// or from an IPv6 address in hexadecimal notation.
/**
 * @relates address
 */
BOOST_ASIO_DECL address make_address(string_view str);

/// Create an address from an IPv4 address string in dotted decimal form,
/// or from an IPv6 address in hexadecimal notation.
/**
 * @relates address
 */
BOOST_ASIO_DECL address make_address(string_view str,
    boost::system::error_code& ec) BOOST_ASIO_NOEXCEPT;

#endif // defined(BOOST_ASIO_HAS_STRING_VIEW)
       //  || defined(GENERATING_DOCUMENTATION)

#if !defined(BOOST_ASIO_NO_IOSTREAM)

/// Output an address as a string.
/**
 * Used to output a human-readable string for a specified address.
 *
 * @param os The output stream to which the string will be written.
 *
 * @param addr The address to be written.
 *
 * @return The output stream.
 *
 * @relates boost::asio::ip::address
 */
template <typename Elem, typename Traits>
std::basic_ostream<Elem, Traits>& operator<<(
    std::basic_ostream<Elem, Traits>& os, const address& addr);

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/ip/impl/address.hpp>
#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/ip/impl/address.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_IP_ADDRESS_HPP

/* address.hpp
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
*/