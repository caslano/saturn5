//
// local/connect_pair.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_LOCAL_CONNECT_PAIR_HPP
#define BOOST_ASIO_LOCAL_CONNECT_PAIR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_LOCAL_SOCKETS) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/basic_socket.hpp>
#include <boost/asio/detail/socket_ops.hpp>
#include <boost/asio/detail/throw_error.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/local/basic_endpoint.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace local {

/// Create a pair of connected sockets.
template <typename Protocol, typename Executor1, typename Executor2>
void connect_pair(basic_socket<Protocol, Executor1>& socket1,
    basic_socket<Protocol, Executor2>& socket2);

/// Create a pair of connected sockets.
template <typename Protocol, typename Executor1, typename Executor2>
BOOST_ASIO_SYNC_OP_VOID connect_pair(basic_socket<Protocol, Executor1>& socket1,
    basic_socket<Protocol, Executor2>& socket2, boost::system::error_code& ec);

template <typename Protocol, typename Executor1, typename Executor2>
inline void connect_pair(basic_socket<Protocol, Executor1>& socket1,
    basic_socket<Protocol, Executor2>& socket2)
{
  boost::system::error_code ec;
  connect_pair(socket1, socket2, ec);
  boost::asio::detail::throw_error(ec, "connect_pair");
}

template <typename Protocol, typename Executor1, typename Executor2>
inline BOOST_ASIO_SYNC_OP_VOID connect_pair(
    basic_socket<Protocol, Executor1>& socket1,
    basic_socket<Protocol, Executor2>& socket2, boost::system::error_code& ec)
{
  // Check that this function is only being used with a UNIX domain socket.
  boost::asio::local::basic_endpoint<Protocol>* tmp
    = static_cast<typename Protocol::endpoint*>(0);
  (void)tmp;

  Protocol protocol;
  boost::asio::detail::socket_type sv[2];
  if (boost::asio::detail::socket_ops::socketpair(protocol.family(),
        protocol.type(), protocol.protocol(), sv, ec)
      == boost::asio::detail::socket_error_retval)
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);

  socket1.assign(protocol, sv[0], ec);
  if (ec)
  {
    boost::system::error_code temp_ec;
    boost::asio::detail::socket_ops::state_type state[2] = { 0, 0 };
    boost::asio::detail::socket_ops::close(sv[0], state[0], true, temp_ec);
    boost::asio::detail::socket_ops::close(sv[1], state[1], true, temp_ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  socket2.assign(protocol, sv[1], ec);
  if (ec)
  {
    boost::system::error_code temp_ec;
    socket1.close(temp_ec);
    boost::asio::detail::socket_ops::state_type state = 0;
    boost::asio::detail::socket_ops::close(sv[1], state, true, temp_ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
}

} // namespace local
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_LOCAL_SOCKETS)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_LOCAL_CONNECT_PAIR_HPP

/* connect_pair.hpp
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
*/