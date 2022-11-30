//
// ip/address_v4.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_ADDRESS_V4_HPP
#define BOOST_ASIO_IP_ADDRESS_V4_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <string>
#include <boost/asio/detail/array.hpp>
#include <boost/asio/detail/cstdint.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/detail/string_view.hpp>
#include <boost/asio/detail/winsock_init.hpp>
#include <boost/system/error_code.hpp>

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

/// Implements IP version 4 style addresses.
/**
 * The boost::asio::ip::address_v4 class provides the ability to use and
 * manipulate IP version 4 addresses.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 */
class address_v4
{
public:
  /// The type used to represent an address as an unsigned integer.
  typedef uint_least32_t uint_type;

  /// The type used to represent an address as an array of bytes.
  /**
   * @note This type is defined in terms of the C++0x template @c std::array
   * when it is available. Otherwise, it uses @c boost:array.
   */
#if defined(GENERATING_DOCUMENTATION)
  typedef array<unsigned char, 4> bytes_type;
#else
  typedef boost::asio::detail::array<unsigned char, 4> bytes_type;
#endif

  /// Default constructor.
  /**
   * Initialises the @c address_v4 object such that:
   * @li <tt>to_bytes()</tt> yields <tt>{0, 0, 0, 0}</tt>; and
   * @li <tt>to_uint() == 0</tt>.
   */
  address_v4() BOOST_ASIO_NOEXCEPT
  {
    addr_.s_addr = 0;
  }

  /// Construct an address from raw bytes.
  /**
   * Initialises the @c address_v4 object such that <tt>to_bytes() ==
   * bytes</tt>.
   *
   * @throws out_of_range Thrown if any element in @c bytes is not in the range
   * <tt>0 - 0xFF</tt>. Note that no range checking is required for platforms
   * where <tt>std::numeric_limits<unsigned char>::max()</tt> is <tt>0xFF</tt>.
   */
  BOOST_ASIO_DECL explicit address_v4(const bytes_type& bytes);

  /// Construct an address from an unsigned integer in host byte order.
  /**
   * Initialises the @c address_v4 object such that <tt>to_uint() == addr</tt>.
   */
  BOOST_ASIO_DECL explicit address_v4(uint_type addr);

  /// Copy constructor.
  address_v4(const address_v4& other) BOOST_ASIO_NOEXCEPT
    : addr_(other.addr_)
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  /// Move constructor.
  address_v4(address_v4&& other) BOOST_ASIO_NOEXCEPT
    : addr_(other.addr_)
  {
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  /// Assign from another address.
  address_v4& operator=(const address_v4& other) BOOST_ASIO_NOEXCEPT
  {
    addr_ = other.addr_;
    return *this;
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  /// Move-assign from another address.
  address_v4& operator=(address_v4&& other) BOOST_ASIO_NOEXCEPT
  {
    addr_ = other.addr_;
    return *this;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  /// Get the address in bytes, in network byte order.
  BOOST_ASIO_DECL bytes_type to_bytes() const BOOST_ASIO_NOEXCEPT;

  /// Get the address as an unsigned integer in host byte order
  BOOST_ASIO_DECL uint_type to_uint() const BOOST_ASIO_NOEXCEPT;

#if !defined(BOOST_ASIO_NO_DEPRECATED)
  /// Get the address as an unsigned long in host byte order
  BOOST_ASIO_DECL unsigned long to_ulong() const;
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

  /// Get the address as a string in dotted decimal format.
  BOOST_ASIO_DECL std::string to_string() const;

#if !defined(BOOST_ASIO_NO_DEPRECATED)
  /// (Deprecated: Use other overload.) Get the address as a string in dotted
  /// decimal format.
  BOOST_ASIO_DECL std::string to_string(boost::system::error_code& ec) const;

  /// (Deprecated: Use make_address_v4().) Create an address from an IP address
  /// string in dotted decimal form.
  static address_v4 from_string(const char* str);

  /// (Deprecated: Use make_address_v4().) Create an address from an IP address
  /// string in dotted decimal form.
  static address_v4 from_string(
      const char* str, boost::system::error_code& ec);

  /// (Deprecated: Use make_address_v4().) Create an address from an IP address
  /// string in dotted decimal form.
  static address_v4 from_string(const std::string& str);

  /// (Deprecated: Use make_address_v4().) Create an address from an IP address
  /// string in dotted decimal form.
  static address_v4 from_string(
      const std::string& str, boost::system::error_code& ec);
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

  /// Determine whether the address is a loopback address.
  /**
   * This function tests whether the address is in the address block
   * <tt>127.0.0.0/8</tt>, which corresponds to the address range
   * <tt>127.0.0.0 - 127.255.255.255</tt>.
   *
   * @returns <tt>(to_uint() & 0xFF000000) == 0x7F000000</tt>.
   */
  BOOST_ASIO_DECL bool is_loopback() const BOOST_ASIO_NOEXCEPT;

  /// Determine whether the address is unspecified.
  /**
   * This function tests whether the address is the unspecified address
   * <tt>0.0.0.0</tt>.
   *
   * @returns <tt>to_uint() == 0</tt>.
   */
  BOOST_ASIO_DECL bool is_unspecified() const BOOST_ASIO_NOEXCEPT;

#if !defined(BOOST_ASIO_NO_DEPRECATED)
  /// (Deprecated: Use network_v4 class.) Determine whether the address is a
  /// class A address.
  BOOST_ASIO_DECL bool is_class_a() const;

  /// (Deprecated: Use network_v4 class.) Determine whether the address is a
  /// class B address.
  BOOST_ASIO_DECL bool is_class_b() const;

  /// (Deprecated: Use network_v4 class.) Determine whether the address is a
  /// class C address.
  BOOST_ASIO_DECL bool is_class_c() const;
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

  /// Determine whether the address is a multicast address.
  /**
   * This function tests whether the address is in the multicast address block
   * <tt>224.0.0.0/4</tt>, which corresponds to the address range
   * <tt>224.0.0.0 - 239.255.255.255</tt>.
   *
   * @returns <tt>(to_uint() & 0xF0000000) == 0xE0000000</tt>.
   */
  BOOST_ASIO_DECL bool is_multicast() const BOOST_ASIO_NOEXCEPT;

  /// Compare two addresses for equality.
  friend bool operator==(const address_v4& a1,
      const address_v4& a2) BOOST_ASIO_NOEXCEPT
  {
    return a1.addr_.s_addr == a2.addr_.s_addr;
  }

  /// Compare two addresses for inequality.
  friend bool operator!=(const address_v4& a1,
      const address_v4& a2) BOOST_ASIO_NOEXCEPT
  {
    return a1.addr_.s_addr != a2.addr_.s_addr;
  }

  /// Compare addresses for ordering.
  /**
   * Compares two addresses in host byte order.
   *
   * @returns <tt>a1.to_uint() < a2.to_uint()</tt>.
   */
  friend bool operator<(const address_v4& a1,
      const address_v4& a2) BOOST_ASIO_NOEXCEPT
  {
    return a1.to_uint() < a2.to_uint();
  }

  /// Compare addresses for ordering.
  /**
   * Compares two addresses in host byte order.
   *
   * @returns <tt>a1.to_uint() > a2.to_uint()</tt>.
   */
  friend bool operator>(const address_v4& a1,
      const address_v4& a2) BOOST_ASIO_NOEXCEPT
  {
    return a1.to_uint() > a2.to_uint();
  }

  /// Compare addresses for ordering.
  /**
   * Compares two addresses in host byte order.
   *
   * @returns <tt>a1.to_uint() <= a2.to_uint()</tt>.
   */
  friend bool operator<=(const address_v4& a1,
      const address_v4& a2) BOOST_ASIO_NOEXCEPT
  {
    return a1.to_uint() <= a2.to_uint();
  }

  /// Compare addresses for ordering.
  /**
   * Compares two addresses in host byte order.
   *
   * @returns <tt>a1.to_uint() >= a2.to_uint()</tt>.
   */
  friend bool operator>=(const address_v4& a1,
      const address_v4& a2) BOOST_ASIO_NOEXCEPT
  {
    return a1.to_uint() >= a2.to_uint();
  }

  /// Obtain an address object that represents any address.
  /**
   * This functions returns an address that represents the "any" address
   * <tt>0.0.0.0</tt>.
   *
   * @returns A default-constructed @c address_v4 object.
   */
  static address_v4 any() BOOST_ASIO_NOEXCEPT
  {
    return address_v4();
  }

  /// Obtain an address object that represents the loopback address.
  /**
   * This function returns an address that represents the well-known loopback
   * address <tt>127.0.0.1</tt>.
   *
   * @returns <tt>address_v4(0x7F000001)</tt>.
   */
  static address_v4 loopback() BOOST_ASIO_NOEXCEPT
  {
    return address_v4(0x7F000001);
  }

  /// Obtain an address object that represents the broadcast address.
  /**
   * This function returns an address that represents the broadcast address
   * <tt>255.255.255.255</tt>.
   *
   * @returns <tt>address_v4(0xFFFFFFFF)</tt>.
   */
  static address_v4 broadcast() BOOST_ASIO_NOEXCEPT
  {
    return address_v4(0xFFFFFFFF);
  }

#if !defined(BOOST_ASIO_NO_DEPRECATED)
  /// (Deprecated: Use network_v4 class.) Obtain an address object that
  /// represents the broadcast address that corresponds to the specified
  /// address and netmask.
  BOOST_ASIO_DECL static address_v4 broadcast(
      const address_v4& addr, const address_v4& mask);

  /// (Deprecated: Use network_v4 class.) Obtain the netmask that corresponds
  /// to the address, based on its address class.
  BOOST_ASIO_DECL static address_v4 netmask(const address_v4& addr);
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

private:
  // The underlying IPv4 address.
  boost::asio::detail::in4_addr_type addr_;
};

/// Create an IPv4 address from raw bytes in network order.
/**
 * @relates address_v4
 */
inline address_v4 make_address_v4(const address_v4::bytes_type& bytes)
{
  return address_v4(bytes);
}

/// Create an IPv4 address from an unsigned integer in host byte order.
/**
 * @relates address_v4
 */
inline address_v4 make_address_v4(address_v4::uint_type addr)
{
  return address_v4(addr);
}

/// Create an IPv4 address from an IP address string in dotted decimal form.
/**
 * @relates address_v4
 */
BOOST_ASIO_DECL address_v4 make_address_v4(const char* str);

/// Create an IPv4 address from an IP address string in dotted decimal form.
/**
 * @relates address_v4
 */
BOOST_ASIO_DECL address_v4 make_address_v4(const char* str,
    boost::system::error_code& ec) BOOST_ASIO_NOEXCEPT;

/// Create an IPv4 address from an IP address string in dotted decimal form.
/**
 * @relates address_v4
 */
BOOST_ASIO_DECL address_v4 make_address_v4(const std::string& str);

/// Create an IPv4 address from an IP address string in dotted decimal form.
/**
 * @relates address_v4
 */
BOOST_ASIO_DECL address_v4 make_address_v4(const std::string& str,
    boost::system::error_code& ec) BOOST_ASIO_NOEXCEPT;

#if defined(BOOST_ASIO_HAS_STRING_VIEW) \
  || defined(GENERATING_DOCUMENTATION)

/// Create an IPv4 address from an IP address string in dotted decimal form.
/**
 * @relates address_v4
 */
BOOST_ASIO_DECL address_v4 make_address_v4(string_view str);

/// Create an IPv4 address from an IP address string in dotted decimal form.
/**
 * @relates address_v4
 */
BOOST_ASIO_DECL address_v4 make_address_v4(string_view str,
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
 * @relates boost::asio::ip::address_v4
 */
template <typename Elem, typename Traits>
std::basic_ostream<Elem, Traits>& operator<<(
    std::basic_ostream<Elem, Traits>& os, const address_v4& addr);

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

} // namespace ip
} // namespace asio
} // namespace boost

#if defined(BOOST_ASIO_HAS_STD_HASH)
namespace std {

template <>
struct hash<boost::asio::ip::address_v4>
{
  std::size_t operator()(const boost::asio::ip::address_v4& addr)
    const BOOST_ASIO_NOEXCEPT
  {
    return std::hash<unsigned int>()(addr.to_uint());
  }
};

} // namespace std
#endif // defined(BOOST_ASIO_HAS_STD_HASH)

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/ip/impl/address_v4.hpp>
#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/ip/impl/address_v4.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_IP_ADDRESS_V4_HPP

/* address_v4.hpp
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
*/