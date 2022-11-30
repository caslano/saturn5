//
// impl/detached.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
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
*/