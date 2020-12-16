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
/3K4BG6E58Cd8Fz4MKyAT8BKjU+9pd/Z4a0an7aS74HfedofrdTy8m04SuJLfsBL4Cx4KTwNXgaL4HdgCayz74vaz4EXwOXwu/A76r8OXgivgGvhNarvR/AyU+71Oyssj1Luf6LjYTfDNrAejoG3wTPhBrgAboSL4O2wROzanmG2qn6/tm/8T1+rP4fc7hjlDsYol747NrncRuR4B5UzSL3ONm2fL+ebepxf+t99bmnkmaWxnVU6B1PShLNKQ+eUHp0zSr+p80lHci/nYlZj6jGPY97BJJ+SYOVg8jElmLWYzZhnMQcx7WdwFiumAFODuR6zA7MPY82knGCmYEow6zAbME9hDmDSCxKskZi5mNWYuzC7MYcwmaeSb5gizHrMdsxezEFM2qwEqz8mH1OBWYfZgHkYsx9zBNN7Nv6YGsx6zHbMHsxhTOacr3e+6r/l/D/mohyN8/+yOP/vIjrsXQzSxlt8u2b6R6H9Kb+mWs4GPLM37xPfd/itIEYshbX0bMAxjrMBi3w61q7vtsdZ+PEQmBc4G/CEWbMKKyoXlvCFXKfDVYfO4XgUDY+JaXyNkn67pk3y+jbb9G+n0b/Nen87/Zl8K/7woQcm9ChM/McX+8a+1/nVlDKvb7le31S/+W/m+kyo94B7I32r+5lwoj4DToJdRYZmGk6Bx8Cp8Dg4DV4PHz6TuobR9tu03Xsx06K0yXO03e2v7SxtbERbWqJt5SEM7aK2iaa9M+1cprZnznbssG3O/Hp1tvnX/Gv+Nf+af82/5l/zr/nX/Gv+Nf++yi8Bs+ybe/+v4YybkkWKozEGYL/HD3C8x1+vr1LTfWhR3mivbbtV3uPnzJ1TOGWSnunG9qclpSsDc9yZCIh/ySLHHHcN08XK0vVPFWIf7OvIv1MxhzCOveHLSytKgvPfCatr5PV8lsViH+HrYvEOiPkbxg5bJtddXruwwqyR0bCdJOzp2MvFnst1E7huAtdNkLBzZR1P2cLqMj3r1IQ9UfyPEf/ipVXu9W7IuNe7pSB7lwyOrjBrxd8WmQf4hjFN3TiTStyq0T3asffQMvGvJMwL4v8Up8a0cfiXi7+t/jnxf8Y6wxpv1ptNvi10XmLpCJFnjn9ozfsNEoYCicwvMaG4nmvOg/iHyFzGt+glsi5tB77vxzE/i8SmJZRwrGpaPN/tIva8zlDZtHi+lQX2Fbo1KPPjTm6ZXGSetvW1rrtYZfBxy8xBJiegZ1tQZrPq8avMamQGB9Zkj2G1nInTT8PkNiA3xJZrsaZ3WmJrIzezrVvu2aC+hLrfpLVM89R3KHTdtmmJKRFyQfvdnWLbuyEPUmdYk0GdiTgPT+qCWR9eJnJSxs1aOsoublJ2zd7/x4gb5VXXYf1J7quEd+2pla+b8/wAz47K65A5eJujjsuKI8+6rbLdzZlEbTbI2kbdY8v+QI6d/5zlHD/yk7ohsqPNOSH3iH04ZRZ//rpa7I9YXXE7FTm/LWfcHzbujjpi1md23qDn9GmdWiX299WfFkTsflMPnPsKbBC/WlqsHrqXWvCaH1gZuE5nVLO1OcuBNYaWZc4O2ixyt6hdw6HFLts3JlD+k7T8tMqNKDtBmbVJWueS69Y46ppc8+IRkWuIiuUa7cyaw4WS5+mBcqs670rSepdWd2tafBsrou6p3G7khsre9muKzdlnGW6ZQ0FdbdYMMHrC9kJYmB7FxLCXWGSdcO9H+Lhu8jVP92GZjdlsr5e73VFmZSPWRas8+iW9p+jdGGjj5VQpjOan6srwWpOl/lOxS9nhb1nlJf4FJny+8bfC1tSPl+u2crTVFWWuPVjFv4uUmQLqaEmytofJU6xQe9jovjbO/WGc+dk=
*/