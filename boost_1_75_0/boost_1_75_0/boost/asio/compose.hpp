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
V65pBvz0cvkge3mCJuXAx1SMzMmcXEa8UX8AR5X/7aH74Cw5j2XvfFX1MZqq3EWzrOhixMNfaTYm60pLg/FYFMHRQjuep1bdqMhrto6iFpDMe2DaaEAYOVe33B1nCbqHxuMZ+RgeHI+tQ97hievwE4Pc0N34uRM5LU3+DzzGWK0EdEXKX93mHoqnm67H03Q5/dXVqG+o8dGfqR9L6F71YwHdpX5k0nr1I4OK6kc6fVj94Oj9+KHuGmoX8GFqrukbBLi3Gs9UpAcp9fNJroPY98llYdRCBhZnaDoU+u7tGILcQj+2q6+jK9UmOhlbLKLj8R+giylbDqqNuEiuc6SRG6EFVBFL9wPHt3g1vfUOtQFsbCZ8F9HDV0XrB1E78s5VTK3ioG+oH076n/BBcu2lTBHzj/aoIsYCovN+VMTIakHgS99F1vbx5xHPH7SxALPc25H7VFfmOJDZARaMDaZMtDxrspgbmVfBnW+qGLCQzHOgR9Z1TvjbFv+u6uTZtE5dfqBflTplig6WiA8L49PuRF+nohLllMLq0/irEGveZFhD5i0AON7Z+32TJTR93XFLoqVydaURY27Sv7+BAHdNxolTPmZc+JlgfETDMdpQpbJKGGdj/2SVMr0yeYQy4c39PowoRgdR8l/oJKbtpCXZzSKozWqJvlqz2YSym9uolT0OZeXtm/Rq3JiSP6GLmRqvJTFvHhTYJt6m3Nm8
*/