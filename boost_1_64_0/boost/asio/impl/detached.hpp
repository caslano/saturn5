//
// impl/detached.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_DETACHED_HPP
#define BOOST_ASIO_IMPL_DETACHED_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/async_result.hpp>
#include <boost/asio/detail/variadic_templates.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

  // Class to adapt a detached_t as a completion handler.
  class detached_handler
  {
  public:
    typedef void result_type;

    detached_handler(detached_t)
    {
    }

#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

    template <typename... Args>
    void operator()(Args...)
    {
    }

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

    void operator()()
    {
    }

#define BOOST_ASIO_PRIVATE_DETACHED_DEF(n) \
    template <BOOST_ASIO_VARIADIC_TPARAMS(n)> \
    void operator()(BOOST_ASIO_VARIADIC_TARGS(n)) \
    { \
    } \
    /**/
    BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_DETACHED_DEF)
#undef BOOST_ASIO_PRIVATE_DETACHED_DEF

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)
  };

} // namespace detail

#if !defined(GENERATING_DOCUMENTATION)

template <typename Signature>
struct async_result<detached_t, Signature>
{
  typedef boost::asio::detail::detached_handler completion_handler_type;

  typedef void return_type;

  explicit async_result(completion_handler_type&)
  {
  }

  void get()
  {
  }

#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

  template <typename Initiation, typename RawCompletionToken, typename... Args>
  static return_type initiate(
      BOOST_ASIO_MOVE_ARG(Initiation) initiation,
      BOOST_ASIO_MOVE_ARG(RawCompletionToken),
      BOOST_ASIO_MOVE_ARG(Args)... args)
  {
    BOOST_ASIO_MOVE_CAST(Initiation)(initiation)(
        detail::detached_handler(detached_t()),
        BOOST_ASIO_MOVE_CAST(Args)(args)...);
  }

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

  template <typename Initiation, typename RawCompletionToken>
  static return_type initiate(
      BOOST_ASIO_MOVE_ARG(Initiation) initiation,
      BOOST_ASIO_MOVE_ARG(RawCompletionToken))
  {
    BOOST_ASIO_MOVE_CAST(Initiation)(initiation)(
        detail::detached_handler(detached_t()));
  }

#define BOOST_ASIO_PRIVATE_INITIATE_DEF(n) \
  template <typename Initiation, typename RawCompletionToken, \
      BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  static return_type initiate( \
      BOOST_ASIO_MOVE_ARG(Initiation) initiation, \
      BOOST_ASIO_MOVE_ARG(RawCompletionToken), \
      BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) \
  { \
    BOOST_ASIO_MOVE_CAST(Initiation)(initiation)( \
        detail::detached_handler(detached_t()), \
        BOOST_ASIO_VARIADIC_MOVE_ARGS(n)); \
  } \
  /**/
  BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_INITIATE_DEF)
#undef BOOST_ASIO_PRIVATE_INITIATE_DEF

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)
};

#endif // !defined(GENERATING_DOCUMENTATION)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_DETACHED_HPP

/* detached.hpp
+vbjhZl06qimJYujCr2wFN0UtLccwY3oXIdyjc84XTRerWgE7aE1txVh9I2NVFZ20HgnoJ8RlCcI6DyV7k98gwxHqRPKx6sOgHnr43RmTjJoGQrVUyJhys4fCyUSOBrXwowy0Cy956oW6ZKjxAjS8sIlq++bu2a/j53HanVydR22wshtRxP0FFuCFPuK2UzGFUNumcHZDM6nl7+ijF8+0M5IrT25UrqLQynTvbev+NdV5yoD9eDQ03EhmqBh4lkG2eMbZZd4wZTOlrAZBC9Zj7pn9J8Sp6+BlmJWS5NG9OImmMgi8QwztGlQ4W+fZ1PJAO3q9zUiXZALrAXkpdkDJcbqFGDBiAWOqUiJ6yLGkxR19UavokInCJMOPNuGMs27eJM6RZwHM+vhE5quXMHHjg3O96XIInoDMsfBLCao6WUbhVkZvwArnN66uVNzkMgQ+oQkBiA50DQUmkr2weswi1w6yhKvAzyff2hez9XO0G2iS68UR7efwUWsgZcSpBOk0J01nsAiMko0uIuaHAbVbzrxgtkwd8BUWpUxJTf1Bd36Zw61iR0zXam7Ng==
*/