//
// compose.hpp
// ~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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