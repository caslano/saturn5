//
// ip/icmp.hpp
// ~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_ICMP_HPP
#define BOOST_ASIO_IP_ICMP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/basic_raw_socket.hpp>
#include <boost/asio/ip/basic_endpoint.hpp>
#include <boost/asio/ip/basic_resolver.hpp>
#include <boost/asio/ip/basic_resolver_iterator.hpp>
#include <boost/asio/ip/basic_resolver_query.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

/// Encapsulates the flags needed for ICMP.
/**
 * The boost::asio::ip::icmp class contains flags necessary for ICMP sockets.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Safe.
 *
 * @par Concepts:
 * Protocol, InternetProtocol.
 */
class icmp
{
public:
  /// The type of a ICMP endpoint.
  typedef basic_endpoint<icmp> endpoint;

  /// Construct to represent the IPv4 ICMP protocol.
  static icmp v4() BOOST_ASIO_NOEXCEPT
  {
    return icmp(BOOST_ASIO_OS_DEF(IPPROTO_ICMP),
        BOOST_ASIO_OS_DEF(AF_INET));
  }

  /// Construct to represent the IPv6 ICMP protocol.
  static icmp v6() BOOST_ASIO_NOEXCEPT
  {
    return icmp(BOOST_ASIO_OS_DEF(IPPROTO_ICMPV6),
        BOOST_ASIO_OS_DEF(AF_INET6));
  }

  /// Obtain an identifier for the type of the protocol.
  int type() const BOOST_ASIO_NOEXCEPT
  {
    return BOOST_ASIO_OS_DEF(SOCK_RAW);
  }

  /// Obtain an identifier for the protocol.
  int protocol() const BOOST_ASIO_NOEXCEPT
  {
    return protocol_;
  }

  /// Obtain an identifier for the protocol family.
  int family() const BOOST_ASIO_NOEXCEPT
  {
    return family_;
  }

  /// The ICMP socket type.
  typedef basic_raw_socket<icmp> socket;

  /// The ICMP resolver type.
  typedef basic_resolver<icmp> resolver;

  /// Compare two protocols for equality.
  friend bool operator==(const icmp& p1, const icmp& p2)
  {
    return p1.protocol_ == p2.protocol_ && p1.family_ == p2.family_;
  }

  /// Compare two protocols for inequality.
  friend bool operator!=(const icmp& p1, const icmp& p2)
  {
    return p1.protocol_ != p2.protocol_ || p1.family_ != p2.family_;
  }

private:
  // Construct with a specific family.
  explicit icmp(int protocol_id, int protocol_family) BOOST_ASIO_NOEXCEPT
    : protocol_(protocol_id),
      family_(protocol_family)
  {
  }

  int protocol_;
  int family_;
};

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IP_ICMP_HPP

/* icmp.hpp
0NGGxn824fTmdrMS2qwjP2+2+NG6LWzVt2ZpIhHbbm6YCpbaLRfrcoHLpJp4SpMestDgv28sNaZpH8fGyuiUt762IJuM52fUFCKGqsNH1L3vSbgFV543//rDFJL2MiLl6KjSaY4UEeEQVtugXrR43DU478paekZdBjMaR6PbCY9Q/uhfi6y+rCA7bwOKwdtlH4261TO+iIaaYxjKkpVGzZJvWGimp9OmA7XWMZeLlXRit5ty/eNznrRk+34aE1fKzzSVUyjA4hLoNPZJf3G7/M5fzxt8tf35K4d4zqv2Kwj464uxYohkDQuaZ5GYphGH7PdP9L5Z3rTyaJzu5yXlpP+QAgd0+zfO+HXvMdvZ1tiVRtGUBlCXIkt5S4NYpmN11c5fLloiZhqC+nQ+Vjgr3pio6BCXZ8yOmuXJM2XROSNQSRd7MpVLXVgJ+cJtHmPIGD2UyRPJeXxuer4poxlXSc5rXsQiQcfzZw5y/2t0Orj0tb34gwv6zyhHHEl4rfT2A5d9utHZ7/XldfF/fUX2IxfrMOOwlioXEdbrMfTj3SiTotA93jjwliBZel0Gk8j/KKtylLdAAnGmzu5g8fUvDKCuUJbsB53IVGJE8JomwoLXRbXgFUTj7Gv+TFBIWzi4VOXbRATZyV/+Eyws09M1DqWxJchkm5YqGmuMuhtAdbq6OIISYiNX9aBWTMi1j1WnPwOo4fCiNILqBqsY
*/