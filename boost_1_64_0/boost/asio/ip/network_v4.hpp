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
fU92aByTXJpRwhFPRWmD/EVJyWNxeIcnpWX6082G6T6G9p7Ted+0yFh9Gs8/AKmx+kXeY3W773zidqnfGyfRLmcOd/Y312OX1SWedslQ3L2/ubzE0d/IcwqsY3EeYztngjQx+xziY/Y5xPfd51SXxGdb95bE7nOuKXH2Of88gT4naswsujnx+g3PP2+U/fPLpX6D0Eep34O2+q1lcpx5FlVU6lZ0Y+lzJH1epO9V4RnGGFufwSdsIu8S4cnRZ8W8qsJl5umlaqwyB9s7AiWrc16msH1a3sUSl43sxRPNuMLIXqc4z88I72GkHErP9rEMcka1gzcKQsw90j/fCX0MPQWnW/Wk5xSkf7brKldsqFnxrDL8/HqxjFxEh/KsUmkvPuOdKtxMqq1ePqnwTNP9aqMKX8UztM5r2tpbmtssc+MNKs110n7Cz5js2r4adPwE3bdvVeGbbW3A6vs9LDIl8c+lLI7zCEwTvETkNuu9mhv+AtPPpO4736sOwTLrvJc2kV4gv2kM7HxfdJ2bVCD87aQ7F0y+IC0tOSct1Z80VPmLmdxfAc0y7WZwo2MuI5ymBVK2lb7RYVtWf/CCvBAZcZxx7G5zzrnUoLZDXXfSx1vbu31sUDTS2Y5vxT7LSqPsUxqxWQfj7X4Dae1tuLK07zYMj60NV5Ta27C5GPhBCH3b27DEPTuiX23YdvbE+Pz42vAVsn9+pehoPvQJ8/wbh46srrOrruCxjwXvEl2N4n8P31l4itzaptbfvSrNFJ6cJu1T+PS4VOZ3Ld/U6lbxJcgp53fIb0QXxHEWX2wdIr+nTdp12yj70q+Dhgl+intHPHQr3SP5i27t+0SFL1+fHzuwzAwzhuL/iyH3/lD44MqV/jBN8XUYmci6HfLqFwPgeJU2SdfFRBVeZwThlrqQ58+y9GFNei53jkp/DvMBGZa+sW6n9ey/ZSpNhuqLOgux/1Fi/wMWOOw/nOaNUdJ+BlV5nrt4RaDvus6y1bXS93H1Qdb6zi5y7ge+i/ruKnOrb/nh2r0tCU+u0kmL6XtAoT4hoMoY73kEYsO2fcvdLnIWUVk9ZeF9ywvOXVW+ad2FVRVqUzX1hm/hsEfS939PNc+z7ameJ7LtGuOUbQZpD7rI1tLRVq/PTHDKJzy5eu6f367o5qVdWOL13MdxyE9+DnshD+6RR1SZ1rvsq885nf/KnWWSzeJeOocn5l5x4vu/V3zO8L73is+XMk2K3pMvPnKRLpN9ClLcZRlDOMtVpOXW5YqcARFVpqEF8Zcp5FdIXvYy2crzlEt5cqmjoFd5trbWUU+e5QnaZCac1T+Z1ZyvyBgsdsrYS1uu9pKRqUUacGMj6fTcXRz2YNXLoWL3Pq3TM086DO93GHz97zN0Hx0l44HxThn/UU4f6i6jdByedSd8ufK+cvQbxPe/3yA/RxsjD+k37OW6YUJUucR/7XEvl3Qe3rqHL/Y5EyfQd4zP77vvOAq+9B94zsTxnnNwsr6l6X6exKn/xuZ9QfP+FTs3P9xd0vHej3zr4ZVnZV56+NSfP/G/+u3Nq8eZ9zdsu/kHmXec95srXt14bPeo9U+Ezp/YD3Gp3yMPUv6fyvpD+VuNxzvBuUbod5Z0/r7AUOsN1P3FEH6fvj/L8vccy9/MC6j0UyDf1Mjzk6ZG0iRb/v67pH+Uv9+Qv1/mb73XuDiyR7czao/uZDqfweAUMAucCmaDJWA+OA0slPAYCcveelkPSFuR51r31t8vZ018FiwDu8FZ4APgeeDnwAvBB8EO8Avg5eBD4HvBL4K7wS/pvbWyrgx8yfw7am/tI3KGw9fBM8FHwaXgY2AD+AS4Hfw2eD34FHgX+H3wAbAXfBA=
*/