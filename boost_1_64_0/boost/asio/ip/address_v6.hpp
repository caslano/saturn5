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
d2lK7N9fNstG8lIueWlJteelrrPz2/CDyW+jMy8VVRV1Xu1I4l8Q8555kfYdFvuGRJT1Wvn2QJ2UdQWyegJtxmlfVdm1wT3il47XezGW1ZVvohmYNqJj3/s2cS5unvwt4n/Jl2M/xt46zkxylmiu+/lDSmx1kSl5xR7yKvZIfvPn2vM7OdSvk93rY+dcR35ryzfXrd10bZVXnaDTZp1EbTMH57rXySGxcTHSQ3hnGm3LYiN7VM+eWRxs/13McbXUbPvv6LiTxdaQbqbZ9vPn4bZ8U75funovMrZyl/11ZSwtte9BLvvxp4mC8lyj9pSc57Bdb3mvPEJrYiskD2Kz6KS1uaepsicJVog91rnJcRd71mJPdRR7Vs1cMp9oEeUq85IztEnKyNYG6+SbAH5RiEPKsGmnq02r1EnNrXwkvj9mW9zKZ0u38PcJ9L5MymZsaXTawkIe23xB27RVjwXlYlNIr5fnXEHCPecKEm6OyUUj295TOdQesYX8lcc8J7D2uUB3+f6xlEMxctUE4jvLQY+DMpcJj2eyhvB1HX8C+0Z1so1nK1Pa/l6YsudisWe71Oh4RJmWh2zAnvz5DnswoKai7JoyS+XY6sYca2dr3T70AZ/UVyi9DK/6kvBsz/qScM/9xufKMTuRN/Vud0r34PXHAbVPeMLQQEKX4NrNUFgeYYv0utDugYREw9oOdLxYx6b2tAXzW3Y9pH9y4CxhpXqnP0rZbyytW1Pu2idEj9rPlrXYn9XuXzG2JxvnUbs/hjLWmPsozzP1emu9Bbjv0e7jRg7/T2W99uswck/invz6wILg+/uZssa+Vet90qjCbzv5DLdd+faZtI/3dLxbuR/TU/xCujfSJ65y1LFOH96v48wzUkl7DBZ5HFd//2cH9ZuUJvXvnxqI6xJISDVkja+E5xH+hArv1C/8rRxZ4xtKYyVxilU7SVgT8F8TSEjwWDc8UOIfJv5S4vtvSM5NnpHYxd8leVRi50DXOIted8KzEcmnrW+nwmxdrhmk29V872C99ouz2X8ilL+u1UbkGuXQsRIYcFNGtr2/fUR71u6J5nml3nbufUPa7UUyho1DNtFujy5wtNvN1TTddfJhB+t5Lk23WdEhhaHUXcjmzti8N4bvdzjnB+G+1ZBu3vczz4HV2JizMGzjpcWLlsxeNbN4uXwVp25TjblvfL8BjnmY6Ma3eR4MrQkmDXMeZrUtKysY+RBpZgivVveTvGw7b9Waspq62ii2iW6W7sPzcRdq937f1zhyso81FohlbN1o7plt6vY23+GYp919fQdV7/b5tN4g3Y9l3a28E7BhkYr3YWOJ0dUxPqjiv0eFk+/Q+y7V2r3NGInfkuA+57JHR735TsZNOk4N+yUOF7+QXiHu/pFjirmm/kYdJ+AYO1R5ZMFrdZ5u8OUY9xo/pTUU+fyWuGuqQv0vE5brtHbQSsk7VVqkcq71t/rCx69XBph7qXxTh8eRBm5sflq7rzamcSw1NmxLD34vYLEaGxYlxvuz1DfJ/DmJ8YE42qjjHO4478txPqXSpQSHehxLn+PkeCkMmqm91Ni1dUzA39kcI/4YetdB4o0jXoqKl7x1RSjOclsc3D2DYw1xZppjTUScLcRJU+l03/poKM5lEmcy7q64yzOD59gqeDmcJ2L1p+9DJbHtoSL3B8L9TfyWm+de2rvj25u6zm3jWr68UPADdb0orFX3F4u8+2VNZa1XnxS9AWbb/oR2P+Kb4PN79UXRIcfSFz+m3U2+l1jx2U3epTq4OPztlcHWfil9/2Gt80lff+K69svFEf1Su2/R/XIBsZROQrCNm339Jh2nlh44QvyUXgz9crH0S49+c6wo2G8=
*/