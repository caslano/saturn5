//
// local/connect_pair.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
99dnTN/maqf2Trfk97ru3/wE5lmumfvbqO1Uo2v7JBwrdCbz5P0dpPR5xbt9MmEGmOe0eWLf2GA91vlKGrav2JdhP13s28PrsnmGmS3+94q93ITv1Wh97m+prJkX6FmfzfPjVSK/xNHmuHWUOb4vJTvq9zRkXxC57mYu10Gxd7ac83ILxC2XeITm5daJ27esEitN5zGF6kZhw++UJzV1vl03qT8Nl+G5UcpwUQNluMyjDDvL7OZTLPndqmM8P8I8bfetz0Uts43u+3CuhFtqjTPrvVWXY7337c81vt47EGZwTOVWZaOW0/KQf0zlsuC52MqlKYcmjCmHDc7ZGxsmX9XInL28MPmVjczZmxYmX9dAv/cecs714HuxO9aDc5+8+7k68Vtu1oPvo+0ry9d+apR7PXh/3EswgX5qfPT14KpjfX6wnypJS+0UsR5cx3Zi7pv+q+uhrBX3mIu40mMuYl30uYjmGT99piW/ch2vKcEk8L6f/XzgfB1qb01g+Z3n+5XKzjbzDy8UewuR7xU80zpUV1W+QO1GXstr9DGFAhPudLW7r/OkfIfhXSDsnIKyRp5BqsLe5zI0L4k3bhJvz/fjbMh1XXvnVz9vxu9c7Wad5rMf00rNb5HZGsjn6nPtseTZc2ZNnzFVRsmX1VZUIOIs+95jWLyfhp/V1qUg8np/tOcPRLkeb+aSh2/jz7091/Huo/L+0Jy/GOIRfD9DH3kj+lx5cSRK3N5E9mCUuHEoVWA2rJaL+6LEkXDmzHu/vIPaIRbXLis2Zc7ImPmvTUjHfY50+HVckOvgZq7jOiNo96mR6XseHem7o6SPj6UNpE3D+B3v11XONfzG37R7XzFd7rMg5BquNG2YFZmm9wifGyVN5y2sqOWGeZUpDeP3nuMWlqZTmpAmR5nznOd2CM6N8zpPwOucB6/zIr758xOiny9x9M6F6DTZdl91/h0vX93ttz/60zuff9B69YPXep3b4HWehtf5G9/8uflNPYck+vkhXudjeJ1b4n0+yV/1PH1+MgZc4JP90uWbVTZ/W5i5jr8nO/6e4vh7VuhveU5Ktt2wHq9/L+Lvifq3XbbP0r+7ko4z9O8X9bwLmlzdL1T2lRS/FnCKxpO2RM4hyIcT4Qx4kto3qX2b2vepXfWyN6S33lGqd7TqHQtPUvsmtW9T+z61o9exDx/XVL3O/ev/bgXOZfgCToVfQolPcI81eFOU+DyKXDv4GMxUe2e1z4FPwkK1X6129PIcrnttwZaqNwHmqN4LibfNi2ACXAuT4fcc+ZSt4W+OEq83NV5vwUy1d1b7HPgHWKj2H6r9U7gLc1D1VvgCejvw93bVu5Dr94YlcDQshcfDJXARLIMrYTm8EFbAS+BSeBVcBu+GlXqfquDrsBr+DdbAL+F5sDXXPh92gSthD7gKDoPfghPhajgTXgBnwe9q/lRZug8KrNf8SYUlmo6het5JLhwCh8MRcAQ8GY6EBXAULIWj4cVwDLwEHguvhuPgtWLX8zmC+4DAW/S6zvM5DvkC5ewzmAH/CnPh53AETEHPWD0vZRJMxr4ItoSl6n8OTIBVaq/Vc1Xq4D/gxfBLeCm08L8C+OBVKv9Ddf+xut8o7sHzInR/DjhN4+88L2KynkczBfaDJ8Lj4FQ4We3mXBfVM0jLkeO8FTk/oxucBQfa7nAoPA1OhafDfHgGPAfOhSvgWbADuhZAvQ57Gnhf51i9zni9znF6nYl6nTy9zvF6nUl6nRP1OtP0OulmbTjjanqd7vZ9gPYvHrl+MAGOgolwLEyCx8IWcAJsqfc1BZ4JU2EhTINLYCtYAdvC5TBD72M7rT/t4XWwA7wedoI3wSx4P+wMd8I=
*/