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
7L5dH2qOTa5jD7tkKLaWggbe1iy/guoUae7tacn5cNRbcyA1ovCkkQKu73Mr5Knd/VG4L20tsNc5xJSusUh/o1eYyj8qDgqYE8Qg0EU0rlzlXkq/q/jeexIHJDruUXM1d0LDC8Y/rwL/9iQQdtpy3dqxq7CH6UeXkCYPV0aPMGaKTWXP92lfKQ/GCiGHDFQF0M+/GBxHUu2a+s593xMR7QmZ4DUiXI/q8pI707PGwGMx/KnXXvJFp35gi6JO8BGHt70KxuwfNjsu+CRHFrEUwCdsn9t3NPO9K8TubcVvs5NKDeESk+DkZzZGn42uibzmLDCnkoOEKFCYWwwp8MvZNFwbP6Pk9O0816hO43QHtH51TR3qYOsGeLYI1ijjaOAcGCqA8vI+1Vg38E/XDBhhGwXckUNVdJ4vLfgQ2tG5v+FdDfQpOpM7BXRtNNCNC5zANmDNFtOZShoHJFjP8ZDtzexGCEbXY1grt03HpsxwjYERV31IAk+s4yNgLaXmSgzaPc7OHo6llr1IO1vHSsV6y6CEfcq+b71T9N+D5lAHbuhHv0VsyRnDTZkrFQ==
*/