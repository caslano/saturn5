//
// compose.hpp
// ~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_COMPOSE_HPP
#define BOOST_ASIO_COMPOSE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/async_result.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES) \
  || defined(GENERATING_DOCUMENTATION)

/// Launch an asynchronous operation with a stateful implementation.
/**
 * The async_compose function simplifies the implementation of composed
 * asynchronous operations automatically wrapping a stateful function object
 * with a conforming intermediate completion handler.
 *
 * @param implementation A function object that contains the implementation of
 * the composed asynchronous operation. The first argument to the function
 * object is a non-const reference to the enclosing intermediate completion
 * handler. The remaining arguments are any arguments that originate from the
 * completion handlers of any asynchronous operations performed by the
 * implementation.

 * @param token The completion token.
 *
 * @param io_objects_or_executors Zero or more I/O objects or I/O executors for
 * which outstanding work must be maintained.
 *
 * @par Example:
 *
 * @code struct async_echo_implementation
 * {
 *   tcp::socket& socket_;
 *   boost::asio::mutable_buffer buffer_;
 *   enum { starting, reading, writing } state_;
 *
 *   template <typename Self>
 *   void operator()(Self& self,
 *       boost::system::error_code error = {},
 *       std::size_t n = 0)
 *   {
 *     switch (state_)
 *     {
 *     case starting:
 *       state_ = reading;
 *       socket_.async_read_some(
 *           buffer_, std::move(self));
 *       break;
 *     case reading:
 *       if (error)
 *       {
 *         self.complete(error, 0);
 *       }
 *       else
 *       {
 *         state_ = writing;
 *         boost::asio::async_write(socket_, buffer_,
 *             boost::asio::transfer_exactly(n),
 *             std::move(self));
 *       }
 *       break;
 *     case writing:
 *       self.complete(error, n);
 *       break;
 *     }
 *   }
 * };
 *
 * template <typename CompletionToken>
 * auto async_echo(tcp::socket& socket,
 *     boost::asio::mutable_buffer buffer,
 *     CompletionToken&& token) ->
 *   typename boost::asio::async_result<
 *     typename std::decay<CompletionToken>::type,
 *       void(boost::system::error_code, std::size_t)>::return_type
 * {
 *   return boost::asio::async_compose<CompletionToken,
 *     void(boost::system::error_code, std::size_t)>(
 *       async_echo_implementation{socket, buffer,
 *         async_echo_implementation::starting},
 *       token, socket);
 * } @endcode
 */
template <typename CompletionToken, typename Signature,
    typename Implementation, typename... IoObjectsOrExecutors>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionToken, Signature)
async_compose(BOOST_ASIO_MOVE_ARG(Implementation) implementation,
    BOOST_ASIO_NONDEDUCED_MOVE_ARG(CompletionToken) token,
    BOOST_ASIO_MOVE_ARG(IoObjectsOrExecutors)... io_objects_or_executors);

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)
      //   || defined(GENERATING_DOCUMENTATION)

template <typename CompletionToken, typename Signature, typename Implementation>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionToken, Signature)
async_compose(BOOST_ASIO_MOVE_ARG(Implementation) implementation,
    BOOST_ASIO_NONDEDUCED_MOVE_ARG(CompletionToken) token);

#define BOOST_ASIO_PRIVATE_ASYNC_COMPOSE_DEF(n) \
  template <typename CompletionToken, typename Signature, \
      typename Implementation, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionToken, Signature) \
  async_compose(BOOST_ASIO_MOVE_ARG(Implementation) implementation, \
      BOOST_ASIO_NONDEDUCED_MOVE_ARG(CompletionToken) token, \
      BOOST_ASIO_VARIADIC_MOVE_PARAMS(n));
  /**/
  BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_ASYNC_COMPOSE_DEF)
#undef BOOST_ASIO_PRIVATE_ASYNC_COMPOSE_DEF

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)
       //   || defined(GENERATING_DOCUMENTATION)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/impl/compose.hpp>

#endif // BOOST_ASIO_COMPOSE_HPP

/* compose.hpp
aqFkR8Tkd1KZUr+WOlFqkdRJUidLLZaqlcpwy5aKScWl9pGqllogdazU4VJHSR0jdbTUoVInSNW4dSd1vNRCqSOlDpM6RGq+VJXUwVIHSe0vta9UpdR+UgdIHSg1T2qcVKnUBlIjpQZLbSi1kdQoqXypPKnNpAqkhkiNl9pcagup1aQ2lhotVSG1jlS51HSpXaT2kNpdakupraQKpVaXWkNqa6ltpMqkJkhNlJokta3UGKmhUptIbSo1VqpYarbULKndpOZKrSu1nlRSajup7aXWlFpLqkhqB6kdpXaSmiw1RWqq1M5Sc6QGSc2QynHHY6lsqYTUNKm13fFGarhUrtRAqRKp9aWGSY2Q2lVqptuHpH4htafU3lJ7Sf3SPT83xkp/6JY6Reoi91zdUO3GPHecd8cJd24m7S+kjg9ku0ld4I6Xwv2k9pVaJvcnSZ3mSe7Gd3ee6vqI/O5uqQPldzXu3Eo4Q6rajd3y+8OFRwtvEPdGqT9IfSTVJfWxVKcb26Tek3pfaoXUB1Ifuu0hfztP6k9uf3f/GqXUIVyjVHOd4o7Nd0TXIpzz2/Pz8Jzei4fXAoOlfs158qledN57FOe+a3N+OJ1jzG5Su3KOO2PV4w3nu9HxZRrngX3H/uJ+zgd373OsmtLP+a3sV3Kd7Y5J0fHoXq65OReRY1d43Opxr0NKjisydyC/73MMOT283uZYIuW54wnX2OYYso0eRziGrG+OIztyLLlT6ki3bf3wWHSY1EI/uj6Prq/D48NJXngexvmSjNnhWB1+XxDXtlzXSh9lrAtDGe/6HevkmCPH5rDvnue5vhz2ycWMgad5rm9G18S5XtinP3H7iCfjQp/runO86HrwbK57fhGE5wi7e+Hxf7fw2CvH3ei4NdeL9qVdvfBajevtfq+1H5FaICX76ipzZrX9z5vJdUD6ubNT+p8/k2uF/ufQTu9/Hk2uJVadS6tZ5Zr/b8+tHRmkm1/7350X+G/N+T3o23k/5iM4Di8MmPczcxLHxaL5QT8WzU0MYn4impfofx7ihODfM3+o8xjl3j83l9E7L/UPzmUsYv7zCeYttzBzlzrHMdn/2/McNbFwnqPE0zmNVeczjnXbzg+Po/u7a59+5zDSz13YudP+5zL6n7s40f/75y76m7fY5p+Yr+idq/g75iTCuQjmIP4/9/B3zz38q/MO0VzDPzbH8P/5hX/P/MKKfuYR7HshOp9wgCfljhtB9L7EPV54/XSa1Eo3FsfsHMLf/75JNM8gvlvnfeYZAteX9LsG+7ynUhV+5xnfsRfOQezJtd4s3m+J5iCYY2Ce4ATed/nU9XsvmjO4kXkDN5d5jPDQPu+/VOt7MLzvUq/vxfAezPm8J7PlvzDf8I/OMfQ7t/B3zCscE/Q3l/DPvU90YODmhaLvCrRzEcO8VeYjeG/of39O4gSpw/p5D+sg7++ffzBzDtFcw//nFf4n5hWiuYTovcmFUptF3yXJd0DqdzdG37k4xVt1/iHPC+cf7FzDPK//uYaDeX/z5lg4x+B56ecZnv0PzDWc6IU/93h6vRy9330n1+NunLzOrU/mkhfxvuvxnOt4sfD53OXGN7fM6Jq097z/THfs98J1cBDn9IM9XVfhGDyUOZdD2Pf31jGNudN9gnD97cs63J/XcoDUgVLzg2jcO5i56AVSh0odJnW4VLXUEVJHSi2UOioIjwX7Sx3Ae31u3dzGe4XHSB0rVSN1XBBuyxOkFjFu1vvRdfFuXnStvLvUHtF1t8x5hHMYZ3OdHUhd7vZ1L7we/5Tr9fP9Va/LL2AOXOcuA8aSDDfmsP1/zZxILfPEi5kDO5X3us9i7K3kGPlJLJxTymJfyWY=
*/