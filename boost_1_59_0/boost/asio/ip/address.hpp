//
// ip/address.hpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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

#if defined(BOOST_ASIO_HAS_STD_HASH)
# include <functional>
#endif // defined(BOOST_ASIO_HAS_STD_HASH)

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

#if defined(BOOST_ASIO_HAS_STD_HASH)
namespace std {

template <>
struct hash<boost::asio::ip::address>
{
  std::size_t operator()(const boost::asio::ip::address& addr)
    const BOOST_ASIO_NOEXCEPT
  {
    return addr.is_v4()
      ? std::hash<boost::asio::ip::address_v4>()(addr.to_v4())
      : std::hash<boost::asio::ip::address_v6>()(addr.to_v6());
  }
};

} // namespace std
#endif // defined(BOOST_ASIO_HAS_STD_HASH)

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/ip/impl/address.hpp>
#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/ip/impl/address.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_IP_ADDRESS_HPP

/* address.hpp
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
*/