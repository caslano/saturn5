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
YSXtavMWGnOkfzSVPBZWg7O8h7eFNEIzH0mvjyTmvif18HKTxjPcCZ6fnt5a+Gaqjl9fecXfh9ZSx0O4AtJ1dd2uKg/Ol0Noi1KfzkGeipI+4IgK7Vj/RhiaF76CQJ4H1mblPo5OZfuoS4Le2/JRC98krIi+REruf2OFdjON/Blh5egBmsq53AmOa1EQ8YpBMgyZokfpomVkUIsH5YA1sRf/AFBLAwQKAAAACAAtZ0pSkaU1NRECAADeAwAAKQAJAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL2xpc3Qtb25seS5kVVQFAAG2SCRgfVJLb9swDL7rV/DWDqiDAd0pOw17YAWCLmgy7KzYdExEEj2RTpb9+lHKo7l0t0T8zO/FBaftHAKJNpzC0a0GzmoPbplZueUgc/i2XsLyx/LRfccwzmFhYChgiNyh+9R12M3hw+y9++wVt5yPc+h1hJHHR9c0jbu3Be/crwFTJaK0BZ/q1o4ytmpfPIAOJCAH0naAnnOLAh6Sj1h1wZ7wMIN1AZE4lBFb8sEGk2A/BaDeNmD5l+HgkwooQ/TtQAmb0WfBOm85KZYp92cN7qoBhFJ7giXO0YdXeZUeOkZJd1pITJuoT53PHQTmHXB2fflIZ1CNGsYmtMNq
*/