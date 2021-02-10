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
AAAALAAJAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL3Byb3h5LWNhcGF0aC5kVVQFAAG2SCRgRY5BCoMwFET3OcVcIFIKpSClIG666KKgF/g1XxuwSfj5Fr19BS1dDsy8N/cYhhJJ4rzYjhLpy9x4TCXqCs4LdxplgUZ8WHy/IDELaCAfsqKPsk1NJSvlsg6upnKOXYlzcToWB9MwWxpz/Ds6Ft0CdmFNysOq2TvQMRtrrWnozaAMuz/Dc1JMmR18wK1tH82PE4PyrIX5AlBLAwQKAAAACAAtZ0pSXV6ulIQAAACrAAAALwAJAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL3Byb3h5LWNlcnQtdHlwZS5kVVQFAAG2SCRgTY1NCoMwFIT37xRzgYRSKIVQCuLGRReCXsAmTwnYJCRP0NtXaaHdDfPzzSOGySDluG7KchYlW2Kq8m7eDnmnyjl2Bld9OesTNTwng3r2HATHwI/eDsI4yhhjRtP3bfchUr0nU8zb9wEyF1JKUTe8GEOB+n3iuQiWwg4+/DNgYxBeRdMbUEsDBAoAAAAIAC1nSlKUWkTmiAAAAKMAAAAqAAkAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvcHJv
*/