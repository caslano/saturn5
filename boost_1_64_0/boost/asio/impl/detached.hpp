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
Oyg8Qs4AZ3ZrjxbPkD0BGC2EjF9AcdtxHlqcsJc+T3E+YdNqpLw/kNqDMlu6X3NGWikpMLUvrCc8t+ySzpC+LQDGQxQ3RRY0Bt3fjd7VgvDzEb+a8GfLfmE/qCiuqS2ch/MIqyprQMf9VyK6zzis8uilvapqyEX2WJaN8FhPRAym+R6nx7SuZtxhY4Wej6sfyf0RuC5FQBT5idM+Te+7+JRv74g/Ka20CtYmlrF8i7GgQIwFXJeMJ8YHlkU35QftxLKYy+EKDucbwiUcruLw1Ybw3zjMsizumE2bJNHfanTyZIIsy7s0skyLTuzy1OLkyHI0Swi5voPornRMxpqC5ZrzStXIaXVFWWWAZi7S76L0SscMR5hJf/vYHvoo4VzuGO9wSH6BM3c+ZKUEF/4WS4zrB9xCuFMdI2DhSQy+c17VImVjnoaYypnK3JxlawPhl4LncMQxvupDqelPhwlvouyRcoQN9RjFuR0ZuBmxTO4jbcL9xT4+s+9FShsKjtvoxxu2i/2T0rs40h2yts+Ltb1rt5L+u/yenMJxkHuiOQ1LwXvgIWjnq6haWEgl5I/TfWxz3UX4Ccg/kuNUnrMdyY5I476KmIfX0btnSSkUVt/rdUQpN8fhnq/OslcqhJbeLidTHxwAnbh9grpGycDy2eOMlMzjnp9xj00Q41Kdx+kz6nOB9+MEXj9EejrUbdaneSdq0j7gfsxpEzjNWV9IY2IrHhPjEJ8/UX13fZXxvdr8qzX51x/Xv3ulJu36roE0dawcgvih2c3bTymyGId67daPQ3MM4V8M4VnP6sPPctg4bq2cItHfDjDZHvA+wDnA2f6ctq/Pqwj1zdy7hLvEwX2baTPs5vpI1/vinWB6n5B3cd6DGOt8z9O+gegHJ4nmFzlDxCFyrxJXDI+jIRoZnj4LWkP012+ILg2zWJeUwv11GOV9j9wT/WEinvlopccBD0qva+Y25TS3Ud//6R6yl2PlHtbU+/H6oB56m94/TR4jY4zm+c0/Ka9rtP1uAZWdeW5D+frE2NwVYXU9nAld7S1Q18ODPZEtLWzHjJdboO2LFv2Q8SYUBNc88yV92hLxrimYw9q/627Ow3l9f1pUKWmDOO3o5TjDjvrhFJhcYt0Z7tnuQcov9El/GMynbd0l+J/o7hoehuRSdxd3iXtOuMfj9kvqmIyzRMm/tAGwgX/z3j3+qsnxS50XpVD97gZ/2AOiOFHnOh3s5/oeTGkrEI6CRSlTfPt/LcWXQjKGB2wRBXTxp6ir+jVcB5x2rzZtJ9vQOG0np3mi67/X0jRcrtZblKg3bb02avPsra9zz2RNmqE9MjVpde/r04Zo03Yzn5w2ldNwPuxKLc2iIE3L6+dwfmibMMUPPDuwNmhBZ8H+mWvkfjFJ1Ffh58R6rTeHizi80BC+xxBuMIR/MIQn7dGHawzhQ4bwL4Zwxl7r9fjOaXyHNPtSXIrnJhTQ+4Jez9rtfbNuZXw/+VTmUD2xPyCtSWkqI/RyNuOy3mXadloavJBIhK24M+FcQuF8QZMgCd1MNLXFWt08jnDcWhzwQkiCl0GEk0z9ZhXGnFemsh5x9sV+j4UeYbyTU1X/v2zGM6yZGS9+mppfR+DxPMMmz7xpap6xHleUOU817GqGfSPU9zDs5yfaxc9rTI7nutfLyeEi9o8AA60Af8NzFTJbpZcTJrWVE8ZPFLayRyh8UvLQyCtbfVPKND0s/WriANu9SHtIaOnRwgf0KoqLo7Zf3EeVD+JF+P1moN53o87PFMJ0S/sWdWucsVD4Xncvdyo0iNvriUCn0NR7SLnuRO/sHFKO+xNOv5ByW/Ri03KbTzjpJLercXHakkJVzuoOQNA=
*/