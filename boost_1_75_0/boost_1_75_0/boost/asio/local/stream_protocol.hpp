//
// local/stream_protocol.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_LOCAL_STREAM_PROTOCOL_HPP
#define BOOST_ASIO_LOCAL_STREAM_PROTOCOL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_LOCAL_SOCKETS) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/basic_socket_acceptor.hpp>
#include <boost/asio/basic_socket_iostream.hpp>
#include <boost/asio/basic_stream_socket.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/local/basic_endpoint.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace local {

/// Encapsulates the flags needed for stream-oriented UNIX sockets.
/**
 * The boost::asio::local::stream_protocol class contains flags necessary for
 * stream-oriented UNIX domain sockets.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Safe.
 *
 * @par Concepts:
 * Protocol.
 */
class stream_protocol
{
public:
  /// Obtain an identifier for the type of the protocol.
  int type() const BOOST_ASIO_NOEXCEPT
  {
    return SOCK_STREAM;
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
  typedef basic_endpoint<stream_protocol> endpoint;

  /// The UNIX domain socket type.
  typedef basic_stream_socket<stream_protocol> socket;

  /// The UNIX domain acceptor type.
  typedef basic_socket_acceptor<stream_protocol> acceptor;

#if !defined(BOOST_ASIO_NO_IOSTREAM)
  /// The UNIX domain iostream type.
  typedef basic_socket_iostream<stream_protocol> iostream;
#endif // !defined(BOOST_ASIO_NO_IOSTREAM)
};

} // namespace local
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_LOCAL_SOCKETS)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_LOCAL_STREAM_PROTOCOL_HPP

/* stream_protocol.hpp
CKRXRqRXRnnnzydp+JMVN7ry+yoaelfUKqHswFaf4/y+AFyKqLjU1ed4DDDdnCynvV+/BPOLP4vMEORnzkUqUySbtTI8Uc4UPcVX4r0LPXu9ktwcyLleabcHMWw6MDYBp6fmR39uiakU422CayaoEfOAZtEoN/D9Cpq1Y5hLEvmSNZ/0vqLkDENZGphgrq1viWxBrATiyVnfiG6BZ7laNYxBlZsVem++gfvRw+pPBa278AOP5M1Ab5Qy72x5CmjVm6Xh9dExieaQn8li4bVwpZJv0M/jltczbCpUeIJ+pPnx+lYrW8LHxZSUx0EpmAe3kKJ5XCtUitwRs4VwBVUuZPV03fcwBPzVR7P3Fx/NAIuPhrf6aP72s48m5bKP5offfDQXruARPvqRg3xyDw+FwtPTCz6lUuntXTqFuQo4EJg6Cj4CdBHgbcBbZ6EvMSD89JOPpuqnppcZ0P7TT04vM+AzcSg1RGY6Xg9XYpWyTj9X2SwKSmizKHhZ5alJGE+IE+QaJx5f4Y3lZ+PqYqz5ij995lddkiqn64u+O/D9yT34XmbfKr2q5LReWXJWXRwiJ2uMDvdIOa4zBoK6LvDho3y5PowlALwA5X5/lD0lADUsytPiXEUWI/E2hNr4JK5fnik1yGDm2fdC9qhAu89y1eODYB5kMxxhGA3DH+RP8sfM+++9buePQR9lXuMLNj1EuGWKb8DQ0ukq81Pg
*/