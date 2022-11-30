//
// ip/address_v6.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/detail/cstdint.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/detail/string_view.hpp>
#include <boost/asio/detail/winsock_init.hpp>
#include <boost/system/error_code.hpp>
#include <boost/asio/ip/address_v4.hpp>

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

template <typename> class basic_address_iterator;

/// Type used for storing IPv6 scope IDs.
typedef uint_least32_t scope_id_type;

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
  /**
   * Initialises the @c address_v6 object such that:
   * @li <tt>to_bytes()</tt> yields <tt>{0, 0, ..., 0}</tt>; and
   * @li <tt>scope_id() == 0</tt>.
   */
  BOOST_ASIO_DECL address_v6() BOOST_ASIO_NOEXCEPT;

  /// Construct an address from raw bytes and scope ID.
  /**
   * Initialises the @c address_v6 object such that:
   * @li <tt>to_bytes() == bytes</tt>; and
   * @li <tt>this->scope_id() == scope_id</tt>.
   *
   * @throws out_of_range Thrown if any element in @c bytes is not in the range
   * <tt>0 - 0xFF</tt>. Note that no range checking is required for platforms
   * where <tt>std::numeric_limits<unsigned char>::max()</tt> is <tt>0xFF</tt>.
   */
  BOOST_ASIO_DECL explicit address_v6(const bytes_type& bytes,
      scope_id_type scope_id = 0);

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
  scope_id_type scope_id() const BOOST_ASIO_NOEXCEPT
  {
    return scope_id_;
  }

  /// The scope ID of the address.
  /**
   * Modifies the scope ID associated with the IPv6 address.
   *
   * @param id The new scope ID.
   */
  void scope_id(scope_id_type id) BOOST_ASIO_NOEXCEPT
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
  /**
   * This function tests whether the address is the loopback address
   * <tt>::1</tt>.
   */
  BOOST_ASIO_DECL bool is_loopback() const BOOST_ASIO_NOEXCEPT;

  /// Determine whether the address is unspecified.
  /**
   * This function tests whether the address is the loopback address
   * <tt>::</tt>.
   */
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
  /**
   * This functions returns an address that represents the "any" address
   * <tt>::</tt>.
   *
   * @returns A default-constructed @c address_v6 object.
   */
  static address_v6 any() BOOST_ASIO_NOEXCEPT
  {
    return address_v6();
  }

  /// Obtain an address object that represents the loopback address.
  /**
   * This function returns an address that represents the well-known loopback
   * address <tt>::1</tt>.
   */
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
  scope_id_type scope_id_;
};

/// Create an IPv6 address from raw bytes and scope ID.
/**
 * @relates address_v6
 */
inline address_v6 make_address_v6(const address_v6::bytes_type& bytes,
    scope_id_type scope_id = 0)
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

#if defined(BOOST_ASIO_HAS_STD_HASH)
namespace std {

template <>
struct hash<boost::asio::ip::address_v6>
{
  std::size_t operator()(const boost::asio::ip::address_v6& addr)
    const BOOST_ASIO_NOEXCEPT
  {
    const boost::asio::ip::address_v6::bytes_type bytes = addr.to_bytes();
    std::size_t result = static_cast<std::size_t>(addr.scope_id());
    combine_4_bytes(result, &bytes[0]);
    combine_4_bytes(result, &bytes[4]);
    combine_4_bytes(result, &bytes[8]);
    combine_4_bytes(result, &bytes[12]);
    return result;
  }

private:
  static void combine_4_bytes(std::size_t& seed, const unsigned char* bytes)
  {
    const std::size_t bytes_hash =
      (static_cast<std::size_t>(bytes[0]) << 24) |
      (static_cast<std::size_t>(bytes[1]) << 16) |
      (static_cast<std::size_t>(bytes[2]) << 8) |
      (static_cast<std::size_t>(bytes[3]));
    seed ^= bytes_hash + 0x9e3779b9 + (seed << 6) + (seed >> 2);
  }
};

} // namespace std
#endif // defined(BOOST_ASIO_HAS_STD_HASH)

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/ip/impl/address_v6.hpp>
#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/ip/impl/address_v6.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_IP_ADDRESS_V6_HPP

/* address_v6.hpp
IqGxQ2j7iKAGIJrMU7Vc8CWUJTXCrxPhv7P5/XVRUEwjeOXtfgWB0/D5xADV+Xk+jsDZcY5fmz/Xc0wHWTdzNfYuF2GCPE1Vf+2N2l7yXjCP+20BR8RqTzrMubrmcvlJ/QUBkc7x2csh3hqvUd9fi85hNDMfY7Rz0C+mfvfZC8luZcn9ENIJiZkbH6PRbYiu0+9eEfU8Olanp/nrhMd3PPrJBS0UrajhvrVwgXm5U9J3r//ZBOA4F5Ujldh9sdxCa+dtBUH6mvJHq1YWQ8lIJ0MBAaIogqNAKafomrb2U+dyzWGWPPXo5qkhi7dptNxdEVXlponH/G5CbpQIC/RKvgGvWv8+u/9SrLpv3n9otRXkFwVN3Wlbv+8GCf1XVQ/5EYzqNvqIvVbjr1M9vw9mff/jxsn3Az/TVrNgVmWGzsruLKzQBxbMW3qg7sHLfSgWBgR1VrEGCv4tC3SNLq2CinKEHq13maEFPY0rb5VuIdLlunzq4YO2Fv6gIEEOgqcolVna5zSwP/pI+uy5BooBAwoh37CbE1kbKevYtnJux5T74+GLw+pngzGg5s8PjGXTXNGkvXr9fXNvjImMhDIn4i8vjxzoICrS7mbWUSNfvjT13LU/VdBkEUXC9QDGufpvGcwntwwzSM8603DAFAkBtfRQOTKqHokoCfQq3HypHZZ3DnpTOQW3It5AVCpzhW57MX3vrKFSg0IuOl++rFIpoO/8TIHyPcH7a2YuWC8USFMABBQPBPJsr9DPb81bPvQu05YRA8aeEs4Harn1epRTGvYfNgu1Qy4whuApV7o66dPGTdIzR+j95miyr39L49JhSXS/EMdRstfMgVMVQeK4fEpd4VxoWN0F/dmkKRKqcMD3FRMvSeo6q1TjeIaokMShQw92/AfR5YQJfG1g5iZI0ingR9JFhlNmpfdyb+AoCUJPT4SY/sEDUPfcY+9Ob+pvxlIubtxjCpck+VJXhNzyr7y+M3d6whM1WIJy0kshgi5Rs2aBAbthBCKrqP2PybjRViwokrhR94UXUmWMQBvEW/YnwEUnrlPKwHeA33CoIYZeHtIGZHJvPSDQDcwUVXg8jVGBiD0KGPLsaF/KddzrJV0kD+yVf20hJMdY8O9QhkXqI6cE2zILfii6PEw4vahGVWBEfiI+8YMK2ZJY/1n8hTNlB2lqON00Kq6yy7o385te9cN5HTkYT5DffNemWbNWdXr/sYv9h6bRvw+JIxWGcPej6Acf5K3oySL7SojSzkhC/iNYvio8mXp76ILZ8Iv9KOHMxQet1mVd+tagcauEo7OkGZNqSCjyRIc1KE7ukBjSwHyqX1G18gH5f+sj9hhnvjNi9UHwcOiBd/9u/HoCsrZNNAC3XF/sdMyCaSDexgnkf9HBikfNw3750krO6OW21TS6sPO4ZBK4SilQ5sLF0U/HvYUXAvy1XOUJpa1CfcySF/kRjrDgWHnysotStf+jg6aaAV2E+ezAr0Oq/zfz4UHxGRKT+WmxRz3xT3wQNvVzcZPTCJYDb61FfTtjNgTl5TCsjRcGsDBOWNgPwZY9sqT0X0vuiLRXXY8vgE9bykew/ymzWYiWWe6vbpM3m+mYSksUIiZ/nnggABJAsU7u8JsnXkWGeCICKOObihnMALx4Xbz+FEZQx3pX9jwPbxr+Wa4LHxxvW+E/Ub60r1VurjfBGIsV1iXpOk6seZ6QltEurnLv/xDZkMFWhihe8c8OteNkrdCV5xlMA3SqsGmo8yspxVDttlwE9eLmYdxqvBRVYcpctB7JLoBc/bL0AcynqAuJ0kVKCTR6eSJJEVpbpvLN9LIpNvNCZbiC5vuf6KGg76Cvx1v6jDGSdTsNjOff99J7R5SyKHGMfvwf+OFivAMsXZ+N6pFA1uJ0eyCcZ2WFY11Jfn9RSmq6+r/tQhK1S+ScphJx9wcoBp4hgUEGpwr27DE0riTYW9lfu4102xv15Lp2gHC48HarYV4vME5jo5CE01AoIMQhHjfRbGjAak1KfLot6XOSdXNLTGpMKpS3aTSl0KiWlS1cVRW4ONsOR6NLLhiUPi744cSPFe7d7dvMv2AJjv3VPRmsPHq135YTfQLjjCmJbKwOp0OI5bFPba8u+yTiB6avRcEbCbXSzUogL0HuIY3CcsbTObUgvTOK/wFnNNxaCfGVt8jCat135Z4wN/NdJEXw19XV56P2NyQf0LBfPPL/fOpp/YiuAeCZ9e7C9YhLiYG/ljUUAFWE41ON1VbRJbXyRIMQtB3OFDnRpLyCEjO+zqoWZefoki9J2dUrV0Tv8+MWw80RABz/nikGPcAH38/EaQ6loKGRhteVvVEWWFNXVlYCT1TR0Eh9+6iQyrsfk+YjLsqSjYHz9Ehvbm52iW3OhQOenp6GZV5enotSQOd8kwXZREIjWACU9Ok6ALMCCQ1hnFDLcWrC5BXBMNgLy3nPQ7T4wLnt5dDI/hdpFAj1Iz832kz8wGkwN1y8XCRs7P5SEb9gFA5exBQUKP1xUbG+1MwYxsTEJI/snXfgbXWuho6O/sNEJytL4idyiRJCp7XulX8LgNGwWOHtBZBzVGC+qvBmdS2OoXfAukCiFyx0/1AA6EsIeKUgnwwACllgx44NEzKAkMtoR8/+22tU7m11Kpak9RJ12uWZDa9TrTAkLjZJ2gw80kxOkHF9eWmJO7uaaUnAzPS7L/2+KPr8m5piEFmQiQqOc0T+AO/Qj/CzQjHhzAVRO6y854lBHDKj1gJr0Rd8DRNAWrKHYKBvaho7YBAs2EsHSK0oILpXeHeRLV7RTnoaqp0kFLKttbkAfGE46rFOtwiMY7cIw6imLoKorr67tqau+99/kGIgSgxqP8RzoE/IHaueaSYYh7y4EBExVWrD74uXN+B+TLS5j2X06GOdguUQTepO+r7sSLADcfVq2B0AAnYlGL3KXZsZyugNWpVmF8msMTqbysVJrLcnNIRb2A1em5DBoFDVyCKlwASkZKSs5VyshWYh2gIO1/52iZby0GU7aO8J/dwQDD3qMAwBwowf6bOF1mSpsUbyymDihBZqR62hw31Q56ngevj+V6vgu+KIDV8nyNppEr1Kku5GFY4YwfSvt3RvMzv2xm9zfE4Kym1bNWyqpUY+KZ16Mj1Fut16DxyISzk982t6ByKlAAojdhhHA2DirkfECmmRCB80IUyPIkCunMUkffy+EXXy+/F6NClHa44qX1tWfTRKBk6c2hm2q9hS8fhfDCEtAL7ngAlDCb6+NXt+oTn3WlAmXzgNezzxCQL/LFORx41o+jCEQSmpszKPnkHlgU+AvTOihzx+A+uCTqOZUycdLK0I9wXdDhmqQBjO8AASVWvYNOkngaSlbQUrvPweWyq6dYY14AFYNKpWDn8CizUe0Vz3ud3bHPNtR5DHDeUGvowtw37o1aGefkOKIwAS3X4fQ/GknnSCx5f8KNcOn73Tl53nK/C+5maDFSD33ntvtmZTNKCBol/1QVN/WBdGaEglhx7fff8ys/z66pcHAjpmNMr4kSxnVxHRe3/l7x/CDvoi86jui6Upbe7cUk7ak8wcsElfqhILvkQGXGIawR6BeUn8y5xMB7UOddvBZwLLH31LKo8gqBJqG+CVx2Pu8x1CTR4KT6O9+8+AOVj1UiSXXZKgF/dnv9I3lKMZjfyMSGgcdWeiPmOndnIIDBTC0L6G+xXeDb4ENu7QaOTdwPyKAbsaA2aHJkjXV5vfL5Ys5bEdy8yHHum/Tu+9dxfi1h+XR1CzA/fuSyjLwMmQRKRGGfS0KQICdtUUtCP+h8VfsWQHxLg1bL0QKie9F80zRl0agUZBlyibZs6J7mtRyw3QJFcF8zEJ3vcZAL89zqHcwiH4Plg69LfOeSMdcbrsEYCQTJZXmIlpSNDjBQNNMIepJhndyRyZWcPMuPEUl0MrykE49dtt9xoenDVOh9C8D0GFsTctsvWjIDXne+mlcDMkbQ6s4bcpq4Sf/R8K5m8X+CRUIKgcRiSI0RZubYq8PaU1BEQEL3iA69495xR8rEXyI2ZPpuz3DHAXSTeZgu0TYIxXlefhDT/mdhuL2yjHUOMick25O1bxNHJWevZ2MVGyzGH/JnUdeEYOePiPULndKieUBpJya7FQzRNmQemTRAzeb1KOf9Um6bzEhSGy/cBjvop5gc43JvwWe/yKI71QWbAPcAIgIDdckxYSvuNZp7D+73pRTUff1qzIClZb+HkQJpVR5vvtWJpkezjZsgnoelk2Uhdb9BEcN6ubMXBaOqgt0NMANU8bew+LLTNa4fvx8F4wnac93ADOVM/Vtv7fqe++/uXF5Tg6cnnYQinxv37lZgT51rU1sxDtJydRKfIaMNObNzJIoiJo/a9TbW6c/TzZrbO9FtSy/MVr/TXAm3NX+2EjYo+KTLFRhelQR+ssf53oh2Bv/k4cf8fdBaoxFyW1srnzp5+7BUcc5Qvn8zG1md3klpdP6uip1r8o1yPm72RNY0hBh3jycsRVAedcVDPhtIq2JAn6mgIeGj5kfZOnN14NpXJ8uY1F4ctLCQG+9qcLzGCSRlNUF4thG0kNRIwoD+oE0/5bvRTltVbmliLN+dF5NldVXyuRZI8fR7FzTd/KpZ+VhAzkawbetLPNT0oLkC5hnGXCnPiA+0jGgAX2a0gTi5+32eZCuBKLnTttwR2zZxsG2FQaHPHW7AOjwJmgqSw7C56K5+rQ+PLqJl8RQM5B48BFZKAJD1g5MBCZLch1wsj6uVDvtNp0llq6wIoEGiA4ZODGecWmRw8fZsoiHkj4vjRvzcIjRKL059/alit66fEydU5OcQXIB/xQyUwvuQGvd+mAHBgCaxBYy6TVnN3MkcHK13aTmoNWcvyNecLTBJYuAbYFOJKh7c1PFIkvq5rXm0F6/HpNbYmz7sBxtUG5deWASc9EzbE1Lb8UGR533kRy1p1B3lAWiNLkS6fw+sETJ6XqiYExiWzt5rqxeP4p8EBvfDFtGLmN2G5K36HVnB/QHiujk7IDIFLNJQtX91LssI27x0ux66Ig07hMiDkwPrakXjG+8UhER3mWmj9KbAAtUx2kdvYztD7x3NF0wXzuL51vCAFNnhDhXHfxqyqW+Nih03OxMr0Et+klvrCVLB8l+rjFiJ09BI7n+9YZ4CX4lkDTEtBluhpGxZwqsXMqCC14VR7VeMPA9q3F1JvHRbK0xrD0zRmS5k31TDc2M5fRG5BMBvqV9FRnlRzTA3C0hMJQDqpxWmDmaEyo71ArT/2U/0+tqaXEWNlVkq/07IlehHEtzMD0JrWNpbT6y6fJ0uv2oZEtch8j1YwPg2FXq7kEtL5QlPBnPf/shJ0NGcmDye3GwZeEuevJBzd8ZCXjkI8HR2/UaNzBDxcfFsI7ACNPGPZDL9iuj1IFbLQeWY9CtalQTz1jh8VJ7GDBObPeAz80NySRjmwxdl8sUNBmGMnUVE43I4HCnodRkqX0zCOKnpZYuIQ26EbJy6uMJFPuJmr9lQKMh2tWHyfpJ+dQDprvWlslZlje7s1FVIH/daSIo6HV7LFrx2zGoY1NPIP3svl7ckGnm0R4GBugcB/cL5EqbVSZ+84B1r6Q4qykwDr8rjctCYX4hqaXMnO2UujQEuofBVTYWcL8dlomaBqAHtlO3kjqcVW2wrvs5lOCSm+SAfYRXol8md/7XeLxKAVuJdJ26M8bqSQ/ASbO+H/EkVKekacmfOVaXEo2oXObl9RutOwiGY8YBGGKweBDxEm7+9aauie9MLMKw5j86TgI6t8AZeqpVZ+vTobrRgisrN3HDS5InBblkA1DzqCkjIEU/0YbtW3lV2vnQNZr90FVzN2D4ocaptuhNwxDpwkIvnm8/yU+tDTGDglCfcJTCciRMibR4iKIlG5/5V9oP61fVP0M1aHFuoaQ1MW3ScPpRYEMhOCA4OSsmb1wFgfgAknO8pTdqNcEkz4az6Z+HsoH5k8x+9A+Gm7Tk6FZbj+BtVqPcMTqv7fXjK7TYYEHe0XeRj0UPIIuFLwmyxuMpEliVb6EWY1llE/X+JvMZn4Shypgs9TT5neuGShW3CykA2fwk5z4rUNfmqawfZHfr/t9OBF//yNkAApCxBorRBqKhJitlK1c9/JvX5Uji3PwEcELVgvBfJe/474bb9h55U92GcUKv41NKMzeEl4iFpJ0ZyWmf6PBEII5fGNwy3g60El5FISeylU2WFyVeprKGFrz1yOSa6KwcSUNkA2fTHbCfKpRyblFdZnK+A4k5n6aRyPbPkO/mGVxcXXitI4xk0pvpyHE5fvPPBmWHtt65iD/cHDCU58AiB3nR969ydu8XSBQXuufevMQLBxX4764MMHNpr0Jh6jNj5qjidTiGO1de21NLz2L+QkugALHADkG65VjTiB1eADeQvSp17/30ww7d5vfHbGBqNznVZI7ibYEmkHjW2bLg/expqX5Z5K1QGo8iqKZFYfo+98IhWD2AzJfPH3pLQdLUGarDZ5z/htPxJGEC1ix9butl69kCIAJpXP3vIDXX0lXZToX7/lSE9HbnwbmWl2p3l7qfyklxxC5O10uVG9GAbAXrJ6tKZ6ecxtjLX7wu5M+nWaV9tmyzIG/XgNypbgTAjRe3ATijRRjp6d0qhWqnnkJ4M435yKC+IkV5BrBuL05nyFii/WkXRmCxZ6OoAB73EAj6oJ9xs/qyPZX/Z/wKx6Uo+u3rrMP6ofm707pvy0fDQG/x5w1xi6ftH2q2NyKAKGwOMKtEb/6iNG9Cgusz2EKq6d6tDPgDa8mAZpV//FOM+neu4f+jCS8R5A4UbWtQQfNpvuRfYofeuzlGHDGP8F/WWSBAjQ0Zvacip0pzVKNWKzegl+sGxtSEhSxjy1GcMJ1+g6SyOXWKidSsfJpSYG/P3LqTHrZzAKSbzKvNUw6pUz3XBuZMSLWwlGH8rDqtdr5huX+o5rkswndzh55fSu/iRFHJgs9ZCEvUz41xd6DOnaqSkEVwN1mHI6VP3+e0yH86uGPBrEl/y6dK6UXhsyrdgz41gwshjXfpjmkX7EpNSz/BK4293i5TWRk5vacDcN2/F5Qchs/VWL8j8EmxB8Jv2jbKWLVxTf8lJMotBCSazODMEZatOZVEjXW+eMjFY/v2bduKdJ4DTsMNmtrHHVuxj3bJXOrkmOZtWexN7jCzufGhW/g5sqqB2HTZjYG0rNL0Wm8VhSu7tmPGSoZZ7floMVTGYvFYRYCzdq3CyHHeQvhml6N8W3L405PCi2xDUfUqNm/RXfVa+4AjNymZdyYstd95tS0SDlE6PuKSeyfYJbPKBN/S8guMi+ARJ4Uc8tDb6YHwW66NiX9PmcU4oEdK9E6uXyAPko7fulD48iPTW6mVbRwJkrQimwyYYoWWXxCvWCtfiwEPvakmOgMOYQUsf3lP73Qd5z4kEI13O0P9YqTJyuO/zqbZ0VNBge/sU/QEahJJF0ClvN7wkx59uw9J0xGF935CepyLSwjXQS3iX+CE85KVNE0USAdCJ7ASTuT2/EFzv2Tyhw0UZEW1wn7SThAAy+PwVQn3NZ4FCIjjTDFThSZ1PNxJl2QJ20ri5UQI8vPqY/eKk29OCfzJu9MmcpkyZQ71JmvNGM3D8tnD0UYCPz1ILjdctto
*/