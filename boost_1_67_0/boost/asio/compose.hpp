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
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
*/