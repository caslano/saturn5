//
// ip/address_v6.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_ADDRESS_V6_HPP
#define BOOST_ASIO_IP_ADDRESS_V6_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <string>
#include <boost/asio/detail/array.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/detail/string_view.hpp>
#include <boost/asio/detail/winsock_init.hpp>
#include <boost/system/error_code.hpp>
#include <boost/asio/ip/address_v4.hpp>

#if !defined(BOOST_ASIO_NO_IOSTREAM)
# include <iosfwd>
#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

template <typename> class basic_address_iterator;

/// Implements IP version 6 style addresses.
/**
 * The boost::asio::ip::address_v6 class provides the ability to use and
 * manipulate IP version 6 addresses.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 */
class address_v6
{
public:
  /// The type used to represent an address as an array of bytes.
  /**
   * @note This type is defined in terms of the C++0x template @c std::array
   * when it is available. Otherwise, it uses @c boost:array.
   */
#if defined(GENERATING_DOCUMENTATION)
  typedef array<unsigned char, 16> bytes_type;
#else
  typedef boost::asio::detail::array<unsigned char, 16> bytes_type;
#endif

  /// Default constructor.
  BOOST_ASIO_DECL address_v6() BOOST_ASIO_NOEXCEPT;

  /// Construct an address from raw bytes and scope ID.
  BOOST_ASIO_DECL explicit address_v6(const bytes_type& bytes,
      unsigned long scope_id = 0);

  /// Copy constructor.
  BOOST_ASIO_DECL address_v6(const address_v6& other) BOOST_ASIO_NOEXCEPT;

#if defined(BOOST_ASIO_HAS_MOVE)
  /// Move constructor.
  BOOST_ASIO_DECL address_v6(address_v6&& other) BOOST_ASIO_NOEXCEPT;
#endif // defined(BOOST_ASIO_HAS_MOVE)

  /// Assign from another address.
  BOOST_ASIO_DECL address_v6& operator=(
      const address_v6& other) BOOST_ASIO_NOEXCEPT;

#if defined(BOOST_ASIO_HAS_MOVE)
  /// Move-assign from another address.
  BOOST_ASIO_DECL address_v6& operator=(address_v6&& other) BOOST_ASIO_NOEXCEPT;
#endif // defined(BOOST_ASIO_HAS_MOVE)

  /// The scope ID of the address.
  /**
   * Returns the scope ID associated with the IPv6 address.
   */
  unsigned long scope_id() const BOOST_ASIO_NOEXCEPT
  {
    return scope_id_;
  }

  /// The scope ID of the address.
  /**
   * Modifies the scope ID associated with the IPv6 address.
   */
  void scope_id(unsigned long id) BOOST_ASIO_NOEXCEPT
  {
    scope_id_ = id;
  }

  /// Get the address in bytes, in network byte order.
  BOOST_ASIO_DECL bytes_type to_bytes() const BOOST_ASIO_NOEXCEPT;

  /// Get the address as a string.
  BOOST_ASIO_DECL std::string to_string() const;

#if !defined(BOOST_ASIO_NO_DEPRECATED)
  /// (Deprecated: Use other overload.) Get the address as a string.
  BOOST_ASIO_DECL std::string to_string(boost::system::error_code& ec) const;

  /// (Deprecated: Use make_address_v6().) Create an IPv6 address from an IP
  /// address string.
  static address_v6 from_string(const char* str);

  /// (Deprecated: Use make_address_v6().) Create an IPv6 address from an IP
  /// address string.
  static address_v6 from_string(
      const char* str, boost::system::error_code& ec);

  /// (Deprecated: Use make_address_v6().) Create an IPv6 address from an IP
  /// address string.
  static address_v6 from_string(const std::string& str);

  /// (Deprecated: Use make_address_v6().) Create an IPv6 address from an IP
  /// address string.
  static address_v6 from_string(
      const std::string& str, boost::system::error_code& ec);

  /// (Deprecated: Use make_address_v4().) Converts an IPv4-mapped or
  /// IPv4-compatible address to an IPv4 address.
  BOOST_ASIO_DECL address_v4 to_v4() const;
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

  /// Determine whether the address is a loopback address.
  BOOST_ASIO_DECL bool is_loopback() const BOOST_ASIO_NOEXCEPT;

  /// Determine whether the address is unspecified.
  BOOST_ASIO_DECL bool is_unspecified() const BOOST_ASIO_NOEXCEPT;

  /// Determine whether the address is link local.
  BOOST_ASIO_DECL bool is_link_local() const BOOST_ASIO_NOEXCEPT;

  /// Determine whether the address is site local.
  BOOST_ASIO_DECL bool is_site_local() const BOOST_ASIO_NOEXCEPT;

  /// Determine whether the address is a mapped IPv4 address.
  BOOST_ASIO_DECL bool is_v4_mapped() const BOOST_ASIO_NOEXCEPT;

#if !defined(BOOST_ASIO_NO_DEPRECATED)
  /// (Deprecated: No replacement.) Determine whether the address is an
  /// IPv4-compatible address.
  BOOST_ASIO_DECL bool is_v4_compatible() const;
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

  /// Determine whether the address is a multicast address.
  BOOST_ASIO_DECL bool is_multicast() const BOOST_ASIO_NOEXCEPT;

  /// Determine whether the address is a global multicast address.
  BOOST_ASIO_DECL bool is_multicast_global() const BOOST_ASIO_NOEXCEPT;

  /// Determine whether the address is a link-local multicast address.
  BOOST_ASIO_DECL bool is_multicast_link_local() const BOOST_ASIO_NOEXCEPT;

  /// Determine whether the address is a node-local multicast address.
  BOOST_ASIO_DECL bool is_multicast_node_local() const BOOST_ASIO_NOEXCEPT;

  /// Determine whether the address is a org-local multicast address.
  BOOST_ASIO_DECL bool is_multicast_org_local() const BOOST_ASIO_NOEXCEPT;

  /// Determine whether the address is a site-local multicast address.
  BOOST_ASIO_DECL bool is_multicast_site_local() const BOOST_ASIO_NOEXCEPT;

  /// Compare two addresses for equality.
  BOOST_ASIO_DECL friend bool operator==(const address_v6& a1,
      const address_v6& a2) BOOST_ASIO_NOEXCEPT;

  /// Compare two addresses for inequality.
  friend bool operator!=(const address_v6& a1,
      const address_v6& a2) BOOST_ASIO_NOEXCEPT
  {
    return !(a1 == a2);
  }

  /// Compare addresses for ordering.
  BOOST_ASIO_DECL friend bool operator<(const address_v6& a1,
      const address_v6& a2) BOOST_ASIO_NOEXCEPT;

  /// Compare addresses for ordering.
  friend bool operator>(const address_v6& a1,
      const address_v6& a2) BOOST_ASIO_NOEXCEPT
  {
    return a2 < a1;
  }

  /// Compare addresses for ordering.
  friend bool operator<=(const address_v6& a1,
      const address_v6& a2) BOOST_ASIO_NOEXCEPT
  {
    return !(a2 < a1);
  }

  /// Compare addresses for ordering.
  friend bool operator>=(const address_v6& a1,
      const address_v6& a2) BOOST_ASIO_NOEXCEPT
  {
    return !(a1 < a2);
  }

  /// Obtain an address object that represents any address.
  static address_v6 any() BOOST_ASIO_NOEXCEPT
  {
    return address_v6();
  }

  /// Obtain an address object that represents the loopback address.
  BOOST_ASIO_DECL static address_v6 loopback() BOOST_ASIO_NOEXCEPT;

#if !defined(BOOST_ASIO_NO_DEPRECATED)
  /// (Deprecated: Use make_address_v6().) Create an IPv4-mapped IPv6 address.
  BOOST_ASIO_DECL static address_v6 v4_mapped(const address_v4& addr);

  /// (Deprecated: No replacement.) Create an IPv4-compatible IPv6 address.
  BOOST_ASIO_DECL static address_v6 v4_compatible(const address_v4& addr);
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

private:
  friend class basic_address_iterator<address_v6>;

  // The underlying IPv6 address.
  boost::asio::detail::in6_addr_type addr_;

  // The scope ID associated with the address.
  unsigned long scope_id_;
};

/// Create an IPv6 address from raw bytes and scope ID.
/**
 * @relates address_v6
 */
inline address_v6 make_address_v6(const address_v6::bytes_type& bytes,
    unsigned long scope_id = 0)
{
  return address_v6(bytes, scope_id);
}

/// Create an IPv6 address from an IP address string.
/**
 * @relates address_v6
 */
BOOST_ASIO_DECL address_v6 make_address_v6(const char* str);

/// Create an IPv6 address from an IP address string.
/**
 * @relates address_v6
 */
BOOST_ASIO_DECL address_v6 make_address_v6(const char* str,
    boost::system::error_code& ec) BOOST_ASIO_NOEXCEPT;

/// Createan IPv6 address from an IP address string.
/**
 * @relates address_v6
 */
BOOST_ASIO_DECL address_v6 make_address_v6(const std::string& str);

/// Create an IPv6 address from an IP address string.
/**
 * @relates address_v6
 */
BOOST_ASIO_DECL address_v6 make_address_v6(const std::string& str,
    boost::system::error_code& ec) BOOST_ASIO_NOEXCEPT;

#if defined(BOOST_ASIO_HAS_STRING_VIEW) \
  || defined(GENERATING_DOCUMENTATION)

/// Create an IPv6 address from an IP address string.
/**
 * @relates address_v6
 */
BOOST_ASIO_DECL address_v6 make_address_v6(string_view str);

/// Create an IPv6 address from an IP address string.
/**
 * @relates address_v6
 */
BOOST_ASIO_DECL address_v6 make_address_v6(string_view str,
    boost::system::error_code& ec) BOOST_ASIO_NOEXCEPT;

#endif // defined(BOOST_ASIO_HAS_STRING_VIEW)
       //  || defined(GENERATING_DOCUMENTATION)

/// Tag type used for distinguishing overloads that deal in IPv4-mapped IPv6
/// addresses.
enum v4_mapped_t { v4_mapped };

/// Create an IPv4 address from a IPv4-mapped IPv6 address.
/**
 * @relates address_v4
 */
BOOST_ASIO_DECL address_v4 make_address_v4(
    v4_mapped_t, const address_v6& v6_addr);

/// Create an IPv4-mapped IPv6 address from an IPv4 address.
/**
 * @relates address_v6
 */
BOOST_ASIO_DECL address_v6 make_address_v6(
    v4_mapped_t, const address_v4& v4_addr);

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
 * @relates boost::asio::ip::address_v6
 */
template <typename Elem, typename Traits>
std::basic_ostream<Elem, Traits>& operator<<(
    std::basic_ostream<Elem, Traits>& os, const address_v6& addr);

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/ip/impl/address_v6.hpp>
#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/ip/impl/address_v6.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_IP_ADDRESS_V6_HPP

/* address_v6.hpp
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
*/