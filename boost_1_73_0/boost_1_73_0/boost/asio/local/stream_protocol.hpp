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
eHktY2VydC5kVVQFAAG2SCRgLY3BCsIwEETv+xX7AwkiiBBEKF568CCkN/EQk20JxCQkW2z/3qg9zQxvmLmmOCnMJS2rsFQYutLy6WvvKpta3+5xhp5CVqiJ0QZPsUnjfvTWMOGYyn8AOufIKTzKw17u4NLglMq6zSOHCkII0OZFaCqK3yE+Z8a5kkMfsR+Gm97qNkWmhSV8AFBLAwQKAAAACAAtZ0pSuqdBQX0AAACcAAAALQAJAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL3Byb3h5LWNpcGhlcnMuZFVUBQABtkgkYDWNQQrCMBBF93OKf4EEEUQIIhQ3XXRRSC8Qm7EGahOSKbS3VzFu/+O938VlMkg5brsaQ3pyLtTkz3SZQ5ErtTwnA2s7VAqJWAvjEfNPo8Z79gZnfTrqA92c8BTzXqOQuZBSiqx7MVyB+t/gvsq35BEWtMPQ22qMcRHeRNMbUEsDBAoAAAAIAC1nSlKtzqJnfgAAAJgAAAAtAAkAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvcHJveHktY3JsZmlsZS5kVVQFAAG2SCRgNY1BCoMwEEX3c4p/gYRSKIVQCuLGhQtpvEBqRgmkRpIR9PZtqd09Prz/2jRP
*/