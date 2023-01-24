//
// local/datagram_protocol.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_LOCAL_DATAGRAM_PROTOCOL_HPP
#define BOOST_ASIO_LOCAL_DATAGRAM_PROTOCOL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_LOCAL_SOCKETS) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/basic_datagram_socket.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/local/basic_endpoint.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace local {

/// Encapsulates the flags needed for datagram-oriented UNIX sockets.
/**
 * The boost::asio::local::datagram_protocol class contains flags necessary for
 * datagram-oriented UNIX domain sockets.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Safe.
 *
 * @par Concepts:
 * Protocol.
 */
class datagram_protocol
{
public:
  /// Obtain an identifier for the type of the protocol.
  int type() const BOOST_ASIO_NOEXCEPT
  {
    return SOCK_DGRAM;
  }

  /// Obtain an identifier for the protocol.
  int protocol() const BOOST_ASIO_NOEXCEPT
  {
    return 0;
  }

  /// Obtain an identifier for the protocol family.
  int family() const BOOST_ASIO_NOEXCEPT
  {
    return AF_UNIX;
  }

  /// The type of a UNIX domain endpoint.
  typedef basic_endpoint<datagram_protocol> endpoint;

  /// The UNIX domain socket type.
  typedef basic_datagram_socket<datagram_protocol> socket;
};

} // namespace local
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_LOCAL_SOCKETS)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_LOCAL_DATAGRAM_PROTOCOL_HPP

/* datagram_protocol.hpp
Pea2HcY/pPvRh4GW1sL45zc6/oEK6y27TX8swyRz0r2035EOQQht52gzdRmaNNP9bbKKw1+kmKkxzVaiHHeJNVcNEOu0nQFv8xVBEEjn5wxZnQwquJ9r0C68h2sIWQTaMcUTB6BaTxyHGy5iEXyO4FDUv6nH5hrwwfOGgdaOlIl+kWxPysTPCRM78rOV1nafEybK+e8oB48gB2PNyxdTDoIMnZ1dbb5/BuEgfxyk+QF8bQVE+q1fWxXpnVchCHgbXm0Kjga26wcWn2QfSDCzv7bctwMvSTrDVZG1yNGTd8hRpKcFGerr6dot1Qrd0sho86z+hNd7pTrjII0Xaw7q36QzvqPJoB64htEFD3ANY7AKxi7yA6aTKmCwCmBGEERc/p5kRhBvjjGnegoN+CzOKc0xovMoad5nH3C05ljzMdHB+omt+Z4Ec4RNaM2B5VpLooK88S7pAe4DDpOfypI5Ktw8gB0YqZ9gSo62jhHbfcvRzkXqfU0zYAAgtncvYKSJqunIObI7be57PbBrDqU67oVfWhWIzb+TID6qltYtjD3ayoLWJx3ueri0lFcCmrcUw8W9ZE62QTIn+5NqY6XeIfQ1N1BxDJp+256t4Y8nF3/Nehku4VSKljYAPKDEmy63WuJPfsMTkwFNcxCsVF+gGNT0gsuimi77jSCgQztJQ3nksvuGkvSbpKE486+VZkOGb1/D6C1SZXJqJnjt
*/