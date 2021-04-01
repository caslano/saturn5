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
RY7U5wnXDjjxb1/wI6x1VxLjAdL8vBF3Rpo6E58ZUgf4Zem6wM1cCImnRstySThjLdvEz0IaE7/IeaAs+CO9qeO/5Th99owqZqPvWPNJ0OkIT6cGuHo7W0HatgOUAxy2hhrrKl6wDB+Fuf0fg5N+YInhDS/J4+T6Wbog4iTzRi9MnCmV9wwqkTRNWbYL3bKvT6bReNU2EflPY8+WbhG0yOr8z0aNjm9JCC50xH9OGBP5y6lj3W5BxWq14Ajn4RMON98GNIubSTfa6mE0bIjZrzLE9734fhKdFuYVv8/vZr+tOvbZlavVPIKP8uIjNrkAFQEIR6LNWmmF9uNnERojZUAVIE6szqSlB4ZSt2Ha2mm/rYwmULI8weLUqlp3HE7x6BHxYC7v027AiNAJBwgotBWMbT+13xdwyqGXpd4QRzebrtwIWH0qPEoMjwkqok48jLFGfgpZ4lQOfj2yH+/hpdi3KfAM2eHI4Cury7eXqm+/V2/I0PsRiJhpFBABw2V6z9obaSzKJR3hidW00BmTnlPUOjK9pRSwwzB3E9yfWxTG0CQTwnP+kqHDBA==
*/